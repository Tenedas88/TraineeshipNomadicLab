package BusinessLogic;

import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

import DataAccessor.DataAccessorHibernateImpl;
import DataAccessor.DataInterface;
import DataModel.Autore;
import DataModel.Preferenza;
import DataModel.Tiporisorsa;
import DataModel.Utente;

public class ControllerUser {
	
	public static DataInterface DI = null;  //Public solo per Testing
	static ReentrantLock  L = null;
	
	public ControllerUser(){
		if(DI == null){
			DI = new DataAccessorHibernateImpl();
		}
		if(L == null) L = new ReentrantLock ();	
	}

	/*
	 * Recupero Autori Per Tipo 
	 */
	public ArrayList<Autore> GetAutoribyTipo(String Tipo){
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist(Tipo);
		if(TR != null){
			ArrayList<Autore> ALA = DI.getAutoruByTipo(TR);
			if(ALA != null){
				return ALA;
			}
		}
		return null;
	}
	
	/*
	 * Inserimento Preferenza:
	 * Autore e Tiporisorsa devono essere già persistenti sulla basedati
	 * L'email è considerato un identificativo univoco dell'utente per l'associazione alla preferenza
	 */
	public boolean InserisciPreferenza(String Tipo, String Autore, String Email){
		boolean Success = false;
		
		Utente U = DI.getUtentebyEmail(Email);
		if(U == null) return Success;
		Tiporisorsa TR = DI.getTipoRisorsaifExist(Tipo);
		if(TR == null) return Success;
		Autore A = DI.getAutoreByNameifExist(Autore);
		if(A == null) return Success;
		Preferenza P = null;
		P = DI.getPreferenzaifExist(TR, A); 
		if(P == null){
			L.lock();
				P = new Preferenza(A,TR);
				U.getPreferenzePerUtente().add(P);
				P.getUtentiPerPreferenza().add(U);
				Success = DI.persistPreferenza(P);
			L.unlock();
		}
		else{	
			ArrayList<Utente> AU = DI.getUtentiByPreferenza(P);
			if(AU.contains(U) != true){
				U.getPreferenzePerUtente().add(P);
				P.getUtentiPerPreferenza().add(U);
				Success = DI.persistPreferenza(P);
			}
		}
		return Success; 
		}

}
