package DataModel;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Objects;

import javax.persistence.*;
import javax.persistence.Entity;
import javax.persistence.Table;

import org.hibernate.annotations.*;
import org.hibernate.annotations.Parameter;


@Entity
@Table(name = "risorsaMultimediale")
public class Risorsamultimediale{

	@Id
	 @GeneratedValue(generator = "RM_SEQ_GEN")
	 @GenericGenerator(name = "RM_SEQ_GEN", strategy = "org.hibernate.id.enhanced.SequenceStyleGenerator",
	 parameters = {
	 @Parameter(name = "sequence_name", value = "RM_SEQ"),
	 @Parameter(name = "initial_value", value = "1"),
	 @Parameter(name = "increment_size", value = "1") }
	 )
	private int idRisorsaMultimediale;
	
	@Column
	private String titolo;
	
	@Column
	private Date dataPubblicazione;
	
	@Column
	private float costoAcquisto;
	
	@Column
	private float costoNoleggio;
	
    @ManyToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "idAutore")
    @Cascade(value={org.hibernate.annotations.CascadeType.ALL})
	private Autore autoreRM;
    
	@ManyToOne(fetch = FetchType.EAGER)
	@JoinColumn(name = "idTipoRisorsa")
    private Tiporisorsa tiporisorsaRM;
	
	@OneToMany(mappedBy = "risorsamultimedialeOrdine")
	private List<Ordine> ordiniPerRisorsa = new ArrayList<>();

	public Risorsamultimediale() {
	}

	public Risorsamultimediale(Autore autore, Tiporisorsa tiporisorsa, String titolo,
			Date dataPubblicazione, float costoAcquisto, float costoNoleggio) {		
		this.autoreRM = autore;
		this.tiporisorsaRM = tiporisorsa;
		this.titolo = titolo;
		this.dataPubblicazione = dataPubblicazione;
		this.costoAcquisto = costoAcquisto;
		this.costoNoleggio = costoNoleggio;
	}

	public int getIdRisorsaMultimediale() {
		return this.idRisorsaMultimediale;
	}

	public void setIdRisorsaMultimediale(int idRisorsaMultimediale) {
		this.idRisorsaMultimediale = idRisorsaMultimediale;
	}

	public String getTitolo() {
		return this.titolo;
	}

	public void setTitolo(String titolo) {
		this.titolo = titolo;
	}

	public Date getDataPubblicazione() {
		return this.dataPubblicazione;
	}

	public void setDataPubblicazione(Date dataPubblicazione) {
		this.dataPubblicazione = dataPubblicazione;
	}

	public float getCostoAcquisto() {
		return this.costoAcquisto;
	}

	public void setCostoAcquisto(float costoAcquisto) {
		this.costoAcquisto = costoAcquisto;
	}

	public float getCostoNoleggio() {
		return this.costoNoleggio;
	}

	public void setCostoNoleggio(float costoNoleggio) {
		this.costoNoleggio = costoNoleggio;
	}

	public Autore getAutore() {
		return this.autoreRM;
	}

	public void setAutore(Autore autore) {
		this.autoreRM = autore;
	}

	public Tiporisorsa getTiporisorsa() {
		return this.tiporisorsaRM;
	}

	public void setTiporisorsa(Tiporisorsa tiporisorsa) {
		this.tiporisorsaRM = tiporisorsa;
	}
	
    @Override
    public boolean equals(Object o) {
        if ( this == o ) {
            return true;
        }
        if ( o == null || getClass() != o.getClass() ) {
            return false;
        }
        Risorsamultimediale RM = (Risorsamultimediale) o;
        return Objects.equals( this.titolo, RM.titolo);
    }

    @Override
    public int hashCode() {
        return Objects.hash( this.titolo );
    }	
}
