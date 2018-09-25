#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <cstring>
#include <string>
#include <stdlib.h>

inline char* generateGuid(char *guidStr)
{
    char *pGuidStr = guidStr;
    int i;

    srand(static_cast<unsigned int> (time(NULL)));  /*Randomize based on time.*/

    /*Data1 - 8 characters.*/
    *pGuidStr++ = '{';
    for(i = 0; i < 8; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    /*Data2 - 4 characters.*/
    *pGuidStr++ = '-';
    for(i = 0; i < 4; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    /*Data3 - 4 characters.*/
    *pGuidStr++ = '-';
    for(i = 0; i < 4; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    /*Data4 - 4 characters.*/
    *pGuidStr++ = '-';
    for(i = 0; i < 4; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    /*Data5 - 12 characters.*/
    *pGuidStr++ = '-';
    for(i = 0; i < 12; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    *pGuidStr++ = '}';
    *pGuidStr = '\0';
    return pGuidStr;
}

#endif // UTILS_H
