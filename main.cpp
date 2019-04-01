// PQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PQueueh.h"
#include <time.h>

#define _CNTRL

int main()
{
	//srand((unsigned)time(NULL)); //	'losowe' liczby do testow
	int nSize = 10; // rozmiar kolejki
	PQueue* pQueue = QInit(nSize);

	/* inicjalizacja */
	for (int i = 0; i < nSize; i++) {
		int nPrior = rand() % nSize + 1;
		int nKey = rand() % (nSize * 2) + 1;
		QEnqueue(pQueue, nKey, nPrior);
	}
#ifdef _CNTRL
	QPrint(pQueue);
	printf("\n\n");
#endif


	/* Dequeue */
	for (int i = 0; i <= 4; i++) {
		int deQ = QDequeue(pQueue);
		printf("wartosc: %d\n", deQ);
	}
#ifdef _CNTRL
	QPrint(pQueue);
	printf("\n\n");
#endif


	/* Enqueue */
	QEnqueue(pQueue, 7, 4);
	QEnqueue(pQueue, 3, 9);
#ifdef _CNTRL
	QPrint(pQueue);
	printf("\n\n");
#endif

	/* zwalnianie pamieci */
	QFreeMemory(&pQueue);

	return 0;
}

