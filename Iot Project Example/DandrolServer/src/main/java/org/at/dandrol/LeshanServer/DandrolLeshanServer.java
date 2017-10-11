package org.at.dandrol.LeshanServer;

import java.io.File;
import java.security.PublicKey;
import java.util.List;

import javax.servlet.http.HttpServletResponse;

import org.at.dandrol.LeshanServer.alarm.AlarmManager;
import org.at.dandrol.LeshanServer.automation.AutomationManager;
import org.at.dandrol.LeshanServer.rules.RuleEngine;
import org.at.dandrol.LeshanServer.rules.model.Condition;
import org.at.dandrol.LeshanServer.rules.model.Rule;
import org.at.dandrol.LeshanServer.servlet.AlarmServlet;
import org.at.dandrol.LeshanServer.servlet.AutomationServlet;
import org.at.dandrol.LeshanServer.servlet.ClientServlet;
import org.at.dandrol.LeshanServer.servlet.EventServlet;
import org.at.dandrol.LeshanServer.servlet.json.LwM2mNodeDeserializer;
import org.at.dandrol.LeshanServer.servlet.json.LwM2mNodeSerializer;
import org.at.dandrol.LeshanServer.servlet.json.RegistrationSerializer;
import org.at.dandrol.LeshanServer.servlet.json.ResponseSerializer;
import org.eclipse.californium.core.network.config.NetworkConfig;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletHolder;
import org.eclipse.jetty.webapp.WebAppContext;
import org.eclipse.leshan.core.model.ObjectLoader;
import org.eclipse.leshan.core.model.ObjectModel;
import org.eclipse.leshan.core.node.LwM2mNode;
import org.eclipse.leshan.core.node.codec.DefaultLwM2mNodeDecoder;
import org.eclipse.leshan.core.node.codec.DefaultLwM2mNodeEncoder;
import org.eclipse.leshan.core.node.codec.LwM2mNodeDecoder;
import org.eclipse.leshan.core.request.ExecuteRequest;
import org.eclipse.leshan.core.request.ObserveRequest;
import org.eclipse.leshan.core.response.ExecuteResponse;
import org.eclipse.leshan.core.response.LwM2mResponse;
import org.eclipse.leshan.core.response.ObserveResponse;
import org.eclipse.leshan.server.californium.LeshanServerBuilder;
import org.eclipse.leshan.server.californium.impl.LeshanServer;
import org.eclipse.leshan.server.model.LwM2mModelProvider;
import org.eclipse.leshan.server.model.StaticModelProvider;
import org.eclipse.leshan.server.registration.Registration;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class DandrolLeshanServer {


	private final static String[] modelPaths = new String[] { "LWM2M_Lock_and_Wipe-V1_0.xml",
			"LWM2M_Cellular_connectivity-v1_0.xml", "LWM2M_APN_connection_profile-v1_0.xml",
			"LWM2M_WLAN_connectivity4-v1_0.xml", "LWM2M_Bearer_selection-v1_0.xml",
			"LWM2M_Portfolio-v1_0.xml", "Communication_Characteristics-V1_0.xml",
			"Non-Access_Stratum_NAS_configuration-V1_0.xml", "3200.xml", "3201.xml", "3202.xml",
			"3203.xml", "3300.xml", "3301.xml", "3302.xml", "3303.xml", "3304.xml", "3305.xml",
			"3306.xml", "3308.xml", "3310.xml", "3311.xml", "3312.xml", "3313.xml", "3314.xml",
			"3315.xml", "3316.xml", "3317.xml", "3318.xml", "3319.xml", "3320.xml", "3321.xml",
			"3322.xml", "3323.xml", "3324.xml", "3325.xml", "3326.xml", "3327.xml", "3328.xml",
			"3329.xml", "3330.xml", "3331.xml", "3332.xml", "3333.xml", "3334.xml", "3335.xml",
			"3336.xml", "3337.xml", "3338.xml", "3339.xml", "3340.xml", "3341.xml", "3342.xml",
			"3343.xml", "3344.xml", "3345.xml", "3346.xml", "3347.xml", "3348.xml", "singlePhasePM.xml",
			"VehicleControlUnit.xml", "Application-Data-Container.xml", "LWM2M_DevCapMgmt-v1_0.xml",
			"LWM2M_Software_Component-v1_0.xml", "LWM2M_Software_Management-v1_0.xml",
			"3-PhasePM.xml", "ActiveCmdhPolicy.xml", "CmdhBackOffParametersSet.xml", "CmdhBuffer.xml",
			"CmdhDefaults.xml", "CmdhDefEcValues.xml", "CmdhEcDefParamValues.xml", "CmdhLimits.xml",
			"CmdhNetworkAccessRules.xml", "CmdhNwAccessRule.xml", "CmdhPolicy.xml" };

	private static final long TIMEOUT = 5000; // ms
	
	private final static String modelsFolderPath = null;
	private static String 	localAddress = null;
	private static int 	localPort = 0;
	private static String 	secureLocalAddress = null;
	private static int 	secureLocalPort = 0;
	private static PublicKey publicKey = null;

	private  static Gson gson;

	private static LeshanServer lwServer;

	private static Server jettyServer;


	private final static AlarmManager alarmManager = new AlarmManager() {

		@Override
		public String sendAlarm(Integer ruleID) {

			System.out.println("Alarm generated");
			return null;
		}
	};

	private final static AutomationManager automationManager = new AutomationManager() {

		@Override
		public String executeAction(Integer requestID)throws RuntimeException, InterruptedException {

			if(gson == null)
				setUpGson();

			System.out.println("executing action " + getRuleByID(requestID).getActionTarget()+ "@" +  getRuleByID(requestID).getActionEndpoint());

			Registration execRegistration = lwServer.getRegistrationService().getByEndpoint(
					getRuleByID(requestID).getActionEndpoint());


			if (execRegistration != null) {
				ExecuteRequest execRequest = new ExecuteRequest(getRuleByID(requestID).getActionTarget());
				ExecuteResponse execResponse = lwServer.send(execRegistration, execRequest, 5000);

				if(execResponse != null){

					String x = gson.toJson(execResponse);
					return  x;
				}
				else{

					return new String ("nullResponse");}
			}
			else{
				System.out.println("6");
				return new String ("nullRegistration");}
		}

	};

	private final static void setUpGson(){
		if( gson == null){
			GsonBuilder gsonBuilder = new GsonBuilder();
			gsonBuilder.registerTypeHierarchyAdapter(Registration.class, new RegistrationSerializer(secureLocalPort));
			gsonBuilder.registerTypeHierarchyAdapter(LwM2mResponse.class, new ResponseSerializer());
			gsonBuilder.registerTypeHierarchyAdapter(LwM2mNode.class, new LwM2mNodeSerializer());
			gsonBuilder.registerTypeHierarchyAdapter(LwM2mNode.class, new LwM2mNodeDeserializer());
			gsonBuilder.setDateFormat("yyyy-MM-dd'T'HH:mm:ssXXX");
			gson = gsonBuilder.create();
		}

	}
	public DandrolLeshanServer() {
		super();


	}

	private static void setParameters(){

		localAddress = "localhost";
		localPort = 5683;
		secureLocalAddress = "localhost";
		secureLocalPort = 60010;
	}

	private static LeshanServer setUpLWM2MServer(){

		// Prepare LWM2M server
		LeshanServerBuilder builder = new LeshanServerBuilder();
		builder.setLocalAddress(localAddress, localPort);
		builder.setLocalSecureAddress(secureLocalAddress, secureLocalPort);
		builder.setEncoder(new DefaultLwM2mNodeEncoder());
		LwM2mNodeDecoder decoder = new DefaultLwM2mNodeDecoder();
		builder.setDecoder(decoder);
		builder.setNetworkConfig(NetworkConfig.getStandard());

		// Define model provider
		List<ObjectModel> models = ObjectLoader.loadDefault();
		models.addAll(ObjectLoader.loadDdfResources("/models/", modelPaths));
		if (modelsFolderPath != null) {
			models.addAll(ObjectLoader.loadObjectsFromDir(new File(modelsFolderPath)));
		}
		LwM2mModelProvider modelProvider = new StaticModelProvider(models);
		builder.setObjectModelProvider(modelProvider);


		// Create and start LWM2M server
		return builder.build();

	}

	private static Server setUpJettyServer(){

		Server server = new Server(8080);
		WebAppContext root = new WebAppContext();
		root.setContextPath("/");
		root.setResourceBase(LeshanServer.class.getClassLoader().getResource("webapp").toExternalForm());
		root.setParentLoaderPriority(true);
		server.setHandler(root);


		AutomationServlet automationServlet = new AutomationServlet(lwServer, automationManager);
		ServletHolder automationServletHolder = new ServletHolder(automationServlet);

		AlarmServlet alarmServlet = new AlarmServlet(lwServer, alarmManager);
		ServletHolder alarmServletHolder = new ServletHolder(alarmServlet);

		ClientServlet clientServlet = new ClientServlet(lwServer, secureLocalPort);
		ServletHolder clientServletHolder = new ServletHolder(clientServlet);

		EventServlet eventServlet = new EventServlet(lwServer, secureLocalPort, automationManager, alarmManager);
		ServletHolder eventServletHolder = new ServletHolder(eventServlet);

		root.addServlet(clientServletHolder, "/api/clients/*");
		root.addServlet(eventServletHolder, "/api/events/*");
		root.addServlet(automationServletHolder, "/api/automations/*");
		root.addServlet(alarmServletHolder, "/api/alarms/*");

		return server;
	}

	private static void observeStored(RuleEngine manager){


		for (Rule rule : manager.getRules()){

			for (Condition cond : rule.getConditions()){
				try{
					Registration registration = lwServer.getRegistrationService().getByEndpoint(cond.getEndpoint());
					if (registration != null) {
						// create & process request

						System.out.println(cond.getTarget());
						System.out.println(cond.getEndpoint());
						ObserveRequest request = new ObserveRequest(cond.getTarget());

						ObserveResponse cResponse = lwServer.send(registration, request, TIMEOUT);
						//processDeviceResponse(req, resp, cResponse);
					} else {
						
						System.out.println("no registered client with id " + cond.getEndpoint());
					}
				} catch (RuntimeException | InterruptedException e) {
					System.out.println(e);
				}
			}
		}
	}

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub

		setParameters();
		
		lwServer = setUpLWM2MServer();

		System.out.println("Server started at:" + lwServer.getNonSecureAddress());
		jettyServer = setUpJettyServer();

		alarmManager.loadStoredAlarms();
		automationManager.loadStoredAutomations();
		
		lwServer.start();
		jettyServer.start();

		Thread.sleep(6000);
		observeStored(alarmManager);
		observeStored(automationManager);


	}

}
