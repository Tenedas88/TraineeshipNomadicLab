import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { DeviceDetail } from './device-detail';

@NgModule({
  declarations: [
    DeviceDetail,
  ],
  imports: [
    IonicPageModule.forChild(DeviceDetail),
  ],
  exports: [
    DeviceDetail
  ]
})
export class DeviceDetailModule {}
