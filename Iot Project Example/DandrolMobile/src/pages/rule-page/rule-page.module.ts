import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { RulePage } from './rule-page';

@NgModule({
  declarations: [
    RulePage,
  ],
  imports: [
    IonicPageModule.forChild(RulePage),
  ],
  exports: [
    RulePage
  ]
})
export class RulePageModule {}
