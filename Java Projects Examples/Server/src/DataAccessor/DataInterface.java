package DataAccessor;

import java.util.ArrayList;

import DataModel.*;

public interface DataInterface {
	
	public void init();
	
	/*
	 * TipoRisorsa
	 */
	
	public boolean persistTiporisorsa(Tiporisorsa Tipo);
	
	public ArrayList<Tiporisorsa> getTipiRisorsaAll();
	
	public Tiporisorsa getTipoRisorsaifExist(String tipo);
	
	/*
	 * Autore
	 */
	
	//public ArrayList<Autore> getAutoriAll();
	
	public Autore getAutoreByNameifExist(String name);
	
	public ArrayList<Autore> getAutoruByTipo(Tiporisorsa TR);
	
	/*
	 * Risorsamultimediale
	 */
	
	public boolean persistRisorsaMultimediale(Risorsamultimediale risorsamultimediale);
	
	public ArrayList<Risorsamultimediale> getRisorsemultimedialiByAutore(Autore autore);

	/*
	 * Preferenza
	 */
	
	public boolean persistPreferenza(Preferenza preferenza);
	
	public Preferenza getPreferenzaifExist(Tiporisorsa TR, Autore A);
	
	//public ArrayList<Preferenza> getPreferenzeByAutore(Autore autore);
	
	/*
	 * Utente
	 */
	
	public Utente getUtentebyEmail(String email);
	
	public ArrayList<Utente> getUtentiByPreferenza(Preferenza preferenza);
	
}
