package DataModelExport;

public class TiporisorsaExport implements java.io.Serializable{
	
	private static final long serialVersionUID = -7816495278301094364L;
	
	private String nomeTipoRisorsa;
	
	public TiporisorsaExport(String nome){
		this.nomeTipoRisorsa = nome;
	}

	public String getNomeTipoRisorsa() {
		return nomeTipoRisorsa;
	}

	public void setNomeTipoRisorsa(String nomeTipoRisorsa) {
		this.nomeTipoRisorsa = nomeTipoRisorsa;
	}

}
