#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
}

class Heap {
private:
    int countHeap;			//количество ключей в куче
    int countBuff;			//количество операций
    int *mas;				//сама куча
    int *decrease;			//буффер операций
    void siftUp(int i);
    void siftDown(int i);
public:
    Heap(const int x);
    ~Heap();
    void push(int x);
    int extractMin();
    void decreaseKey(int operation, int val);
};

Heap::Heap(const int x) //Конструктор, создаем кучу размером x
{
    mas = new int[x + 1];
    decrease = new int[2*x + 1];
    for (int i = 0; i < 2*x + 1; i++) {
        decrease[i] = -1;
    }
    countHeap = 0;
    countBuff = 0;
}

Heap::~Heap() //Деструктор
{
    delete[] mas;
    delete[] decrease;
}

void Heap::siftUp(int i) //Восстановление свойств кучи, если этот элемент меньше своего предка
{
    while ( ( (i-1)/2 >= 0 ) && (mas[i] < mas[(i - 1) / 2]) ) {
        swap(mas[i], mas[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void Heap::siftDown(int i) //Восстановление свойст кучи, если этот элемент больше своего ребенка
{
    int leftChild;
    int rightChild;
    while (2 * i + 1 < countHeap) {
        leftChild = 2 * i + 1;
        rightChild = 2 * i + 2;
        int j = leftChild;
        if (rightChild < countHeap && mas[rightChild] < mas[leftChild])
            j = rightChild;
        if (mas[i] <= mas[j])
            break;
        swap(mas[i], mas[j]);
        i = j;
    }
}

void Heap::push(int x) //добавление элемента
{
    mas[countHeap] = x;
    decrease[countBuff] = x;
    countHeap++;
    countBuff++;
    siftUp(countHeap - 1);
}

int Heap::extractMin() //Берём минимум - он является корнем дерева
{
    if (countHeap == 0) {
        return -1;
    }
    int temp = mas[0];
    mas[0] = mas[countHeap - 1];
    countHeap--;
    siftDown(0);
    return temp;
}

void Heap::decreaseKey(int operation, int val) //заменяем ключ, который был добавлен на operation операции, ключом val
{
    operation--;
    int temp = decrease[operation];
    decrease[operation] = -1;
    if (temp != -1) {
        for (int i = 0; i < countHeap; i++) {
            if (mas[i] == temp) {
                mas[i] = val;
                siftUp(i);
            }
        }
    }
}

int main()
{
    ifstream in("priorityqueue.in");
    ofstream out("priorityqueue.out");
    string command;
    int x, y;
    Heap H(100001);
    while (!in.eof()) {
        in >> command;
        if (command == "push") {
            in >> x;
            H.push(x);
        }
        if (command == "extract-min") {
            x = H.extractMin();
            if (x == -1) {
                out << "*\n";
            }
            else
                out << x << '\n';
        }
        if (command == "decrease-key") {
            in >> x;
            in >> y;
            H.decreaseKey(x, y);
        }
    }

    return 0;
}