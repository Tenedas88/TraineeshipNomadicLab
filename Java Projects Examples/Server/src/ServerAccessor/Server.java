package ServerAccessor;

import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

import BusinessLogic.Controller;
import BusinessLogic.ControllerAdmin;
import BusinessLogic.ControllerUser;
import DataAccessor.DataAccessorHibernateImpl;
import DataAccessor.DataInterface;

public class Server {
	
	public static Registry registry;
	public static Controller C;
	
	public void Init(){
		C =new Controller();
		
		System.out.println("Server Initialized");
	}
	
	public void Start() throws RemoteException, AlreadyBoundException{
		if(C != null){
			System.setSecurityManager(new SecurityManager());
		
			ServerAccessorAdminImpl SAA = new ServerAccessorAdminImpl();
			ServerAccessorAdminInterface StubAdmin = (ServerAccessorAdminInterface) UnicastRemoteObject.exportObject(SAA,0);
			
			ServerAccessorUserImpl SAU = new ServerAccessorUserImpl();
			ServerAccessorUserInterface StubUser = (ServerAccessorUserInterface) UnicastRemoteObject.exportObject(SAU,0);
		
			registry = LocateRegistry.createRegistry(1099);
			registry.bind("Admin", StubAdmin);
			registry.bind("User", StubUser);
			System.out.println("Server Started!");
		}
		else{
			System.out.println("Failed to Start, Init First!");
		}
	}
	
	public void addStubData(){
		if(C!=null){
			/****RISORSE STUB*****/
			ControllerAdmin CA = new ControllerAdmin();
			CA.InserisciRisorsa("prova", "audio", "Davide", 50, 5);
			CA.InserisciRisorsa("prova", "audio", "Rolando", 50, 5);
			ControllerUser CU = new ControllerUser();
			CU.InserisciPreferenza("video", "Davide", "email@stub2.psss2");
			CU.InserisciPreferenza("video", "Davide", "email@stub.psss");
			CU.InserisciPreferenza("video", "Davide", "email@stub3.psss3");
			CU.InserisciPreferenza("video", "Davide", "email@stub4.psss4");
			
			System.out.println("Stub Data Added!");
		}
		else{
			System.out.println("Init Before Adding Stub Data!");
		}
	}

	public static void main(String[] args) throws RemoteException, AlreadyBoundException {
		
		Server S = new Server();
		S.Init();
		S.addStubData();
		S.Start();
		
	}

}
