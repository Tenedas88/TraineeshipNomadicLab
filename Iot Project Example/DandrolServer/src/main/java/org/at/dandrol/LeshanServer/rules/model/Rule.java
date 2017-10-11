package org.at.dandrol.LeshanServer.rules.model;

import java.io.Serializable;
import java.util.ArrayList;

import org.eclipse.leshan.util.StringUtils;

public class Rule implements Serializable {

	
	private static final long serialVersionUID = 1L;

	protected Integer ruleID;
	protected ArrayList<Condition> conditions;
	protected String actionEndpoint;
	protected String actionTarget;
	
	public Rule(int ID, ArrayList<Condition> conditions, String actionEndpoint, String actionTarget) {

		this.ruleID = ID;
		this.conditions = conditions;
		this.actionEndpoint = actionEndpoint;
		this.actionTarget = actionTarget;
	}
	
	public Rule(int ID, ArrayList<Condition> conditions) {

		this.ruleID = ID;
		this.conditions = conditions;
		this.actionEndpoint = null;
		this.actionTarget = null;
	}
	
	public boolean evaluate(){
		return privateEvaluate(0);
	}
	private boolean privateEvaluate(int i){

		if(conditions.get(i).getConcatenationOp()!=null){
			return conditions.get(i).getConcatenationOp().apply
					(conditions.get(i).evaluate(), privateEvaluate(i+1));
		}
		else
			return conditions.get(i).evaluate();
	} 

	public Condition getConditionByEndpoint(String endpoint, String target){
		
		target = StringUtils.removeStart(target, "/");
		
		for (Condition cond : conditions){
			
			if(endpoint.equals(cond.getEndpoint()) && target.equals(cond.getTarget()))
				return cond;
		}
		return null;
	}
	
	public ArrayList<Condition> getAllConditionsFor(String endpoint){
		ArrayList<Condition> returnConditions = new ArrayList<Condition>();
		
		for(Condition cond : conditions){
			if (cond.getEndpoint().equals(endpoint))
				returnConditions.add(cond);
		}
		return returnConditions;
	}
	
	public ArrayList<Condition> getConditions() {
		return conditions;
	}
	public void setConditions(ArrayList<Condition> conditions) {
		this.conditions = conditions;
	}

	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	public int getRuleID() {
		return ruleID;
	}
	public void setRuleID(int ruleID) {
		this.ruleID = ruleID;
	}
	public String getActionEndpoint() {
		return actionEndpoint;
	}

	public void setActionEndpoint(String actionEndpoint) {
		this.actionEndpoint = actionEndpoint;
	}

	public String getActionTarget() {
		return actionTarget;
	}

	public void setActionTarget(String actionTarget) {
		this.actionTarget = actionTarget;
	}

	public void setRuleID(Integer ruleID) {
		this.ruleID = ruleID;
	}

	
	
}
