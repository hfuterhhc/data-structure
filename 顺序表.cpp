/*
顺序表
*/

#include<stdio.h>
#include<stdlib.h>

// 线性表存储空间的初始分配量
#define LIST_INIT_SIZE 100
// 线性表存储空间的增加分配
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

// 线性表的动态分配顺序存储结构
typedef struct {
	ElemType *elem;
	int length;
	int listsize;
}SqList;

// 构造一个空的线性表
Status InitList_Sq(SqList &L){
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L.elem){
		exit(OVERFLOW);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

// 在顺序表L中第i个位置之前插入新的元素e
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

// 在顺序线性表L中删除第i个元素，并用e返回其值
Status ListDelete_Sq(SqList &L, int i, ElemType &e){
	if ((i<1) || (i>L.length)){
		return ERROR;
	}
	// p的初值为第一个元素的存储位置
	ElemType* p = &(L.elem[i - 1]);
	e = *p;
	ElemType *q = L.elem + L.length - 1;
	for (++p; p <= q; ++p){
		*(p - 1) = *p;
	}
	--L.length;
	return OK;
}

// 在顺序线性表L中查找第1一个值与e满足compare()的元素的位序
int LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)){
	int i = 1;
	// p的初值为第一个元素的存储位置
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

// La和Lb的元素按值非递减排序，归并La和Lb得到新的顺序线性表Lc,Lc的元素也按非递减排序
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

// 输出顺序线性表L
void Show_Sq(SqList L){
	printf("顺序表L的内容为\n");
	for (int i = 1; i <= L.length; i++){
		printf("%5d",L.elem[i - 1]);
	}
	printf("\n");
}

// 为顺序线性表L赋值
void Fu(SqList &L){
	int i = 0;
	int in;
	printf("请为顺序表L赋值，以-1结束\n");
	while (scanf("%d", &in) == 1 && in!= -1){
		L.elem[i++] = in;
		L.length++;
	}
}

// 测试各个功能
int main(){

	SqList sqList,sqList1,sqList2;
	int a;
	InitList_Sq(sqList);
	InitList_Sq(sqList1);
	printf("------------测试赋值------------\n");
	Fu(sqList);
	Show_Sq(sqList);
	printf("------------测试插入------------\n");
	ListInsert_Sq(sqList, 2, 9);
	Show_Sq(sqList);
	printf("------------测试删除------------\n");
	ListDelete_Sq(sqList, 2, a);
	Show_Sq(sqList);
	printf("------------测试查找------------\n");
	printf("%d\n",LocateElem_Sq(sqList, 1, fun));
	printf("------------归并La和Lb得到新的顺序线性表Lc------------\n");
	Fu(sqList1);
	MergeList_Sq(sqList,sqList1, sqList2);
	Show_Sq(sqList2);
	return 0;

}


