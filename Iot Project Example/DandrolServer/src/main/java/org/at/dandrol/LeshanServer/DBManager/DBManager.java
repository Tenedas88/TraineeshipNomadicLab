package org.at.dandrol.LeshanServer.DBManager;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Properties;

import org.at.dandrol.LeshanServer.rules.model.Condition;
import org.at.dandrol.LeshanServer.rules.model.Rule;

public class DBManager {

	private static DBManager instance;

	private Properties dbProperties = new Properties();
	private InputStream input = null;
	private String dbURL;
	private String dbUser;
	private String dbPassword;
	private String dbDriver;
	private Connection conn;

	private DBManager(){

		try {
			input = new FileInputStream("config\\db_config.properties");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// load a properties file
		try {
			dbProperties.load(input);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// get the property value and print it out
		dbURL = dbProperties.getProperty("url");
		dbUser = dbProperties.getProperty("user");
		dbPassword = dbProperties.getProperty("password");
		dbDriver = dbProperties.getProperty("driverclass");

		// Register JDBC driver
		try{

			Class.forName(dbDriver).newInstance();

			// Open a connection
			conn = DriverManager.getConnection(dbURL, dbUser, dbPassword);
		}
		catch(Exception e){
			e.printStackTrace();
		}

	}

	public synchronized static DBManager getInstance(){

		if(instance == null)
			instance = new DBManager();

		return instance;

	}

	public ArrayList<Rule> loadAlarms(){

		ArrayList<Rule> storedAlarms = new ArrayList<Rule>();


		String query = "SELECT * FROM ALARM;";
		try{
			PreparedStatement pstmt = conn.prepareStatement( query );
			ResultSet result = pstmt.executeQuery();


			Integer alarmID;
			while (result.next()) {
				ArrayList<Condition> conditions = new ArrayList<Condition>();
				alarmID = result.getInt(result.findColumn("alarm_ID"));

				String conditionQuery = "SELECT * FROM ALARM_CONDITION WHERE alarm_ID  = ?";
				PreparedStatement conditionPstmt = conn.prepareStatement( conditionQuery );
				conditionPstmt.setInt(1, alarmID); 
				ResultSet conditionResult = conditionPstmt.executeQuery();

				while(conditionResult.next())
					conditions.add(extractCondition(conditionResult));	

				storedAlarms.add(new Rule(alarmID, conditions));
			}

		}catch(SQLException e){
			e.printStackTrace();
		}

		return storedAlarms;

	}

	public ArrayList<Rule> loadAutomations(){

		ArrayList<Rule> storedAutomations = new ArrayList<Rule>();

		try{	
			String query = "SELECT * FROM AUTOMATION;";
			PreparedStatement pstmt = conn.prepareStatement( query );
			ResultSet result = pstmt.executeQuery();

			Integer automationID;
			while (result.next()) {

				ArrayList<Condition> conditions = new ArrayList<Condition>();
				automationID = result.getInt(result.findColumn("automation_ID"));

				String conditionQuery = "SELECT * FROM AUTOMATION_CONDITION WHERE automation_ID  = ?";

				PreparedStatement conditionPstmt = conn.prepareStatement( conditionQuery );
				conditionPstmt.setInt(1, automationID); 

				ResultSet conditionResult = conditionPstmt.executeQuery();

				while(conditionResult.next())
					conditions.add(extractCondition(conditionResult));	

				String actionEndpoint = result.getString(result.findColumn("action_endpoint"));
				String actionTarget = result.getString(result.findColumn("action_target"));

				storedAutomations.add(new Rule(automationID, conditions, actionEndpoint, actionTarget));
			}
		}catch(SQLException e){
			e.printStackTrace();
		}
		
		return storedAutomations;
	}

	private Condition extractCondition(ResultSet result){

		String srcEndpoint;
		String srcTarget;
		String operator;
		Double value;
		String catOperator;


		try {
			srcEndpoint = result.getString(result.findColumn("src_endpoint"));
			srcTarget = result.getString(result.findColumn("src_target"));
			operator = result.getString(result.findColumn("operator"));
			value = result.getDouble(result.findColumn("value"));
			catOperator = result.getString(result.findColumn("cat_operator"));

			return new Condition(srcEndpoint, srcTarget, operator, value, catOperator);

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}




}
