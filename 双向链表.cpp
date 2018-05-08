#include<stdio.h>
#include<stdlib.h>
#define ERROR 1
#define OK 0

typedef int ElemType;
typedef int Status;

typedef struct DuLNode{
	ElemType data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode,*DuLinlList;

// 
DuLinlList GetElemP_DuL(DuLinlList &L, int i){
	int j = 1;
	DuLinlList p = L->next;
	while (p&&j < i){
		p = p->next;
		j++;
	}
	if (!p || j > i){
		return NULL;
	}

	return p;
}

// ��λ������n��Ԫ�ص�ֵ����������ͷ����˫������L
void CreateList_L(DuLinlList &L, int n){

	L = (DuLinlList)malloc(sizeof(DuLNode));
	L->next = L;
	L->prior = L;
	for (int i = n; i > 0; --i){
		DuLinlList p = (DuLinlList)malloc(sizeof(DuLNode));
		DuLinlList q;
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
		p->prior = L;
		p->next->prior = p;
	}
}

// չʾ
void Show_L(DuLinlList L){
	DuLinlList p = L->next;
	while (p!=L){
		printf("%5d", p->data);
		p = p->next;
	}
	printf("\n");
}

// �ڴ�ͷ����˫�������Ա�L�е�i��λ��֮ǰ����Ԫ��e
Status ListInsert_DuL(DuLinlList &L,int i,ElemType e){
	DuLinlList p;
	if (!(p = GetElemP_DuL(L,i))){
		return ERROR;
	}
	DuLinlList s = (DuLinlList)malloc(sizeof(DuLNode));
	if (!s){
		return ERROR;
	}
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

// ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ��
Status ListDelete_DuL(DuLinlList &L, int i, ElemType &e){
	DuLinlList p;
	if (!(p = GetElemP_DuL(L, i))){
		return ERROR;
	}
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}


int main(){
	DuLinlList duLinlList;
	int a;
	CreateList_L(duLinlList, 5);
	printf("------------���Ը�ֵ------------\n");
	Show_L(duLinlList);
	printf("------------���Բ���------------\n");
	ListInsert_DuL(duLinlList, 2, 9);
	Show_L(duLinlList);
	printf("------------����ɾ��------------\n");
	ListDelete_DuL(duLinlList, 3, a);
	Show_L(duLinlList);
	return 0;
}