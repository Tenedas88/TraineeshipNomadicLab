package ServerAccessor;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

import DataModelExport.AutoreExport;
import DataModelExport.TiporisorsaExport;



public interface ServerAccessorAdminInterface extends Remote {
	
	public ArrayList<TiporisorsaExport> GetTipiDisoponibili() throws RemoteException;
	
	public boolean InserisciRisorsa
	//(String Titolo, String Tipo, String Autore, float CostoAcquisto, float CostoNoleggio)
	(String Titolo, TiporisorsaExport Tipo, AutoreExport Autore, float CostoAcquisto, float CostoNoleggio)
			throws RemoteException;

}
