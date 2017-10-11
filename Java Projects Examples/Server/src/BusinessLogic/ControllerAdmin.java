package BusinessLogic;

import java.util.ArrayList;
import java.util.Date;
import java.util.concurrent.locks.ReentrantLock;

import DataAccessor.DataAccessorHibernateImpl;
import DataAccessor.DataInterface;
import DataModel.Autore;
import DataModel.Preferenza;
import DataModel.Risorsamultimediale;
import DataModel.Tiporisorsa;
import DataModel.Utente;
import Email.EmailStub;

public class ControllerAdmin {
	
	public static DataInterface DI = null;  //Public solo per Testing
	static ReentrantLock  L = null;
	
	public ControllerAdmin(){
		if(DI == null){
			DI = new DataAccessorHibernateImpl();
		}
		if(L == null) L = new ReentrantLock ();	
	}
	
	/*
	 * Inserimento Risorsa:
	 * l'autore viene generato all'atto dell'inserimento se non esiste.
	 * Il tipo della risorsa deve essere già presente.
	 * L'inserimento di una risorsa è effettuato in mutua esclusione 
	 * dato che più client Amministratori possono effettuarlo in concorrenza.
	 */
	public boolean InserisciRisorsa
		(String Titolo, String Tipo, String Autore, float CostoAcquisto, float CostoNoleggio)
	{
		boolean success = false;
		boolean Exist = false;
		
		Tiporisorsa TR = null;
		Autore A = null;
		
		L.lock();
		try{
			A = DI.getAutoreByNameifExist(Autore);
			if(A != null){
				ArrayList<Risorsamultimediale> ARM = DI.getRisorsemultimedialiByAutore(A);
				for(Risorsamultimediale RM : ARM){
					System.out.println("Titolo: " + RM.getTitolo());
					if(RM.getTitolo().equals(Titolo)){
						Exist = true;
						break;
					}
				}
			}
			else{
				A = new Autore(Autore);
			}
			
			if(!Exist == true){
				TR = DI.getTipoRisorsaifExist(Tipo);
				if(TR != null){
					Risorsamultimediale RM = new Risorsamultimediale(A,TR,Titolo,new Date(),CostoAcquisto,CostoNoleggio);
					success = DI.persistRisorsaMultimediale(RM);
				}
			}
		}
		finally{
			L.unlock();
		}
		
		if(success == true){
			Preferenza P = DI.getPreferenzaifExist(TR, A);
			if(P != null){
				ArrayList<Utente> AU = DI.getUtentiByPreferenza(P);
				if(AU != null){
					for(int i=0;i<AU.size();i++){
						EmailStub.sendEmail("Stub Invio Email a ", AU.get(i).getEmail());
						//System.out.println("Stub Invio Email a " + AU.get(i).getEmail() );
					}
				}
			}
		}
			return success;
	}

}
