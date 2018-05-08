#include"SQueue.h"

// 层次遍历二叉树
Status LevelOrderTraverse(BiTree T, Status(*Visit)(TElemtype e)) {
	SqQueue Q;
	InitQueue(Q);
	if (T) {
		EnQueue(Q, T);
	}
	while (!QueueEmpty(Q)) {
		BiTree p = (BiTree)malloc(sizeof(BiTNode));
		DeQueue(Q, p);
		Visit(p->data);
		if (p->lchild) {
			BiTree p1 = (BiTree)malloc(sizeof(BiTNode));
			p1 = p->lchild;
			EnQueue(Q, p1);
		}
		if (p->rchild) {
			BiTree p2 = (BiTree)malloc(sizeof(BiTNode));
			p2 = p->rchild;
			EnQueue(Q, p2);
		}
	}
}

// 中序遍历二叉树T的非递归算法
Status InOrderTraverse1(BiTree T, Status(*Visit)(TElemtype e)) {
	SqStack S;
	InitStack(S);
	Push(S, T);
	while (!StackEmpty(S))
	{
		BiTree p = (BiTree)malloc(sizeof(BiTNode));
		while (GetTop(S,p)&&p)
		{
			Push(S,p->lchild );
		}
		Pop(S, p);
		if (!StackEmpty(S)) {
			Pop(S, p);
			if (!Visit(p->data)) {
				return ERROR;
			}
			Push(S, p->rchild);
		}
	}
}

int main() {
	BiTree Bt;
    CreateBiTree(Bt);
	PreOrderTraverse(Bt, PrintElement);
	printf("\n\n");
	InOrderTraverse1(Bt, PrintElement);
	printf("\n\n");
	PostOrderTraverse(Bt, PrintElement);
	printf("\n\n");
	LevelOrderTraverse(Bt, PrintElement);
	printf("\n\n");
	printf("%4d\n\n",Depth(Bt));
	return 0;
}