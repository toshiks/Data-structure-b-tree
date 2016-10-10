#include <stdio.h>
#include <stdlib.h>
#include "B-tree.h"
#define MAX_IN ( ( 1 << 31 )  - 1 )

int main ( int argc, char *argv[] )
{
    FILE *in;
    in = fopen( "input.txt", "r" );
    int t;
    scanf( "%d", &t );

    Tree *myTree = initTree( t );
    int x;
    for ( int i = 0; i < 40; i++ ){
        fscanf( in, "%d", &x );
        insertKeyIntoTree( myTree, x );
        write( myTree );
        printf("\n\n");
    }
    /*while ( x != 0 ) {
        scanf("%d", &x);
        deleteKeyFromTree(myTree, x);
        write(myTree);
    }*/

    fclose( in );
    destroyTree( myTree->root );
    system("pause>>null");
    return 0;
}