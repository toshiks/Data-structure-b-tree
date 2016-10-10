//
// Created by toxad on 10.10.2016.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

struct Node{        //структура листа
    int leaf;       //является ли узел листом
    int counter;    //количество заполненных ячеек
    int *key;       //значение ячеек
    Node **child;   //указатели на детей
};

struct Tree{        //структура дерева
    int level;      //количество уровней дерева
    Node *root;     //указатель на корень дерева
};

Tree* initTree                ( int levelTree );                                                       //инициализация дерева
void insertKeyIntoTree        ( Tree *, int newKey);                                                   //вставка ключа в дерево
void write                    ( Tree * );                                                              //вывод дерева
bool deleteKeyFromTree        ( Tree *, int deleteKey );                                               //удаление ключа из дерева
void destroyTree              ( Node * );                                                              //удаление дерева

#endif //B_TREE_B_TREE_H
