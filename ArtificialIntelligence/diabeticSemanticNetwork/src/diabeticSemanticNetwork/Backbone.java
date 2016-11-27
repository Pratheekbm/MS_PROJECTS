package diabeticSemanticNetwork;

import java.util.ArrayList;
import java.util.List;

public class Backbone {
	private static List<Facts> facts = new ArrayList<>();

	public static void addFact(String server, String connection, String client) {
		Facts tempFact = new Facts();

		tempFact.setServer(server);
		tempFact.setConnection(connection);
		tempFact.setClient(client);

		facts.add(tempFact);
	}

	public static boolean validateFact(String server, String connection, String client) {
		if (connection.equals("isa") || connection.equals("ako")) {
			for (Facts fact : facts) {
				if (true == fact.checkFact(server, connection, client)) {
					return true;
				}
			}
			return false;
		} else if (connection.equals("contains")) {
			for (Facts fact : facts) {
				if (server.equals(fact.getServer())) {
					if (fact.getConnection().equals(connection)) {
						if (fact.getClient().equals(client)) {
							return true;
						}
					} else if (fact.getConnection().equals("ako")) {
						for (Facts localFact : facts) {
							if (fact.getClient().equals(localFact.getServer())) {
								if (localFact.getConnection().equals(connection)) {
									if (localFact.getClient().equals(client)) {
										return true;
									}
								}
							}
						}
					}
				}
			}

			return false;
		} else {
			String badStuff = new String();
			ArrayList<String> containsBadStuff = new ArrayList<>();

			if(null == getFactFromServer(server)) {
				return false;
			}
			
			if (getFactFromServer(server).getConnection().equals(connection)) {
				badStuff = getFactFromServer(server).getClient();
			} else if (getFactFromServer(server).getConnection().equals("isa")) {
				badStuff = getFactFromServer(getFactFromServer(server).getClient()).getClient();
			}

			if (badStuff.equals("")) {
				return false;
			}

			containsBadStuff.add(badStuff);
			containsBadStuff.add(getFactFromClientConnection(containsBadStuff.get(0), "contains").getServer());
			containsBadStuff.add(getFactFromClientConnection(containsBadStuff.get(1), "ako").getServer());

			for (String content : containsBadStuff) {
				if (client.equals(content)) {
					return true;
				}
			}
			return false;
		}
	}

	public static void validateAllFacts(String server, String connection, String client) {
		ArrayList<Facts> allValidFacts = new ArrayList<>();
		ArrayList<String> limbs = new ArrayList<>();
		ArrayList<String> connections = new ArrayList<>();

		for (Facts fact : facts) {
			allValidFacts.add(fact);
		}

		limbs = getAllLimbs();
		connections = getAllConnections();

		for (String limb : limbs) {
			String serv = limb;
			for (String connect : connections) {
				String conn = connect;
				for (String innerLimb : limbs) {
					String clien = innerLimb;
					//System.out.println("MUHA >> " + serv + ' ' + conn + ' ' + clien);
					if (validateFact(serv, conn, clien)) {
						Facts tempFact = new Facts();
						tempFact.setServer(serv);
						tempFact.setConnection(conn);
						tempFact.setClient(clien);
						if (!(checkForDuplicate(allValidFacts, tempFact))) {
							allValidFacts.add(tempFact);
						}
					}
				}
			}
		}

		for (Facts fact : allValidFacts) {
			System.out.println(server + " : " + fact.getServer() );
			System.out.println(connection + " : " + fact.getConnection() );
			System.out.println(client + " : " + fact.getClient() );
			System.out.println();
		}
	}

	private static boolean checkForDuplicate(ArrayList<Facts> allValidFacts, Facts tempFact) {
		for (Facts fact : allValidFacts) {
			String serv = fact.getServer();
			String clien = fact.getClient();
			String conn = fact.getConnection();
			
			if (clien.equals(tempFact.getClient()) && conn.equals(tempFact.getConnection())
					&& serv.equals(tempFact.getServer())) {
				return true;
			}
		}
		return false;
	}

	private static ArrayList<String> getAllLimbs() {
		ArrayList<String> limbs = new ArrayList<>();

		for (Facts fact : facts) {
			limbs.add(fact.getServer());
			limbs.add(fact.getClient());
		}
		return limbs;
	}

	private static ArrayList<String> getAllConnections() {
		ArrayList<String> connections = new ArrayList<>();

		for (Facts fact : facts) {
			connections.add(fact.getConnection());
		}
		return connections;
	}

	private static Facts getFactFromServer(String server) {
		for (Facts fact : facts) {
			if (server.equals(fact.getServer())) {
				return fact;
			}
		}
		return null;
	}

	private static Facts getFactFromClientConnection(String client, String connection) {
		for (Facts fact : facts) {
			if (client.equals(fact.getClient()) && connection.equals(fact.getConnection())) {
				return fact;
			}
		}
		return null;
	}
}
