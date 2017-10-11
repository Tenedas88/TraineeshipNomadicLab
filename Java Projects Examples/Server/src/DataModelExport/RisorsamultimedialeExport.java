package DataModelExport;

public class RisorsamultimedialeExport implements java.io.Serializable {
	
	private static final long serialVersionUID = -2928655064502691297L;

	private String titolo;
	
	private float costoAcquisto;
	
	private float costoNoleggio;
	
	private AutoreExport autoreRM;
	
	private TiporisorsaExport tiporisorsaRM;
	
	public RisorsamultimedialeExport(String Titolo, TiporisorsaExport TR, AutoreExport A, float CostoA, float CostoN){
		this.titolo = Titolo;
		this.tiporisorsaRM = TR;
		this.autoreRM = A;
		this.costoAcquisto = CostoA;
		this.costoNoleggio = CostoN;
	}

	public String getTitolo() {
		return titolo;
	}

	public void setTitolo(String titolo) {
		this.titolo = titolo;
	}

	public float getCostoAcquisto() {
		return costoAcquisto;
	}

	public void setCostoAcquisto(float costoAcquisto) {
		this.costoAcquisto = costoAcquisto;
	}

	public float getCostoNoleggio() {
		return costoNoleggio;
	}

	public void setCostoNoleggio(float costoNoleggio) {
		this.costoNoleggio = costoNoleggio;
	}

	public AutoreExport getAutoreRM() {
		return autoreRM;
	}

	public void setAutoreRM(AutoreExport autoreRM) {
		this.autoreRM = autoreRM;
	}

	public TiporisorsaExport getTiporisorsaRM() {
		return tiporisorsaRM;
	}

	public void setTiporisorsaRM(TiporisorsaExport tiporisorsaRM) {
		this.tiporisorsaRM = tiporisorsaRM;
	}
	
	

}
