package DataModel;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import javax.persistence.*;

import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.NaturalId;
import org.hibernate.annotations.Parameter;

@Entity
@Table(name = "tipoRisorsa")
public class Tiporisorsa {

	@Id
	 @GeneratedValue(generator = "TR_SEQ_GEN")
	 @GenericGenerator(name = "TR_SEQ_GEN", strategy = "org.hibernate.id.enhanced.SequenceStyleGenerator",
	 parameters = {
	 @Parameter(name = "sequence_name", value = "TR_SEQ"),
	 @Parameter(name = "initial_value", value = "1"),
	 @Parameter(name = "increment_size", value = "1") }
	 )
	private int idTipoRisorsa;
	
	@NaturalId
	@Column
	private String nomeTipoRisorsa;
	
    @OneToMany(mappedBy = "tiporisorsaRM")  
    private List<Risorsamultimediale> risorsePerTipo = new ArrayList<>();
    
    @OneToMany(mappedBy = "tiporisorsaPreferenza")  
    private List<Preferenza> preferenzePerTipo = new ArrayList<>();

	public Tiporisorsa() {
	}

	public Tiporisorsa(String nomeTipoRisorsa) {
		this.nomeTipoRisorsa = nomeTipoRisorsa;
	}

	public int getIdTipoRisorsa() {
		return this.idTipoRisorsa;
	}

	public void setIdTipoRisorsa(int idTipoRisorsa) {
		this.idTipoRisorsa = idTipoRisorsa;
	}

	public String getNomeTipoRisorsa() {
		return this.nomeTipoRisorsa;
	}

	public void setNomeTipoRisorsa(String nomeTipoRisorsa) {
		this.nomeTipoRisorsa = nomeTipoRisorsa;
	}

	public List<Risorsamultimediale> getRisorsePerTipo() {
		return risorsePerTipo;
	}

	public void setRisorsePerTipo(List<Risorsamultimediale> risorsePerTipo) {
		this.risorsePerTipo = risorsePerTipo;
	}

	public List<Preferenza> getPreferenzePerTipo() {
		return preferenzePerTipo;
	}

	public void setPreferenzePerTipo(List<Preferenza> preferenzePerTipo) {
		this.preferenzePerTipo = preferenzePerTipo;
	}
	
    @Override
    public boolean equals(Object o) {
        if ( this == o ) {
            return true;
        }
        if ( o == null || getClass() != o.getClass() ) {
            return false;
        }
        Tiporisorsa A = (Tiporisorsa) o;
        return Objects.equals( this.nomeTipoRisorsa, A.nomeTipoRisorsa );
    }

    @Override
    public int hashCode() {
        return Objects.hash( this.nomeTipoRisorsa );
    }

}
