package SearchUSA;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;

public class SearchUSA {

	private static HashMap<String, Integer> cityNumber = new HashMap<String, Integer>();
	private static HashMap<Integer, String> cityName = new HashMap<Integer, String>();
	private static double[][] cityConnectionMatrix;
	private static int numberOfCitiesInTheMap;
	private static CityData[] cityDataBase;
	private static int[] visitedCity;
	private static double[] currentMinDistanceFromSource;
	private static List<String> citiesExpanded = new ArrayList<>();

	public static void main(String[] args) {
		createMap();
		String sourceCity = args[1];
		String destinationCity = args[2];
		String searchType = args[0];
		
		Paths path = SearchAlgos.search(sourceCity, destinationCity, searchType);
		System.out.println(searchType + sourceCity + destinationCity);
		System.out.println("Source :" + sourceCity + " Destination : " + destinationCity);
		System.out.println("Cities Expanded are:");
		printCitiesExpanded();
		System.out.println("\nNumber of noded Expanded      : " + citiesExpanded.size());
		path.printCitiesInPath();
		
		/*for (int i = 0; i < numberOfCitiesInTheMap - 1; i ++) {
			for (int j = 0; j < numberOfCitiesInTheMap - 1; j ++) {
				Paths path = SearchAlgos.search(cityName.get(i), cityName.get(j), "astar");
				System.out.println("astar");
				System.out.println("Source :" + cityName.get(i) + " Destination : " + cityName.get(j));
				System.out.println("Cities Expanded are:");
				printCitiesExpanded();
				System.out.println("\nNumber of noded Expanded      : " + citiesExpanded.size());
				path.printCitiesInPath();
				resetVisited();
				
				path = SearchAlgos.search(cityName.get(i), cityName.get(j), "greedy");
				System.out.println("greedy");
				System.out.println("Source :" + cityName.get(i) + " Destination : " + cityName.get(j));
				System.out.println("Cities Expanded are:");
				printCitiesExpanded();
				System.out.println("\nNumber of noded Expanded      : " + citiesExpanded.size());
				path.printCitiesInPath();
				resetVisited();
			}
		}*/
	}

	public static void resetVisited () {
		for (int i = 0; i < numberOfCitiesInTheMap; i ++) {
			visitedCity[i] = 0;
			currentMinDistanceFromSource[i] = 0;
		}
		for (int i = citiesExpanded.size() - 1; i >= 0; i--) {
			citiesExpanded.remove(i);
		}
		
		
	}
	
	public static List<String> getCitiesExpanded() {
		return citiesExpanded;
	}

	public static void addCityToCitiesExpanded(String city) {
		citiesExpanded.add(city);
	}

	public static void printCitiesExpanded() {
		int numberOfCities = citiesExpanded.size();
		for (int i = 0; i < numberOfCities; i++) {
			System.out.printf(citiesExpanded.get(i) + ", ");
		}
	}

	public static int getNumberOfCitiesInTheMap() {
		return numberOfCitiesInTheMap;
	}

	public static CityData getCityDataFromCity(String city) {
		return cityDataBase[cityNumber.get(city)];
	}

	public static CityData getCityDataFromCityIndex(int city) {
		return cityDataBase[city];
	}

	public static boolean checkAdjacency(int cityIndex1, int cityIndex2) {
		if (0 == cityConnectionMatrix[cityIndex1][cityIndex2]) {
			return false;
		} else {
			return true;
		}
	}

	public static void markCityVisited(String city) {
		visitedCity[cityNumber.get(city)] = 1;
	}

	public static boolean checkIfCityIsVisited(String city) {
		if (1 == visitedCity[cityNumber.get(city)]) {
			return true;
		} else {
			return false;
		}
	}

	public static void setCurrentMinDistanceFromSource(String city, double distance) {
		currentMinDistanceFromSource[cityNumber.get(city)] = distance;
	}

	public static double getCurrentMinDistanceFromSource(String city) {
		return currentMinDistanceFromSource[cityNumber.get(city)];
	}

	public static double getPathCostBetweenAdjCities(String city1, String city2) {
		double pathCost = cityConnectionMatrix[cityNumber.get(city1)][cityNumber.get(city2)];
		if (0 == pathCost) {
			if (city1 == city2) {
				return 0;
			} else {
				return -1;
			}
		} else {
			return pathCost;
		}
	}

	public static double getHeuristic(String city1, String city2) {
		int city1Index = cityNumber.get(city1);
		int city2Index = cityNumber.get(city2);
		double heuristic = 0;
		double lat1 = cityDataBase[city1Index].getLattitude();
		double long1 = cityDataBase[city1Index].getLongitude();
		double lat2 = cityDataBase[city2Index].getLattitude();
		double long2 = cityDataBase[city2Index].getLongitude();

		/*
		 * sqrt( (69.5 * (Lat1 - Lat2)) ^ 2 + (69.5 * cos((Lat1 + Lat2)/360 *
		 * pi) * (Long1 - Long2)) ^ 2 )
		 */
		heuristic = Math.sqrt(Math.pow((69.5 * (lat1 - lat2)), 2)
				+ Math.pow((69.5 * Math.cos((lat1 + lat2) / 360 * Math.PI) * (long1 - long2)), 2));

		return heuristic;
	}

	public static void createMap() {
		// hash table mapping form string to number
		createCityHashMap();
		numberOfCitiesInTheMap = cityNumber.size();

		// Initializing Connection Matrix
		cityConnectionMatrix = new double[numberOfCitiesInTheMap][numberOfCitiesInTheMap];
		visitedCity = new int[numberOfCitiesInTheMap];
		currentMinDistanceFromSource = new double[numberOfCitiesInTheMap];
		for (int i = 0; i < numberOfCitiesInTheMap; i++) {
			for (int j = 0; j < numberOfCitiesInTheMap; j++) {
				cityConnectionMatrix[i][j] = 0;
			}
			visitedCity[i] = 0;
			currentMinDistanceFromSource[i] = 0;
		}

		createCityConnections();

		buildCityData();

	} // createmap()

	public static void createCityHashMap() {

		cityNumber.put("albanyGA", 0);
		cityNumber.put("albanyNY", 1);
		cityNumber.put("albuquerque", 2);
		cityNumber.put("atlanta", 3);
		cityNumber.put("augusta", 4);
		cityNumber.put("austin", 5);
		cityNumber.put("bakersfield", 6);
		cityNumber.put("baltimore", 7);
		cityNumber.put("batonRouge", 8);
		cityNumber.put("beaumont", 9);
		cityNumber.put("boise", 10);
		cityNumber.put("boston", 11);
		cityNumber.put("buffalo", 12);
		cityNumber.put("calgary", 13);
		cityNumber.put("charlotte", 14);
		cityNumber.put("chattanooga", 15);
		cityNumber.put("chicago", 16);
		cityNumber.put("cincinnati", 17);
		cityNumber.put("cleveland", 18);
		cityNumber.put("coloradoSprings", 19);
		cityNumber.put("columbus", 20);
		cityNumber.put("dallas", 21);
		cityNumber.put("dayton", 22);
		cityNumber.put("daytonaBeach", 23);
		cityNumber.put("denver", 24);
		cityNumber.put("desMoines", 25);
		cityNumber.put("elPaso", 26);
		cityNumber.put("eugene", 27);
		cityNumber.put("europe", 28);
		cityNumber.put("ftWorth", 29);
		cityNumber.put("fresno", 30);
		cityNumber.put("grandJunction", 31);
		cityNumber.put("greenBay", 32);
		cityNumber.put("greensboro", 33);
		cityNumber.put("houston", 34);
		cityNumber.put("indianapolis", 35);
		cityNumber.put("jacksonville", 36);
		cityNumber.put("japan", 37);
		cityNumber.put("kansasCity", 38);
		cityNumber.put("keyWest", 39);
		cityNumber.put("lafayette", 40);
		cityNumber.put("lakeCity", 41);
		cityNumber.put("laredo", 42);
		cityNumber.put("lasVegas", 43);
		cityNumber.put("lincoln", 44);
		cityNumber.put("littleRock", 45);
		cityNumber.put("losAngeles", 46);
		cityNumber.put("macon", 47);
		cityNumber.put("medford", 48);
		cityNumber.put("memphis", 49);
		cityNumber.put("mexia", 50);
		cityNumber.put("mexico", 51);
		cityNumber.put("miami", 52);
		cityNumber.put("midland", 53);
		cityNumber.put("milwaukee", 54);
		cityNumber.put("minneapolis", 55);
		cityNumber.put("modesto", 56);
		cityNumber.put("montreal", 57);
		cityNumber.put("nashville", 58);
		cityNumber.put("newHaven", 59);
		cityNumber.put("newOrleans", 60);
		cityNumber.put("newYork", 61);
		cityNumber.put("norfolk", 62);
		cityNumber.put("oakland", 63);
		cityNumber.put("oklahomaCity", 64);
		cityNumber.put("omaha", 65);
		cityNumber.put("orlando", 66);
		cityNumber.put("ottawa", 67);
		cityNumber.put("pensacola", 68);
		cityNumber.put("philadelphia", 69);
		cityNumber.put("phoenix", 70);
		cityNumber.put("pittsburgh", 71);
		cityNumber.put("pointReyes", 72);
		cityNumber.put("portland", 73);
		cityNumber.put("providence", 74);
		cityNumber.put("provo", 75);
		cityNumber.put("raleigh", 76);
		cityNumber.put("redding", 77);
		cityNumber.put("reno", 78);
		cityNumber.put("richmond", 79);
		cityNumber.put("rochester", 80);
		cityNumber.put("sacramento", 81);
		cityNumber.put("salem", 82);
		cityNumber.put("salinas", 83);
		cityNumber.put("saltLakeCity", 84);
		cityNumber.put("sanAntonio", 85);
		cityNumber.put("sanDiego", 86);
		cityNumber.put("sanFrancisco", 87);
		cityNumber.put("sanJose", 88);
		cityNumber.put("sanLuisObispo", 89);
		cityNumber.put("santaFe", 90);
		cityNumber.put("saultSteMarie", 91);
		cityNumber.put("savannah", 92);
		cityNumber.put("seattle", 93);
		cityNumber.put("stLouis", 94);
		cityNumber.put("stamford", 95);
		cityNumber.put("stockton", 96);
		cityNumber.put("tallahassee", 97);
		cityNumber.put("tampa", 98);
		cityNumber.put("thunderBay", 99);
		cityNumber.put("toledo", 100);
		cityNumber.put("toronto", 101);
		cityNumber.put("tucson", 102);
		cityNumber.put("tulsa", 103);
		cityNumber.put("uk1", 104);
		cityNumber.put("uk2", 105);
		cityNumber.put("vancouver", 106);
		cityNumber.put("washington", 107);
		cityNumber.put("westPalmBeach", 108);
		cityNumber.put("wichita", 109);
		cityNumber.put("winnipeg", 110);
		cityNumber.put("yuma", 111);

		for (Entry<String, Integer> entry : cityNumber.entrySet()) {
			cityName.put(entry.getValue(), entry.getKey());
		}
	} // createCityHashMap

	public static void createCityConnections() {
		addRoad("albanyNY", "montreal", 226);
		addRoad("albanyNY", "boston", 166);
		addRoad("albanyNY", "rochester", 148);
		addRoad("albanyGA", "tallahassee", 120);
		addRoad("albanyGA", "macon", 106);
		addRoad("albuquerque", "elPaso", 267);
		addRoad("albuquerque", "santaFe", 61);
		addRoad("atlanta", "macon", 82);
		addRoad("atlanta", "chattanooga", 117);
		addRoad("augusta", "charlotte", 161);
		addRoad("augusta", "savannah", 131);
		addRoad("austin", "houston", 186);
		addRoad("austin", "sanAntonio", 79);
		addRoad("bakersfield", "losAngeles", 112);
		addRoad("bakersfield", "fresno", 107);
		addRoad("baltimore", "philadelphia", 102);
		addRoad("baltimore", "washington", 45);
		addRoad("batonRouge", "lafayette", 50);
		addRoad("batonRouge", "newOrleans", 80);
		addRoad("beaumont", "houston", 69);
		addRoad("beaumont", "lafayette", 122);
		addRoad("boise", "saltLakeCity", 349);
		addRoad("boise", "portland", 428);
		addRoad("boston", "providence", 51);
		addRoad("buffalo", "toronto", 105);
		addRoad("buffalo", "rochester", 64);
		addRoad("buffalo", "cleveland", 191);
		addRoad("buffalo", "toronto", 105);
		addRoad("buffalo", "rochester", 164);
		addRoad("buffalo", "cleveland", 191);
		addRoad("calgary", "vancouver", 605);
		addRoad("calgary", "winnipeg", 829);
		addRoad("charlotte", "greensboro", 91);
		addRoad("chattanooga", "nashville", 129);
		addRoad("chicago", "milwaukee", 90);
		addRoad("chicago", "midland", 279);
		addRoad("cincinnati", "indianapolis", 110);
		addRoad("cincinnati", "dayton", 56);
		addRoad("cleveland", "pittsburgh", 157);
		addRoad("cleveland", "columbus", 142);
		addRoad("coloradoSprings", "denver", 70);
		addRoad("coloradoSprings", "santaFe", 316);
		addRoad("columbus", "dayton", 72);
		addRoad("dallas", "denver", 792);
		addRoad("dallas", "mexia", 83);
		addRoad("daytonaBeach", "jacksonville", 92);
		addRoad("daytonaBeach", "orlando", 54);
		addRoad("denver", "wichita", 523);
		addRoad("denver", "grandJunction", 246);
		addRoad("desMoines", "omaha", 135);
		addRoad("desMoines", "minneapolis", 246);
		addRoad("elPaso", "sanAntonio", 580);
		addRoad("elPaso", "tucson", 320);
		addRoad("eugene", "salem", 63);
		addRoad("eugene", "medford", 165);
		addRoad("europe", "philadelphia", 3939);
		addRoad("ftWorth", "oklahomaCity", 209);
		addRoad("fresno", "modesto", 109);
		addRoad("grandJunction", "provo", 220);
		addRoad("greenBay", "minneapolis", 304);
		addRoad("greenBay", "milwaukee", 117);
		addRoad("greensboro", "raleigh", 74);
		addRoad("houston", "mexia", 165);
		addRoad("indianapolis", "stLouis", 246);
		addRoad("jacksonville", "savannah", 140);
		addRoad("jacksonville", "lakeCity", 113);
		addRoad("japan", "pointReyes", 5131);
		addRoad("japan", "sanLuisObispo", 5451);
		addRoad("kansasCity", "tulsa", 249);
		addRoad("kansasCity", "stLouis", 256);
		addRoad("kansasCity", "wichita", 190);
		addRoad("keyWest", "tampa", 446);
		addRoad("lakeCity", "tampa", 169);
		addRoad("lakeCity", "tallahassee", 104);
		addRoad("laredo", "sanAntonio", 154);
		addRoad("laredo", "mexico", 741);
		addRoad("lasVegas", "losAngeles", 275);
		addRoad("lasVegas", "saltLakeCity", 486);
		addRoad("lincoln", "wichita", 277);
		addRoad("lincoln", "omaha", 58);
		addRoad("littleRock", "memphis", 137);
		addRoad("littleRock", "tulsa", 276);
		addRoad("losAngeles", "sanDiego", 124);
		addRoad("losAngeles", "sanLuisObispo", 182);
		addRoad("medford", "redding", 150);
		addRoad("memphis", "nashville", 210);
		addRoad("miami", "westPalmBeach", 67);
		addRoad("midland", "toledo", 82);
		addRoad("minneapolis", "winnipeg", 463);
		addRoad("modesto", "stockton", 29);
		addRoad("montreal", "ottawa", 132);
		addRoad("newHaven", "providence", 110);
		addRoad("newHaven", "stamford", 92);
		addRoad("newOrleans", "pensacola", 268);
		addRoad("newYork", "philadelphia", 101);
		addRoad("norfolk", "richmond", 92);
		addRoad("norfolk", "raleigh", 174);
		addRoad("oakland", "sanFrancisco", 8);
		addRoad("oakland", "sanJose", 42);
		addRoad("oklahomaCity", "tulsa", 105);
		addRoad("orlando", "westPalmBeach", 168);
		addRoad("orlando", "tampa", 84);
		addRoad("ottawa", "toronto", 269);
		addRoad("pensacola", "tallahassee", 120);
		addRoad("philadelphia", "pittsburgh", 319);
		addRoad("philadelphia", "newYork", 101);
		addRoad("philadelphia", "uk1", 3548);
		addRoad("philadelphia", "uk2", 3548);
		addRoad("phoenix", "tucson", 117);
		addRoad("phoenix", "yuma", 178);
		addRoad("pointReyes", "redding", 215);
		addRoad("pointReyes", "sacramento", 115);
		addRoad("portland", "seattle", 174);
		addRoad("portland", "salem", 47);
		addRoad("reno", "saltLakeCity", 520);
		addRoad("reno", "sacramento", 133);
		addRoad("richmond", "washington", 105);
		addRoad("sacramento", "sanFrancisco", 95);
		addRoad("sacramento", "stockton", 51);
		addRoad("salinas", "sanJose", 31);
		addRoad("salinas", "sanLuisObispo", 137);
		addRoad("sanDiego", "yuma", 172);
		addRoad("saultSteMarie", "thunderBay", 442);
		addRoad("saultSteMarie", "toronto", 436);
		addRoad("seattle", "vancouver", 115);
		addRoad("thunderBay", "winnipeg", 440);
	} // createCityConnections

	public static void addRoad(String city1, String city2, int distance) {
		int city1Number = -1;
		int city2Number = -1;

		city1Number = cityNumber.get(city1);
		city2Number = cityNumber.get(city2);

		if ((-1 != city1Number) || (-1 != city2Number)) {
			cityConnectionMatrix[city1Number][city2Number] = distance;
			cityConnectionMatrix[city2Number][city1Number] = distance;
		}

	} // addRoad

	public static void buildCityData() {
		cityDataBase = new CityData[numberOfCitiesInTheMap];

		loadCity("albanyGA", 31.58, 84.17);
		loadCity("albanyNY", 42.66, 73.78);
		loadCity("albuquerque", 35.11, 106.61);
		loadCity("atlanta", 33.76, 84.40);
		loadCity("augusta", 33.43, 82.02);
		loadCity("austin", 30.30, 97.75);
		loadCity("bakersfield", 35.36, 119.03);
		loadCity("baltimore", 39.31, 76.62);
		loadCity("batonRouge", 30.46, 91.14);
		loadCity("beaumont", 30.08, 94.13);
		loadCity("boise", 43.61, 116.24);
		loadCity("boston", 42.32, 71.09);
		loadCity("buffalo", 42.90, 78.85);
		loadCity("calgary", 51.00, 114.00);
		loadCity("charlotte", 35.21, 80.83);
		loadCity("chattanooga", 35.05, 85.27);
		loadCity("chicago", 41.84, 87.68);
		loadCity("cincinnati", 39.14, 84.50);
		loadCity("cleveland", 41.48, 81.67);
		loadCity("coloradoSprings", 38.86, 104.79);
		loadCity("columbus", 39.99, 82.99);
		loadCity("dallas", 32.80, 96.79);
		loadCity("dayton", 39.76, 84.20);
		loadCity("daytonaBeach", 29.21, 81.04);
		loadCity("denver", 39.73, 104.97);
		loadCity("desMoines", 41.59, 93.62);
		loadCity("elPaso", 31.79, 106.42);
		loadCity("eugene", 44.06, 123.11);
		loadCity("europe", 48.87, -2.33);
		loadCity("ftWorth", 32.74, 97.33);
		loadCity("fresno", 36.78, 119.79);
		loadCity("grandJunction", 39.08, 108.56);
		loadCity("greenBay", 44.51, 88.02);
		loadCity("greensboro", 36.08, 79.82);
		loadCity("houston", 29.76, 95.38);
		loadCity("indianapolis", 39.79, 86.15);
		loadCity("jacksonville", 30.32, 81.66);
		loadCity("japan", 35.68, 220.23);
		loadCity("kansasCity", 39.08, 94.56);
		loadCity("keyWest", 24.56, 81.78);
		loadCity("lafayette", 30.21, 92.03);
		loadCity("lakeCity", 30.19, 82.64);
		loadCity("laredo", 27.52, 99.49);
		loadCity("lasVegas", 36.19, 115.22);
		loadCity("lincoln", 40.81, 96.68);
		loadCity("littleRock", 34.74, 92.33);
		loadCity("losAngeles", 34.03, 118.17);
		loadCity("macon", 32.83, 83.65);
		loadCity("medford", 42.33, 122.86);
		loadCity("memphis", 35.12, 89.97);
		loadCity("mexia", 31.68, 96.48);
		loadCity("mexico", 19.40, 99.12);
		loadCity("miami", 25.79, 80.22);
		loadCity("midland", 43.62, 84.23);
		loadCity("milwaukee", 43.05, 87.96);
		loadCity("minneapolis", 44.96, 93.27);
		loadCity("modesto", 37.66, 120.99);
		loadCity("montreal", 45.50, 73.67);
		loadCity("nashville", 36.15, 86.76);
		loadCity("newHaven", 41.31, 72.92);
		loadCity("newOrleans", 29.97, 90.06);
		loadCity("newYork", 40.70, 73.92);
		loadCity("norfolk", 36.89, 76.26);
		loadCity("oakland", 37.80, 122.23);
		loadCity("oklahomaCity", 35.48, 97.53);
		loadCity("omaha", 41.26, 96.01);
		loadCity("orlando", 28.53, 81.38);
		loadCity("ottawa", 45.42, 75.69);
		loadCity("pensacola", 30.44, 87.21);
		loadCity("philadelphia", 40.72, 76.12);
		loadCity("phoenix", 33.53, 112.08);
		loadCity("pittsburgh", 40.40, 79.84);
		loadCity("pointReyes", 38.07, 122.81);
		loadCity("portland", 45.52, 122.64);
		loadCity("providence", 41.80, 71.36);
		loadCity("provo", 40.24, 111.66);
		loadCity("raleigh", 35.82, 78.64);
		loadCity("redding", 40.58, 122.37);
		loadCity("reno", 39.53, 119.82);
		loadCity("richmond", 37.54, 77.46);
		loadCity("rochester", 43.17, 77.61);
		loadCity("sacramento", 38.56, 121.47);
		loadCity("salem", 44.93, 123.03);
		loadCity("salinas", 36.68, 121.64);
		loadCity("saltLakeCity", 40.75, 111.89);
		loadCity("sanAntonio", 29.45, 98.51);
		loadCity("sanDiego", 32.78, 117.15);
		loadCity("sanFrancisco", 37.76, 122.44);
		loadCity("sanJose", 37.30, 121.87);
		loadCity("sanLuisObispo", 35.27, 120.66);
		loadCity("santaFe", 35.67, 105.96);
		loadCity("saultSteMarie", 46.49, 84.35);
		loadCity("savannah", 32.05, 81.10);
		loadCity("seattle", 47.63, 122.33);
		loadCity("stLouis", 38.63, 90.24);
		loadCity("stamford", 41.07, 73.54);
		loadCity("stockton", 37.98, 121.30);
		loadCity("tallahassee", 30.45, 84.27);
		loadCity("tampa", 27.97, 82.46);
		loadCity("thunderBay", 48.38, 89.25);
		loadCity("toledo", 41.67, 83.58);
		loadCity("toronto", 43.65, 79.38);
		loadCity("tucson", 32.21, 110.92);
		loadCity("tulsa", 36.13, 95.94);
		loadCity("uk1", 51.30, 0.00);
		loadCity("uk2", 51.30, 0.00);
		loadCity("vancouver", 49.25, 123.10);
		loadCity("washington", 38.91, 77.01);
		loadCity("westPalmBeach", 26.71, 80.05);
		loadCity("wichita", 37.69, 97.34);
		loadCity("winnipeg", 49.90, 97.13);
		loadCity("yuma", 32.69, 114.62);
	}

	public static void loadCity(String name, double lati, double longi) {
		int index = cityNumber.get(name);

		if ((0 <= index) || (numberOfCitiesInTheMap > index)) {
			if (cityDataBase[index] == null) {
				cityDataBase[index] = new CityData();
			}
			cityDataBase[index].setName(name);
			cityDataBase[index].setIndex(index);
			cityDataBase[index].setLattitude(lati);
			cityDataBase[index].setLongitude(longi);
		} else {
			System.out.println("ERROR, wonrg index");
		}
	}
} // class SearchUSA