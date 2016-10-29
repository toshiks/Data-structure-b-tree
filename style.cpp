#include <iostream>
#include <cmath>
using namespace std;

struct Clothes {
    int color;
    int type;
};

Clothes mass[200001];

void swap(Clothes &a, Clothes &b)
{
    int tc = a.color;
    int tt = a.type;
    a = b;
    b.color = tc;
    b.type = tt;
}


void sortq(int left, int right, Clothes *mas)
{
    int i = left;
    int j = right;
    int r = mas[(i + j) / 2].color;
    while (i <= j) {
        while (mas[i].color < r)
            i++;
        while (mas[j].color > r)
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

int sub(Clothes a, Clothes b)
{
    if (a.type == b.type)
        return 10000001;
    return abs(a.color - b.color);
}

int main()
{
    int N, M;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> mass[i].color;
        mass[i].type = 0;
    }
    cin >> M;
    for (int i = N; i < N+ M; i++) {
        cin >> mass[i].color;
        mass[i].type = 1;
    }
    sortq(0, N + M - 1, mass);
    int a, b, raz = 10000001;
    for (int i = 1; i < N + M; i++) {
        int temp = sub(mass[i - 1], mass[i]);
        if (temp < raz) {
            raz = temp;
            if (mass[i].type == 1) {
                a = mass[i - 1].color;
                b = mass[i].color;
            }
            else {
                b = mass[i - 1].color;
                a = mass[i].color;
            }
        }
    }

    cout << a << ' ' << b;
    return 0;
}