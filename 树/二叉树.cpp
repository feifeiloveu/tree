#include <iostream>
#define MaxSize 50
using namespace std;

typedef struct BiTNode {
	char data;
	struct BiTNode *lchild, *rchild;
	int ltag, rtag;
}BiTNode, *BiTree;

typedef struct Stack {
	BiTree Stdata[MaxSize];
	int top;
}Stack;

void InitStack(Stack &S) {
	S.top = -1;
}

bool Push(Stack &S, BiTree x) {
	if (S.top == MaxSize - 1)
		return false;
	S.Stdata[++S.top] = x;
	return true;
}

bool Pop(Stack &S, BiTree &x) {
	if (S.top == -1)
		return false;
	x = S.Stdata[S.top--];
	return true;
}

void GetTop(Stack S, BiTree &x) {
	if (S.top == -1)
		exit(0);
	x = S.Stdata[S.top];
}

bool IsEmpty(Stack S) {
	if (S.top == -1)
		return true;
	else
		return false;
}

void CreatBiTree(BiTree &T) {//先序遍历构建树
	char c;
	cin >> c;
	if (c == '0')
		T = NULL;
	else {

		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = c;
		T->ltag = 0; T->rtag = 0;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
}

void PreOrder(BiTree T) {//前序遍历
	if (T != NULL) {
		cout << T->data << endl;
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void PreOrder2(BiTree T) {//先序遍历非递归算法
	Stack S; InitStack(S);
	BiTree p;
	if (T == NULL)
		return;
	Push(S, T);
	while (!IsEmpty(S)) {
		Pop(S, p);
		cout << p->data << endl;
		if (p->rchild)
			Push(S, p->rchild);
		if (p->lchild)
			Push(S, p->lchild);
	}
}

void InOrder(BiTree T) {//中序遍历
	if (T != NULL) {
		InOrder(T->lchild);
		cout << T->data << endl;
		InOrder(T->rchild);
	}
}

void PostOrder(BiTree T) {//后序遍历
	if (T != NULL) {
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout << T->data << endl;
	}
}

void InOrder2(BiTree T) {//中序遍历非递归算法
	BiTree p = T; Stack S;
	InitStack(S);
	while (p != NULL || !IsEmpty(S)) {
		if (p) {
			Push(S, p);
			p = p->lchild;
		}
		else {
			Pop(S, p);
			cout << p->data << endl;
			p = p->rchild;
		}
	}
}

void PostOrder2(BiTree T) {//非递归后序遍历
	Stack S; InitStack(S);
	BiTree p = T, r = NULL;
	while (p || !IsEmpty(S)) {
		if (p) {
			Push(S, p);
			p = p->lchild;
		}
		else {
			GetTop(S, p);
			if (p->rchild&&p->rchild != r) {
				p = p->rchild;
				//Push(S, p);
				//p = p->lchild;
			}
			else {
				Pop(S, p);
				cout << p->data << endl;
				r = p;
				p = NULL;
			}
		}
	}
}

void LevelOrder(BiTree T) {//层序遍历
	BiTree a[MaxSize]; int front = 0, rear = 0;//用数组表示队列，只是因为懒得再次构造队列了
	BiTree p = T;
	a[rear++] = p;
	while (rear != front) {
		p = a[front++];
		cout << p->data << endl;
		if (p->lchild != NULL)
			a[rear++] = p->lchild;
		if (p->rchild != NULL)
			a[rear++] = p->rchild;
	}
}

void ThreadInO(BiTree &p, BiTree &pre) {//中序遍历线索化
	if (p != NULL) {
		ThreadInO(p->lchild, pre);
		if (p->lchild == NULL) {
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL && pre->rchild == NULL) {
			pre->rchild = p;
			pre->rtag = 1;
		}
		pre = p;
		ThreadInO(p->rchild, pre);
	}
}

void CreatInThread(BiTree &T) {//建立中序线索二叉树
	BiTree pre = NULL;
	if (T != NULL) {
		ThreadInO(T, pre);
		pre->rchild = NULL;
		pre->rtag = 1;
	}
}

BiTree FirstNode(BiTree &T) {//中序线索二叉树寻找第一个结点
	while (T->ltag == 0)
		T = T->lchild;
	return T;
}

BiTree NextNode(BiTree &T) {//中序线索二叉树寻找后继点
	if (T->rtag == 1)
		return T->rchild;
	else
		return FirstNode(T->rchild);
}

void InThreadOrder(BiTree T) {//线索二叉树的中序遍历
	for (BiTree p = FirstNode(T); p != NULL; p = NextNode(p))
		cout << p->data << endl;
}

void NO4(BiTree T) {
	BiTree p = T, a[MaxSize];
	Stack S; InitStack(S);
	int rear = 0, front = 0;
	a[0] = p; rear++;
	while (rear != front) {
		p = a[front];
		Push(S, p);
		front++;
		if (p->lchild != NULL)
			a[rear++] = p->lchild;
		if (p->rchild != NULL)
			a[rear++] = p->rchild;
	}
	while (!IsEmpty(S)) {
		Pop(S, p);
		cout << p->data << endl;
	}
}

void NO5(BiTree T) {
	BiTree p = T, a[MaxSize];
	int rear = 0, front = 0, level = 0, last = 1;
	a[rear++] = T;
	while (rear != front) {
		p = a[front++];
		if (p->lchild != NULL)
			a[rear++] = p->lchild;
		if (p->rchild != NULL)
			a[rear++] = p->rchild;
		if (front == last) {
			level++;
			last = rear;
		}
	}
	cout << level << endl;
}

BiTree NO6(char a[], char b[], int l1, int h1, int l2, int h2) {//l1和h1是先序序列的范围
	BiTree root; int i, llen, rlen;
	root = (BiTree)malloc(sizeof(BiTNode));
	root->data = a[l1];
	for (i = l2; b[i] != root->data; i++);
	llen = i - l2;
	rlen = h2 - i;
	if (llen > 0)
		root->lchild = NO6(a, b, l1 + 1, l1 + llen, l2, i - 1);
	else
		root->lchild = NULL;
	if (rlen > 0)
		root->rchild = NO6(a, b, l1 + llen + 1, h1, i + 1, h2);
	else
		root->rchild = NULL;
	return root;
}

bool NO7(BiTree T) {
	BiTree p = T, a[MaxSize];
	int rear = 0, front = 0;
	a[rear++] = p;
	while (front != rear) {
		p = a[front++];
		if (p) {
			a[rear++] = p->lchild;
			a[rear++] = p->rchild;
		}
		else {
			while (front != rear) {
				p = a[front++];
				if (p != NULL)
					return false;
			}
		}
	}
	return true;
}

void NO9(BiTree &T) {
	BiTree temp;
	if (T) {
		NO9(T->lchild);
		NO9(T->rchild);
		temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
	}
}

int Q10 = 1;//第十题专用全局变量
char NO10(BiTree T, int k) {
	char ch;
	if (T == NULL)
		return '#';
	if (Q10 == k)
		return T->data;
	Q10++;
	ch = NO10(T->lchild, k);
	if (ch != '#')
		return ch;
	ch = NO10(T->rchild, k);
	return ch;
}

void DeleteTree(BiTree &T) {//删除一棵以T为根的树
	if (T) {
		DeleteTree(T->lchild);
		DeleteTree(T->rchild);
		free(T);
	}
}

void NO11(BiTree &T, char x) {
	if (T->data == x) {
		DeleteTree(T);
		exit(0);
	}
	BiTree p = T, a[MaxSize]; int rear = 0, front = 0;
	a[rear++] = p;
	while (rear != front) {
		p = a[front++];
		if (p->lchild) {
			if (p->lchild->data == x) {
				DeleteTree(p->lchild);
				p->lchild = NULL;
			}
			else
				a[rear++] = p->lchild;
		}
		if (p->rchild) {
			if (p->rchild->data == x) {
				DeleteTree(p->rchild);
				p->rchild = NULL;
			}
			else
				a[rear++] = p->rchild;
		}
	}
}

void NO12(BiTree &T, char x) {
	Stack S; InitStack(S);
	BiTree p = T, r = NULL;
	while (p || !IsEmpty(S)) {
		if (p) {
			Push(S, p);
			p = p->lchild;
		}
		else {
			GetTop(S, p);
			if (p->rchild&&p->rchild != r)
				p = p->rchild;
			else {
				Pop(S, p);
				if (p->data == x) {
					while (!IsEmpty(S)) {
						Pop(S, p);
						cout << p->data << endl;
					}
					return;
				}

				r = p;
				p = NULL;
			}
		}
	}
}

void NO13(BiTree T, char x, char y) {//假设x在y右边
	Stack S1, S2; InitStack(S1); InitStack(S2);
	BiTree r = NULL, p = T;
	while (p || !IsEmpty(S1)) {
		if (p) {
			Push(S1, p);
			p = p->lchild;
		}
		else {
			GetTop(S1, p);
			if (p->rchild&&p->rchild != r)
				p = p->rchild;
			else {
				Pop(S1, p);
				if (p->data == x) {
					for (int i = S1.top; i > -1; i--)
						Push(S2, S1.Stdata[i]);
				}
				if (p->data == y) {
					for (int i = S1.top; i>-1; i--)
						for (int j = S2.top; j>-1; j--)
							if (S1.Stdata[i] == S2.Stdata[j]) {
								cout << S1.Stdata[i]->data << endl;
								return;
							}
				}
				r = p;
				p = NULL;
			}
		}
	}

}

void NO14(BiTree T) {
	BiTree p = T, Q[MaxSize];
	int front = 0, rear = 0, Level[MaxSize];
	int k;
	Level[rear] = 1; Q[rear++] = p;
	while (rear != front) {
		k = Level[front];//此处是关键，重新定位k的值
		p = Q[front++];
		if (p->lchild) {
			Level[rear] = k + 1;
			Q[rear++] = p->lchild;
		}
		if (p->rchild) {
			Level[rear] = k + 1;
			Q[rear++] = p->rchild;
		}
	}
	//遍历Level数组，找到最多结点的层数
	int max = 0, maxlevel = 0, i = 0, n;
	k = 1;
	while (i < rear) {
		n = 0;
		while (i < rear&&Level[i] == k) {
			n++;
			i++;
		}
		if (n > max) {
			max = n;
			maxlevel = k;
		}
		k++;
	}
	cout << max << endl;
}

void NO15(char pre[], int l1, int h1, char post[], int l2, int h2) {
	int half;
	if (h1 >= l1) {
		post[h2] = pre[l1];
		half = (h1 - l1) / 2;
		NO15(pre, l1 + 1, l1 + half, post, l2, l2 + half - 1);
		NO15(pre, l1 + 1 + half, h1, post, l2 + half, h2 - 1);
	}
}

BiTree NO16head, NO16pre = NULL;
BiTree NO16(BiTree &T) {
	if (T) {
		if (T->lchild == NULL && T->rchild == NULL) {
			if (NO16pre == NULL) {
				NO16head = T;
				NO16pre = NO16head;
			}
			else {
				NO16pre->rchild = T;
				NO16pre = T;
			}
		}
		NO16(T->lchild);
		NO16(T->rchild);
	}
	NO16pre->rchild = NULL;
	return NO16head;
}

bool NO17(BiTree A, BiTree B) {
	int left, right;
	if (A == NULL && B == NULL)
		return true;
	else if (A == NULL || B == NULL)
		return false;
	else {
		left = NO17(A->lchild, B->lchild);
		right = NO17(A->rchild, B->rchild);
		return left && right;
	}
}

void NO18(BiTree T, BiTree p) {
	if (p->rtag == 0)
		cout << p->rchild->data << endl;
	else if (p->ltag == 0)
		cout << p->lchild->data << endl;
	else if (p->lchild == NULL)
		cout << "NULL" << endl;
	else {
		while (p->ltag == 1 && p->lchild != NULL) {
			p = p->lchild;//此处一直向上寻找，一旦p的左孩子存在就跳出
		}
		if (p->lchild == NULL)
			cout << "NULL" << endl;
		else
			cout << p->lchild->data << endl;
	}
}

void NO19(BiTree T) {//层次遍历解决
	BiTree p = T, a[MaxSize]; int wpl = 0, level = 0, r;
	int front = 0, rear = 0;
	if (T)
		a[rear++] = T;
	r = 1;
	while (rear != front) {
		p = a[front++];
		if (p->lchild == NULL && p->rchild == NULL)
			wpl += level;
		if (p->lchild)
			a[rear++] = p->lchild;
		if (p->rchild)
			a[rear++] = p->rchild;
		if (r == front) {
			r = rear;
			level++;
		}
	}
	cout << wpl << endl;
}

int NO19part2wpl = 0;
int NO19part2(BiTree T, int deep) {//递归方法解决
	if (T->lchild == NULL && T->rchild == NULL)
		NO19part2wpl += deep;
	if (T->lchild)
		NO19part2(T->lchild, deep + 1);
	if (T->rchild)
		NO19part2(T->rchild, deep + 1);
	return  NO19part2wpl;
}

void P173(BiTree T,int k) {//要使用这个函数，记得将struct和Create函数的char改成int
	int sum = 0; Stack S; InitStack(S);
	BiTree p = T, r = NULL;
	while (p || !IsEmpty(S)) {
		if (p) {
			Push(S, p);
			sum += p->data;
			p = p->lchild;
		}
		else {
			GetTop(S, p);
			if (p->rchild&&r != p->rchild)
				p = p->rchild;
			else {
				if (!p->lchild && !p->rchild&&sum == k) {
					for (int i = 0; i <= S.top; i++)
						cout << S.Stdata[i]->data << endl;
				}
				Pop(S, p);
				sum -= p->data;
				r = p;
				p = NULL;
			}
		}
	}
}


void main() {
	BiTree T, p;
	CreatBiTree(T);
	P173(T, 22);

	//PostOrder(T);
	system("pause");
}