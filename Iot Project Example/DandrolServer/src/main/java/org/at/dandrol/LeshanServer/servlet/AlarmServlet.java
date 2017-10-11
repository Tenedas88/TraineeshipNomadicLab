package org.at.dandrol.LeshanServer.servlet;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.at.dandrol.LeshanServer.alarm.AlarmManager;
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

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class AlarmServlet extends HttpServlet {

	private static final long serialVersionUID = 1L;
	private static final long TIMEOUT = 5000; // ms
	
	private static final Logger LOG = LoggerFactory.getLogger(ClientServlet.class);
	private final Gson gson;
	
	private final LwM2mServer server;
	private final AlarmManager alarmManager;
	
	
	public AlarmServlet(LwM2mServer server, AlarmManager alarmManager) {
		super();
		
		GsonBuilder gsonBuilder = new GsonBuilder();
		gsonBuilder.registerTypeHierarchyAdapter(Rule.class, new RuleSerializer());
		this.gson = gsonBuilder.create();
		
		this.server = server;
		this.alarmManager = alarmManager;
	}

	protected void doGet (HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
	
	
		System.out.println("[ALARM SERVLET - doGet]");

		getAlarm(req, resp);

	
	
	}
	
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		
		
		doAlarm(req, resp);
		
	}
	
	
	
	private void getAlarm(HttpServletRequest req, HttpServletResponse resp) throws IOException{
		
		ArrayList<Rule> rules = alarmManager.getRules(); 

		String json = this.gson.toJson(rules.toArray(new Rule[] {}));
		resp.setContentType("application/json");
		try {
			resp.getOutputStream().write(json.getBytes(StandardCharsets.UTF_8));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			resp.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
			e.printStackTrace();
		}
		resp.setStatus(HttpServletResponse.SC_OK);

	}
	
	private void doAlarm(HttpServletRequest req, HttpServletResponse resp) throws IOException{
		System.out.println("[ALARM SERVLET POST - doAlarm]");
		ArrayList<Condition> conditions = createAlarm(req);

		for (Condition cond : conditions){
			observe(cond, resp);
		}

		int id = alarmManager.createAlarmRule(conditions);
		
		System.out.println("\t alarm rule created with id "+ id);
	}

	private ArrayList<Condition> createAlarm(HttpServletRequest req){

		int conditionsCount = Integer.parseInt(req.getParameter("conditioncount"));

		ArrayList<Condition> conditions = new ArrayList<Condition>();

		for(int i = 0; i < conditionsCount; i++){
			conditions.add(alarmManager.createCondition(
					req.getParameter("srcendpoint"+(i+1)),
					req.getParameter("srctarget"+(i+1)),
					req.getParameter("operator"+(i+1)),
					Double.parseDouble(req.getParameter("targetvalue"+ (i+1))),
					req.getParameter("catop"+(i+1))
					));

		}
		return conditions;
	}

	private void observe(Condition cond, HttpServletResponse resp) throws IOException{
		try{
			Registration registration = server.getRegistrationService().getByEndpoint(cond.getEndpoint());
			if (registration != null) {
				// create & process request

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
