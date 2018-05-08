/*
maloc�����Ĳ���������Ҫ������ڴ棨�ֽڣ�����malloc������ڴ��������ģ����ڴ������sizet_size��С�������ڴ�ʱ�ͷ���ָ����ڴ���ʼλ�õ�ָ��
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

// ��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L
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

// ˳��λ����n��Ԫ��
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

// ȡ��i������Ԫ��
Status GetElem_L(Linklist L, int i, ElemType &e){
	// LΪ��ͷ���ĵ������ͷָ��
	// ��ʼ����pָ���һ����㣬jΪ������
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

// LΪ��ͷ���ĵ�����ͷָ�룬������
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

// �ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ��
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

// �鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
void MergeList_L(Linklist &La, Linklist &Lb, Linklist &Lc){
	Linklist pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	Lc = pc = La;
	// ��La��ͷ�����ΪLc��ͷ���
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

// չʾ
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
	printf("------------���Ը�ֵ------------\n");
	Show_L(sqList);
	Show_L(sqList1);
	printf("------------���Բ���------------\n");
	ListInsert_L(sqList, 2, 9);
	Show_L(sqList);
	printf("------------����ɾ��------------\n");
	ListDelete_L(sqList, 2, a);
	Show_L(sqList);
	printf("------------����ȡ��i������Ԫ��------------\n");
	GetElem_L(sqList, 1, a);
	printf("%d\n", a);
	printf("------------�鲢La��Lb�õ��µĵ������Ա�Lc------------\n");
	MergeList_L(sqList, sqList1, sqList2);
	Show_L(sqList2);
	return 0;

}
