import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams, MenuController } from 'ionic-angular';

import { ConditionDesc, RuleDesc} from '../../app/rule';

@IonicPage()
@Component({
  selector: 'page-rule-detail',
  templateUrl: 'rule-detail.html',
})
export class RuleDetail {
  
  currentRuleID: number;
  currentRuleConditions: ConditionDesc[];
  
  constructor(public navCtrl: NavController, public navParams: NavParams,
				public menu: MenuController) {
		this.currentRuleID = navParams.get('ruleID');
		this.currentRuleConditions = navParams.get('conditions');
  }
  
  goToResDetail(target: string, endpoint: string){
	let fields = target.split('/');
	let path = `/${endpoint}/${fields[0]}/${fields[1]}`;
	this.navCtrl.push('ResourceDetail', {currentPath: path});
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad RuleDetail');
  }
  

}
