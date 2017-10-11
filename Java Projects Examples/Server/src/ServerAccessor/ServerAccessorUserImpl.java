package ServerAccessor;

import java.rmi.RemoteException;
import java.util.ArrayList;

import BusinessLogic.Controller;
import BusinessLogic.ControllerUser;
import DataModel.Autore;

import DataModel.Tiporisorsa;
import DataModelExport.AutoreExport;
import DataModelExport.PreferenzaExport;
import DataModelExport.TiporisorsaExport;


public class ServerAccessorUserImpl implements ServerAccessorUserInterface {

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
	 * Entity: AutoriExport
	 * @see ServerAccessor.ServerAccessorUserInterface#GetAutoriByTipo(DataModelExport.TiporisorsaExport)
	 */
	@Override
	public ArrayList<AutoreExport> GetAutoriByTipo(TiporisorsaExport TR) throws RemoteException{
		ControllerUser C = new ControllerUser();
		ArrayList<Autore> ALA = C.GetAutoribyTipo(TR.getNomeTipoRisorsa());
		ArrayList<AutoreExport> ALAE = null;
		if(ALA != null){		
			ALAE = new ArrayList<AutoreExport>();
			for(Autore A : ALA){
				ALAE.add(new AutoreExport(A.getNome()));
			}
		}
		return ALAE;
	}

	/*
	 * Entity: PreferenzaExport
	 * @see ServerAccessor.ServerAccessorUserInterface#InserisciPreferenza(DataModelExport.PreferenzaExport, java.lang.String)
	 */
	@Override
	public boolean InserisciPreferenza(PreferenzaExport P, String Email) throws RemoteException {
		ControllerUser C = new ControllerUser();
		return C.InserisciPreferenza(P.getTiporisorsaPreferenza().getNomeTipoRisorsa(),
													P.getAutorePreferenza().getNome(), Email);
	}

}
