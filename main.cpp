#include <stdio.h>
#include "B+tree/B+tree.h"
#include <stdlib.h>

int main ( int argc, char *argv[] )
{
    int t;
    int temp;
    int quantity;
    int indx;

    printf("Enter the minimum number of keys in a node (3 or more): ");
    scanf( "%d", &t );

    printf("Enter the quantity elements of tree: ");
    scanf( "%d", &quantity );

    struct Tree *myTree = initTree( t );
    string *a = strCreate();

    for ( int i = 0; i < quantity; i++ ){
        scanf( "%d", &indx );
        strScan( a, stdin );
        insertKeyIntoTree( myTree, indx, a );
    }

    write( myTree );

    printf( "Enter the index of the item that you want to remove: " );
    scanf( "%d", &temp );
    deleteKeyFromTree( myTree, temp );

    write( myTree );
    system("pause>>null");


    destroyTree(myTree->root, myTree->level);

    return 0;
}