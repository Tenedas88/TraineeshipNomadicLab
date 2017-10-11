package BusinessLogic;

import static org.junit.Assert.*;


import java.util.Date;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import DataAccessor.DataAccessorHibernateImpl;
import DataAccessor.DataInterface;
import DataModel.Autore;
import DataModel.Risorsamultimediale;
import DataModel.Tiporisorsa;

/*
 * Decommentare righe da 61-80 DataAccessorHibernateImpl per eseguire i test
 */
public class ControllerAdminTest {

	@Before
	public void setUp() throws Exception {
		ControllerAdmin CA = new ControllerAdmin();
		CA.DI.init();
	}

	@After
	public void tearDown() throws Exception {
	}

	/*
	 * Risorsa nuova con invio di email ad utenti stub la cui preferenza su tipo/autore è registrata 
	 */
	@Test
	public void testInserisciRisorsa1() {
		
		ControllerAdmin CA = new ControllerAdmin();
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		
		Success = CA.InserisciRisorsa("JunitControllerTest1", "JunitTipoEsistente", "JunitAutoreEsistente", 1, 1);
		
		assertEquals(true,Success);
	}
	
	/*
	 * Risorsa già presente
	 */
	@Test
	public void testInserisciRisorsa2() {
		
		ControllerAdmin CA = new ControllerAdmin();
		DataInterface DI = new DataAccessorHibernateImpl();
		
		boolean Success = false;
		if(CA.InserisciRisorsa("JunitControllerTest2", "JunitTipoEsistente", "JunitAutoreEsistente", 1, 1)==true){
			Success = CA.InserisciRisorsa("JunitControllerTest2", "JunitTipoEsistente", "JunitAutoreEsistente", 1, 1);
		}
		
		assertEquals(false,Success);
	}

}
