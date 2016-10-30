#include <iostream>
#include <ctime>
using namespace std;

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

void sortq(int left, int right, int *mas)
{
    int i = left;
    int j = right;
    int r = mas[i + rand() % (j - i)];
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
    srand(time(NULL));

    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    int n;
    cin >> n;
    int *mas = new int[n];
    for (int i = 0; i < n; i++)
        cin >> mas[i];
    sortq(0, n - 1, mas);
    for (int i = 0; i < n; i++) {
        cout << mas[i] << ' ';
    }

    delete[] mas;
    return 0;
}