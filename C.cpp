#include <iostream>
#include <fstream>
using namespace std;

void sortq(int left, int right, int *mas)
{
	int i = left;
	int j = right;
	int r = mas[(i + j) / 2];
	while (i <= j) {
		while (mas[i] < r)
			i++;
		while (mas[j] > r)
			j--;
		if (i <= j) {
			swap(mas[i], mas[j]);
			i++;
			j--;
		}
	}
	if (left < j)
		sortq(left, j, mas);
	if (right > i)
		sortq(i, right, mas);
}

int main()
{
	ifstream in("sort.in");
	ofstream out("sort.out");
	int n;
	in >> n;
	int *mas = new int[n];
	for (int i = 0; i < n; i++)
		in >> mas[i];
	sortq(0, n - 1, mas);
	for (int i = 0; i < n; i++) {
		out << mas[i] << ' ';
	}

	delete[] mas;
	return 0;
}