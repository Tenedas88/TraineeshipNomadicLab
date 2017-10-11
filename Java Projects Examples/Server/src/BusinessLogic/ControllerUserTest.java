package BusinessLogic;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/*
 * Decommentare righe da 61-80 DataAccessorHibernateImpl per eseguire i test
 */
public class ControllerUserTest {

	@Before
	public void setUp() throws Exception {
		ControllerUser CU = new ControllerUser();
		CU.DI.init();
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void testInserisciPreferenza() {
		ControllerUser CU = new ControllerUser();
		
		boolean Success = false;
		
		Success = CU.InserisciPreferenza("JunitTipoEsistente", "JunitAutoreEsistente", "email@stub.psss");
		
		assertEquals(true,Success);
	}

}
