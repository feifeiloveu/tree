#include <iostream>
using namespace std;
#include <math.h>

typedef struct BSTNode {
	int data;
	struct BSTNode *lchild, *rchild;
	int count;
}BSTNode,*BSTree;

typedef struct BTNode {
	int data;
	struct BTNode *lchild, *rchild;
	int ltag, rtag;
}BTNode, *BTree;

void CreatBiTree(BTree &T) {//先序遍历构建树
	int c;
	cin >> c;
	if (c == 0)
		T = NULL;
	else {

		T = (BTree)malloc(sizeof(BTNode));
		T->data = c;
		T->ltag = 0; T->rtag = 0;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
}

bool Insert(BSTree &T, int x) {
	if (T == NULL) {
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = x;
		T->lchild = NULL; T->rchild = NULL;
		return true;
	}
	else if (x == T->data)
		return false;
	else if (x < T->data)
		return Insert(T->lchild,x);
	else
		return Insert(T->rchild,x);
}

void CreatBSTree(BSTree &T,int a[],int n) {
	T = NULL;        //初始置空
	for (int i = 0; i < n; i++)
		Insert(T, a[i]);
}

void InOrder(BSTree T) {//中序遍历
	if (T) {
		InOrder(T->lchild);
		cout << T->data << endl;
		InOrder(T->rchild);
	}
}

BSTree Search(BSTree T, int x,BSTree &p) {//p为查找结点的双亲，便于插入和删除
	p = NULL;//记得先将其双亲置空
	while (T != NULL && T->data != x) {
		p = T;
		if (x < T->data)
			T = T->lchild;
		else
			T = T->rchild;
	}
	return T;
}

int predt = -32767;
bool NO6(BTree T) {
	int b1, b2;
	if (T == NULL)
		return true;
	else {
		b1 = NO6(T->lchild);
		if (b1 == false || predt >= T->data)
			return false;
		predt = T->data;
		b2 = NO6(T->rchild);
		return b2;
	}
}

int NO7(BSTree T,int x) {
	int n = 1;
	while (T != NULL && T->data != x) {
		n++;
		if (x > T->data)
			T = T->rchild;
		else
			T = T->lchild;
	}
	return n;
}

void NO8(BSTree T, int &balance, int &h) {
	int h1, h2, b1, b2;
	if (T == NULL) {
		balance = 1;
		h = 0;
	}
	else if (T != NULL && T->lchild == NULL && T->rchild == NULL) {
		balance = 1;
		h = 1;
	}
	else {
		NO8(T->lchild, b1, h1);
		NO8(T->rchild, b2, h2);
		h = (h1 > h2 ? h1 : h2) + 1;
		if (abs(h1 - h2) > 1)
			balance = 0;
		else
			balance = b1&&b2;
	}
}

void NO9(BSTree T) {
	BSTree p=T;
	while (p->lchild)
		p = p->lchild;
	cout << "最小值:" << p->data << endl;
	p = T;
	while (p->rchild)
		p = p->rchild;
	cout << "最大值：" << p->data << endl;
}

void NO10(BSTree T, int k) {
	if (T) {
		NO10(T->rchild, k);
		if (T->data >= k)
			cout << T->data << endl;
		NO10(T->lchild, k);
	}
}

int CreatCount(BSTree T) {//十一题辅助用函数，专门用来计算子树结点数并赋值给count（包括此根节点)
	int sum1, sum2;
	if (T == NULL)
		return 0;
	else {
		sum1 = CreatCount(T->lchild);
		sum2 = CreatCount(T->rchild);
		T->count = sum1 + sum2 + 1;
		return sum1 + sum2 + 1;
	}

}

BSTree NO12(BSTree T,int k) {
	if (T->lchild == NULL && k == 1)
		return T;
	if (k == T->lchild->count + 1)
		return T;
	else if (k < T->lchild->count + 1)
		NO12(T->lchild, k);
	else
		NO12(T->rchild, k-T->lchild->count-1);
}


void xxmain() {
	BSTree T; int a[11] = { 5,3,7,2,4,6,9,1,8,10,11 }, b[10] = { 1,2,3,4,5,6,7,8,9,10 };
	CreatBSTree(T,a,11);
	CreatCount(T);

	cout << NO12(T, 3)->data << endl;

	system("pause"); 
}