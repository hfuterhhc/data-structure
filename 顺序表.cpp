/*
˳���
*/

#include<stdio.h>
#include<stdlib.h>

// ���Ա�洢�ռ�ĳ�ʼ������
#define LIST_INIT_SIZE 100
// ���Ա�洢�ռ�����ӷ���
#define LISTINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1
typedef int ElemType;
typedef int Status;

int fun(ElemType a, ElemType b){
	if (a == b){
		return 1;
	}
	else
	{
		return 0;
	}
}

// ���Ա�Ķ�̬����˳��洢�ṹ
typedef struct {
	ElemType *elem;
	int length;
	int listsize;
}SqList;

// ����һ���յ����Ա�
Status InitList_Sq(SqList &L){
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L.elem){
		exit(OVERFLOW);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

// ��˳���L�е�i��λ��֮ǰ�����µ�Ԫ��e
Status ListInsert_Sq(SqList &L, int i, ElemType e){
	if (i<1 || i>L.length + 1){
		return ERROR;
	}
	if (L.length >= L.listsize){
		ElemType * newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT)*sizeof(ElemType));
		if (!newbase){
			exit(OVERFLOW);
		}
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	ElemType *q = &(L.elem[i - 1]);
	ElemType *p;
	for (p = &(L.elem[L.length - 1]); p >= q; --p){
		*(p + 1) = *p;
	}
	*q = e;
	++L.length;
	return OK;
}

// ��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
Status ListDelete_Sq(SqList &L, int i, ElemType &e){
	if ((i<1) || (i>L.length)){
		return ERROR;
	}
	// p�ĳ�ֵΪ��һ��Ԫ�صĴ洢λ��
	ElemType* p = &(L.elem[i - 1]);
	e = *p;
	ElemType *q = L.elem + L.length - 1;
	for (++p; p <= q; ++p){
		*(p - 1) = *p;
	}
	--L.length;
	return OK;
}

// ��˳�����Ա�L�в��ҵ�1һ��ֵ��e����compare()��Ԫ�ص�λ��
int LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)){
	int i = 1;
	// p�ĳ�ֵΪ��һ��Ԫ�صĴ洢λ��
	ElemType *p = L.elem;
	while (i <= L.length&&!(*compare)(*p++, e)){
		++i;
	}
	if (i <= L.length){
		return i;
	}
	else
	{
		return 0;
	}
}

// La��Lb��Ԫ�ذ�ֵ�ǵݼ����򣬹鲢La��Lb�õ��µ�˳�����Ա�Lc,Lc��Ԫ��Ҳ���ǵݼ�����
void MergeList_Sq(SqList La, SqList Lb, SqList &Lc){
	ElemType *pa, *pb, *pc, *pa_last, *pb_last;
	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (ElemType*)malloc(Lc.listsize*sizeof(ElemType));
	if (!Lc.elem){
		exit(OVERFLOW);
	}
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last&&pb <= pb_last){
		if (*pa <= *pb){
			*pc++ = *pa++;
		}
		else{
			*pc++ = *pb++;
		}
	}
	while (pa <= pa_last){
		*pc++ = *pa++;
	}
	while (pb <= pb_last){
		*pc++ = *pb++;
	}
}

// ���˳�����Ա�L
void Show_Sq(SqList L){
	printf("˳���L������Ϊ\n");
	for (int i = 1; i <= L.length; i++){
		printf("%5d",L.elem[i - 1]);
	}
	printf("\n");
}

// Ϊ˳�����Ա�L��ֵ
void Fu(SqList &L){
	int i = 0;
	int in;
	printf("��Ϊ˳���L��ֵ����-1����\n");
	while (scanf("%d", &in) == 1 && in!= -1){
		L.elem[i++] = in;
		L.length++;
	}
}

// ���Ը�������
int main(){

	SqList sqList,sqList1,sqList2;
	int a;
	InitList_Sq(sqList);
	InitList_Sq(sqList1);
	printf("------------���Ը�ֵ------------\n");
	Fu(sqList);
	Show_Sq(sqList);
	printf("------------���Բ���------------\n");
	ListInsert_Sq(sqList, 2, 9);
	Show_Sq(sqList);
	printf("------------����ɾ��------------\n");
	ListDelete_Sq(sqList, 2, a);
	Show_Sq(sqList);
	printf("------------���Բ���------------\n");
	printf("%d\n",LocateElem_Sq(sqList, 1, fun));
	printf("------------�鲢La��Lb�õ��µ�˳�����Ա�Lc------------\n");
	Fu(sqList1);
	MergeList_Sq(sqList,sqList1, sqList2);
	Show_Sq(sqList2);
	return 0;

}


