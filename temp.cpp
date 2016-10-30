#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct heaper {
    int key;
    int val;
};

void swap(heaper &x, heaper &y)
{
    heaper tmp = x;
    x = y;
    y = tmp;
}



class Heap {
private:
    int countHeap;			//количество ключей в куче
    vector<heaper> mas;				//сама куча
    void siftUp(int i);
    void siftDown(int i);
public:
    Heap();
    void push(int x, int key);
    int extractMin();
    void decreaseKey(int operation, int val);
    bool isEmpty();
};

Heap::Heap() //Конструктор, создаем кучу размером x
{
    countHeap = 0;
}


void Heap::siftUp(int i) //Восстановление свойств кучи, если этот элемент меньше своего предка
{
    while (((i - 1) / 2 >= 0) && (mas[i].val < mas[(i - 1) / 2].val)) {
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
        if (rightChild < countHeap && mas[rightChild].val < mas[leftChild].val)
            j = rightChild;
        if (mas[i].val <= mas[j].val)
            break;
        swap(mas[i], mas[j]);
        i = j;
    }
}

void Heap::push(int x, int key) //добавление элемента
{
    heaper temp;
    temp.val = x;
    temp.key = key;
    mas.push_back(temp);
    countHeap++;
    siftUp(countHeap - 1);
}

int Heap::extractMin() //Берём минимум - он является корнем дерева
{
    int temp = mas[0].val;
    mas[0] = mas[countHeap - 1];
    mas.pop_back();
    countHeap--;
    siftDown(0);
    return temp;
}

void Heap::decreaseKey(int operation, int val) //заменяем ключ, который был добавлен на operation операции, ключом val
{
    for (int i = 0; i < countHeap; i++) {
        if (mas[i].key == operation) {
            mas[i].val = val;
            siftDown(i);
            siftUp(i);
            break;
        }
    }
}

bool Heap::isEmpty()
{
    if (countHeap == 0)
        return 1;
    else
        return 0;
}

int main()
{
    ifstream in("priorityqueue.in");
    ofstream out("priorityqueue.out");
    string command;
    int x, y;
    Heap H;
    int coun = 0;
    while (in >> command) {
        coun++;
        if (command == "push") {
            in >> x;
            H.push(x, coun);
        }
        if (command == "extract-min") {
            if (H.isEmpty()) {
                out << "*\n";
            }
            else
                out << H.extractMin() << '\n';
        }
        if (command == "decrease-key") {
            in >> x;
            in >> y;
            H.decreaseKey(x, y);
        }
    }
    in.close();
    out.close();
    return 0;
}