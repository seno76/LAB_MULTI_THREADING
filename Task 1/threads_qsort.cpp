#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <thread>

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

void q_sort(vector<int>& arr, int start, int end, int r_depth) {
	if (arr.size() != 1 && start < end) {
		int middle = partition(arr, start, end);
		if (r_depth > 4) {
            q_sort(arr, start, middle - 1, r_depth + 1);
            q_sort(arr, middle + 1, end, r_depth + 1);
		}
		else {
        thread th1(q_sort, ref(arr), start, middle - 1, r_depth + 1);
        thread th2(q_sort, ref(arr), middle + 1, end, r_depth + 1);
        th1.join();
        th2.join();
		}
	}
}


void q_sort_classic(vector<int>& arr, int start, int end, int r_depth) {
	if (arr.size() != 1 && start < end) {
		int middle = partition(arr, start, end);
        q_sort_classic(arr, start, middle - 1, r_depth + 1);
        q_sort_classic(arr, middle + 1, end, r_depth + 1);
	}
}



int main() {
	vector<int> test, res, test1;


	test = {1, 888, 34, 456, 23, 12, 1, 1, 34, 2, 5, 2, 5, 4, 6, 5, 4};
	for (int i = 0; i < 1000000; i++){
        test1.push_back(1 + rand() % 1000);
	}

	q_sort(test1, 0, test1.size() - 1, 0);

	return 228;
}
