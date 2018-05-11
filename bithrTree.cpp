/*
线索二叉树
*/

#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
typedef char TElemType;

// 线索链表的类型描述
typedef enum { Link, Thread }PointerTag;
// Link==0：指针，thread==1：线索
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;

// Visit所指向的函数
Status PrintElement(TElemType e) {
	printf("%4c", e);
	return OK;
}
// 中序线索二叉树遍历顺序
/*
1.设置一个搜索指针p
2.先寻找中序遍历之首结点(即最左下角结点)：
当LTag=0时(表示有左孩子)，p=p->lchild；直到LTag=1
(无左孩子，已到最左下角)；首先访问p->data;
3.接着进入该结点的右子树，检查RTag和p->rchild;
4.若该结点的RTag=1(表示有后继线索)且后继线索不空，则p=p->rchild;
访问p->data;并重复4），直到后继结点的Rtag=0；
5.当RTag=0时(表示有右孩子)，则应从该结点的右孩子开始(p=p->rchild)
查找左下角的子孙结点；即重复2）
*/

void InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType e)) {
	BiThrTree p=(BiThrTree)malloc(sizeof(BiThrNode));
	p= T->lchild;
	while (p != T) {
		while (p->LTag == Link) {
			p = p->lchild;
		}
		Visit(p->data);
		while (p->RTag == Thread && p->rchild != T) {
			p = p->rchild;
			Visit(p->data);
		}
		p=p->rchild;
	}
}

BiThrTree pre = (BiThrTree)malloc(sizeof(BiThrNode));

// 建立线索链表
/*
在中序遍历过程中修改结点的左，右指针域，以保存当前的访问结点
的“前驱”和“后继”信息
遍历过程中，附设指针pre,并始终保持指针pre指向当前访问的、指针p所指
结点的前驱
每次只修改前驱结点的右指针(后继)和本结点的左指针(前驱)
*/
void InThreading(BiThrTree p) {
	// 对以p为根的非空二叉树进行线索化
	if (p) {
		InThreading(p->lchild);
		if (!p->lchild) {
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild) {
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}



Status InOrderThreading(BiThrTree &Thrt, BiThrTree T) {
	// 构建中序线索链表
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) {
		exit(OVERFLOW);
	}
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T) {
		Thrt->lchild = Thrt; // T为空二叉树
	}
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
}


// 按先序次序输入二叉树中结点的值(一个字符)，空格字符表示空树
Status CreateBiTree(BiThrTree &T) {
	TElemType ch;
	scanf_s("%c", &ch);
	if (ch != -1) {
		if (ch == ' ') {
			T = NULL;
		}
		else
		{
			if (!(T = (BiThrTree)malloc(sizeof(BiThrNode)))) {
				exit(OVERFLOW);
			}
			T->data = ch;
			T->LTag = Link;
			T->RTag = Link;
			CreateBiTree(T->lchild);
			CreateBiTree(T->rchild);
		}
	}
	return OK;
}

int main() {
	BiThrTree biThrTree,bithrTree;
	CreateBiTree(biThrTree);
	InOrderThreading(bithrTree,biThrTree);
	// 中序遍历
	InOrderTraverse_Thr(bithrTree, PrintElement);
	return 0;
}