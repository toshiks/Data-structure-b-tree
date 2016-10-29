#include <iostream>
#include <cmath>
using namespace std;

struct Clothes {
    int color;
    int type;
};

Clothes mass[400001];
int typ[4];
int col[4];
int Nc[4];

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

void read(int l, int t, int &N)
{
    cin >> N;
    for (int i = l; i < l + N; i++) {
        cin >> mass[i].color;
        mass[i].type = t;
    }
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    read(0, 0, Nc[0]);
    read(Nc[0], 1, Nc[1]);
    read(Nc[0]+Nc[1], 2, Nc[2]);
    read(Nc[0]+Nc[1]+Nc[2], 3, Nc[3]);
    sortq(0, Nc[0] + Nc[1] + Nc[2] + Nc[3] - 1, mass);
    int i, j, raz = 10000001;
    i = 0;
    j = Nc[0] + Nc[1] + Nc[2] + Nc[3] - 1;
    while (Nc[0] != 0 && Nc[1] != 0 && Nc[2] != 0 && Nc[3] != 0) {
        if (Nc[mass[i].type] > 1) {
            Nc[mass[i].type]--;
            i++;
        }
        else {
            if (Nc[mass[j].type] > 1) {
                Nc[mass[j].type]--;
                j--;
            }
            else
                break;
        }
    }

    typ[mass[i].type] = 1;
    typ[mass[j].type] = 1;
    col[mass[i].type] = mass[i].color;
    col[mass[j].type] = mass[j].color;

    int mi = min(col[mass[i].type], col[mass[j].type]);
    int ma = max(col[mass[i].type], col[mass[j].type]);


    for (int z = 0; z < 4; z++) {
        if (typ[z] == 0) {
            for (int k = i + 1; k < j; k++) {
                if (mass[k].type == z) {
                    if (mass[k].color >= mi && mass[k].color <= ma) {
                        typ[z] = 1;
                        col[z] = mass[k].color;
                        break;
                    }
                }
            }
        }
    }

    for (i = 0; i < 4; i++)
        cout << col[i] << ' ';
    return 0;
}