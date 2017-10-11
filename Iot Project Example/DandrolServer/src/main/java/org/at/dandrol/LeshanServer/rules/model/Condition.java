package org.at.dandrol.LeshanServer.rules.model;

import java.io.Serializable;

public class Condition implements Serializable{

	private String endpoint;
	private String target;
	private double readValue;
	private Operator operator;
	private double value;
	private Concatenate concatenationOp; 

	public Condition(String endpoint, String target, double readValue, String operator, double value, String concatenationOp) {
		super();
		this.endpoint = endpoint;
		this.target = target;
		this.readValue = readValue;
		this.operator = Operator.from(operator);
		this.value = value;
		this.concatenationOp = Concatenate.from(concatenationOp);
	}

	public Condition(String endpoint, String target, String operator, double value, String concatenationOp) {
		super();
		this.endpoint = endpoint;
		this.target = target;
		this.operator = Operator.from(operator);
		this.value = value;
		this.concatenationOp = Concatenate.from(concatenationOp);
	}


	public enum Operator  {
		gt(">") {
			public boolean apply(double v1, double v2) {
				return v1 > v2;
			}
		},
		lt(">") {
			public boolean apply(double v1, double v2) {
				return v1 < v2;
			}
		},

		eq("=") {
			public boolean apply(double v1, double v2) {
				return v1 == v2;
			}
		},
		nd("nd") {
			@Override
			public boolean apply(double v1, double v2) {
				
				return false;
			}
		};

		public abstract boolean apply(double v1, double v2);
		private final String stringOperator;


		Operator(String op) {
			this.stringOperator = op;
		}

		public String getStringOperator() {
			return stringOperator;
		}

		public static Operator from(String str) {
			if(str == null)
				return null;
			
			switch (str){
			case ">": return Operator.gt; 
			case "<": return Operator.lt; 
			case "=": return Operator.eq; 
			}
			return null;
		}
	}

	public enum Concatenate{
		and("and"){
			public boolean apply(boolean v1, boolean v2){
				return v1 && v2;
			}
		},
		or("or"){
			public boolean apply(boolean v1, boolean v2){
				return v1 || v2;
			}
		};

		public abstract boolean apply(boolean v1, boolean v2);

		private final String stringConcatenationOperator;

		public String getStringConcatenationOperator() {
			return stringConcatenationOperator;
		}

		Concatenate(String op){
			this.stringConcatenationOperator = op;
		}

		public static Concatenate from(String str) {
			if(str == null)
				return null;
			
			switch (str){
			case "and": return Concatenate.and;
			case "AND": return Concatenate.and;
			case "or": return Concatenate.or; 
			case "OR": return Concatenate.or;
			}
			return null;
		}
	}

	public boolean evaluate(){

		return operator.apply(readValue, value);

	}
	

	public String getEndpoint() {
		return endpoint;
	}
	public void setEndpoint(String endpoint) {
		this.endpoint = endpoint;
	}
	public String getTarget() {
		return target;
	}
	public void setTarget(String target) {
		this.target = target;
	}
	public double getReadValue() {
		return readValue;
	}
	public void setReadValue(double readValue) {
		this.readValue = readValue;
	}
	public Operator getOperator() {
		return operator;
	}
	public void setOperator(Operator operator) {
		this.operator = operator;
	}
	public double getValue() {
		return value;
	}
	public void setValue(double value) {
		this.value = value;
	}
	public Concatenate getConcatenationOp() {
		return concatenationOp;
	}
	public void setConcatenationOp(Concatenate concatenationOp) {
		this.concatenationOp = concatenationOp;
	}
}
