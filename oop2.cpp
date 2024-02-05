#include <iostream> //1
#define SIZE 10
using namespace std;

int Max(int* arr, const int n);
int Min(int* arr, const int n);

int main()
{
	int arr[SIZE]{};
	srand((unsigned)time(NULL));
	for (int i = 0; i < SIZE; i++) arr[i] = rand() % 15;
	for (int i = 0; i < SIZE; ++i) cout << arr[i] << endl;
	cout << endl;
	cout << "Min: " << Min(arr, SIZE) << endl;
	cout << "Max: " << Max(arr, SIZE) << endl;
	return 0;
}

int Min(int* arr, const int n) {
	int min = arr[0];
	for (int i = 1; i < n; ++i) if (arr[i] < min) min = arr[i];
	return min;
}
int Max(int* arr, const int n) {
	int max = arr[0];
	for (int i = 1; i < n; ++i) if (max < arr[i]) max = arr[i];
	return max;
}


#include <iostream> //2
using namespace std;

double Avg(int* arr, int n);

int main()
{
	srand((unsigned)time(NULL));
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) arr[i] = rand() % 25;
	cout << "Input array: ";
	for (int i = 0; i < n; ++i) cout << arr[i] << " ";
	cout << endl;
	cout << "Average value: " << Avg(arr, n);
	delete[] arr;
	return 0;
}

double Avg(int* arr, int n) {
	double sum = 0;
	for (int i = 0; i < n; ++i) sum += arr[i];
	return sum / n;
}

#include <iostream> //3
using namespace std;

void Fill(int** arr, int x, int y);

int main()
{
	int x;
	int y;

	cout << "x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;

	int** arr = new int* [x];

	for (int i = 0; i < x; ++i) arr[i] = new int[y];

	Fill(arr, x, y);

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << arr[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < x; ++i) delete[] arr[i];
	delete[] arr;
	return 0;
}

void Fill(int** arr, int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; ++j)
			arr[i][j] = rand() % 10;
	}
}
