export class ConditionDesc{
	endpoint: string;
	target: string;
	readValue: any;
	operator: string;
	value: any;
	concatenationOp: string;
}

export class RuleDesc{	
	ruleID: number;
	conditions: ConditionDesc[];
	actionEndpoint: string;
	actionTarget: string;
}