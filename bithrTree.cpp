/*
����������
*/

#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
typedef char TElemType;

// �����������������
typedef enum { Link, Thread }PointerTag;
// Link==0��ָ�룬thread==1������
typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;

// Visit��ָ��ĺ���
Status PrintElement(TElemType e) {
	printf("%4c", e);
	return OK;
}
// ������������������˳��
/*
1.����һ������ָ��p
2.��Ѱ���������֮�׽��(�������½ǽ��)��
��LTag=0ʱ(��ʾ������)��p=p->lchild��ֱ��LTag=1
(�����ӣ��ѵ������½�)�����ȷ���p->data;
3.���Ž���ý��������������RTag��p->rchild;
4.���ý���RTag=1(��ʾ�к������)�Һ���������գ���p=p->rchild;
����p->data;���ظ�4����ֱ����̽���Rtag=0��
5.��RTag=0ʱ(��ʾ���Һ���)����Ӧ�Ӹý����Һ��ӿ�ʼ(p=p->rchild)
�������½ǵ������㣻���ظ�2��
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

// ������������
/*
����������������޸Ľ�������ָ�����Ա��浱ǰ�ķ��ʽ��
�ġ�ǰ�����͡���̡���Ϣ
���������У�����ָ��pre,��ʼ�ձ���ָ��preָ��ǰ���ʵġ�ָ��p��ָ
����ǰ��
ÿ��ֻ�޸�ǰ��������ָ��(���)�ͱ�������ָ��(ǰ��)
*/
void InThreading(BiThrTree p) {
	// ����pΪ���ķǿն���������������
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
	// ����������������
	if (!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) {
		exit(OVERFLOW);
	}
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T) {
		Thrt->lchild = Thrt; // TΪ�ն�����
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


// �������������������н���ֵ(һ���ַ�)���ո��ַ���ʾ����
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
	// �������
	InOrderTraverse_Thr(bithrTree, PrintElement);
	return 0;
}