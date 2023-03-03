#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


using namespace std;

int partition(vector<int>& lst, int start, int end) {
	int i;
	int pivot = lst[end];
	i = start;
	for (int j = start; j < end; j++) {
		if (lst[j] <= pivot) {
			swap(lst[j], lst[i]);
			i++;
		}
	}
	swap(lst[i], lst[end]);
	return i;
}

vector<int> qsort(vector<int>& arr, int start, int end) {
	if (arr.size() == 1) 
		return arr;
	if (start < end) {
		int middle = partition(arr, start, end);
		qsort(arr, start, middle - 1);
		qsort(arr, middle + 1, end);
	}
	return arr;
}

int main() {
	vector<int> test, res;
	test = {1, 888, 34, 456, 23, 12, 1, 1, 34, 2, 5, 2, 5, 4, 6, 5, 4};
	res = qsort(test, 0, test.size() - 1);
	for (auto x : res) {
		cout << x << endl;
	}
	return -1;
}