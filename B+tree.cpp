//
// Created by toxad on 02.11.2016.
//
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "B+tree.h"

void swap (int *x, int *y)
{
    /*
     * Функиция, меняющая местами два числа
     */

    int t = *x;
    *x = *y;
    *y = t;
}

struct ParentWithChild{   //структура связи родителя и сына
    Node *children;       //узел-сын
    Node *parent;         //узел-родитель
    int position;         //позиция сына в родителе
};

void swap                     ( int *, int * );                                                        //меняем местами два числа
Node* initNode                ( int levelTree );                                                       //инициализация узла дерева
void splitNode                ( Node *, int levelTree, int position );
void insertKeyIntoNode ( Node *currentNode, int levelTree, int newKey, string *newStr );
bool deleteKeyFromNode ( Node *currentNode, int levelTree, int position, int deleteKey );
int findKeyInNode ( Node *, int findKey );
void replaceKeyToRightLeaf( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position);
void replaceKeyToLeftLeaf( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position);
void replaceKeyToRightNode( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position);
void replaceKeyToLeftNode( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position);
bool mergeLeafs ( Node *currentNode, int levelTree, int positionFirst, int positionSecond );
int ogr( int levelTree );

int ogr( int levelTree )
{
    return 2 * levelTree - 1;
}

Node* initNode ( int levelTree )
{
    Node *temp = ( Node * )malloc( sizeof( Node ) );

    temp->str = strMasCreate( 2 * levelTree - 1 );
    temp->counter = 0;
    temp->child = ( Node ** )malloc( 2 * levelTree * sizeof( Node * ) );
    temp->key = ( int * )malloc(  ( 2 * levelTree - 1 ) * sizeof( int ) );
    temp->leaf = true;

    return temp;
}

Tree* initTree ( int levelTree )
{
    Tree *temp = ( Tree * )malloc( sizeof( Tree ) );

    temp->level = levelTree;
    temp->root = initNode( levelTree );

    return temp;
}

void insertKeyIntoTree ( Tree *currentTree, int newKey, string *newStr)
{
    Node *tempRoot = currentTree->root;

    if ( tempRoot->counter + 1 == ogr( currentTree->level ) ){
        Node *newRoot = initNode( currentTree->level );

        currentTree->root = newRoot;
        newRoot->leaf = false;
        newRoot->child[ 0 ] = tempRoot;

        insertKeyIntoNode( newRoot, currentTree->level, newKey, newStr );
    }
    else{
        insertKeyIntoNode( tempRoot, currentTree->level, newKey, newStr );
    }
}

void splitNode( Node *currentNode, int levelTree, int position )
{
    Node *firstPart = currentNode->child[ position ];
    Node *secondPart = initNode( levelTree );

    secondPart->leaf = firstPart->leaf;
    secondPart->counter = levelTree;
    if ( !secondPart->leaf ) {
        secondPart->counter -= 1;

        for (int j = 0; j < secondPart->counter; j++) {

            secondPart->key[j] = firstPart->key[j + levelTree];
            strCopy(firstPart->str[j + levelTree - 1], secondPart->str[j]);
        }


        for (int j = 0; j <= secondPart->counter; j++) {

            secondPart->child[j] = firstPart->child[j + levelTree ];
        }
    }
    else{
        for (int j = 0; j < levelTree; j++) {

            secondPart->key[j] = firstPart->key[j + levelTree - 1];
            strCopy(firstPart->str[j + levelTree - 1], secondPart->str[j]);
        }
    }

    firstPart->counter = levelTree - 1;
    if ( firstPart->leaf ) {
        firstPart->child[ levelTree - 1 ] = secondPart;
    }

    for ( int j = currentNode->counter + 1; j >= position + 1; j-- ){

        currentNode->child[ j + 1 ] = currentNode->child[ j ];
    }

    currentNode->child[ position + 1 ] = secondPart;

    for ( int j = currentNode->counter; j >= position; j-- ){

        currentNode->key[ j + 1 ] = currentNode->key[ j ];

    }

    currentNode->key[ position ] = firstPart->key[ levelTree - 1 ];
    strDestroy( currentNode->str[ position ] );
    currentNode->str[ position ] = strCreate();

    currentNode->counter += 1;
}

void insertKeyIntoNode ( Node *currentNode, int levelTree, int newKey, string *newStr )
{
    int pos = currentNode->counter - 1;

    if ( currentNode->leaf ){
        while ( ( pos >= 0 ) && newKey < currentNode->key[ pos ] ){
            currentNode->key[ pos + 1 ] = currentNode->key[ pos ];
            strCopy( currentNode->str[ pos ], currentNode->str[ pos + 1 ] );
            pos -= 1;
        }

        pos += 1;

        currentNode->key[ pos ] = newKey;
        strCopy( newStr, currentNode->str[ pos ] );

        currentNode->counter += 1;
    }
    else{

        while ( ( pos >= 0 ) && ( newKey < currentNode->key[ pos ] ) ){

            pos -= 1;
        }

        pos += 1;

        insertKeyIntoNode( currentNode->child[ pos ], levelTree, newKey, newStr );

        if ( currentNode->child[ pos ]->counter == ogr( levelTree ) ){

            if ( currentNode->child[ pos ]->leaf ) {
                splitNode(currentNode, levelTree, pos);
            }
            else
                splitNode( currentNode, levelTree, pos  );

            //printf("%d", currentNode->key[pos] );
        }

    }
}

void wr ( Node *temp, Tree *tr )
{
    printf("%s %d\n", "Start Node:", temp->counter);
    for ( int i = 0; i < temp->counter; i++ ){
        printf("%d ", temp->key[i]);
        strPrint( temp->str[i] );
    }
    printf("\n");

        if (temp->leaf) {
            printf("%s\n\n", "End Leaf.");
        } else {
            for (int i = 0; i <= temp->counter; i++) {
                    wr(temp->child[i], tr);
            }
            printf("%s\n\n", "End Node.");
        }
}

void write( Tree *temp )
{
    wr( temp->root, temp );
}

bool deleteKeyFromTree( Tree *currentTree, int deleteKey )
{
    //int pos = findKeyInNode( currentTree->root, deleteKey );
    //printf("position: %d\n", pos);
    return deleteKeyFromNode( currentTree->root, currentTree->level, 0, deleteKey );
}

bool mergeNodes ( Node *currentNode, int levelTree, int positionFirst, int positionSecond )
{
    /*
     * Соединение двух узлов в один
     * Из предка берем текущий ключ, относительно
     * которого выбираются узлы, и опускается в левого предка.
     * В левого предка также сливается правый предок, который
     * впоследствии удаляется.
     * Далее возможны 2 варианта:
     *   1. Если родитель состоял из одного элемента - заменить
     *      его левым ребенком
     *   2. Если родитель состоит из множества элементов - удаляем
     *      искомый элемент
     *
     * currentNode    - рассматриваемый предок, дети которого сольются
     * levelTree      - основная характеристика B-дерева
     * positionFirst  - позиция левого ребенка в currentNode
     * positionSecond - позиция правого ребенка в currentNode
     */

    if ( positionFirst < 0 || positionFirst > currentNode->counter ) {

        return false;
    }

    if ( positionSecond < 0 || positionSecond > currentNode->counter ) {

        return false;
    }

    if ( positionFirst > positionSecond ) {

        swap( &positionFirst, &positionSecond );
    }

    Node *firstNode  = currentNode->child[ positionFirst ];
    Node *secondNode = currentNode->child[ positionSecond ];



    if ( ( firstNode->counter + secondNode->counter + 1 ) > ( 2 * levelTree - 1 ) ){

        return false;
    }

    firstNode->key[ firstNode->counter ] = currentNode->key[ positionFirst ]; //спускаем предка
    firstNode->counter += 1;

    for ( int i = 0; i < secondNode->counter; i++ ){

        firstNode->key[ i + firstNode->counter ] = secondNode->key[ i ];
    }
    for ( int i = 0; i <= secondNode->counter; i++ ){

        firstNode->child[ i + firstNode->counter ] = secondNode->child[ i ];
    }

    firstNode->counter += secondNode->counter;

    //destroyNode( secondNode );


    if ( currentNode->counter != 1 ){

        for ( int i = positionFirst; i < currentNode->counter - 1; i++ ) {

            currentNode->key[ i ] = currentNode->key[ i + 1 ];
        }

        for ( int i = positionFirst + 1; i < currentNode->counter; i++ ) {

            currentNode->child[ i ] = currentNode->child[ i + 1 ];
        }

        currentNode->counter -= 1;
    }
    else{

        currentNode->counter = firstNode->counter;
        currentNode->leaf    = firstNode->leaf;

        for ( int i = 0; i < currentNode->counter; i++ ) {

            currentNode->key[ i ] = firstNode->key[ i ];
        }

        for ( int i = 0; i <= currentNode->counter; i++ ) {

            currentNode->child[ i ] = firstNode->child[ i ];
        }

        //destroyNode( firstNode );
    }

    return true;
}

bool deleteKeyFromNode ( Node *currentNode, int levelTree, int position, int deleteKey )
{
    if ( !currentNode->leaf ){
        int pos = findKeyInNode( currentNode, deleteKey );
        printf("position: %d\n", pos);
        if ( currentNode->child[ pos ]->leaf ){
            if ( currentNode->child[ pos ]->counter > levelTree - 1){
                deleteKeyFromNode(  currentNode->child[ pos ], levelTree, pos, deleteKey );
            }
            else{
                if ( pos != currentNode->counter ){
                    if ( currentNode->child[ pos + 1]->counter > levelTree - 1 ){
                        replaceKeyToLeftLeaf( currentNode, currentNode->child[ pos ], currentNode->child[ pos + 1 ], pos );
                        currentNode->key[ pos ] = currentNode->child[ pos + 1 ]->key[ 0 ];
                        return deleteKeyFromNode(  currentNode->child[ pos ], levelTree, pos, deleteKey );

                    }
                    else{
                        mergeLeafs( currentNode, levelTree, pos, pos + 1 );
                        printf("ok\n");
                        if ( currentNode->leaf ){
                            return deleteKeyFromNode( currentNode, levelTree, pos, deleteKey );
                        }
                        else{
                            return deleteKeyFromNode( currentNode->child[ pos ], levelTree, pos, deleteKey );
                        }

                    }
                }
            }
        }
        else{
            bool temp = currentNode->child[pos]->leaf;
            deleteKeyFromNode( currentNode->child[ pos ], levelTree, pos, deleteKey );
            if ( currentNode->leaf )
                temp = 0;
            else {
                temp ^= currentNode->child[pos]->leaf;
                if ( currentNode->child[pos]->counter < levelTree - 1)
                    temp = 1;
            }

            if ( temp ){
                if ( currentNode->child[ pos + 1 ]->counter > levelTree - 1 ){
                    printf("parent: %d\n", currentNode->child[ pos + 1 ]->key[ 0 ]);
                    //swap( &currentNode->key[ pos ], &currentNode->child[ pos + 1 ]->key[ 0 ] );

                    replaceKeyToLeftNode( currentNode, currentNode->child[pos], currentNode->child[pos+1], pos );
                }
                else{

                    //swap( &currentNode->key[ pos ], &Right.parent->key[ Right.position ] );

                    mergeNodes( currentNode, levelTree, pos, pos + 1 );
                }

            }
        }
    }
    else{
        int pos = findKeyInNode( currentNode, deleteKey );
        if ( pos == -1 )
            return 0;
        for (int i = pos; i < currentNode->counter; i++){
            currentNode->key[ i ] = currentNode->key[ i + 1 ];
            strCopy( currentNode->str[ i + 1 ], currentNode->str[ i ] );
        }
        for (int i = pos; i <= currentNode->counter; i++){
            currentNode->child[ i ] = currentNode->child[ i + 1 ];
        }
        currentNode->counter--;
        return 1;
    }
}

bool mergeLeafs ( Node *currentNode, int levelTree, int positionFirst, int positionSecond ) {
    /*
     * Соединение двух узлов в один
     * Из предка берем текущий ключ, относительно
     * которого выбираются узлы, и опускается в левого предка.
     * В левого предка также сливается правый предок, который
     * впоследствии удаляется.
     * Далее возможны 2 варианта:
     *   1. Если родитель состоял из одного элемента - заменить
     *      его левым ребенком
     *   2. Если родитель состоит из множества элементов - удаляем
     *      искомый элемент
     *
     * currentNode    - рассматриваемый предок, дети которого сольются
     * levelTree      - основная характеристика B-дерева
     * positionFirst  - позиция левого ребенка в currentNode
     * positionSecond - позиция правого ребенка в currentNode
     */

    if (positionFirst < 0 || positionFirst > currentNode->counter) {

        return false;
    }

    if (positionSecond < 0 || positionSecond > currentNode->counter) {

        return false;
    }

    if (positionFirst > positionSecond) {

        swap(&positionFirst, &positionSecond);
    }

    Node *firstNode = currentNode->child[positionFirst];
    Node *secondNode = currentNode->child[positionSecond];


    if ((firstNode->counter + secondNode->counter + 1) > (2 * levelTree - 1)) {

        return false;
    }

    //firstNode->key[ firstNode->counter ] = currentNode->key[ positionFirst ]; //спускаем предка
    //firstNode->counter += 1;

    for (int i = 0; i < secondNode->counter; i++) {

        firstNode->key[i + firstNode->counter] = secondNode->key[i];
        strCopy(secondNode->str[i], firstNode->str[i + firstNode->counter]);
    }
    for (int i = 0; i <= secondNode->counter; i++) {

        firstNode->child[i + firstNode->counter] = secondNode->child[i];
    }

    firstNode->counter += secondNode->counter;

    //destroyNode( secondNode, levelTree );




    for (int i = positionFirst; i < currentNode->counter - 1; i++) {

        currentNode->key[i] = currentNode->key[i + 1];
    }

    for (int i = positionFirst + 1; i < currentNode->counter; i++) {

        currentNode->child[i] = currentNode->child[i + 1];
    }

    currentNode->counter -= 1;


    return true;
}

void replaceKeyToLeftLeaf( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position)
{
    /*
     * Функция перебрасывания ключа с правого ребенка в левого ребенка
     *
     * parentNode     - родителей двух детей
     * leftChildNode  - левый ребенок
     * rightChildNode - правый ребенок
     * position       - позиция ключа, относительно которого рассматриваются
     *                  дети в предке
     */

    leftChildNode->counter += 1;

    leftChildNode->key[ leftChildNode->counter - 1 ] = rightChildNode->key[ 0 ];
    strCopy( rightChildNode->str[0], leftChildNode->str[ leftChildNode->counter - 1 ] );
    leftChildNode->child[ leftChildNode->counter - 1 ]   =  rightChildNode->child[ 0 ];
    leftChildNode->child[ leftChildNode->counter ] = rightChildNode;
    leftChildNode->counter -= 1;
    parentNode->key[ position ] = rightChildNode->key[ 1 ];

    for ( int i = 0; i <= rightChildNode->counter; i++ ){

        rightChildNode->child[ i ] = rightChildNode->child[ i + 1 ];
    }

    for ( int i = 0; i < rightChildNode->counter; i++ ){

        rightChildNode->key[ i ] = rightChildNode->key[ i + 1 ];
        strCopy( rightChildNode->str[ i + 1 ], rightChildNode->str[ i ] );
    }

    rightChildNode->counter -= 1;
}
void replaceKeyToLeftNode( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position)
{
    /*
     * Функция перебрасывания ключа с правого ребенка в левого ребенка
     *
     * parentNode     - родителей двух детей
     * leftChildNode  - левый ребенок
     * rightChildNode - правый ребенок
     * position       - позиция ключа, относительно которого рассматриваются
     *                  дети в предке
     */

    leftChildNode->counter += 1;

    leftChildNode->key[ leftChildNode->counter - 1 ] = parentNode->key[ position ];
    leftChildNode->child[ leftChildNode->counter ]   =  rightChildNode->child[ 0 ];

    parentNode->key[ position ] = rightChildNode->key[ 0 ];

    for ( int i = 0; i <= rightChildNode->counter; i++ ){

        rightChildNode->child[ i ] = rightChildNode->child[ i + 1 ];
    }

    for ( int i = 0; i < rightChildNode->counter; i++ ){

        rightChildNode->key[ i ] = rightChildNode->key[ i + 1 ];
    }

    rightChildNode->counter -= 1;
}

void replaceKeyToRightLeaf( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position)
{
    /*
     * Функция перебрасывания ключа с левого ребенка в правого ребенка
     *
     * parentNode     - родителей двух детей
     * leftChildNode  - левый ребенок
     * rightChildNode - правый ребенок
     * position       - позиция ключа, относительно которого рассматриваются
     *                  дети в предке
     */

    for ( int i = rightChildNode->counter; i > 0; i-- ){

        rightChildNode->key[ i ] = rightChildNode->key[i - 1];
    }

    for ( int i = rightChildNode->counter + 1; i > 0; i-- ){

        rightChildNode->child[ i ] = rightChildNode->child[i - 1];
    }

    rightChildNode->counter += 1;

    rightChildNode->key[ 0 ]   = leftChildNode->key[ leftChildNode->counter - 1 ];
    rightChildNode->child[ 0 ] = leftChildNode->child[ leftChildNode->counter - 1 ];
    rightChildNode->str[ 0 ]   = rightChildNode->str[ leftChildNode->counter - 1 ];

    parentNode->key[ position ] = rightChildNode->key[ 0 ];

    leftChildNode->counter -= 1;
    leftChildNode->child[ leftChildNode->counter ] = rightChildNode;
}


void replaceKeyToRightNode( Node *parentNode, Node *leftChildNode, Node *rightChildNode, int position)
{
    /*
     * Функция перебрасывания ключа с левого ребенка в правого ребенка
     *
     * parentNode     - родителей двух детей
     * leftChildNode  - левый ребенок
     * rightChildNode - правый ребенок
     * position       - позиция ключа, относительно которого рассматриваются
     *                  дети в предке
     */

    for ( int i = rightChildNode->counter; i > 0; i-- ){

        rightChildNode->key[ i ] = rightChildNode->key[i - 1];
    }

    for ( int i = rightChildNode->counter + 1; i > 0; i-- ){

        rightChildNode->child[ i ] = rightChildNode->child[i - 1];
    }

    rightChildNode->counter += 1;

    rightChildNode->key[ 0 ]   = parentNode->key[ position ];
    rightChildNode->child[ 0 ] = leftChildNode->child[ leftChildNode->counter ];

    parentNode->key[ position ] = leftChildNode->key[ leftChildNode->counter - 1 ];

    leftChildNode->counter -= 1;
}

bool deleteKeyFromLeaf ( Node *nodeIsLeaf, int levelTree, int positionKey )
{
    /*
     * Функция удаления ключа из листа
     *
     * nodeIsLeaf  - рассматриваемый лист
     * levelTree   - основная характеристика B-дерева
     * positionKey - позиция ключа в листе
     */

    if ( nodeIsLeaf->counter == levelTree - 1 ) {

        return false;
    }

    for ( int i = positionKey; i < nodeIsLeaf->counter - 1; i++){

        nodeIsLeaf->key[ i ] = nodeIsLeaf->key[ i + 1 ];
    }

    for ( int i = positionKey; i < nodeIsLeaf->counter; i++){

        nodeIsLeaf->child[ i ] = nodeIsLeaf->child[ i + 1 ];
    }

    nodeIsLeaf->counter -= 1;

    return true;
}

int findKeyInNode ( Node *currentNode, int findKey )
{
    if ( currentNode->leaf ){
        for (int i = 0; i < currentNode->counter; i++ ){
            if ( currentNode->key[ i ] == findKey )
                return i;
        }
        return -1;
    }
    else{
        for (int i = 0; i < currentNode->counter; i++ ){
            if ( currentNode->key[ i ] > findKey )
                return i ;
        }
        return currentNode->counter;
    }
}