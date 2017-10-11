package org.at.dandrol.LeshanServer.rules;

import java.util.ArrayList;
import java.util.Random;

import org.at.dandrol.LeshanServer.rules.model.Condition;
import org.at.dandrol.LeshanServer.rules.model.Rule;

public class RuleEngine {

	protected ArrayList<Rule> rules = null;
	protected Random idGenerator = null;

	public RuleEngine(){
		rules = new ArrayList<Rule>();
		idGenerator = new Random();
	}

	public Condition createCondition(String endpoint, String target, String operator, double targetValue, String catOp){

		return new Condition(endpoint, target, -1.0, operator, targetValue, catOp);
	}

	public int createRule(ArrayList<Condition> conditions, String actionEndpoint, String actionTarget){

		int id = idGenerator.nextInt();
		return createRule(id, conditions, actionEndpoint, actionTarget);
	}

	public int createRule(int id, ArrayList<Condition> conditions, String actionEndpoint, String actionTarget){

		rules.add(new Rule(id, conditions, actionEndpoint, actionTarget));
		return id;
	}


	protected  ArrayList<Integer> updateRules(String endpoint, String target, double value){

		ArrayList<Integer> updatedID = new ArrayList<Integer>();


		for (Rule rule : rules){

			Condition cond = rule.getConditionByEndpoint(endpoint, target);

			if(cond != null){
				cond.setReadValue(value);
				if(evaluate(rule.getRuleID()))
					updatedID.add(rule.getRuleID());
			}
		} 		
		if(updatedID.isEmpty())
			updatedID.add(-1);

		return updatedID;
	}

	public boolean evaluate(Integer requestID){

		return getRuleByID(requestID).evaluate();		
	}

	public Rule getRuleByID(Integer ID){

		for (Rule rule : rules){
			if (ID.equals(rule.getRuleID()))
				return rule;
		}			
		return null;
	}

	public boolean thereIsRuleFor(String endpoint){

		for(Rule rule : rules){
			
			if(!rule.getAllConditionsFor(endpoint).isEmpty()) return true;
		}
		return false;
	}

	public ArrayList<Rule> getRules(){
		return rules;
	}
	public void setRules(ArrayList<Rule> rules) {
		this.rules = rules;
		System.out.println("stored automation rule set");
	}

}




