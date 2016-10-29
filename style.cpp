#include <iostream>
#include <cmath>
using namespace std;

int mas1[100001];
int mas2[100001];

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = a;
}


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
    int N, M;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> mas1[i];
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> mas2[i];
    }

    sortq(0, N-1, mas1);
    sortq(0, M-1, mas2);
    int a, b, raz = 10000001;
    int chet1 = 0;
    int chet2 = 0;
    a = mas1[chet1];
    b = mas2[chet2];
    raz = abs(a - b);
    while (chet1 < N && chet2 < M) {
        if (mas1[chet1] < mas2[chet2])
            chet1++;
        else
            chet2++;
        if (raz > abs(mas1[chet1] - mas2[chet2])) {
            raz = abs(mas1[chet1] - mas2[chet2]);
            a = mas1[chet1];
            b = mas2[chet2];
        }
    }

    cout << a << ' ' << b;
    return 0;
}