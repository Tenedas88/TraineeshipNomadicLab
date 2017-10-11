package DataAccessor;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;
import java.util.ListIterator;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import DataModel.Autore;
import DataModel.Preferenza;
import DataModel.Risorsamultimediale;
import DataModel.Tiporisorsa;
import DataModel.Utente;

public class DataAccessorHibernateImpl implements DataInterface {
	
	public static SessionFactory factory;  //Public Solo PER Testing

	/*
	 * Inizializzazione Facade
	 * @see DataAccessor.DataInterface#init()
	 */
	@Override
	public void init() {
		if(factory == null){
			factory = new Configuration().configure().buildSessionFactory();
		}
		
		/*****Inserimento Dati STUB*****/
		
		Session S = DataAccessorHibernateImpl.factory.openSession();
		Transaction tx = null;
		
		try {
			tx = S.beginTransaction();
			
			/************************Inserimento Dati STUB*****/
			
			Utente U = new Utente("Domenico","Amalfitano","email@stub.psss","psss");
			S.save(U);
			
			Utente U1 = new Utente("Davide","Piscopo","email@stub2.psss2","psss2");
			S.save(U1);
			
			Utente U2 = new Utente("Rolando", "Silvestro", "email@stub3.psss3", "30elode");
			S.save(U2);
			
			Utente U3 = new Utente("Cristiano", "Maritn", "email@stub4.psss4","matchmakinginfame");
			S.save(U3);
			
			/************************Inserimento Dati STUB*****/
			
			/**********************JUNIT TEST*****************/
			
			/*Autore A = new Autore("JunitAutoreEsistente");
			S.save(A);
			
			Autore A1 = new Autore("JunitAutoreEsistenteNoRisorsa");
			S.save(A1);
			
			Tiporisorsa TR = new Tiporisorsa("JunitTipoEsistente");
			S.save(TR);
			
			Tiporisorsa TR1 = new Tiporisorsa("JunitTipoEsistenteNoAutori");
			S.save(TR1);
			
			Risorsamultimediale RM = new Risorsamultimediale(A,TR,"JunitRisorsa",new Date(),5,5);
			S.save(RM);
			
			Preferenza P = new Preferenza(A,TR);
			U.getPreferenzePerUtente().add(P);
			P.getUtentiPerPreferenza().add(U);
			S.saveOrUpdate(U);
			S.saveOrUpdate(P);*/
			
			/**********************JUNIT TEST***************/
			
			S.flush();
			tx.commit();
		} catch(HibernateException e) {
			if(tx != null) {
				tx.rollback();
				e.printStackTrace();
			}
		} finally {
			S.close();

		}
		/*******************Fine Dati STUB*****************/
	}

	/************************************************TIPORISORSA**********************************/
	
	/*
	 * Entity: Tiporisorsa
	 * @see DataAccessor.DataInterface#persistTiporisorsa(DataModel.Tiporisorsa)
	 */
	@Override
	public boolean persistTiporisorsa(Tiporisorsa Tipo){	
		boolean Success = false;
		Session S = factory.openSession();
		Transaction tx = null;
		try{
			tx = S.beginTransaction();
			S.save(Tipo);
			S.flush();
			tx.commit();
			Success = true;
		}catch(HibernateException e){
			if(tx != null){
				e.printStackTrace();
				tx.rollback();
			}
		}
		finally{
			S.close();
		}
		return Success;
	}
	
	/*
	 * Entity: Tiporisorsa
	 * @see DataAccessor.DataInterface#getTipiRisorsaAll()
	 */
	@Override
	public ArrayList<Tiporisorsa> getTipiRisorsaAll() throws HibernateException{
		Session S = factory.openSession();
		ArrayList<Tiporisorsa> ATR = null;
		try{
		ATR = (ArrayList<Tiporisorsa>)S.createQuery("from Tiporisorsa").list();
		}
		catch(HibernateException e){
			e.printStackTrace();
		}
		finally{
		S.close();
		}
		return ATR;
	}
	
	/*
	 * Entity: Tiporisorsa
	 * @see DataAccessor.DataInterface#getTipoRisorsa(java.lang.String)
	 */
	@Override
	public Tiporisorsa getTipoRisorsaifExist(String tipo) throws HibernateException { 
		Session S = factory.openSession();
		try{
			Tiporisorsa TR = S.byNaturalId(Tiporisorsa.class).using("nomeTipoRisorsa", tipo).load();
			if(TR != null){
				S.close();
				return TR;
			}
			else{
				S.close();
				return null;
			}
				
		}
		catch(HibernateException e){
			e.printStackTrace();
			S.close();
			return null;
		}		
		
	}
	
	/************************************************AUTORE**********************************/
	
	/*
	 * Entity: Autore
	 * @see DataAccessor.DataInterface#getAutoriAll()
	 */
	/*@Override
	public ArrayList<Autore> getAutoriAll() {
		Session S = factory.openSession();
		ArrayList<Autore> AA = null;
		try{
		AA = (ArrayList<Autore>)S.createQuery("from Autore").list();
		}
		catch(HibernateException e){
			e.printStackTrace();
		}
		finally{
		S.close();
		}
		return AA;
	}*/

	/*
	 * Entity: Autore
	 * @see DataAccessor.DataInterface#getAutoreByNameifExist(java.lang.String)
	 */
	@Override
	public Autore getAutoreByNameifExist(String name) throws HibernateException {
		Session S = factory.openSession();
		try{
			Autore A = S.byNaturalId(Autore.class).using("nome", name).load();
			if(A != null){
				S.close();
				return A;
			}
			else{
				S.close();
				return null;
			}
				
		}
		catch(HibernateException e){
			e.printStackTrace();
			S.close();
			return null;
		}
	}
	
	/*
	 * Entity: Autore
	 * @see DataAccessor.DataInterface#getAutoruByTipo(DataModel.Tiporisorsa)
	 */
	@Override
	public ArrayList<Autore> getAutoruByTipo(Tiporisorsa TR){
		Session S = factory.openSession();
		try{
			ArrayList<Risorsamultimediale> ARM = (ArrayList<Risorsamultimediale>)
					S.createQuery("select R from Risorsamultimediale R join R.tiporisorsaRM where R.tiporisorsaRM = :tipo").setEntity("tipo",TR).list();
			ArrayList<Autore> ALA = new ArrayList<Autore>();
			for(Risorsamultimediale RM : ARM){
				if(ALA.contains(RM.getAutore()) == false){
					ALA.add(RM.getAutore());
				}
			}
			if(ALA.size() > 0 ){
				S.close();
				return ALA;
			}
			else{
				S.close();
				return null;
			}
				
		}
		catch(HibernateException e){
			e.printStackTrace();
			S.close();
			return null;
		}	
		
	}
	
	/*********************************************RISORSAMULTIMEDIALE**********************************/
	
	/*
	 * Entity: Risorsamultimediale
	 * @see DataAccessor.DataInterface#persistRisorsaMultimediale(DataModel.Risorsamultimediale)
	 */
	@Override
	public boolean persistRisorsaMultimediale(Risorsamultimediale risorsamultimediale) throws HibernateException{
			Session S = factory.openSession();
			Transaction tx = null;
			try{
				tx = S.beginTransaction();
				S.save(risorsamultimediale);
				S.flush();
				tx.commit();
			}catch(HibernateException e){
				if(tx != null){
					e.printStackTrace();
					tx.rollback();
				}
				return false;
			}
			finally{
				S.close();
			}
			return true;
			
	}

	/*
	 * Entity: Risorsamultimediale
	 * @see DataAccessor.DataInterface#getRisorsemultimedialiByAutore(DataModel.Autore)
	 */
	@Override
	public ArrayList<Risorsamultimediale> getRisorsemultimedialiByAutore(Autore autore) throws HibernateException{
		if(autore != null){
			Session S = factory.openSession();
			try{
				ArrayList<Risorsamultimediale> RM = (ArrayList<Risorsamultimediale>)
						S.createQuery("select R from Risorsamultimediale R join R.autoreRM where R.autoreRM = :autore").setEntity("autore", autore).list();
				if(RM != null){
					S.close();
					return RM;
				}
				else{
					S.close();
					return null;
				}
					
			}
			catch(HibernateException e){
				e.printStackTrace();
				S.close();
				return null;
			}
		}
		else{
			return null;
		}
	}

	/*********************************************PREFERENZA**********************************/
	
	/*
	 * Entity: Preferenza
	 * @see DataAccessor.DataInterface#persistPreferenza(DataModel.Preferenza)
	 */
	@Override
	public boolean persistPreferenza(Preferenza preferenza) {
		
		boolean Success = false;
		Session S = factory.openSession();
		Transaction tx = null;
		try{
			tx = S.beginTransaction();
			/*try{
			Preferenza pref = (Preferenza)S.createQuery("Select P From Preferenza P with P:=preferenza").setEntity("preferenza", preferenza).uniqueResult();
			}
			catch(HibernateException e){
				S.saveOrUpdate(preferenza);
			}*/
			S.saveOrUpdate(preferenza);
			S.flush();
			tx.commit();
			Success = true;
		}catch(HibernateException e){
			if(tx != null){
				e.printStackTrace();
				tx.rollback();
			}
			Success = false;
		}
		finally{
			S.close();
		}
		return Success;
	}
	
	/*
	 * Entity: Preferenza
	 * @see DataAccessor.DataInterface#getPreferenzaifExist(DataModel.Tiporisorsa, DataModel.Autore)
	 */
	@Override
	public Preferenza getPreferenzaifExist(Tiporisorsa TR, Autore A) throws HibernateException{
		Preferenza P = null;
		Session S = factory.openSession();
		try{
			P = (Preferenza)
					S.createQuery("select P from Preferenza P join P.autorePreferenza where P.autorePreferenza = :autore and P.tiporisorsaPreferenza = :tipo").setEntity("autore", A).setEntity("tipo",TR).uniqueResult();	
		}
		catch(HibernateException e){
			e.printStackTrace();
		}		
		finally{
			S.close();
		}
		return P;
	}

	/*
	 * Entity: Preferenza
	 * @see DataAccessor.DataInterface#getPreferenzeByAutore(DataModel.Autore)
	 */
	/*@Override
	public ArrayList<Preferenza> getPreferenzeByAutore(Autore autore) throws HibernateException{
		Session S = factory.openSession();
		try{
			ArrayList<Preferenza> P = (ArrayList<Preferenza>)
					S.createQuery("select P from Preferenza P join P.autorePreferenza where P.autorePreferenza = :autore").setEntity("autore", autore).list();
			if(P != null){
				S.close();
				return P;
			}
			else{
				S.close();
				return null;
			}
				
		}
		catch(HibernateException e){
			e.printStackTrace();
			S.close();
			return null;
		}
	}*/
	
	/*********************************************UTENTE**********************************/
	
	/*
	 * Entity: Utente
	 * @see DataAccessor.DataInterface#getUtentebyEmail(java.lang.String)
	 */
	@Override
	public Utente getUtentebyEmail(String email){
		Session S = factory.openSession();
		try{
			Utente U = S.byNaturalId(Utente.class).using("email", email).load();
			if(U != null){
				S.close();
				return U;
			}
			else{
				S.close();
				return null;
			}
				
		}
		catch(HibernateException e){
			e.printStackTrace();
			S.close();
			return null;
		}		
	}

	/*
	 * Entity: Utente
	 * @see DataAccessor.DataInterface#getUtentiByPreferenza(DataModel.Preferenza)
	 */
	@Override
	public ArrayList<Utente> getUtentiByPreferenza(Preferenza preferenza) throws HibernateException{
		ArrayList<Utente> AUP = null;
		if(preferenza != null){
			Session S = factory.openSession();
			Transaction tx = null;
			try{
				tx = S.beginTransaction();
	
				AUP = (ArrayList<Utente>) 
						//S.createQuery("Select U FROM Utente U left join U.preferenzePerUtente as P with P=:pref").setEntity("pref", preferenza).list();
						S.createQuery("Select U FROM Utente U left join U.preferenzePerUtente as P where P=:pref").setEntity("pref", preferenza).list();
				tx.commit();
			}
			catch(HibernateException e){
				e.printStackTrace();
				tx.rollback();
			}
			finally{
				S.close();
			}
		}
		return AUP;
	}



}
