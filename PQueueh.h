#pragma once
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

typedef struct {
	int nKey;
	int nPrior;
}QItem;

typedef struct {
	QItem* pQArray; // kolejka stogowa (calloc - ilosc el.)
	int nTotalSize;
	int nCurrSize;
}PQueue;

/* Queue func */
PQueue* QInit(int nSize);
int QisEmpty(PQueue* pQueue); // 1 Empty, 0 nEmpty
int QDequeue(PQueue* pQueue);
void QEnqueue(PQueue* pQueue, int nKey, int nPrior);
void QClear(PQueue* pQueue);
void QFreeMemory(PQueue** pQueue);
void QPrint(PQueue* pQueue);

/* in/decrease prior */
void IncreaseKey(PQueue* p, int nKey, int nPrior);
void DecreaseKey(PQueue* p, int nKey, int nPrior);

