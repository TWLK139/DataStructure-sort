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

//***********************顺序表结构*************************//
typedef struct sList										//
{															//
	elementType data[MAXLEN];								//
	int listLen = 0;										//
}seqList, * seqP;			//定义结点类型、结点指针类型	//
//**********************************************************//

//*********************二叉树结构定义***********************//
typedef struct lBNode										//
{															//
	elementType data;										//
	struct lBNode* lChild, * rChild;						//
}BiNode, * BiTree;											//
//**********************************************************//

//********************改编数据链队列结构********************//
//链队列结点结构											//
typedef struct LNode										//
{															//
	BiTree point;					//结点地址存放			//
	elementType data;				//元素值存放			//
	struct LNode* next, * prior;	//下一个、上一个指针	//
}queueNode;													//
															//
//链队列结构												//
typedef struct LNodes										//
{															//
	queueNode* front;				//队头指针				//
	queueNode* rear;				//队尾指针				//
	bool flag = false;				//标记用于打印二叉树	//
}linkQueue, * lQP;											//
//**********************************************************//

//******************************************************函数声明************************************************************//
//队列函数声明																												//
bool initialQueue(lQP& Q);																//链队列初始化						//
bool enQueue(lQP Q, BiTree data);														//链队列入队						//
bool enQueue(lQP Q, elementType data);													//链队列入队						//
bool outQueue(lQP Q, BiTree& data);														//链队列出队						//
bool outQueue(lQP Q, elementType& data);												//链队列出队						//
//顺序表函数声明																											//
void showSeqList(seqP L);																//打印顺序表						//
void creatSeqList(seqP L,int num = MAXLEN, int min = 100, int max = 999);				//随机数创建顺序表					//
//排序函数声明																												//
int partition(elementType A[], int start, int end);										//快排划分							//
void quickSort(seqP L, int start, int end, BiTree* Tpp = nullptr, bool print = false);	//快速排序							//
void quickSort(seqP L, bool print = false);												//快速排序							//
bool partitionThree(seqP L);															//数字3特性划分						//
void shellSort(seqP L);																	//希尔排序							//
void shift(seqP L, int root, int max);													//堆排划分（小根堆）				//
void heapSort(seqP L);																	//堆排序							//
bool merge(seqP L, int sA, int eA, int sB, int eB);										//原地归并							//
void mergeSort(seqP L);																	//归并排序							//
//二叉树通用函数声明																										//
bool addTreeNode(BiTree* Tpp, elementType x);											//二叉树创建新结点					//
void creatTreeByFloor(BiTree& T, seqP& L, int n);										//顺序表创建二叉树					//
bool creatTreeByFloor(BiTree& T, seqP& L);												//顺序表创建二叉树					//
int getTreeHeight(BiTree T);															//求二叉树高度						//
void preTraverse(BiTree T);																//二叉树先序遍历					//
void inOrderTraverse(BiTree T);															//二叉树中序遍历					//
void postTraverse(BiTree T);															//二叉树后序遍历					//
void printBST(BiTree T);																//打印二叉树						//
void destoryTreeNode(BiTree T);															//销毁二叉树						//
bool destoryTree(BiTree& T);															//销毁二叉树						//
//**************************************************************************************************************************//

#endif // !SORT_H


#ifdef DEBUG
int DEBUG_exchangeNum = 0;
int DEBUG_carryNum = 0;
int DEBUG_compareNum = 0;
BiTree* TppHead = nullptr;
//DEBUG函数声明
void resetDEBUG(void);	//还原DEBUG变量
//DEBUG函数定义
//辅助函数：还原DEBUG变量
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
			cout << "重置失败" << endl;
		}
	}
}
#endif // DEBUG


//*********************************************************函数定义*********************************************************//

//******************************************************链队列函数定义******************************************************//

//辅助函数：链队列初始化
//输入：队列指针
//返回：成功返回true，失败返回false
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
		cout << "当前指针已占用，队列初始化失败！" << endl;

		return false;
	}
}


//辅助函数：链队列入队
//输入：队列指针，入队指针
//返回：成功返回true，失败返回false
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
		cout << "当前队列未初始化，入队失败！" << endl;

		return false;
	}
}


//辅助函数：链队列入队
//输入：队列指针，入队指针
//返回：成功返回true，失败返回false
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
		cout << "当前队列未初始化，入队失败！" << endl;

		return false;
	}
}


//辅助函数：链队列出队
//输入：队列指针，出队指针
//返回：成功返回true，失败返回false
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
		cout << "当前队列未初始化，出队失败！" << endl;

		return false;
	}
}


//辅助函数：链队列出队
//输入：队列指针，出队指针
//返回：成功返回true，失败返回false
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
		cout << "当前队列未初始化，出队失败！" << endl;

		return false;
	}
}


//****************************************************二叉树通用函数声明****************************************************//

//辅助函数：二叉树创建新结点
//输入：二叉树指针，顺序表
//返回：成功返回true，失败返回false
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
		cout << "当前结点已占用！" << endl;

		return false;
	}
}


//辅助函数：顺序表创建二叉树
//输入：二叉树指针，顺序表，顺序表结点序号（在处理结点时转换成下标）
//返回：成功返回true，失败返回false
void creatTreeByFloor(BiTree& T, seqP& L, int n)
{
	if (!T && n < L->listLen)
	{
		addTreeNode(&T, L->data[n - 1]);
		creatTreeByFloor(T->lChild, L, n * 2);
		creatTreeByFloor(T->rChild, L, n * 2 + 1);
	}
}


//辅助函数：顺序表创建二叉树
//输入：二叉树指针，顺序表
//返回：成功返回true，失败返回false
bool creatTreeByFloor(BiTree& T, seqP& L)
{
	if (!T)
	{
		creatTreeByFloor(T, L, 1);		//传入结点序号，在处理结点时转换成下标

		return true;
	}
	else
	{
		return false;
	}
}


//辅助函数：求二叉树的高度
//输入：二叉树指针 
//返回：二叉树高度
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


//****************二叉树先序遍历****************
//辅助函数：二叉树先序遍历
//输入：二叉树指针 
//打印：函数内打印二叉树结点
void preTraverse(BiTree T)
{
	if (T)
	{
		cout << T->data << '\t';
		preTraverse(T->lChild);
		preTraverse(T->rChild);
	}
}


//****************二叉树中序遍历****************
//辅助函数：二叉树中序遍历
//输入：二叉树指针 
//打印：函数内打印二叉树结点
void inOrderTraverse(BiTree T)
{
	if (T)
	{
		inOrderTraverse(T->lChild);
		cout << T->data << '\t';
		inOrderTraverse(T->rChild);
	}
}


//****************二叉树后序遍历****************
//辅助函数：二叉树后序遍历
//输入：二叉树指针 
//打印：函数内打印二叉树结点
void postTraverse(BiTree T)
{
	if (T)
	{
		postTraverse(T->lChild);
		postTraverse(T->rChild);
		cout << T->data << '\t';
	}
}


//辅助函数：打印二叉排序树
//输入：二分查找树指针，顺序表
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


//辅助函数：销毁二叉树
//输入：二叉树根节点
void destoryTreeNode(BiTree T)
{
	if (T)
	{
		destoryTreeNode(T->lChild);
		destoryTreeNode(T->rChild);
		delete(T);
	}
}


//辅助函数：销毁二叉树
//输入：二叉树根节点
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


//******************************************************顺序表函数定义******************************************************//

//辅助函数：打印顺序表
//输入：顺序表指针
//打印：函数内打印顺序表结点元素
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


//辅助函数：随机数创建顺序表
//输入：顺序表指针，数据量（默认MAXLEN），随机数下限（默认100），随机数上限（默认999）
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


//********************************************************排序函数定义********************************************************//

//辅助函数：快排划分函数
//输入：数组，开始下标，结束下标
//返回：中间下标
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


//辅助函数：快速排序
//输入：顺序表指针，开始下标，结束下标，二叉树结点指针的指针（传入空指针则不会创建，默认为空）
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
		cout << "经历" << DEBUG_carryNum << "次快排后：" << endl;
		showSeqList(L);
		if (print)
		{
			cout << "当前生成树为：" << endl;
			printBST(*TppHead);
		}
#endif // DEBUG

		quickSort(L, start, mid - 1, TppCl, print);
		quickSort(L, mid + 1, end, TppCr, print);
	}
}


//实验十.排序.1：快速排序
//输入：顺序表指针
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
	cout << endl << "最终快排结果：" << endl;
	showSeqList(L);
	cout << "交换次数：" << DEBUG_exchangeNum << endl;
	cout << "比较次数：" << DEBUG_compareNum << endl;
	cout << "执行次数：" << DEBUG_carryNum << endl;
	if (print)
	{
		cout << "构建二叉树：" << endl;
		printBST(*TppHead);
		cout << "先序遍历：\t";
		preTraverse(*TppHead);
		cout << endl;
		cout << "中序遍历：\t";
		inOrderTraverse(*TppHead);
		cout << endl;
		cout << "后序遍历：\t";
		postTraverse(*TppHead);
	}
	resetDEBUG();
#endif // DEBUG
}


//实验十.排序.2：按数字3的特性划分数组
//输入：顺序表
bool partitionThree(seqP L)
{
	elementType keepData = L->data[0];
	lQP Q = nullptr;
	int sE = 0, eE = L->listLen - 1, s = 0, e = L->listLen - 1;

	if (initialQueue(Q))
	{
#ifdef DEBUG
		cout << "比较元素依次为：";
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
		cout << "划分结果为：" << endl;
		showSeqList(L);
#endif // DEBUG


		return true;
	}
	else
	{
		return false;
	}
}


//实验十.排序.3：希尔排序
//输入：顺序表
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
		cout << "经历" << DEBUG_carryNum << "次希尔排序后：" << endl;
		showSeqList(L);
#endif // DEBUG

		step /= 2;
	}

#ifdef DEBUG
	cout << endl << "最终希尔排序结果：" << endl;
	showSeqList(L);
	cout << "交换次数：" << DEBUG_exchangeNum << endl;
	cout << "比较次数：" << DEBUG_compareNum << endl;
	cout << "执行次数：" << DEBUG_carryNum << endl;

	resetDEBUG();
#endif // DEBUG

}


//辅助函数：堆排划分（小根堆）
//输入：顺序表指针，开始下标，结束下标
void shift(seqP L, int root, int max)
{									//root、max都是元素的序号，比其下标大一
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


//实验十.排序.5：堆排序
//输入：顺序表
void heapSort(seqP L)
{
	int i = L->listLen / 2;
	elementType keepData = NULL;
#ifdef DEBUG
	BiTree T = nullptr;
#endif // DEBUG

#ifdef DEBUG
	cout << "初始化堆前，堆数组形式：" << endl;
	showSeqList(L);
	cout << "初始化堆前，堆的树形式：" << endl;
	creatTreeByFloor(T, L);
	printBST(T);
	destoryTree(T);
	cout << "排序过程的堆变化如下：" << endl;
#endif // DEBUG

	for (i; i >= 1; i--)
	{			//直接传入对应的序号，在shift对元素进行操作时再转换成下标
		shift(L, i, L->listLen);
#ifdef DEBUG
		DEBUG_carryNum++;
		cout << "第" << DEBUG_carryNum << "次初始化结果：" << endl;
		cout << "当前堆数组形式（初始化）：" << endl;
		showSeqList(L);
		cout << "当前堆的树形式（初始化）：" << endl;
		creatTreeByFloor(T, L);
		printBST(T);
		destoryTree(T);
#endif // DEBUG

	}
#ifdef DEBUG
	cout << "初始化共执行筛选函数次数：" << DEBUG_carryNum << endl;
	DEBUG_carryNum = 0;
	cout << "初始化完成后，排序过程堆的变化如下：" << endl;
#endif // DEBUG

	for (i = L->listLen; i >= 2; i--)
	{
#ifdef DEBUG
		DEBUG_carryNum++;
		cout << "第" << DEBUG_carryNum << "次排序筛选结果：" << endl;
		cout << "当前堆数组形式：" << endl;
		showSeqList(L);
		cout << "当前堆的树形式：" << endl;
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
	cout << "排序后堆数组形式：" << endl;
	showSeqList(L);
	cout << "排序后堆的树形式：" << endl;
	creatTreeByFloor(T, L);
	printBST(T);
	destoryTree(T);
	cout << "比较次数：" << DEBUG_compareNum << endl;
	cout << "交换次数：" << DEBUG_exchangeNum << endl;
	cout << "执行次数：" << DEBUG_carryNum << endl;

	resetDEBUG();
#endif // DEBUG

}


//辅助函数：原地归并
//输入：原地归并的顺序表，归并数组A的开始下标，归并数组A的结束下标，归并数组B的开始下标，归并数组B的结束下标
//返回：成功返回true，失败返回false
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


//实验十.排序.6：归并排序
//输入：顺序表
void mergeSort(seqP L)
{
	int step = 1, begin = 0;
#ifdef DEBUG
	cout << "初始顺序表为：" << endl;
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
		cout << "第" << DEBUG_carryNum << "次归并后：" << endl;
		showSeqList(L);
#endif // DEBUG

	}
#ifdef DEBUG
	cout << "共执行归并次数：" << DEBUG_carryNum << endl;
	cout << "执行结束后顺序表为：" << endl;
	showSeqList(L);

	resetDEBUG();
#endif // DEBUG

}