package org.at.dandrol.LeshanServer.automation;

import java.util.ArrayList;

import org.at.dandrol.LeshanServer.DBManager.DBManager;
import org.at.dandrol.LeshanServer.rules.RuleEngine;
import org.at.dandrol.LeshanServer.rules.model.Condition;

public abstract class AutomationManager extends RuleEngine {


	public AutomationManager(){
		super();

	}

	public int createAutomationRule(ArrayList<Condition> conditions, String actionEndpoint, String actionTarget){

		return createRule(conditions, actionEndpoint, actionTarget);

	}

	public int createAutomationRule(int id, ArrayList<Condition> conditions, String actionEndpoint, String actionTarget){

		return createRule(id, conditions, actionEndpoint, actionTarget);

	}

	public ArrayList<Integer> updateRuleValue(String endpoint, String target, double value){

		return updateRules(endpoint, target, value);

	}

	public void loadStoredAutomations() {

		setRules(DBManager.getInstance().loadAutomations());
	}

	public abstract String executeAction(Integer ruleID) throws RuntimeException, InterruptedException;

}
