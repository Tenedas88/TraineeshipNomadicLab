package DataModel;

import javax.persistence.*;

@Entity
@Table(name = "offerta")
public class Offerta {

	@Id
	@GeneratedValue
	private int idOfferta;

	public Offerta() {
	}

	public int getIdOfferta() {
		return this.idOfferta;
	}

	public void setIdOfferta(int idOfferta) {
		this.idOfferta = idOfferta;
	}

}
