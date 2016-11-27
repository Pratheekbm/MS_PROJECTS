package SearchUSA;

import java.util.Comparator;
import java.util.PriorityQueue;

public class SearchAlgos {

	static Comparator<Paths> comparator = new CostComparator();
	static PriorityQueue<Paths> queue = new PriorityQueue<Paths>(110, comparator);
/*	private static Paths aStarPath;
	private static double aStarCurrentMinDistance = -1;*/

	public static Paths search(String sourceCity, String destinationCity, String searchType) {
		Paths initialPath = new Paths();
		boolean addHeuristic = false;
		boolean addPathCost = false;

		if (searchType.equals("uniform")) {
			addPathCost = true;
		} else if (searchType.equals("greedy")) {
			addHeuristic = true;
		} else if (searchType.equals("astar")) {
			addPathCost = true;
			addHeuristic = true;
		}

		if (false == addHeuristic && false == addPathCost) {
			System.out.println("Invalid Search Algorithm selected");
			return initialPath;
		}
		initialPath.addCity(SearchUSA.getCityDataFromCity(sourceCity));
		initialPath.setCost(addHeuristic, addPathCost, destinationCity);
		queue.add(initialPath);
		SearchUSA.markCityVisited(sourceCity);
		SearchUSA.setCurrentMinDistanceFromSource(sourceCity, 0);

		while (!(queue.isEmpty())) {

			Paths queueTipPath = queue.remove();
			SearchUSA.addCityToCitiesExpanded(queueTipPath.getLastCity().getName());

			/*System.out.printf("\nPaths expanded :");
			queueTipPath.printCitiesInPath();*/

			if (true == addHeuristic && true == addPathCost) {

				/*
				 * if (destinationCity == queueTipPath.getLastCity().getName())
				 * { if (-1 == aStarCurrentMinDistance) { aStarPath = new
				 * Paths(queueTipPath); aStarPath.setCost(addHeuristic,
				 * addPathCost, destinationCity); aStarCurrentMinDistance =
				 * queueTipPath.getPathCost();
				 * System.out.println(aStarCurrentMinDistance); continue; } else
				 * if (aStarCurrentMinDistance < queueTipPath.getPathCost()) {
				 * return aStarPath; } } else { if (-1 !=
				 * aStarCurrentMinDistance) { if (aStarCurrentMinDistance <
				 * queueTipPath.getPathCost()) { System.out.println("" +
				 * aStarCurrentMinDistance + " " + queueTipPath.getPathCost());
				 * return aStarPath; } } }
				 */

			}

			if (destinationCity.equals(queueTipPath.getLastCity().getName()) ) {
				return queueTipPath;
			} else {
				int numberOfCities = SearchUSA.getNumberOfCitiesInTheMap();
				int lastCityIndex = queueTipPath.getLastCity().getIndex();
				for (int i = 0; i < numberOfCities; i++) {
					if (SearchUSA.checkAdjacency(lastCityIndex, i)) {
						Paths tempPath = new Paths(queueTipPath);
						tempPath.addCity(SearchUSA.getCityDataFromCityIndex(i));
						tempPath.setCost(addHeuristic, addPathCost, destinationCity);

						if (true == SearchUSA.checkIfCityIsVisited(tempPath.getLastCity().getName())) {
							if (tempPath.getPathCost() > SearchUSA.getCurrentMinDistanceFromSource(tempPath
									.getLastCity().getName())) {
								continue;
							} else {
								SearchUSA.setCurrentMinDistanceFromSource(tempPath.getLastCity().getName(),
										tempPath.getPathCost());
								queue.add(tempPath);
							}
						} else {
							SearchUSA.markCityVisited(tempPath.getLastCity().getName());
							SearchUSA.setCurrentMinDistanceFromSource(tempPath.getLastCity().getName(),
									tempPath.getPathCost());
							queue.add(tempPath);
						}
						/*System.out.printf(tempPath.getLastCity().getName());
						System.out.println(" - TC PC H : "
								+ (int)tempPath.getCost() + "  " + (int)tempPath.getPathCost() + " " + (int)(tempPath.getCost() - tempPath.getPathCost()));
						// tempPath.printCitiesInPath();
*/					}
				}
			}
		}

		return initialPath;
	}
}