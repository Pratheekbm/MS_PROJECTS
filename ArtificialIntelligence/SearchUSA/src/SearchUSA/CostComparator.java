package SearchUSA;

import java.util.Comparator;

public class CostComparator implements Comparator<Paths> {
	@Override
	public int compare(Paths path1, Paths path2) {
		if (path1.getCost() < path2.getCost()) {
			return -1;
		} else if (path1.getCost() > path2.getCost()) {
			return 1;
		} else {
			return 0;
		}
	}
}
