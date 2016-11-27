package diabeticSemanticNetwork;

public class Facts {

	private String server;
	private String connection;
	private String client;
	
	public String getServer() {
		return server;
	}
	public void setServer(String server) {
		this.server = server;
	}
	public String getConnection() {
		return connection;
	}
	public void setConnection(String connection) {
		this.connection = connection;
	}
	public String getClient() {
		return client;
	}
	public void setClient(String client) {
		this.client = client;
	}
	public boolean checkFact(String server, String connection, String client) {
		if (this.server.equals(server) &&  this.client.equals(client) && this.connection.equals(connection)) {
			return true;
		} else {
			return false;
		}
	}
	public boolean checkServerFromOthers(String connection, String client) {
		if (this.client.equals(client) && this.connection.equals(connection)) {
			return true;
		} else {
			return false;
		}
	}
	
}
