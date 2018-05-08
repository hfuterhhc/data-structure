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

// 逆位序输入n个元素的值，建立带表头结点的双向链表L
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

// 展示
void Show_L(DuLinlList L){
	DuLinlList p = L->next;
	while (p!=L){
		printf("%5d", p->data);
		p = p->next;
	}
	printf("\n");
}

// 在带头结点的双链环线性表L中第i个位置之前插入元素e
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

// 删除带头结点的双链循环线性表L的第i个元素
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
	printf("------------测试赋值------------\n");
	Show_L(duLinlList);
	printf("------------测试插入------------\n");
	ListInsert_DuL(duLinlList, 2, 9);
	Show_L(duLinlList);
	printf("------------测试删除------------\n");
	ListDelete_DuL(duLinlList, 3, a);
	Show_L(duLinlList);
	return 0;
}