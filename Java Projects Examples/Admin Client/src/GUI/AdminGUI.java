package GUI;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import javax.swing.JButton;
import javax.swing.JFormattedTextField;

import DataModelExport.AutoreExport;
import DataModelExport.TiporisorsaExport;
import ServerAccessor.ServerAccessorAdminInterface;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.rmi.AccessException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;

import javax.swing.JTextField;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JLabel;
import javax.swing.DefaultListModel;

import javax.swing.ListSelectionModel;
import javax.swing.JScrollPane;

public class AdminGUI extends JFrame {
	
	/*
	 * Parametri di Connessione
	 */
	Registry registry;
	ServerAccessorAdminInterface stub;
	
	/*
	 * Parametri di Business Logic
	 */
	ArrayList<TiporisorsaExport> TipoDisponibili;
	boolean response;	

	/*
	 * Parametri GUI
	 */
	private JPanel contentPane;
	private JButton btnNewButton;
	private JTextField txtAutore;
	private JTextField txtTitolo;
	private JFormattedTextField  txtCostoDiAcquisto;
	private JFormattedTextField txtCostoDiNoleggio;
	
	private JList list;
	private DefaultListModel ListaTipi = new DefaultListModel();


	/*
	 * Inizializzazione Connessione JavaRMI
	 */
	public void SetupConnection() throws RemoteException, NotBoundException{
		
		System.setSecurityManager(new SecurityManager());
    	
        registry = LocateRegistry.getRegistry();
        stub = (ServerAccessorAdminInterface) registry.lookup("Admin");
        
        response = false;
        TipoDisponibili = stub.GetTipiDisoponibili();
        if(TipoDisponibili != null){
        	createListaTipi();
        }
	}
	
	public void createListaTipi(){
		for(TiporisorsaExport TRE : TipoDisponibili){
			ListaTipi.addElement(TRE.getNomeTipoRisorsa());
		}
	}
	
	public void InserisciRisorsaGUI(){
        try {        
        	String Titolo = txtTitolo.getText();
        	if(Titolo.equals("") == true) {
        		JOptionPane.showMessageDialog(btnNewButton, "Inserire un Titolo!");
        		return;
        	}
        	
        	AutoreExport Autore = new AutoreExport(txtAutore.getText());
        	if(Autore.getNome().equals("") == true) {
        		JOptionPane.showMessageDialog(btnNewButton, "Inserire un Autore!");
        		return;
        	}
        	
        	if(list.getSelectedIndex() == -1) {
        		JOptionPane.showMessageDialog(btnNewButton, "Selezionare un Tipo!");
        		return;
        	}
        	TiporisorsaExport Tipo = new TiporisorsaExport(TipoDisponibili.get(list.getSelectedIndex()).getNomeTipoRisorsa());
        	
            int CostoAcquisto = ((Number)txtCostoDiAcquisto.getValue()).intValue();
            if(CostoAcquisto <=0) {
            	JOptionPane.showMessageDialog(btnNewButton, "Inserimento Prezzo Acquisto Valido!");
            	return;
            }
            
            int CostoNoleggio = ((Number)txtCostoDiNoleggio.getValue()).intValue();
            if(CostoNoleggio <=0){
            	JOptionPane.showMessageDialog(btnNewButton, "Inserimento Prezzo Noleggio Valido!");
            	return;
            }
            
            response = stub.InserisciRisorsa(Titolo, Tipo,  Autore, CostoAcquisto, CostoNoleggio);
            
            if(response == true){
            	//System.out.println("Inserimento riuscito!");
            	JOptionPane.showMessageDialog(btnNewButton, "Inserimento Riuscito!");
            }
            else{
            	//System.out.println("Risorsa già presente!");
            	JOptionPane.showMessageDialog(btnNewButton, "Errore Inserimento!");	
            }
        } catch (Exception e) {
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
					AdminGUI frame = new AdminGUI();
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
	 * @throws AccessException 
	 */
	public AdminGUI() throws AccessException, RemoteException, NotBoundException {
		setTitle("Inserisci Nuova Risorsa Multimediale");
    	
		SetupConnection();
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		txtTitolo = new JTextField();
		txtTitolo.setBounds(100, 5, 160, 25);
		contentPane.add(txtTitolo);
		txtTitolo.setColumns(10);
		
		txtAutore = new JTextField();
		txtAutore.setBounds(100, 31, 160, 25);
		contentPane.add(txtAutore);
		txtAutore.setColumns(10);
		
		txtCostoDiAcquisto = new JFormattedTextField ();
		txtCostoDiAcquisto.setValue(new Double(0));
		txtCostoDiAcquisto.setBounds(100, 57, 160, 25);
		contentPane.add(txtCostoDiAcquisto);
		txtCostoDiAcquisto.setColumns(10);
		
		txtCostoDiNoleggio = new JFormattedTextField ();
		txtCostoDiNoleggio.setValue(new Double(0));
		txtCostoDiNoleggio.setBounds(100, 83, 160, 25);
		contentPane.add(txtCostoDiNoleggio);
		txtCostoDiNoleggio.setColumns(10);
		
		btnNewButton = new JButton("Inserisci");
		btnNewButton.setBounds(325, 225, 89, 23);
		btnNewButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				InserisciRisorsaGUI();
			}
		});
		contentPane.add(btnNewButton);
		
		JLabel lblNewLabel = new JLabel("Titolo:");
		lblNewLabel.setBounds(5, 10, 46, 15);
		contentPane.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("Autore:");
		lblNewLabel_1.setBounds(5, 36, 46, 14);
		contentPane.add(lblNewLabel_1);
		
		JLabel lblNewLabel_2 = new JLabel("Costo di Acquisto:");
		lblNewLabel_2.setBounds(5, 63, 90, 14);
		contentPane.add(lblNewLabel_2);
		
		JLabel lblCostoDiNoleggio = new JLabel("Costo di Noleggio:");
		lblCostoDiNoleggio.setBounds(5, 88, 90, 14);
		contentPane.add(lblCostoDiNoleggio);
		
		JLabel lblTipo = new JLabel("Tipo:");
		lblTipo.setBounds(22, 158, 46, 14);
		contentPane.add(lblTipo);
		
		list = new JList();
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		list.setModel(ListaTipi);
		list.setBounds(237, 126, 78, 25);

		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setViewportView(list);
		scrollPane.setBounds(106, 126, 100, 74);
		contentPane.add(scrollPane);

	}
}
