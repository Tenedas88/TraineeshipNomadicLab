package GUI;

import java.awt.EventQueue;

import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.border.EmptyBorder;

import DataModelExport.AutoreExport;
import DataModelExport.PreferenzaExport;
import DataModelExport.TiporisorsaExport;
import ServerAccessor.ServerAccessorUserInterface;

import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JLabel;
import javax.swing.JButton;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;

public class UserGUI extends JFrame {
	
	/*
	 * Parametri di Connessione
	 */
	Registry registry;
	ServerAccessorUserInterface stub;
	
	/*
	 * Parametri di Business Logic
	 */
	ArrayList<TiporisorsaExport> TipoDisponibili;
	ArrayList<AutoreExport> AutoriPerTipo;
	String TipoSelezionato = null;
	boolean response;
	String email;
	
	JButton btnInserisciPreferenza;

	private JList JlistTipi;
	private DefaultListModel ListaTipi = new DefaultListModel();
	
	private JList JlistAutoriPerTipo;
	private DefaultListModel ListaAutoriPerTipo = new DefaultListModel();
	
	private JPanel contentPane;
	
	/*
	 * Inizializzazione Connessione JavaRMI
	 */
	public void SetupConnection() throws RemoteException, NotBoundException{
		
		System.setSecurityManager(new SecurityManager());
    	
        registry = LocateRegistry.getRegistry();
        stub = (ServerAccessorUserInterface) registry.lookup("User");
        
        response = false;
        email = "email@stub2.psss2";
        TipoDisponibili = stub.GetTipiDisoponibili();
        if(TipoDisponibili != null){
        	createListaTipi();
        }
        AutoriPerTipo = null;
	}
	
	public void createListaTipi(){
		for(TiporisorsaExport TRE : TipoDisponibili){
			ListaTipi.addElement(TRE.getNomeTipoRisorsa());
		}
	}
	
	public void createListaAutoriPerTipo(){
		try{
			TiporisorsaExport TR = new TiporisorsaExport(TipoDisponibili.get(JlistTipi.getSelectedIndex()).getNomeTipoRisorsa());
			AutoriPerTipo = stub.GetAutoriByTipo(TR);
			if(AutoriPerTipo != null){
				ListaAutoriPerTipo.clear();
				for(AutoreExport A : AutoriPerTipo){
					ListaAutoriPerTipo.addElement(A.getNome());
				}
			}
			else{
				ListaAutoriPerTipo.clear();
			}
		}
		catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
	}
	
	public void InserisciPreferenzaGUI() {
		try{
			
			if(JlistTipi.getSelectedIndex() == -1){
				JOptionPane.showMessageDialog(btnInserisciPreferenza, "Seleziona un Tipo!");
				return;
			}
			TiporisorsaExport TR = new TiporisorsaExport(TipoDisponibili.get(JlistTipi.getSelectedIndex()).getNomeTipoRisorsa());
			
			if(JlistAutoriPerTipo.getSelectedIndex() == -1){
				JOptionPane.showMessageDialog(btnInserisciPreferenza, "Seleziona un Autore!");
				return;
			}
			AutoreExport A = new AutoreExport(AutoriPerTipo.get(JlistAutoriPerTipo.getSelectedIndex()).getNome());
			
			PreferenzaExport PE = new PreferenzaExport(TR,A);
			response = stub.InserisciPreferenza(PE, email);
			
            if(response == true){
            	System.out.println("Inserimento riuscito!");
            	JOptionPane.showMessageDialog(btnInserisciPreferenza, "Inserimento Riuscito!");
            }
            else{
            	System.out.println("Inserimento non andato a buon fine!");
            	JOptionPane.showMessageDialog(btnInserisciPreferenza, "Inserimento non andato a buon fine!");	
            }
		}
		catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
        }
	}

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UserGUI frame = new UserGUI();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 * @throws NotBoundException 
	 * @throws RemoteException 
	 */
	public UserGUI() throws RemoteException, NotBoundException {
		setTitle("Inserisci Preferenza");
		
		SetupConnection();
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JlistTipi = new JList();
		JlistTipi.addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent arg0) {
				createListaAutoriPerTipo();
			}
		});
		JlistTipi.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JlistTipi.setModel(ListaTipi);
		JlistTipi.setBounds(82, 183, 49, 35);
		
		JScrollPane scrollPaneTipi = new JScrollPane();
		scrollPaneTipi.setViewportView(JlistTipi);
		scrollPaneTipi.setBounds(51, 29, 111, 130);
		contentPane.add(scrollPaneTipi);
		
		JlistAutoriPerTipo = new JList();
		JlistAutoriPerTipo.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JlistAutoriPerTipo.setModel(ListaAutoriPerTipo);
		JlistAutoriPerTipo.setBounds(82, 183, 49, 35);
		
		JScrollPane scrollPaneAutori = new JScrollPane();
		scrollPaneAutori.setViewportView(JlistAutoriPerTipo);
		scrollPaneAutori.setBounds(213, 29, 111, 130);
		contentPane.add(scrollPaneAutori);
		
		JLabel lblTipo = new JLabel("Tipo:");
		lblTipo.setBounds(86, 11, 32, 14);
		contentPane.add(lblTipo);
		
		JLabel lblAutore = new JLabel("Autore:");
		lblAutore.setBounds(242, 11, 46, 14);
		contentPane.add(lblAutore);
		
		btnInserisciPreferenza = new JButton("Inserisci Preferenza");
		btnInserisciPreferenza.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				InserisciPreferenzaGUI();
			}
		});
		btnInserisciPreferenza.setBounds(114, 198, 151, 23);
		contentPane.add(btnInserisciPreferenza);
		

	}
}
