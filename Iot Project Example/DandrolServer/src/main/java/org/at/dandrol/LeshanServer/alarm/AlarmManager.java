package org.at.dandrol.LeshanServer.alarm;

import java.util.ArrayList;

import org.at.dandrol.LeshanServer.DBManager.DBManager;
import org.at.dandrol.LeshanServer.rules.RuleEngine;
import org.at.dandrol.LeshanServer.rules.model.Condition;

public abstract class AlarmManager extends RuleEngine {

	public AlarmManager(){
		super();
	}

	public int createAlarmRule(ArrayList<Condition> conditions){

		return createRule(conditions, null, null);

	}
	
	public int createAlarmRule(int id, ArrayList<Condition> conditions){

		return createRule(id, conditions, null, null);

	}

	public ArrayList<Integer> updateRuleValue(String endpoint, String target, double value){

		return updateRules(endpoint, target, value);

	}

	public abstract String sendAlarm(Integer ruleID);

	public void loadStoredAlarms() {

		setRules(DBManager.getInstance().loadAlarms());
	}
 
}
