package BusinessLogic;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.concurrent.locks.*;

import DataAccessor.DataAccessorHibernateImpl;
import DataAccessor.DataInterface;
import DataModel.Autore;
import DataModel.Preferenza;
import DataModel.Risorsamultimediale;
import DataModel.Tiporisorsa;
import DataModel.Utente;

public class Controller {
	
	public static DataInterface DI = null;  //Public solo per Testing
	static ReentrantLock  L = null;
	
	public Controller(){
		if(DI == null){
			DI = new DataAccessorHibernateImpl();
			DI.init();
			DI.persistTiporisorsa(new Tiporisorsa("audio"));
			DI.persistTiporisorsa(new Tiporisorsa("video"));
			DI.persistTiporisorsa(new Tiporisorsa("podcast"));
			DI.persistTiporisorsa(new Tiporisorsa("immagine"));
		}
		if(L == null) L = new ReentrantLock ();		
	}
	
	/*
	 * Recupero Tipi Disponibili nel DB
	 */
	public ArrayList<Tiporisorsa> GetTipiDisoponibili(){
		return DI.getTipiRisorsaAll();
	}

}
