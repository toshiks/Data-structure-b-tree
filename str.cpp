//
// Created by toxad on 01.11.2016.
//
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "str.h"

unsigned int strLength( string *s )
{
    return s->size;
}

string* strCreate()
{
    string *str = ( string * )malloc( sizeof( string ) );

    str->size = STR_INIT_SIZE;
    str->str  = ( char * )calloc( str->size, sizeof( char ) );

    return str;
}

string** strMasCreate( int size )
{
    string **s = ( string ** )malloc( size * sizeof( string * ) );

    for (int i = 0; i < size; i++ )
        s[i] = strCreate();

    return s;
}

void strDestroy( string* strDelete )
{
    free( strDelete->str );
    free( strDelete );
}

void strScan( string* s, FILE *in )
{
    if (strLength(s) > 0) {
        free(s->str);
        s->size = STR_INIT_SIZE;
        s->str = (char*) calloc(s->size, sizeof(char));
    }

    char c;
    unsigned int length = 0;
    while ((c = getc( in )) != '\n') {
        if (length + 1 > s->size) {
            s->size += 100;
            s->str = (char*) realloc(s->str, s->size);
        }

        s->str[length] = c;
        length++;
    }

    s->str[length] = '\0';
}

void strPrint( string* s)
{
    printf("%s\n", s->str );
}

void strCopy ( string* s, string* p )
{
    if (s->size != p->size){
        p->size = s->size;
        p->str  = ( char *)realloc( p->str, s->size );
    }

    strcpy(p->str, s->str);
}

void strMasDestroy( string** strDelete, int size )
{
    for (int i = 0; i < size; i++ )
        strDestroy( strDelete[i] );
    free( strDelete );
}
