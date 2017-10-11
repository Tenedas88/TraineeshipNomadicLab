package DataModelExport;

public class PreferenzaExport implements java.io.Serializable{
	
	private static final long serialVersionUID = -7141456483250175691L;

	private TiporisorsaExport tiporisorsaPreferenza;
	
	private AutoreExport autorePreferenza;
	
	public PreferenzaExport(TiporisorsaExport TR, AutoreExport A){
		tiporisorsaPreferenza = TR;
		autorePreferenza = A;
	}

	public TiporisorsaExport getTiporisorsaPreferenza() {
		return tiporisorsaPreferenza;
	}

	public void setTiporisorsaPreferenza(TiporisorsaExport tiporisorsaPreferenza) {
		this.tiporisorsaPreferenza = tiporisorsaPreferenza;
	}

	public AutoreExport getAutorePreferenza() {
		return autorePreferenza;
	}

	public void setAutorePreferenza(AutoreExport autorePreferenza) {
		this.autorePreferenza = autorePreferenza;
	}
	
	
	

}
