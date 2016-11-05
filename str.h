//
// Created by toxad on 01.11.2016.
//

#ifndef B_TREE_STR_H
#define B_TREE_STR_H
#define STR_INIT_SIZE 10
#include <stdio.h>

struct string{
    char *str;
    unsigned int size;
};

unsigned int strLength( string *s);
string* strCreate();
string** strMasCreate( int size );
void strDestroy( string* );
void strScan( string*, FILE * );
void strPrint( string* );
void strCopy ( string*, string* );
void strMasDestroy( string** strDelete, int size );


#endif //B_TREE_STR_H
