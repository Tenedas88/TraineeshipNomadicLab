package DataModel;

import java.util.Date;
import javax.persistence.*;

@Entity
@Table(name="ordine")
public class Ordine{

	@Id
	@GeneratedValue
	private int idOrdine;
	@Column
	private Date dataOrdine;
	@ManyToOne
	private Risorsamultimediale risorsamultimedialeOrdine;
	@ManyToOne
	private Utente utenteOrdine;


	public Ordine() {
	}

	public Ordine(Date dataOrdine) {
		this.dataOrdine = dataOrdine;
	}

	public int getIdOrdine() {
		return this.idOrdine;
	}

	public void setIdOrdine(int idOrdine) {
		this.idOrdine = idOrdine;
	}
	
	public Date getDataOrdine() {
		return this.dataOrdine;
	}

	public void setDataOrdine(Date dataOrdine) {
		this.dataOrdine = dataOrdine;
	}

	public Risorsamultimediale getRisorsamultimedialeORdine() {
		return this.risorsamultimedialeOrdine;
	}

	public void setRisorsamultimedialeORdine(Risorsamultimediale risorsamultimediale) {
		this.risorsamultimedialeOrdine = risorsamultimediale;
	}

	public Utente getUtenteOrdine() {
		return this.utenteOrdine;
	}

	public void setUtenteOrdine(Utente utente) {
		this.utenteOrdine = utente;
	}

}
