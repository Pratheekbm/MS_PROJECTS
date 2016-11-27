package SearchUSA;

import java.util.ArrayList;
import java.util.List;

public class Paths {
	private double cost;
	private double pathCost;
	private List<CityData> cities = new ArrayList<>();

	public Paths() {
		// TODO Auto-generated constructor stub
	}

	public Paths(Paths p) {
		// TODO Auto-generated constructor stub
		this.cities = new ArrayList<>(p.getCities());
		this.cost = p.getCost();
	}

	public double getCost() {
		return cost;
	}

	public double getPathCost() {
		return pathCost;
	}

	public void setCost(boolean addHeuristic, boolean addPathCost, String destinationCity) {
		int numberOfPaths = getSizeOfThePath() - 1;
		double totalCost = 0;

		for (int i = 0; i < numberOfPaths; i++) {
			pathCost += SearchUSA.getPathCostBetweenAdjCities(cities.get(i).getName(), cities.get(i + 1).getName());
		}

		if (true == addPathCost) {
			totalCost += pathCost;
		}
		if (true == addHeuristic) {
			totalCost += SearchUSA.getHeuristic(getLastCity().getName(), destinationCity);
		}

		this.cost = totalCost;
	}

	public List<CityData> getCities() {
		return cities;
	}

	public void setCities(List<CityData> cities) {
		this.cities = cities;
	}

	public void addCity(CityData city) {
		cities.add(city);
	}

	public CityData getLastCity() {
		return cities.get(cities.size() - 1);
	}

	public int getSizeOfThePath() {
		return cities.size();
	}

	public void printCitiesInPath() {
		int numberOfCitiesInPath = getSizeOfThePath();
		for (int i = 0; i < numberOfCitiesInPath; i++) {
			System.out.printf(cities.get(i).getName() + "  ");
		}
		System.out.println("\nNumber of nodes in the path   : " + cities.size());
		System.out.println("Total Distance                : " + getPathCost());
		//System.out.println("Total Cost                    : " + getCost());
		System.out.println();
	}
}
