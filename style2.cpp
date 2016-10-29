#include <iostream>
#include <cmath>
using namespace std;

struct Clothes {
	int color;
	int type;
};

Clothes mass[400001]; //массив для одежды и её типов
int otr[400001];      //массив отрезков
int tekN[4];          //массив текущих типов одежды
int typ[4];           //массив типов одежды
int col[4];           //массив цветов одежды
int Nc[4];            //массив количества одежды i-того вида

void swap(Clothes &a, Clothes &b) //swap для одежды
{
	int tc = a.color;
	int tt = a.type;
	a = b;
	b.color = tc;
	b.type = tt;
}


void sortq(int left, int right, Clothes *mas) //быстрая сортировка для одежды
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

void read(int l, int t, int &N)         //чтение i-того типа одежды
{
	cin >> N;
	for (int i = l; i < l + N; i++) {
		cin >> mass[i].color;
		mass[i].type = t;
	}
}

int prov()          //проверка для отрезка по вхождению всех типов одежды в него
{
	for (int i = 0; i < 4; i++) {
		if (tekN[i] == 0)
			return 0;
	}
	return 1;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int max(int a, int b)
{
	if (a > b)
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
	
	int i = 0;
	int j = 0;
	int N = Nc[0] + Nc[1] + Nc[2] + Nc[3];

	while (j < N) {  //для каждого i найдем такой индекс j, что в отрезок [i,j] будут входить все 4 типа одежды
		if (prov()) {
			otr[i] = j - 1;
			tekN[mass[i].type]--;
			i++;
		}
		else {
			tekN[mass[j].type]++;
			j++;
		}
	}

	while (prov()) { //сдвинем теперь i, вдруг будет там какой-то меньший отрезок
		tekN[mass[i].type]--;
		otr[i] = j - 1;
		i++;
	}

	int mi, a, b;
	mi = 100000001;

	for (j = 0; j < i; j++) { //ищем отрезок минимальной длины
		if (mi > mass[otr[j]].color - mass[j].color) {
			mi = mass[otr[j]].color - mass[j].color;
			a = j;
			b = otr[j];
		}
	}

    //для одежды типа c индексом a и с индексом b проставим их цвета
	typ[mass[a].type] = 1;
	typ[mass[b].type] = 1;
	col[mass[a].type] = mass[a].color;
	col[mass[b].type] = mass[b].color;


    //найдём цвета для остальных двух типов одежды
	mi = min(col[mass[a].type], col[mass[b].type]);
	int ma = max(col[mass[a].type], col[mass[b].type]);

	for (int z = 0; z < 4; z++) {
		if (typ[z] == 0) {
			for (int k = a + 1; k < b; k++) {
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