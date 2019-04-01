#include "PQueueh.h"

/* private update fuc */

void UpdateUp(PQueue* pQueue, int l, int p);
void UpdateDown(PQueue* pQueue, int l, int p);
 

PQueue* QInit(int nSize) {

	PQueue* myQ = (PQueue*)calloc(1, sizeof(PQueue));
	if (!myQ) {
		perror("nie udalo sie zaalokowac pamieci!\n");
		return NULL;
	}

	myQ->nTotalSize = nSize;
	myQ->nCurrSize = 0;
	myQ->pQArray = (QItem*)calloc(nSize, sizeof(QItem));

	if (!(myQ->pQArray)) {
		perror("nie udalo sie zaalokowac pamieci!\n");
		return NULL;
	}
	return myQ;
}


int QisEmpty(PQueue* pQueue) {
	return !(pQueue->nCurrSize);
}


int QDequeue(PQueue* pQueue) {

	if (!(pQueue->nCurrSize)) {
		perror("kolejka jest pusta!\n");
		return 0;
	}

	int value = pQueue->pQArray->nKey;
	*(pQueue->pQArray) = pQueue->pQArray[pQueue->nCurrSize--];//!!!
	UpdateDown(pQueue, 0, pQueue->nCurrSize);
	return value;
}

void QEnqueue(PQueue* pQueue, int nKey, int nPrior) {

	if (pQueue->nCurrSize == pQueue->nTotalSize) {
		perror("kolejka jest pe³na!\n");
		return;
	}

	pQueue->pQArray[pQueue->nCurrSize].nPrior = nPrior;
	pQueue->pQArray[pQueue->nCurrSize].nKey = nKey;
	pQueue->nCurrSize++;

	UpdateUp(pQueue, 0, pQueue->nCurrSize);
}


void QClear(PQueue* pQueue) {

	pQueue->nCurrSize = 0;
	memset(pQueue->pQArray, 0, pQueue->nTotalSize * sizeof(QItem));
}


void QFreeMemory(PQueue** pQueue) {

	free((*pQueue)->pQArray);
	free(*pQueue);
	*pQueue = NULL;
}


void QPrint(PQueue* pQueue) {
	for (int i = 0; i < pQueue->nCurrSize; i++)
		printf("pozycja: %d, wartosc: %d  klucz: %d\n", i, pQueue->pQArray[i].nKey, pQueue->pQArray[i].nKey);
}

/* Update */
void UpdateUp(PQueue* pQueue, int l, int p) {

	if (l == p)
		return;

	int i = l;
	int j = 2 * i + 1;
	QItem item = pQueue->pQArray[i];

	while (j <= p) {
		if (j < p)
			if (pQueue->pQArray[j].nPrior < pQueue->pQArray[j + 1].nPrior)
				j++;
		if (pQueue->pQArray[i].nPrior < item.nPrior)
			break;
		pQueue->pQArray[i] = pQueue->pQArray[j];
		i = j;
		j = 2 * i + 1;
	}
	pQueue->pQArray[i] = item;
}

void UpdateDown(PQueue* pQueue, int l, int p) {

	int i = p;
	int j = (i - 1) / 2;
	QItem item = pQueue->pQArray[i];

	while (i > 0 && pQueue->pQArray[j].nPrior < item.nPrior) {
		pQueue->pQArray[i] = pQueue->pQArray[j];
		i = j;
		j = (i - 1) / 2;
	}
	pQueue->pQArray[i] = item;
}


/* in/decrease prior */
void DecreaseKey(PQueue* p, int nKey, int nPrior) {
	if (nPrior < p->pQArray[nKey].nPrior) {
		p->pQArray[nKey].nPrior = nPrior;
		UpdateDown(p, nKey, p->nCurrSize - 1);
	}
	/*wyszukiwanie elementu o podanym kluczu, zamiana priorytatu na mniejszy, updatedown*/
}


void IncreaseKey(PQueue* p, int nKey, int nPrior) {
	if (nPrior > p->pQArray[nKey].nPrior) {
		p->pQArray[nKey].nPrior = nPrior;
		UpdateUp(p, 0, nKey);
	}

}