/*
maloc函数的参数就是需要分配的内存（字节）数，malloc分配的内存是连续的，当内存池中有sizet_size大小的连续内存时就返回指向该内存起始位置的指针
*/

#include<stdio.h>
#include<stdlib.h>
#define ERROR 1
#define OK 0
typedef int ElemType;
typedef int Status;

typedef struct LNode{
	ElemType data;
	struct LNode *next;
}Lnode,*Linklist;

// 逆位序输入n个元素的值，建立带表头结点的单链线性表L
void CreateList_L(Linklist &L, int n){
	
	L = (Linklist)malloc(sizeof(Lnode));
	L->next = NULL;
	for (int i = n; i > 0; --i){
		Linklist p = (Linklist)malloc(sizeof(Lnode));
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
}

// 顺序位输入n个元素
void creat_L(Linklist &L, int n){
	Linklist p , pc;
    L = (Linklist)malloc(sizeof(Lnode));
	p = pc = L;
	p->next = NULL;
	for (int i = 0; i < n; i++){
		Linklist q = (Linklist)malloc(sizeof(Lnode));
		scanf("%d", &q->data);
		q->next = p->next;
		p->next = q;
		p = q;
	}
	L = pc;
}

// 取第i个数据元素
Status GetElem_L(Linklist L, int i, ElemType &e){
	// L为带头结点的单链表的头指针
	// 初始化，p指向第一个结点，j为计数器
	Linklist p = L->next;
	int j = 1;
	while (p&&j < i){
		p = p->next;
		++j;
	}
	if (!p || j > i){
		return ERROR;
	}
	e = p->data;
	return OK;
}

// L为带头结点的单链表头指针，插入结点
Status ListInsert_L(Linklist &L, int i, ElemType e){
	Linklist p = L;
	int j = 0;
	while (p&&j<i-1)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1){
		return ERROR;
	}
	Linklist s = (Linklist)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

// 在带头结点的单链线性表L中，删除第i个元素
Status ListDelete_L(Linklist &L, int i, ElemType &e){
	Linklist p = L;
	int j = 0;
	while (p->next&&j < i - 1){
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1){
		return ERROR;
	}
	Linklist q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return OK;
}

// 归并La，Lb得到新的单链线性表Lc，Lc的元素也按值非递减排序
void MergeList_L(Linklist &La, Linklist &Lb, Linklist &Lc){
	Linklist pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;
	// 用La的头结点作为Lc的头结点
	while (pa&&pb)
	{
		if (pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(Lb);
}

// 展示
void Show_L(Linklist L){
	Linklist p = L->next;
	while (p){
		printf("%5d", p->data);
		p=p->next;
	}
	printf("\n");
}

int main(){

	Linklist sqList, sqList1, sqList2;
	int a;
	creat_L(sqList, 4);
	CreateList_L(sqList1,3);
	printf("------------测试赋值------------\n");
	Show_L(sqList);
	Show_L(sqList1);
	printf("------------测试插入------------\n");
	ListInsert_L(sqList, 2, 9);
	Show_L(sqList);
	printf("------------测试删除------------\n");
	ListDelete_L(sqList, 2, a);
	Show_L(sqList);
	printf("------------测试取第i个数据元素------------\n");
	GetElem_L(sqList, 1, a);
	printf("%d\n", a);
	printf("------------归并La和Lb得到新的单链线性表Lc------------\n");
	MergeList_L(sqList, sqList1, sqList2);
	Show_L(sqList2);
	return 0;

}
