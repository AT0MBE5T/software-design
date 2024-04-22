#include <iostream> 
using namespace std;

void Print(int* arra, int n);

int main() {
	int n;
	cout << "Enter a size: ";
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) {
		cout << "arr[" << i << "]: ";
		cin >> arr[i];
	}
	cout << "Stock: ";
	for (int i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
	Print(arr, n);
	delete[] arr;
	return 0;
}

void Print(int* arra, int n) {
	cout << "\nPairs: ";
	for (int i = 0; i < n; ++i) {
		if (!(arra[i] & 1)) {
			cout << arra[i] << " ";
		}
	}
}
