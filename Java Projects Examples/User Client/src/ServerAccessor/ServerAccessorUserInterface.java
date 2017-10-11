package ServerAccessor;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;

import DataModelExport.AutoreExport;
import DataModelExport.PreferenzaExport;
import DataModelExport.TiporisorsaExport;

public interface ServerAccessorUserInterface extends Remote {
	
	public ArrayList<TiporisorsaExport> GetTipiDisoponibili() throws RemoteException;
	
	public ArrayList<AutoreExport> GetAutoriByTipo(TiporisorsaExport TR) throws RemoteException;
	
	public boolean InserisciPreferenza(PreferenzaExport P, String Email) throws RemoteException;

}
