import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { RuleDetail } from './rule-detail';

@NgModule({
  declarations: [
    RuleDetail,
  ],
  imports: [
    IonicPageModule.forChild(RuleDetail),
  ],
  exports: [
    RuleDetail
  ]
})
export class RuleDetailModule {}
