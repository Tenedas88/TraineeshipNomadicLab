import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { ResourceDetail } from './resource-detail';

@NgModule({
  declarations: [
    ResourceDetail,
  ],
  imports: [
    IonicPageModule.forChild(ResourceDetail),
  ],
  exports: [
    ResourceDetail
  ]
})
export class ResourceDetailModule {}
