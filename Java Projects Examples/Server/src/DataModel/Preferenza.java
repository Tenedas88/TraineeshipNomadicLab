package DataModel;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import javax.persistence.*;

import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.Parameter;

@Entity
@Table(name = "preferenza")
public class Preferenza {

	@Id
	 @GeneratedValue(generator = "P_SEQ_GEN")
	 @GenericGenerator(name = "P_SEQ_GEN", strategy = "org.hibernate.id.enhanced.SequenceStyleGenerator",
	 parameters = {
	 @Parameter(name = "sequence_name", value = "P_SEQ"),
	 @Parameter(name = "initial_value", value = "1"),
	 @Parameter(name = "increment_size", value = "1") }
	 )
	@Column(name = "idPreferenza")
	private int idPreferenza;
	
    @ManyToOne
    @JoinColumn(name = "idAutore")
	private Autore autorePreferenza;
    
	@ManyToOne
	@JoinColumn(name = "idTipoRisorsa")
	private Tiporisorsa tiporisorsaPreferenza;
	
	@ManyToMany(fetch = FetchType.EAGER)
	@JoinTable(name = "preferenza_utente", 
    joinColumns = { @JoinColumn(name = "idPreferenza") }, 
    inverseJoinColumns = { @JoinColumn(name = "idUtente") })
	private List<Utente> utentiPerPreferenza = new ArrayList<>();

	public Preferenza() {
	}

	public Preferenza(Autore autore, Tiporisorsa tiporisorsa) {
		this.autorePreferenza = autore;
		this.tiporisorsaPreferenza = tiporisorsa;
	}


	public int getIdPreferenza() {
		return this.idPreferenza;
	}

	public void setIdPreferenza(int idPreferenza) {
		this.idPreferenza = idPreferenza;
	}

	public Autore getAutore() {
		return this.autorePreferenza;
	}

	public void setAutore(Autore autore) {
		this.autorePreferenza = autore;
	}

	public Tiporisorsa getTiporisorsa() {
		return this.tiporisorsaPreferenza;
	}

	public void setTiporisorsa(Tiporisorsa tiporisorsa) {
		this.tiporisorsaPreferenza = tiporisorsa;
	}
	
    public List<Utente> getUtentiPerPreferenza() {
		return utentiPerPreferenza;
	}

	public void setUtentiPerPreferenza(List<Utente> utentiPerPreferenza) {
		this.utentiPerPreferenza = utentiPerPreferenza;
	}

	@Override
    public boolean equals(Object o) {
        if ( this == o ) {
            return true;
        }
        if ( o == null || getClass() != o.getClass() ) {
            return false;
        }
        Preferenza P = (Preferenza) o;
        return Objects.equals( this.idPreferenza, P.idPreferenza);
    }

    @Override
    public int hashCode() {
        return Objects.hash( this.idPreferenza );
    }

}
