/*
二叉树的二叉链表存储表示
*/

#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
typedef char TElemtype;

typedef struct BiTNode {
	TElemtype data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

// 按先序次序输入二叉树中结点的值(一个字符)，空格字符表示空树
Status CreateBiTree(BiTree &T) {
	TElemtype ch;
	scanf_s("%c", &ch);
	if (ch != -1) {
		if (ch == ' ') {
			T = NULL;
		}
		else
		{
			if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) {
				exit(OVERFLOW);
			}
			T->data = ch;
			CreateBiTree(T->lchild);
			CreateBiTree(T->rchild);
		}
	}
	return OK;
}

// Visit所指向的函数
Status PrintElement(TElemtype e) {
	printf("%4c", e);
	return OK;
}

// 先序遍历二叉树
Status PreOrderTraverse(BiTree T, Status(*Visit)(TElemtype e)) {
	if (T) {
		if (Visit(T->data))
			if (PreOrderTraverse(T->lchild, Visit))
				if (PreOrderTraverse(T->rchild, Visit))
					return OK;
		return ERROR;
	}
	else
	{
		return OK;
	}
}

// 中序遍历二叉树
Status InOrderTraverse(BiTree T, Status(*Visit)(TElemtype e)) {
	if (T) {
		if (InOrderTraverse(T->lchild, Visit))
			if (Visit(T->data))
				if (InOrderTraverse(T->rchild, Visit))
					return OK;
		return ERROR;
	}
	else
	{
		return OK;
	}
}

// 后序遍历二叉树
Status PostOrderTraverse(BiTree T, Status(*Visit)(TElemtype e)) {
	if (T) {
		if (PostOrderTraverse(T->lchild, Visit))
			if (PostOrderTraverse(T->rchild, Visit))
				if (Visit(T->data))
					return OK;
		return ERROR;
	}
	else
	{
		return OK;
	}
}

// 二叉树深度
Status Depth(BiTree T) {
	int depthval;
	if (!T) {
		depthval = 0;
	}
	else
	{
		int depthLeft = Depth(T->lchild);
		int depthRight = Depth(T->rchild);
		depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
	return depthval;
}