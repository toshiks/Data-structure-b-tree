//
// Created by toxad on 02.11.2016.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include "str.h"

struct Node{        //структура листа
    int leaf;       //является ли узел листом
    int counter;    //количество заполненных ячеек
    int *key;       //значение ячеек
    string **str;
    Node **child;   //указатели на детей
};

struct Tree{        //структура дерева
    int level;      //количество уровней дерева
    Node *root;     //указатель на корень дерева
};

Tree* initTree                ( int levelTree );                                                              //инициализация дерева
void insertKeyIntoTree        ( struct Tree *, int newKey, struct string *newStr);                            //вставка ключа в дерево
void write                    ( struct Tree * );                                                              //вывод дерева
bool deleteKeyFromTree        ( struct Tree *, int deleteKey );                                               //удаление ключа из дерева
void destroyTree              ( struct Node *, int levelTree );                                               //удаление дерева


#endif //B_TREE_B_TREE_H
