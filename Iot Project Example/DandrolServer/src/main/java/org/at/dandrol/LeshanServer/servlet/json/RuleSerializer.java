package org.at.dandrol.LeshanServer.servlet.json;

import java.lang.reflect.Type;
import java.util.ArrayList;

import org.at.dandrol.LeshanServer.rules.model.Condition;
import org.at.dandrol.LeshanServer.rules.model.Rule;

import com.eclipsesource.json.JsonArray;
import com.google.gson.Gson;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonSerializationContext;
import com.google.gson.JsonSerializer;


public class RuleSerializer implements JsonSerializer<Rule> {

	protected Integer ruleID;
	protected ArrayList<Condition> conditions;
	protected String actionEndpoint;
	protected String actionTarget;
	

	@Override
	public JsonElement serialize(Rule src, Type typeOfSrc, JsonSerializationContext context) {

		JsonObject element = new JsonObject();
		
		element.addProperty("RuleID", src.getRuleID());
	
		Gson gson = new Gson();

		
		element.addProperty("conditions", gson.toJson(src.getConditions()));
		element.addProperty("actionEndpoint", src.getActionEndpoint());
		element.addProperty("actionTarget", src.getActionTarget());
		
		return element;

		
	}

}
