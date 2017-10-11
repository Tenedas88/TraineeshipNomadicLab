/*******************************************************************************
 * Copyright (c) 2013-2015 Sierra Wireless and others.
 * 
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * 
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *    http://www.eclipse.org/org/documents/edl-v10.html.
 * 
 * Contributors:
 *     Sierra Wireless - initial API and implementation
 *******************************************************************************/
package org.at.dandrol.LeshanServer.servlet;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Properties;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import javax.servlet.http.HttpServletRequest;

import org.at.dandrol.LeshanServer.alarm.AlarmManager;
import org.at.dandrol.LeshanServer.automation.AutomationManager;
import org.at.dandrol.LeshanServer.rules.RuleEngine;
import org.at.dandrol.LeshanServer.rules.model.Condition;
import org.at.dandrol.LeshanServer.rules.model.Rule;
import org.at.dandrol.LeshanServer.servlet.json.LwM2mNodeSerializer;
import org.at.dandrol.LeshanServer.servlet.json.RegistrationSerializer;
import org.at.dandrol.LeshanServer.servlet.log.CoapMessage;
import org.at.dandrol.LeshanServer.servlet.log.CoapMessageListener;
import org.at.dandrol.LeshanServer.servlet.log.CoapMessageTracer;
import org.at.dandrol.LeshanServer.servlet.utils.EventSource;
import org.at.dandrol.LeshanServer.servlet.utils.EventSourceServlet;
import org.eclipse.californium.core.network.Endpoint;
import org.eclipse.leshan.core.node.LwM2mNode;
import org.eclipse.leshan.core.observation.Observation;
import org.eclipse.leshan.core.request.ObserveRequest;
import org.eclipse.leshan.core.response.ObserveResponse;
import org.eclipse.leshan.server.LwM2mServer;
import org.eclipse.leshan.server.californium.impl.LeshanServer;
import org.eclipse.leshan.server.observation.ObservationListener;
import org.eclipse.leshan.server.registration.Registration;
import org.eclipse.leshan.server.registration.RegistrationListener;
import org.eclipse.leshan.server.registration.RegistrationUpdate;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class EventServlet extends EventSourceServlet {

	private static final String EVENT_DEREGISTRATION = "DEREGISTRATION";

	private static final String EVENT_UPDATED = "UPDATED";

	private static final String EVENT_REGISTRATION = "REGISTRATION";

	private static final String EVENT_NOTIFICATION = "NOTIFICATION";

	private static final String EVENT_AUTOMATION = "AUTOMATION";

	private static final String EVENT_ALARM = "ALARM";

	private static final String EVENT_COAP_LOG = "COAPLOG";

	private static final String QUERY_PARAM_ENDPOINT = "ep";

	private static final long TIMEOUT = 5000; // ms

	private static final long serialVersionUID = 1L;

	private static final Logger LOG = LoggerFactory.getLogger(EventServlet.class);

	private final Gson gson;

	private final AutomationManager automationManager; 
	private final AlarmManager alarmManager;

	private final LwM2mServer server;

	private final CoapMessageTracer coapMessageTracer;

	private Set<LeshanEventSource> eventSources = Collections
			.newSetFromMap(new ConcurrentHashMap<LeshanEventSource, Boolean>());


	private final RegistrationListener registrationListener = new RegistrationListener() {

		@Override
		public void registered(Registration registration) {
			String jReg = EventServlet.this.gson.toJson(registration);
			String endpoint = registration.getEndpoint();

			//Check if alarm or automation  rules that refers to new registered endpoint exist 
			//and if so observe the targets specified in the rule
			checkAffectedRules(alarmManager, endpoint);
			checkAffectedRules(automationManager, endpoint);

			sendEvent(EVENT_REGISTRATION, jReg, registration.getEndpoint());
		}

		@Override
		public void updated(RegistrationUpdate update, Registration updatedRegistration,
				Registration previousRegistration) {
			String jReg = EventServlet.this.gson.toJson(updatedRegistration);
			sendEvent(EVENT_UPDATED, jReg, updatedRegistration.getEndpoint());
		}

		@Override
		public void unregistered(Registration registration, Collection<Observation> observations, boolean expired) {
			String jReg = EventServlet.this.gson.toJson(registration);
			sendEvent(EVENT_DEREGISTRATION, jReg, registration.getEndpoint());
		}


		private void checkAffectedRules(RuleEngine manager, String endpoint){
			if(manager.thereIsRuleFor(endpoint)){
				for(Rule rule : manager.getRules() ){
					ArrayList<Condition> affectedConditions = rule.getAllConditionsFor(endpoint);
					if(!affectedConditions.isEmpty()){
						for(Condition cond : affectedConditions){
							try {
								observe(cond);
							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
					}
				}
			}
		}



	};

	private final ObservationListener observationListener = new ObservationListener() {

		@Override
		public void cancelled(Observation observation) {
		}

		@Override
		public void onResponse(Observation observation, Registration registration, ObserveResponse response) {

			if (registration != null) {
				String data = new StringBuilder("{\"ep\":\"").append(registration.getEndpoint()).append("\",\"res\":\"")
						.append(observation.getPath().toString()).append("\",\"val\":")
						.append(gson.toJson(response.getContent())).append("}").toString(); 
				sendEvent(EVENT_NOTIFICATION, data, registration.getEndpoint());


				//Extract updated value
				Properties value = gson.fromJson(gson.toJson(response.getContent()), Properties.class);
				double readValue = Double.parseDouble(value.getProperty("value"));

				//---------------------------ALARM CHECK--------------------------------------------------------------

				//Check if any alarm is been triggered
				ArrayList<Integer> affectedAlarms = 
						alarmManager.updateRuleValue(registration.getEndpoint(), observation.getPath().toString(), readValue);

				if(!affectedAlarms.contains(-1)){
					try {
						//Make the manager evaluate the affected alarms
						for (Integer id : affectedAlarms){
							if(alarmManager.evaluate(id)){
								String alarmMessage = new StringBuilder("alarm: ").append(id).append(" triggered!").toString();

								sendEvent(EVENT_ALARM, alarmMessage, alarmManager.getRuleByID(id).toString());
								System.out.println("\t" + alarmMessage);
							}
						}
					}			
					catch (RuntimeException  e) {
						System.out.println(e);
					}
				}
				else{
					System.out.println("Nessuna allarme");
					return;
				}



				//---------------------------AUTOMATION CHECK--------------------------------------------------------------

				//Check if any automation rule is been affected
				ArrayList<Integer> affectedAutomations = 
						automationManager.updateRuleValue(registration.getEndpoint(), observation.getPath().toString(), readValue);
				if(!affectedAutomations.contains(-1)){
					try {
						//Make the manager evaluate the affected requests
						for (Integer id : affectedAutomations){
							if(automationManager.evaluate(id)){
								String execResult = automationManager.executeAction(id);
								//TODO -> inserire notifiche send event

								if("nullResponse".equals(execResult))
									System.out.println("server error");
								else if("nullRegistration".equals(execResult))
									System.out.println("null registration");
								else
								{
									String automationMessage = new StringBuilder("automation request: ").append(id).append(" , actionResult: ").
											append(execResult).toString();
									System.out.println("\t" + automationMessage);
									sendEvent(EVENT_AUTOMATION, automationMessage, automationManager.getRuleByID(id).getActionEndpoint());
								}
							}
						}			
					} catch (RuntimeException | InterruptedException e) {
						System.out.println(e);
					}
				}
				else{
					System.out.println("Nessuna rihiesta di automazione interessata");
					return;
				}
			}
		}

		@Override
		public void onError(Observation observation, Registration registration, Exception error) {
			if (LOG.isWarnEnabled()) {
				LOG.warn(String.format("Unable to handle notification of [%s:%s]", observation.getRegistrationId(),
						observation.getPath()), error);
			}
		}

		@Override
		public void newObservation(Observation observation, Registration registration) {
		}
	};

	public EventServlet(LeshanServer server, int securePort, AutomationManager automationManager, AlarmManager alarmManager) {

		this.automationManager = automationManager;
		this.alarmManager = alarmManager;

		this.server = server;
		server.getRegistrationService().addListener(this.registrationListener);
		server.getObservationService().addListener(this.observationListener);

		// add an interceptor to each endpoint to trace all CoAP messages
		coapMessageTracer = new CoapMessageTracer(server.getRegistrationService());
		for (Endpoint endpoint : server.getCoapServer().getEndpoints()) {
			endpoint.addInterceptor(coapMessageTracer);
		}

		GsonBuilder gsonBuilder = new GsonBuilder();
		gsonBuilder.registerTypeHierarchyAdapter(Registration.class, new RegistrationSerializer(securePort));
		gsonBuilder.registerTypeHierarchyAdapter(LwM2mNode.class, new LwM2mNodeSerializer());
		gsonBuilder.setDateFormat("yyyy-MM-dd'T'HH:mm:ssXXX");
		this.gson = gsonBuilder.create();
	}

	private synchronized void sendEvent(String event, String data, String endpoint) {
		if (LOG.isDebugEnabled()) {
			LOG.debug("Dispatching {} event from endpoint {}", event, endpoint);
		}

		for (LeshanEventSource eventSource : eventSources) {
			if (eventSource.getEndpoint() == null || eventSource.getEndpoint().equals(endpoint)) {
				eventSource.sentEvent(event, data);
			}
		}
	}

	class ClientCoapListener implements CoapMessageListener {

		private final String endpoint;

		ClientCoapListener(String endpoint) {
			this.endpoint = endpoint;
		}

		@Override
		public void trace(CoapMessage message) {
			String coapLog = EventServlet.this.gson.toJson(message);
			sendEvent(EVENT_COAP_LOG, coapLog, endpoint);
		}

	}

	private void cleanCoapListener(String endpoint) {
		// remove the listener if there is no more eventSources for this endpoint
		for (LeshanEventSource eventSource : eventSources) {
			if (eventSource.getEndpoint() == null || eventSource.getEndpoint().equals(endpoint)) {
				return;
			}
		}
		coapMessageTracer.removeListener(endpoint);
	}


	private void observe(Condition cond) throws IOException{
		try{
			Registration registration = server.getRegistrationService().getByEndpoint(cond.getEndpoint());
			if (registration != null) {
				// create & process request

				System.out.println(cond.getTarget());
				System.out.println(cond.getEndpoint());
				ObserveRequest request = new ObserveRequest(cond.getTarget());

				ObserveResponse cResponse = server.send(registration, request, TIMEOUT);
				//processDeviceResponse(req, resp, cResponse);
			} else {
				System.out.println("no registered client with id " + cond.getEndpoint());
			}
		} catch (RuntimeException | InterruptedException e) {
			e.printStackTrace();
		}
	}



	@Override
	protected EventSource newEventSource(HttpServletRequest req) {
		String endpoint = req.getParameter(QUERY_PARAM_ENDPOINT);
		return new LeshanEventSource(endpoint);
	}

	private class LeshanEventSource implements EventSource {

		private String endpoint;
		private Emitter emitter;

		public LeshanEventSource(String endpoint) {
			this.endpoint = endpoint;
		}

		@Override
		public void onOpen(Emitter emitter) throws IOException {
			this.emitter = emitter;
			eventSources.add(this);
			if (endpoint != null) {
				coapMessageTracer.addListener(endpoint, new ClientCoapListener(endpoint));
			}
		}

		@Override
		public void onClose() {
			cleanCoapListener(endpoint);
			eventSources.remove(this);
		}

		public void sentEvent(String event, String data) {
			try {
				emitter.event(event, data);
			} catch (IOException e) {
				onClose();
			}
		}

		public String getEndpoint() {
			return endpoint;
		}
	}
}
