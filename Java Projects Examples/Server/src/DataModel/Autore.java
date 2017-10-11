package DataModel;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import javax.persistence.*;

import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.NaturalId;
import org.hibernate.annotations.Parameter;

@Entity
@Table(name = "autore")
public class Autore {

	@Id
	 @GeneratedValue(generator = "A_SEQ_GEN")
	 @GenericGenerator(name = "A_SEQ_GEN", strategy = "org.hibernate.id.enhanced.SequenceStyleGenerator",
	 parameters = {
	 @Parameter(name = "sequence_name", value = "A_SEQ"),
	 @Parameter(name = "initial_value", value = "1"),
	 @Parameter(name = "increment_size", value = "1") }
	 )
	private int idAutore;
	
	@NaturalId
	@Column
	private String nome;

    @OneToMany(mappedBy = "autoreRM")  
    private List<Risorsamultimediale> risorsePerAutore = new ArrayList<>();

    @OneToMany(mappedBy = "autorePreferenza")  
    private List<Preferenza> preferenzePerAutore = new ArrayList<>();

	public Autore() {
	}

	public Autore(String nome) {
		this.nome = nome;
	}

	public int getIdAutore() {
		return this.idAutore;
	}

	public void setIdAutore(int idAutore) {
		this.idAutore = idAutore;
	}

	public String getNome() {
		return this.nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public List<Risorsamultimediale> getRisorsePerAutore() {
		return risorsePerAutore;
	}

	public void setRisorsePerAutore(List<Risorsamultimediale> risorsePerAutore) {
		this.risorsePerAutore = risorsePerAutore;
	}

	public List<Preferenza> getPreferenzePerAutore() {
		return preferenzePerAutore;
	}

	public void setPreferenzePerAutore(List<Preferenza> preferenzePerAutore) {
		this.preferenzePerAutore = preferenzePerAutore;
	}
	
    @Override
    public boolean equals(Object o) {
        if ( this == o ) {
            return true;
        }
        if ( o == null || getClass() != o.getClass() ) {
            return false;
        }
        Autore A = (Autore) o;
        return Objects.equals( this.nome, A.nome );
    }

    @Override
    public int hashCode() {
        return Objects.hash( this.nome );
    }
}
