# include "orientation.h"
#define MAX_POINTS 101

Point startPoint;

#define SQ_DIST(a,b) ((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y))
int compare(Point p, Point q) { // return -ve if p should come before p
	if (p == q) {
		return 0;
	}

	auto o = orientation(startPoint, p, q);
	if (o == COLINEAR) {
		int dist1 = SQ_DIST(startPoint, p);
		int dist2 = SQ_DIST(startPoint, q);
		return dist1 - dist2;
	}
	if (o == ANTICLOCKWISE) {
		return -1;
	}
	return 1;
}

void printPoints(Point* points, int count) {
	for (int i = 0; i < count; i++) {
		cout << points[i];
	}
	cout << endl;
}

void insertionSort(Point* points, int start, int count) {
	printPoints(points, count);
	for (int i = start; i < (count-1); i++) { // already sorted till i
		int j = i + 1;
		for (; j >= start; j--) {
			if (compare(points[i], points[j]) < 0) {
				break;
			}
		}
		if (j != i+1) { // i + 1 should be inserted after j
			auto t = points[i + 1];
			for (int k = i; k > j; k--) {
				points[k + 1] = points[k];
			}
			points[j + 1] = t;
		}
		printPoints(points, count);
	}
	printPoints(points, count);
}

int grahamScan(Point* points, int count) {
	
	if (count <= 3) {
		return count;
	}

	for (int i = 1; i < count; i++) {
		if ((points[0].y > points[i].y) || ((points[0].y == points[i].y) && (points[i].x < points[0].x))) {
			auto t = points[0];
			points[0] = points[i];
			points[i] = t;
		}
	}
	startPoint = points[0];
	insertionSort(points, 1, count);

	// Remove duplicates if 
	{
		Point unique[MAX_POINTS];
		unique[0] = points[0];
		int newCount = 1;
		for (int i = 1; i < count; i++) {
			if (!(points[i] == unique[newCount - 1])) {
				unique[newCount] = points[i];
				newCount++;
			}
		}

		// copy unique points back to points
		for (int i = 0; i < newCount; i++) {
			points[i] = unique[i];
		}
		count = newCount;
	}



	if (count <= 3) {
		return count;
	}

	Point stack[MAX_POINTS];
	for (int i = 0; i < 3; i++) {
		stack[i] = points[i];
	}

	int top = 2;
	for (int i = 3; i < count; i++) { // adding ith point to stack
		auto o = orientation(stack[top - 1], stack[top], points[i]);
		while (o != ANTICLOCKWISE) {
			top--;
			o = orientation(stack[top - 1], stack[top], points[i]);
		}
		// push
		top += 1;
		stack[top] = points[i]; // push
	}


	for (int i = 0; i <= top; i++) {
		points[i] = stack[i];
	}
	return top + 1;
}

int main() {
	Point points[] = { {0, 3}, {1, 1}, {2, 2}, {4, 4},
					  {0, 0}, {1, 2}, {3, 1}, {3, 3} };
	int n = sizeof(points) / sizeof(points[0]);
	int cnt = grahamScan(points, n);

	for (int i = 0; i < cnt; i++) {
		cout << points[i];
	}
	return 0;
}