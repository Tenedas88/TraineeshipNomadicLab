package org.at.dandrol.LeshanServer.servlet;

import java.io.IOException;
import java.io.StringReader;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.io.IOUtils;
import org.apache.commons.lang.StringUtils;
import org.at.dandrol.LeshanServer.automation.AutomationManager;
import org.at.dandrol.LeshanServer.rules.model.Condition;
import org.at.dandrol.LeshanServer.rules.model.Rule;
import org.at.dandrol.LeshanServer.servlet.json.RuleSerializer;
import org.eclipse.leshan.core.node.codec.CodecException;
import org.eclipse.leshan.core.request.ObserveRequest;
import org.eclipse.leshan.core.request.exception.InvalidRequestException;
import org.eclipse.leshan.core.request.exception.InvalidResponseException;
import org.eclipse.leshan.core.request.exception.RequestCanceledException;
import org.eclipse.leshan.core.request.exception.RequestRejectedException;
import org.eclipse.leshan.core.response.ObserveResponse;
import org.eclipse.leshan.server.LwM2mServer;
import org.eclipse.leshan.server.registration.Registration;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.eclipsesource.json.Json;
import com.eclipsesource.json.JsonObject;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonSyntaxException;
import com.google.gson.stream.JsonReader;

public class AutomationServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private static final long TIMEOUT = 5000; // ms

	private static final Logger LOG = LoggerFactory.getLogger(ClientServlet.class);
	private final Gson gson;

	private final LwM2mServer server;
	private final AutomationManager automationManager;


	public AutomationServlet(LwM2mServer server, AutomationManager automationManager) {
		super();
		this.server = server;
		this.automationManager = automationManager;

		GsonBuilder gsonBuilder = new GsonBuilder();
//		gsonBuilder.registerTypeHierarchyAdapter(Rule.class, new RuleSerializer());
		
		this.gson = gsonBuilder.create();
 

	}

	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

		
			doAutomation(req, resp);

	}

	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException{

		getAutomation(req, resp);

	}
	
	private void getAutomation(HttpServletRequest req, HttpServletResponse resp){

		System.out.println("[AUTOMATION SERVLET GET - getAutomation]");
		ArrayList<Rule> rules = automationManager.getRules(); 

		String json = this.gson.toJson(rules.toArray(new Rule[] {}));
		
		resp.setContentType("application/json");
		try {			
			resp.getOutputStream().write(json.getBytes(StandardCharsets.UTF_8));
		} catch (IOException e) {
			resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			e.printStackTrace();
		}
		resp.setStatus(HttpServletResponse.SC_OK);


	}

	private void doAutomation(HttpServletRequest req, HttpServletResponse resp) throws IOException{
		System.out.println("[AUTOMATION SERVLET POST - doautomation]");
	
		StringBuilder jsonReq = new StringBuilder();
		while(!req.getInputStream().isFinished())
			jsonReq.append((char)req.getInputStream().read());
		
		String jsonReqToString = jsonReq.toString();
	
		JsonReader reader = new JsonReader(new StringReader(jsonReqToString));
		reader.setLenient(true);
		try{Rule newRule = gson.fromJson(reader, Rule.class);
		
		for(Condition cond : newRule.getConditions()){
			System.out.println(cond.getEndpoint());
			System.out.println(cond.getTarget());
			System.out.println(cond.getOperator());
			System.out.println(cond.getValue());
			System.out.println(cond.getConcatenationOp());
		}
		for (Condition cond : newRule.getConditions()){
			observe(cond,resp);
		}

		
		automationManager.createAutomationRule(newRule.getConditions(), newRule.getActionEndpoint(), newRule.getActionTarget());
		System.out.println("\tautomation rule created with id "+ newRule.getRuleID());
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}

	
	private void observe(Condition cond, HttpServletResponse resp) throws IOException{
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
				resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
				resp.getWriter().format("no registered client with id '%s'", cond.getEndpoint()).flush();
			}
		} catch (RuntimeException | InterruptedException e) {
			handleException(e, resp);
		}
	}

	private void handleException(Exception e, HttpServletResponse resp) throws IOException {
		if (e instanceof InvalidRequestException || e instanceof CodecException ) {
			LOG.warn("Invalid request", e);
			resp.setStatus(HttpServletResponse.SC_BAD_REQUEST);
			resp.getWriter().append("Invalid request:").append(e.getMessage()).flush();
		} else if (e instanceof RequestRejectedException) {
			LOG.warn("Request rejected", e);
			resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			resp.getWriter().append("Request rejected:").append(e.getMessage()).flush();
		} else if (e instanceof RequestCanceledException) {
			LOG.warn("Request cancelled", e);
			resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			resp.getWriter().append("Request cancelled:").append(e.getMessage()).flush();
		} else if (e instanceof InvalidResponseException) {
			LOG.warn("Invalid response", e);
			resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			resp.getWriter().append("Invalid Response:").append(e.getMessage()).flush();
		} else if (e instanceof InterruptedException) {
			LOG.warn("Thread Interrupted", e);
			resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			resp.getWriter().append("Thread Interrupted:").append(e.getMessage()).flush();
		} else {
			LOG.warn("Unexpected exception", e);
			resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			resp.getWriter().append("Unexpected exception:").append(e.getMessage()).flush();
		}
	}


}
