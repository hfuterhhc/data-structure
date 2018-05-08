/*
�������Ķ�������洢��ʾ
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

// �������������������н���ֵ(һ���ַ�)���ո��ַ���ʾ����
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

// Visit��ָ��ĺ���
Status PrintElement(TElemtype e) {
	printf("%4c", e);
	return OK;
}

// �������������
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

// �������������
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

// �������������
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

// ���������
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