#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	ifstream in("radixsort.in");
	ofstream out("radixsort.out");

	int n, m, k;
	in >> n >> m >> k;
	string *A = new string[n];
	string *B = new string[n];
	int C[255];

	for (int i = 0; i < n; i++) {
		in >> A[i];
	}

	for (int i = m-1; i >= m-k; i--) {
		for (int j = 0; j < 255; j++) {
			C[j] = 0;
		}

		for (int j = 0; j < n; j++) {
			C[int(A[j][i])-97]++;
		}

		int coun = 0;

		for (int j = 0; j < 255; j++) {
			int temp = C[j];
			C[j] = coun;
			coun += temp;
		}

		for (int j = 0; j < n; j++) {
			B[C[int(A[j][i])-97]] = A[j];
			C[int(A[j][i])-97]++;
		}

		for (int i = 0; i < n; i++) {
			A[i] = B[i];
		}
	}

	for (int i = 0; i < n; i++) {
		out << A[i] << '\n';
	}

	delete[] B;
	delete[] A;
	return 0;
}