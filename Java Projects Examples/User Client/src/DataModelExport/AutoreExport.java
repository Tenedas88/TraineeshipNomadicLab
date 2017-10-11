package DataModelExport;

public class AutoreExport implements java.io.Serializable{
	
	private static final long serialVersionUID = -3119368884887228511L;
	
	private String nome;
	
	public AutoreExport(String nome){
		this.nome = nome;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

}
