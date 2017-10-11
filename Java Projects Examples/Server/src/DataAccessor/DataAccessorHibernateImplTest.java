package DataAccessor;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.Date;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import DataModel.Autore;
import DataModel.Preferenza;
import DataModel.Risorsamultimediale;
import DataModel.Tiporisorsa;
import DataModel.Utente;

/*
 * Decommentare righe da 61-80 DataAccessorHibernateImpl per eseguire i test
 */
public class DataAccessorHibernateImplTest {

	@Before
	public void setUp() throws Exception {
		DataInterface DI = new DataAccessorHibernateImpl();
		DI.init();
	}

	@After
	public void tearDown() throws Exception {
	}

	/*
	 * TipoRisorsa già presente
	 */
	@Test
	public void testPersistTipoRisorsa1() {
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = true;
		Tiporisorsa TR = new Tiporisorsa("Junitaudio");
		DI.persistTiporisorsa(TR);
		
		Success = DI.persistTiporisorsa(TR);
		
		assertEquals(false,Success);
	}
	
	/*
	 * TipoRisorsa non presente
	 */
	@Test
	public void testPersistTipoRisorsa2() {
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		Tiporisorsa TR = new Tiporisorsa("JunitPersistTipoTest");
		
		Success = DI.persistTiporisorsa(TR);
		
		assertEquals(true,Success);
	}
	
	/*
	 * Recupera tutti i tipi disponibili
	 */
	@Test
	public void testgetTipiRisorsaAll() {
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		ArrayList<Tiporisorsa> ATR = DI.getTipiRisorsaAll();
		
		if(ATR != null){
			Success = true;
			for(Tiporisorsa T : ATR){
				System.out.println("Junit testgetTipiRisorsaAll, risorsa:" + T.getNomeTipoRisorsa());
			}
		}
		assertEquals(true,Success);
	}
	
	
	/*
	 * Recupera tipo risorsa inesistente
	 */
	@Test
	public void testgetTipoRisorsaifExist1() {
	
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		if(DI.getTipoRisorsaifExist("JunitTipoinesistente") != null) Success = true;
		
		assertEquals(false, Success);
	}
	
	/*
	 * Recupera tipo risorsa esistente
	 */
	@Test
	public void testgetTipoRisorsaifExist2() {
	
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		Tiporisorsa TR = new Tiporisorsa("JunitTipoEsiste");
		if(DI.persistTiporisorsa(TR) == true){
			if(DI.getTipoRisorsaifExist("JunitTipoEsiste") != null) Success = true;
		}
		
		assertEquals(true, Success);
	}
	
	/*
	 * Recupera Autore Inesistente
	 */
	@Test
	public void testgetAutoreByNameifExist1() {
	
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		if(DI.getAutoreByNameifExist("JunitAutoreInesistente") != null) Success = true;
		
		assertEquals(false,Success);
	}

	/*
	 * Recupera Autore Esistente
	 */
	@Test
	public void testgetAutoreByNameifExist2() {
	
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		if(DI.getAutoreByNameifExist("JunitAutoreEsistente") != null) Success = true;
		
		assertEquals(true,Success);
	}
	
	/*
	 * Tiporisorsa Errato
	 */
	@Test
	public void testgetAutoriByTipo1(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = new Tiporisorsa("JunitErrato");
		
		ArrayList<Autore> AA = DI.getAutoruByTipo(TR);
		if(AA != null){
			Success = true;
			for(Autore A : AA){
				System.out.println("Junit testgetAutoriByTipo1, Autore: " + A.getNome());
			}
		}
		assertEquals(false,Success);
	}
	
	/*
	 * Tiporisorsa Presente nel DB nessun Autore associato
	 */
	@Test
	public void testgetAutoriByTipo2(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = new Tiporisorsa("JunitTipoEsistenteNoAutori");
		
		ArrayList<Autore> AA = DI.getAutoruByTipo(TR);
		if(AA != null){
			Success = true;
			for(Autore A : AA){
				System.out.println("Junit testgetAutoriByTipo1, Autore: " + A.getNome());
			}
		}
		
		assertEquals(false,Success);
	}
	
	/*
	 * Tiporisorsa Presente nel DB Autori associati
	 */
	@Test
	public void testgetAutoriByTipo3(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist("JunitTipoEsistente");
		
		ArrayList<Autore> AA = DI.getAutoruByTipo(TR);
		if(AA != null){
			Success = true;
			for(Autore A : AA){
				System.out.println("Junit testgetAutoriByTipo1, Autore: " + A.getNome());
			}
		}
		
		assertEquals(true,Success);
	}
	
	/*
	 * Risorsa Multimediale non presente
	 */
	@Test
	public void testpersistRisorsaMultimediale1(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist("JunitTipoEsistente");
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistente");
		Risorsamultimediale RM = new Risorsamultimediale(A,TR,"JunitPersistRMTest",new Date(),1,1);
		Success = DI.persistRisorsaMultimediale(RM);
		
		assertEquals(true,Success);
		
	}
	
	/*
	 * Risorsa Multimediale non presente
	 */
	@Test
	public void testpersistRisorsaMultimediale2(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist("JunitTipoEsistente");
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistente");
		Risorsamultimediale RM = new Risorsamultimediale(A,TR,"JunitPersistRMTest",new Date(),1,1);
		DI.persistRisorsaMultimediale(RM);
		Success = DI.persistRisorsaMultimediale(RM);
		
		assertEquals(true,Success);
		
	}
	
	/*
	 * Autore non esiste
	 */
	@Test
	public void testgetRisorsemultimedialiByAutore1(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Autore A = DI.getAutoreByNameifExist("JunitAutoreInesistente");
		ArrayList<Risorsamultimediale> ARM = DI.getRisorsemultimedialiByAutore(A);
		if(ARM != null){
			Success = true;
			for(Risorsamultimediale R : ARM){
				System.out.println("Junit testgetRisorsemultimedialiByAutore1, Risorsa:" + R.getTitolo());
			}
		}
		
		assertEquals(false,Success);
	}
	
	/*
	 * Autore Esiste non esiste Risorsa
	 */
	@Test
	public void testgetRisorsemultimedialiByAutore2(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistenteNoRisorsa");
		ArrayList<Risorsamultimediale> ARM = DI.getRisorsemultimedialiByAutore(A);
		if(ARM != null){
			if(ARM.isEmpty() != true){
				Success = true;
				for(Risorsamultimediale R : ARM){
					System.out.println("Junit testgetRisorsemultimedialiByAutore1, Risorsa:" + R.getTitolo());
				}
			}
		}
		
		assertEquals(false,Success);		
	}
	
	/*
	 * Autore e Risorsa Associata Esistono 
	 */
	@Test
	public void testgetRisorsemultimedialiByAutore3(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistente");
		ArrayList<Risorsamultimediale> ARM = DI.getRisorsemultimedialiByAutore(A);
		if(ARM != null){
			Success = true;
			for(Risorsamultimediale R : ARM){
				System.out.println("Junit testgetRisorsemultimedialiByAutore1, Risorsa:" + R.getTitolo());
			}
		}
		
		assertEquals(true,Success);		
	}
	
	/*
	 * Preferenza non presente
	 */
	@Test
	public void testpersistPreferenza1(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Preferenza P = new Preferenza();
		P.setAutore(DI.getAutoreByNameifExist("JunitAutoreEsistente"));
		P.setTiporisorsa(DI.getTipoRisorsaifExist("JunitTipoEsistente"));
		Success = DI.persistPreferenza(P);
		
		assertEquals(true,Success);
		
	}
	
	/*
	 * Preferenza già presente
	 */
	@Test
	public void testpersistPreferenza2(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist("JunitTipoEsistente");
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistente");
		Preferenza P = new Preferenza();
		P.setAutore(A);
		P.setTiporisorsa(TR);
		DI.persistPreferenza(P);
		Success = DI.persistPreferenza(P);
		
		assertEquals(true,Success);
		
	}
	
	/*
	 * Preferenza esiste
	 */
	@Test
	public void testgetPreferenzaifExist1(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist("JunitTipoEsistente");
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistente");
		Preferenza P = new Preferenza();
		P.setAutore(A);
		P.setTiporisorsa(TR);
		DI.persistPreferenza(P);
		Preferenza P1 = DI.getPreferenzaifExist(TR, A);
		if(P1 != null){
			Success = true;
		}
		
		assertEquals(true,Success);
	}
	
	/*
	 * Preferenza non esiste
	 */
	@Test
	public void testgetPreferenzaifExist2(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist("JunitTipoEsistenteNoAutori");
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistenteNoRisorsa");
		Preferenza P1 = DI.getPreferenzaifExist(TR, A);
		if(P1 != null){
			Success = true;
		}
		
		assertEquals(false,Success);
	}
	
	/*
	 * Utente Esistente
	 */
	@Test
	public void testgetUtentebyEmail1(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Utente U = DI.getUtentebyEmail("email@stub.psss");
		
		if(U != null){
			Success = true;
		}
		
		assertEquals(true,Success);
	}
	
	/*
	 * Utente non Esistente
	 */
	@Test
	public void testgetUtentebyEmail2(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Utente U = DI.getUtentebyEmail("JUNIT@stub.psss");
		
		if(U != null){
			Success = true;
		}
		
		assertEquals(false,Success);
	}
	
	/*
	 * Preferenza non esiste
	 */
	@Test
	public void testgetUtentiByPreferenza1(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Preferenza P = new Preferenza(new Autore("JunitPrefAut"),new Tiporisorsa("JunitPrefTipo"));
		ArrayList<Utente> U = DI.getUtentiByPreferenza(P);
		if(U != null) Success = true;
		
		assertEquals(false,Success);
	}
	
	/*
	 * Preferenza esiste No utente associato
	 */
	@Test
	public void testgetUtentiByPreferenza2(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = true;
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist("JunitTipoEsistenteNoAutori");
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistenteNoRisorsa");
		Preferenza P = new Preferenza(A,TR);
		DI.persistPreferenza(P);
		Preferenza P1 = DI.getPreferenzaifExist(TR, A);
		ArrayList<Utente> U = DI.getUtentiByPreferenza(P);
		if(U != null){
			Success = false;
			if(U.isEmpty() != true) Success = true;
		}
		
		assertEquals(false,Success);
	}
	
	/*
	 * Preferenza esiste utentì associato
	 */
	@Test
	public void testgetUtentiByPreferenza3(){
		
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Tiporisorsa TR = DI.getTipoRisorsaifExist("JunitTipoEsistenteNoAutori");
		Autore A = DI.getAutoreByNameifExist("JunitAutoreEsistenteNoRisorsa");
		Utente U = DI.getUtentebyEmail("email@stub.psss");
		Preferenza P = DI.getPreferenzaifExist(TR, A);
		U.getPreferenzePerUtente().add(P);
		P.getUtentiPerPreferenza().add(U);
		DI.persistPreferenza(P);
		Preferenza P1 = DI.getPreferenzaifExist(TR, A);
		ArrayList<Utente> AU = DI.getUtentiByPreferenza(P1);
		if(U != null){
			if(AU.isEmpty() != true) Success = true;
		}
		
		assertEquals(true,Success);
	}
}
