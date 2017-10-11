export class Device{
	id: number;
	name: string;
	desc: string;
}

export class ResourceDesc{
	id: number;
	value: any;
}

export class ContentDesc{
	id: number;
	resources: ResourceDesc[];
}

export class ObjectDesc{
	status: string;
	content: ContentDesc;
}

export class ObjectLinkDesc{
	url: string;
	attributes: any;
}

export class EndPointDesc {
	endpoint: string;
	registrationId: string;
	registrationDate: string;
	lastUpdate: string;
	address: string;
	lwM2mVersion: string;
	lifetime: number;
	bindingMode: string;
	rootPath: string;
	objectLinks: ObjectLinkDesc[];
	secure: boolean;
	additionalRegistrationAttributes: string;
}