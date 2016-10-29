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