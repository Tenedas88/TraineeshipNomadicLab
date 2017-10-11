package DataModel;

import javax.persistence.*;

@Entity
@Table(name = "amministratore")
public class Amministratore{

	@Id
	@GeneratedValue
	private int idAmministratore;
	@Column
	private String email;
	@Column
	private String password;
	

	public Amministratore() {
	}

	public Amministratore(String email, String password) {
		this.email = email;
		this.password = password;
	}

	public int getIdAmministratore() {
		return this.idAmministratore;
	}

	public void setIdAmministratore(int idAmministratore) {
		this.idAmministratore = idAmministratore;
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

}
