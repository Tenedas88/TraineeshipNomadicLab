package ServerAccessor;

import java.rmi.RemoteException;
import java.util.ArrayList;

import BusinessLogic.Controller;
import BusinessLogic.ControllerAdmin;
import DataModel.Tiporisorsa;
import DataModelExport.AutoreExport;
import DataModelExport.TiporisorsaExport;


public class ServerAccessorAdminImpl implements ServerAccessorAdminInterface {

	/*
	 * Entity: TiporisorsaExport
	 * @see ServerAccessor.ServerAccessorInterface#GetTipiDisoponibili()
	 */
	@Override
	public ArrayList<TiporisorsaExport> GetTipiDisoponibili() throws RemoteException {
		Controller C = new Controller();
		ArrayList<Tiporisorsa> ATR = C.GetTipiDisoponibili();
		if(ATR != null){
			ArrayList<TiporisorsaExport> ATRE = new ArrayList<TiporisorsaExport>();
			for( Tiporisorsa TR : ATR){
				ATRE.add(new TiporisorsaExport(TR.getNomeTipoRisorsa()));
			}
			return ATRE;
		}
		else{
			return null;
		}
	}

	/*
	 * Entity: Risorsamultimediale
	 * @see ServerAccessor.ServerAccessorInterface#InserisciRisorsa(java.lang.String, java.lang.String, java.lang.String, float, float)
	 */
	@Override
	public boolean InserisciRisorsa(String Titolo, TiporisorsaExport Tipo, AutoreExport Autore, float CostoAcquisto, float CostoNoleggio)
			throws RemoteException {
		ControllerAdmin C = new ControllerAdmin();
		return C.InserisciRisorsa(Titolo, Tipo.getNomeTipoRisorsa(), Autore.getNome(), CostoAcquisto, CostoNoleggio);
	}

}
