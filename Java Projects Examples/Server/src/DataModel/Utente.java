package DataModel;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import javax.persistence.*;

import org.hibernate.annotations.Cascade;
import org.hibernate.annotations.GenericGenerator;
import org.hibernate.annotations.NaturalId;
import org.hibernate.annotations.Parameter;

@Entity
@Table(name = "utente")
public class Utente{

	@Id
	 @GeneratedValue(generator = "U_SEQ_GEN")
	 @GenericGenerator(name = "U_SEQ_GEN", strategy = "org.hibernate.id.enhanced.SequenceStyleGenerator",
	 parameters = {
	 @Parameter(name = "sequence_name", value = "U_SEQ"),
	 @Parameter(name = "initial_value", value = "1"),
	 @Parameter(name = "increment_size", value = "1") }
	 )
	@Column(name = "idUtente")
	private int idUtente;
	
	@Column
	private String nome;
	
	@Column
	private String cognome;
	
	@NaturalId
	@Column
	private String email;
	
	@Column
	private String password;
	
	@ManyToMany(fetch = FetchType.EAGER, mappedBy = "utentiPerPreferenza")
    @Cascade(value={org.hibernate.annotations.CascadeType.ALL})
	private List<Preferenza> preferenzePerUtente = new ArrayList<>();
	
	@OneToMany(mappedBy = "utenteOrdine")
	private List<Ordine> ordiniPerUtente = new ArrayList<>();

	public Utente() {
	}

	public Utente(String nome, String cognome, String email, String password) {
		this.nome = nome;
		this.cognome = cognome;
		this.email = email;
		this.password = password;
	}

	public int getIdUtente() {
		return this.idUtente;
	}

	public void setIdUtente(int idUtente) {
		this.idUtente = idUtente;
	}

	public String getNome() {
		return this.nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getCognome() {
		return this.cognome;
	}

	public void setCognome(String cognome) {
		this.cognome = cognome;
	}

	public String getEmail() {
		return this.email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getPassword() {
		return this.password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public List<Ordine> getOrdiniPerUtente() {
		return this.ordiniPerUtente;
	}

	public void setOrdiniPerUtente(ArrayList<Ordine> ordini) {
		this.ordiniPerUtente = ordini;
	}

	public List<Preferenza> getPreferenzePerUtente() {
		return this.preferenzePerUtente;
	}

	public void setPreferenzePerUtente(ArrayList<Preferenza> preferenze) {
		this.preferenzePerUtente = preferenze;
	}
	
	@Override
    public boolean equals(Object o) {
        if ( this == o ) {
            return true;
        }
        if ( o == null || getClass() != o.getClass() ) {
            return false;
        }
        Utente U = (Utente) o;
        return Objects.equals( this.idUtente, U.idUtente);
    }

    @Override
    public int hashCode() {
        return Objects.hash( this.idUtente );
    }

}
