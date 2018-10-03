#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <cstring>
#include <string>
#include <stdlib.h>

#include "QString"
#include <QDateTime>

enum COLUMNS {COL_DATE, COL_NAME, COL_SHOT_NAME, COL_COUNT_IN, COL_COUNT, COL_EDIZM, COL_COST, COL_CATEGOTRY, COL_SUM_COUNT, COL_GAR, COL_TYPE_GAR};

enum eWarrantyType{
    NONE = 0,
    DAYS,
    MONTHS,
    YEARS
};

struct sItem{
    QString name;
    QString newname;
    float count;
    float countFactor;
    QString countType;
    QString category;
    eWarrantyType warrantyType;
    int warrantyPeriod;
    int price;
    QDateTime dateTime;
    QString getTotalCount(){
        return QString("%1 %2").arg(QString::number(count*countFactor)).arg(countType);
    }
};

enum RECONIZE_RESULT {NO_RECONIZE, RECONIZE_PROGRESS, RECONIZE_OK, RECONIZE_ERR};

//структура для модели
struct mItem{
    QDateTime date;
    QString name;
    QString category;
    double count;
    double price;
    double sum;
    //---
    QString FN;
    QString FD;
    QString FPD;
    RECONIZE_RESULT result;
};

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

inline QString getGuid()
{
    char g[256] = {0};
    QString guid;
    generateGuid(g);
    guid.append(g);
    return guid;
}

inline QString getDateTime()
{
    QDateTime now = QDateTime::currentDateTime();
    return QString("%1-%2-%3T%4:%5:%6:%7").arg(now.date().year()).arg(now.date().month()).arg(now.date().day()).arg(now.time().hour()).arg(now.time().minute()).arg(now.time().second()).arg(now.time().msec());
}

inline QString getDate()
{
    QDateTime now = QDateTime::currentDateTime();
    return QString("%1-%2-%3").arg(now.date().year()).arg(now.date().month()).arg(now.date().day());
}

#endif // UTILS_H
