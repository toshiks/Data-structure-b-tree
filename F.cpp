#include <iostream>
#include <fstream>
using namespace std;

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

int main()
{
	ifstream in("antiqs.in");
	ofstream out("antiqs.out");
	int n;
	in >> n;
	int *mas = new int[n+1];
	for (int i = 0; i < n+1; i++)
		mas[i] = i;

	for (int i = 3; i < n+1; i++) {
		swap(mas[(i + 1) / 2], mas[i]);
	}

	for (int i = 1; i < n+1; i++) {
		out << mas[i] << ' ';
	}
	delete[] mas;
	return 0;
}