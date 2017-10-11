import { Injectable } from '@angular/core';
import { Http } from '@angular/http';
import 'rxjs/add/operator/map';

import 'rxjs/add/operator/toPromise';
import { EndPointDesc, ObjectLinkDesc, ObjectDesc, ContentDesc, ResourceDesc} from '../app/ipso';
import { ConditionDesc, RuleDesc} from '../app/rule';

@Injectable()
export class ServerCom {

	serverUrl = 'http://192.168.43.160:8080/';
	clientServlet = 'api/clients';
	automationServlet = 'api/automations';

  constructor(public http: Http) {
    console.log('Hello ServerCom Provider');
  }
  
  getReq(): Promise<any> {
  let path = `${this.serverUrl}${this.clientServlet}`
      return this.http.get(path)
        .toPromise().then(data => data.json() as EndPointDesc[] );
  }
  
  getResReq(resPath: string): Promise<any> {
	  let path = `${this.serverUrl}${this.clientServlet}${resPath}`
      return this.http.get(path)
        .toPromise().then(data => data.json() );
  }

  getReqRule(): Promise<any> {
	  let path = `${this.serverUrl}${this.automationServlet}`
      return this.http.get(path)
        .toPromise().then(data => data.json() as RuleDesc[] );
  }
  
  postReqRule(input: RuleDesc): Promise<any> {
	  let path = `${this.serverUrl}${this.automationServlet}`
      return this.http.post(path,input,{params : input})
        .toPromise().then(data => data.json());
  }
  
  postObsReq(): Promise<any>{
	return this.http.post("http://192.168.43.160:8080/api/clients/Alfred/3303/0/5700/observe",null)
		.toPromise().then(data => data.json());
  }

}
