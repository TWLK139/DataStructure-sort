#pragma once
#ifndef SORT_H

#define SORT_H

#define DEBUG

#include<iostream>
#include <cstdlib>
#include <ctime>
#include<stdlib.h>

using namespace std;

#define elementType int
#define MAXLEN 200

//***********************˳���ṹ*************************//
typedef struct sList										//
{															//
	elementType data[MAXLEN];								//
	int listLen = 0;										//
}seqList, * seqP;			//���������͡����ָ������	//
//**********************************************************//

//*********************�������ṹ����***********************//
typedef struct lBNode										//
{															//
	elementType data;										//
	struct lBNode* lChild, * rChild;						//
}BiNode, * BiTree;											//
//**********************************************************//

//********************�ı����������нṹ********************//
//�����н��ṹ											//
typedef struct LNode										//
{															//
	BiTree point;					//����ַ���			//
	elementType data;				//Ԫ��ֵ���			//
	struct LNode* next, * prior;	//��һ������һ��ָ��	//
}queueNode;													//
															//
//�����нṹ												//
typedef struct LNodes										//
{															//
	queueNode* front;				//��ͷָ��				//
	queueNode* rear;				//��βָ��				//
	bool flag = false;				//������ڴ�ӡ������	//
}linkQueue, * lQP;											//
//**********************************************************//

//******************************************************��������************************************************************//
//���к�������																												//
bool initialQueue(lQP& Q);																//�����г�ʼ��						//
bool enQueue(lQP Q, BiTree data);														//���������						//
bool enQueue(lQP Q, elementType data);													//���������						//
bool outQueue(lQP Q, BiTree& data);														//�����г���						//
bool outQueue(lQP Q, elementType& data);												//�����г���						//
//˳���������																											//
void showSeqList(seqP L);																//��ӡ˳���						//
void creatSeqList(seqP L,int num = MAXLEN, int min = 100, int max = 999);				//���������˳���					//
//����������																												//
int partition(elementType A[], int start, int end);										//���Ż���							//
void quickSort(seqP L, int start, int end, BiTree* Tpp = nullptr, bool print = false);	//��������							//
void quickSort(seqP L, bool print = false);												//��������							//
bool partitionThree(seqP L);															//����3���Ի���						//
void shellSort(seqP L);																	//ϣ������							//
void shift(seqP L, int root, int max);													//���Ż��֣�С���ѣ�				//
void heapSort(seqP L);																	//������							//
bool merge(seqP L, int sA, int eA, int sB, int eB);										//ԭ�ع鲢							//
void mergeSort(seqP L);																	//�鲢����							//
//������ͨ�ú�������																										//
bool addTreeNode(BiTree* Tpp, elementType x);											//�����������½��					//
void creatTreeByFloor(BiTree& T, seqP& L, int n);										//˳�����������					//
bool creatTreeByFloor(BiTree& T, seqP& L);												//˳�����������					//
int getTreeHeight(BiTree T);															//��������߶�						//
void preTraverse(BiTree T);																//�������������					//
void inOrderTraverse(BiTree T);															//�������������					//
void postTraverse(BiTree T);															//�������������					//
void printBST(BiTree T);																//��ӡ������						//
void destoryTreeNode(BiTree T);															//���ٶ�����						//
bool destoryTree(BiTree& T);															//���ٶ�����						//
//**************************************************************************************************************************//

#endif // !SORT_H


#ifdef DEBUG
int DEBUG_exchangeNum = 0;
int DEBUG_carryNum = 0;
int DEBUG_compareNum = 0;
BiTree* TppHead = nullptr;
//DEBUG��������
void resetDEBUG(void);	//��ԭDEBUG����
//DEBUG��������
//������������ԭDEBUG����
void resetDEBUG(void)
{
	DEBUG_carryNum = 0;
	DEBUG_compareNum = 0;
	DEBUG_exchangeNum = 0;
	if (TppHead)
	{
		if (destoryTree(*TppHead))
		{
			TppHead = nullptr;
		}
		else
		{
			cout << "����ʧ��" << endl;
		}
	}
}
#endif // DEBUG


//*********************************************************��������*********************************************************//

//******************************************************�����к�������******************************************************//

//���������������г�ʼ��
//���룺����ָ��
//���أ��ɹ�����true��ʧ�ܷ���false
bool initialQueue(lQP& Q)
{
	if (Q == nullptr)
	{
		Q = new linkQueue;
		Q->front = new queueNode;
		Q->rear = Q->front;
		Q->front->next = nullptr;
		Q->front->prior = nullptr;

		return true;
	}
	else
	{
		cout << "��ǰָ����ռ�ã����г�ʼ��ʧ�ܣ�" << endl;

		return false;
	}
}


//�������������������
//���룺����ָ�룬���ָ��
//���أ��ɹ�����true��ʧ�ܷ���false
bool enQueue(lQP Q, BiTree data)
{
	if (Q != nullptr)
	{
		Q->rear->next = new queueNode;
		Q->rear->next->prior = Q->rear;
		Q->rear = Q->rear->next;
		Q->rear->point = data;
		Q->rear->next = nullptr;

		return true;
	}
	else
	{
		cout << "��ǰ����δ��ʼ�������ʧ�ܣ�" << endl;

		return false;
	}
}


//�������������������
//���룺����ָ�룬���ָ��
//���أ��ɹ�����true��ʧ�ܷ���false
bool enQueue(lQP Q, elementType data)
{
	if (Q != nullptr)
	{
		Q->rear->next = new queueNode;
		Q->rear->next->prior = Q->rear;
		Q->rear = Q->rear->next;
		Q->rear->data = data;
		Q->rear->next = nullptr;

		return true;
	}
	else
	{
		cout << "��ǰ����δ��ʼ�������ʧ�ܣ�" << endl;

		return false;
	}
}


//���������������г���
//���룺����ָ�룬����ָ��
//���أ��ɹ�����true��ʧ�ܷ���false
bool outQueue(lQP Q, BiTree& data)
{
	queueNode* dp = nullptr;

	if (Q != nullptr)
	{
		if (Q->front != Q->rear)
		{
			dp = Q->front->next;
			data = dp->point;
			Q->front->next = dp->next;
			if (dp->next)
			{
				dp->next->prior = Q->front;
			}
			delete(dp);
			if (Q->front->next == nullptr)
			{
				Q->rear = Q->front;
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "��ǰ����δ��ʼ��������ʧ�ܣ�" << endl;

		return false;
	}
}


//���������������г���
//���룺����ָ�룬����ָ��
//���أ��ɹ�����true��ʧ�ܷ���false
bool outQueue(lQP Q, elementType& data)
{
	queueNode* dp = nullptr;

	if (Q != nullptr)
	{
		if (Q->front != Q->rear)
		{
			dp = Q->front->next;
			data = dp->data;
			Q->front->next = dp->next;
			if (dp->next)
			{
				dp->next->prior = Q->front;
			}
			delete(dp);
			if (Q->front->next == nullptr)
			{
				Q->rear = Q->front;
			}

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "��ǰ����δ��ʼ��������ʧ�ܣ�" << endl;

		return false;
	}
}


//****************************************************������ͨ�ú�������****************************************************//

//���������������������½��
//���룺������ָ�룬˳���
//���أ��ɹ�����true��ʧ�ܷ���false
bool addTreeNode(BiTree* Tpp, elementType x)
{
	if (*Tpp == nullptr)
	{
		*Tpp = new BiNode;
		(*Tpp)->data = x;
		(*Tpp)->lChild = nullptr;
		(*Tpp)->rChild = nullptr;

		return true;
	}
	else
	{
		cout << "��ǰ�����ռ�ã�" << endl;

		return false;
	}
}


//����������˳�����������
//���룺������ָ�룬˳���˳�������ţ��ڴ�����ʱת�����±꣩
//���أ��ɹ�����true��ʧ�ܷ���false
void creatTreeByFloor(BiTree& T, seqP& L, int n)
{
	if (!T && n < L->listLen)
	{
		addTreeNode(&T, L->data[n - 1]);
		creatTreeByFloor(T->lChild, L, n * 2);
		creatTreeByFloor(T->rChild, L, n * 2 + 1);
	}
}


//����������˳�����������
//���룺������ָ�룬˳���
//���أ��ɹ�����true��ʧ�ܷ���false
bool creatTreeByFloor(BiTree& T, seqP& L)
{
	if (!T)
	{
		creatTreeByFloor(T, L, 1);		//��������ţ��ڴ�����ʱת�����±�

		return true;
	}
	else
	{
		return false;
	}
}


//������������������ĸ߶�
//���룺������ָ�� 
//���أ��������߶�
int getTreeHeight(BiTree T)
{
	int lh = 0, rh = 0;

	if (!T)
	{
		return 0;
	}
	else
	{
		lh = 1 + getTreeHeight(T->lChild);
		rh = 1 + getTreeHeight(T->rChild);

		return lh > rh ? lh : rh;
	}
}


//****************�������������****************
//�����������������������
//���룺������ָ�� 
//��ӡ�������ڴ�ӡ���������
void preTraverse(BiTree T)
{
	if (T)
	{
		cout << T->data << '\t';
		preTraverse(T->lChild);
		preTraverse(T->rChild);
	}
}


//****************�������������****************
//�����������������������
//���룺������ָ�� 
//��ӡ�������ڴ�ӡ���������
void inOrderTraverse(BiTree T)
{
	if (T)
	{
		inOrderTraverse(T->lChild);
		cout << T->data << '\t';
		inOrderTraverse(T->rChild);
	}
}


//****************�������������****************
//�����������������������
//���룺������ָ�� 
//��ӡ�������ڴ�ӡ���������
void postTraverse(BiTree T)
{
	if (T)
	{
		postTraverse(T->lChild);
		postTraverse(T->rChild);
		cout << T->data << '\t';
	}
}


//������������ӡ����������
//���룺���ֲ�����ָ�룬˳���
void printBST(BiTree T)
{
	int i = 0;
	int nowHeight = 1, height = 0;
	BiTree nowT = nullptr;
	lQP SQF = nullptr, SQS = nullptr, SQC = nullptr;

	height = getTreeHeight(T);

	initialQueue(SQF);
	initialQueue(SQS);
	enQueue(SQF, T);
	if (T)
	{
		SQF->flag = true;
	}
	while (SQF->flag)
	{
		while (outQueue(SQF, nowT))
		{
			cout << " ";
			for (i = 0; i < (int)(pow(2, height - nowHeight) - 1); i++)
			{
				cout << "  ";
			}
			if (nowT)
			{
				cout << nowT->data;
			}
			else
			{
				cout << "___";
			}
			for (i = 0; i < (int)(pow(2, height - nowHeight) - 1); i++)
			{
				cout << "  ";
			}

			if (nowT)
			{
				enQueue(SQS, nowT->lChild);
				enQueue(SQS, nowT->rChild);
				if (nowT->lChild || nowT->rChild)
				{
					SQS->flag = true;
				}
			}
			else
			{
				enQueue(SQS, nullptr);
				enQueue(SQS, nullptr);
			}
		}
		cout << endl;
		nowHeight++;
		SQF->flag = false;
		SQC = SQF;
		SQF = SQS;
		SQS = SQC;
	}

	cout << endl;
}


//�������������ٶ�����
//���룺���������ڵ�
void destoryTreeNode(BiTree T)
{
	if (T)
	{
		destoryTreeNode(T->lChild);
		destoryTreeNode(T->rChild);
		delete(T);
	}
}


//�������������ٶ�����
//���룺���������ڵ�
bool destoryTree(BiTree& T)
{
	if (T)
	{
		destoryTreeNode(T);
		T = nullptr;
	}

	if (T == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//******************************************************˳���������******************************************************//

//������������ӡ˳���
//���룺˳���ָ��
//��ӡ�������ڴ�ӡ˳�����Ԫ��
void showSeqList(seqP L)
{
	int i = 0;
	while (i < L->listLen)
	{
		cout << L->data[i] << "\t";
		i++;
	}
	cout << endl;
}


//�������������������˳���
//���룺˳���ָ�룬��������Ĭ��MAXLEN������������ޣ�Ĭ��100������������ޣ�Ĭ��999��
void creatSeqList(seqP L, int num, int min, int max)
{
	int index = 0;

	srand((int)time(nullptr));
	for (index = 0; index < num; index++)
	{
		L->data[index] = rand() % (max - min + 1) + min;
	}
	L->listLen = num;
}


//********************************************************����������********************************************************//

//�������������Ż��ֺ���
//���룺���飬��ʼ�±꣬�����±�
//���أ��м��±�
int partition(elementType A[], int start, int end)
{
	elementType keepData = A[start];

	while (start != end)
	{
		while (start<end && A[end]>keepData)
		{
#ifdef DEBUG
			DEBUG_compareNum++;
#endif // DEBUG

			end--;
		}
		if (start < end)
		{
			A[start] = A[end];
			start++;
#ifdef DEBUG
			DEBUG_exchangeNum++;
#endif // DEBUG
		}
		while (start < end && A[start] < keepData)
		{
#ifdef DEBUG
			DEBUG_compareNum++;
#endif // DEBUG

			start++;
		}
		if (start < end)
		{
			A[end] = A[start];
			end--;
#ifdef DEBUG
			DEBUG_exchangeNum++;
#endif // DEBUG
		}
	}

	A[start] = keepData;

	return start;
}


//������������������
//���룺˳���ָ�룬��ʼ�±꣬�����±꣬���������ָ���ָ�루�����ָ���򲻻ᴴ����Ĭ��Ϊ�գ�
void quickSort(seqP L, int start, int end, BiTree* Tpp, bool print)
{
	int mid = 0;
	BiTree* TppCl = nullptr, * TppCr = nullptr;

#ifdef DEBUG
	if (Tpp && end>=start)
	{
		addTreeNode(Tpp, L->data[start]);
		TppCl = &((*Tpp)->lChild);
		TppCr = &((*Tpp)->rChild);
	}
#endif // DEBUG

	if (start < end)
	{
		mid = partition(L->data, start, end);
#ifdef DEBUG
		DEBUG_carryNum++;
		cout << "����" << DEBUG_carryNum << "�ο��ź�" << endl;
		showSeqList(L);
		if (print)
		{
			cout << "��ǰ������Ϊ��" << endl;
			printBST(*TppHead);
		}
#endif // DEBUG

		quickSort(L, start, mid - 1, TppCl, print);
		quickSort(L, mid + 1, end, TppCr, print);
	}
}


//ʵ��ʮ.����.1����������
//���룺˳���ָ��
void quickSort(seqP L, bool print)
{
#ifdef DEBUG
	BiTree T = nullptr;
	TppHead = &T;
#else
	BiTree* TppHead = nullptr;
#endif // DEBUG


	quickSort(L, 0, L->listLen - 1, TppHead, print);

#ifdef DEBUG
	cout << endl << "���տ��Ž����" << endl;
	showSeqList(L);
	cout << "����������" << DEBUG_exchangeNum << endl;
	cout << "�Ƚϴ�����" << DEBUG_compareNum << endl;
	cout << "ִ�д�����" << DEBUG_carryNum << endl;
	if (print)
	{
		cout << "������������" << endl;
		printBST(*TppHead);
		cout << "���������\t";
		preTraverse(*TppHead);
		cout << endl;
		cout << "���������\t";
		inOrderTraverse(*TppHead);
		cout << endl;
		cout << "���������\t";
		postTraverse(*TppHead);
	}
	resetDEBUG();
#endif // DEBUG
}


//ʵ��ʮ.����.2��������3�����Ի�������
//���룺˳���
bool partitionThree(seqP L)
{
	elementType keepData = L->data[0];
	lQP Q = nullptr;
	int sE = 0, eE = L->listLen - 1, s = 0, e = L->listLen - 1;

	if (initialQueue(Q))
	{
#ifdef DEBUG
		cout << "�Ƚ�Ԫ������Ϊ��";
#endif // DEBUG

		while (s!=e)
		{
			while (s < e && L->data[e] % 3 != 0)
			{
#ifdef DEBUG
				cout << L->data[e] << '\t';
#endif // DEBUG

				if (L->data[e] % 3 == 2)
				{
					L->data[eE] = L->data[e];
					eE--;
				}
				else
				{
					enQueue(Q, L->data[e]);
				}
				e--;
			}
			if (s < e)
			{
				L->data[sE] = L->data[e];
				sE++;
				s++;
			}
			while (s < e && L->data[s] % 3 != 2)
			{
#ifdef DEBUG
				cout << L->data[e] << '\t';
#endif // DEBUG

				if (L->data[s] % 3 == 0)
				{
					L->data[sE] = L->data[s];
					sE++;
				}
				else
				{
					enQueue(Q, L->data[s]);
				}
				s++;
			}
			if (s < e)
			{
				L->data[eE] = L->data[s];
				eE--;
				e--;
			}
		}
#ifdef DEBUG
		cout << endl;
#endif // DEBUG

		if (keepData % 3 != 2)
		{
			L->data[sE] = keepData;
			sE++;
		}
		else
		{
			L->data[eE] = keepData;
			eE--;
		}
		while (sE <= eE)
		{
			if (outQueue(Q, keepData))
			{
				L->data[sE] = keepData;
				sE++;
			}
			else
			{
				return false;
			}
		}

#ifdef DEBUG
		cout << "���ֽ��Ϊ��" << endl;
		showSeqList(L);
#endif // DEBUG


		return true;
	}
	else
	{
		return false;
	}
}


//ʵ��ʮ.����.3��ϣ������
//���룺˳���
void shellSort(seqP L)
{
	elementType temp = NULL;
	int step = L->listLen / 2, i, j;

	while (step > 0)
	{
		for (i = step; i < L->listLen; i+=step)
		{
			temp = L->data[i];
			j = i;
			while (j >= step && temp < L->data[j - step])
			{
#ifdef DEBUG
				DEBUG_compareNum++;
				DEBUG_exchangeNum++;
#endif // DEBUG

				L->data[j] = L->data[j - step];
				j -= step;
			}
#ifdef DEBUG
			DEBUG_exchangeNum++;
#endif // DEBUG

			L->data[j] = temp;
		}
#ifdef DEBUG
		DEBUG_carryNum++;
		cout << "����" << DEBUG_carryNum << "��ϣ�������" << endl;
		showSeqList(L);
#endif // DEBUG

		step /= 2;
	}

#ifdef DEBUG
	cout << endl << "����ϣ����������" << endl;
	showSeqList(L);
	cout << "����������" << DEBUG_exchangeNum << endl;
	cout << "�Ƚϴ�����" << DEBUG_compareNum << endl;
	cout << "ִ�д�����" << DEBUG_carryNum << endl;

	resetDEBUG();
#endif // DEBUG

}


//�������������Ż��֣�С���ѣ�
//���룺˳���ָ�룬��ʼ�±꣬�����±�
void shift(seqP L, int root, int max)
{									//root��max����Ԫ�ص���ţ������±��һ
	elementType keepData = L->data[root - 1];
	int nowSon = 2 * root;

	while (nowSon <= max)
	{
		if (nowSon < max && L->data[nowSon - 1] < L->data[nowSon])
		{
#ifdef DEBUG
			DEBUG_compareNum++;
#endif // DEBUG

			nowSon++;
		}
		if (keepData < L->data[nowSon - 1])
		{
#ifdef DEBUG
			DEBUG_compareNum++;
			DEBUG_exchangeNum++;
#endif // DEBUG
			L->data[root - 1] = L->data[nowSon - 1];
			root = nowSon;
			nowSon *= 2;
		}
		else
		{
			break;
		}
	}
#ifdef DEBUG
	DEBUG_exchangeNum++;
#endif // DEBUG

	L->data[root - 1] = keepData;
}


//ʵ��ʮ.����.5��������
//���룺˳���
void heapSort(seqP L)
{
	int i = L->listLen / 2;
	elementType keepData = NULL;
#ifdef DEBUG
	BiTree T = nullptr;
#endif // DEBUG

#ifdef DEBUG
	cout << "��ʼ����ǰ����������ʽ��" << endl;
	showSeqList(L);
	cout << "��ʼ����ǰ���ѵ�����ʽ��" << endl;
	creatTreeByFloor(T, L);
	printBST(T);
	destoryTree(T);
	cout << "������̵Ķѱ仯���£�" << endl;
#endif // DEBUG

	for (i; i >= 1; i--)
	{			//ֱ�Ӵ����Ӧ����ţ���shift��Ԫ�ؽ��в���ʱ��ת�����±�
		shift(L, i, L->listLen);
#ifdef DEBUG
		DEBUG_carryNum++;
		cout << "��" << DEBUG_carryNum << "�γ�ʼ�������" << endl;
		cout << "��ǰ��������ʽ����ʼ������" << endl;
		showSeqList(L);
		cout << "��ǰ�ѵ�����ʽ����ʼ������" << endl;
		creatTreeByFloor(T, L);
		printBST(T);
		destoryTree(T);
#endif // DEBUG

	}
#ifdef DEBUG
	cout << "��ʼ����ִ��ɸѡ����������" << DEBUG_carryNum << endl;
	DEBUG_carryNum = 0;
	cout << "��ʼ����ɺ�������̶ѵı仯���£�" << endl;
#endif // DEBUG

	for (i = L->listLen; i >= 2; i--)
	{
#ifdef DEBUG
		DEBUG_carryNum++;
		cout << "��" << DEBUG_carryNum << "������ɸѡ�����" << endl;
		cout << "��ǰ��������ʽ��" << endl;
		showSeqList(L);
		cout << "��ǰ�ѵ�����ʽ��" << endl;
		creatTreeByFloor(T, L);
		printBST(T);
		destoryTree(T);
#endif // DEBUG

		keepData = L->data[i - 1];
		L->data[i - 1] = L->data[0];
		L->data[0] = keepData;

		shift(L, 1, i - 1);
	}
#ifdef DEBUG
	cout << "������������ʽ��" << endl;
	showSeqList(L);
	cout << "�����ѵ�����ʽ��" << endl;
	creatTreeByFloor(T, L);
	printBST(T);
	destoryTree(T);
	cout << "�Ƚϴ�����" << DEBUG_compareNum << endl;
	cout << "����������" << DEBUG_exchangeNum << endl;
	cout << "ִ�д�����" << DEBUG_carryNum << endl;

	resetDEBUG();
#endif // DEBUG

}


//����������ԭ�ع鲢
//���룺ԭ�ع鲢��˳����鲢����A�Ŀ�ʼ�±꣬�鲢����A�Ľ����±꣬�鲢����B�Ŀ�ʼ�±꣬�鲢����B�Ľ����±�
//���أ��ɹ�����true��ʧ�ܷ���false
bool merge(seqP L, int sA, int eA, int sB, int eB)
{
	elementType keepData = NULL;
	int index = sA;
	lQP data = nullptr;

	if (eA < sB && eB < L->listLen && initialQueue(data))
	{
		while (sA <= eA && sB <= eB)
		{
			if (L->data[sA] <= L->data[sB])
			{
				enQueue(data, L->data[sA]);
				sA++;
			}
			else
			{
				enQueue(data, L->data[sB]);
				sB++;
			}
		}
		while (sA <= eA)
		{
			enQueue(data, L->data[sA]);
			sA++;
		}
		while (sB <= eB)
		{
			enQueue(data, L->data[sB]);
			sB++;
		}
		while (outQueue(data, keepData))
		{
			L->data[index] = keepData;
			index++;
		}
		return true;
	}
	else
	{
		return false;
	}
}


//ʵ��ʮ.����.6���鲢����
//���룺˳���
void mergeSort(seqP L)
{
	int step = 1, begin = 0;
#ifdef DEBUG
	cout << "��ʼ˳���Ϊ��" << endl;
	showSeqList(L);
#endif // DEBUG

	while (step < L->listLen)
	{
		begin = 0;
		while (begin < L->listLen - 2 * step)
		{
			merge(L, begin, begin + step - 1, begin + step, begin + 2 * step - 1);
			begin += step * 2;
		}
		merge(L, begin, begin + step - 1, begin + step, L->listLen - 1);
		step *= 2;
#ifdef DEBUG
		DEBUG_carryNum++;
		cout << "��" << DEBUG_carryNum << "�ι鲢��" << endl;
		showSeqList(L);
#endif // DEBUG

	}
#ifdef DEBUG
	cout << "��ִ�й鲢������" << DEBUG_carryNum << endl;
	cout << "ִ�н�����˳���Ϊ��" << endl;
	showSeqList(L);

	resetDEBUG();
#endif // DEBUG

}