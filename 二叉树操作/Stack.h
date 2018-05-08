/*
˳��ջ
*/
#include"Btree.h"
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK1 1
#define ERROR1 0
#define OVERFLOW1 -1

typedef BiTree SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	// ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
	int stacksize;
}SqStack;

Status InitStack(SqStack &S);
Status DestroyStack(SqStack &S);
Status ClearStack(SqStack &S);
Status StackEmpty(SqStack S);
Status StackLength(SqStack S);
Status GetTop(SqStack S, SElemType &e);
Status Push(SqStack &S, SElemType e);
Status Pop(SqStack &p, SElemType &e);

// ��ʼ��
Status InitStack(SqStack &S) {
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base) {
		exit(OVERFLOW1);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK1;
}

// ��ջ���գ�����e����S��ջ��Ԫ��
Status GetTop(SqStack S, SElemType &e) {
	if (S.top == S.base) {
		return ERROR1;
	}
	e = *(S.top - 1);
	return OK1;
}

// ����Ԫ��eΪ�µ�ջ��Ԫ��
Status Push(SqStack &S, SElemType e) {
	if (S.top - S.base >= S.stacksize) {
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base) {
			exit(OVERFLOW1);
		}
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK1;
}

// ��ջ���գ���ɾ��S��ջ��Ԫ��
Status Pop(SqStack &S, SElemType &e) {
	if (S.top == S.base) {
		return ERROR1;
	}
	e = *--S.top;
	return OK1;
}

void Show(SqStack S) {
	for (int i = 1; i <= (S.top - S.base); i++) {
		printf("%4d", *(S.top - i));
	}
	printf("\n");
}

Status StackEmpty(SqStack S) {
	return S.top - S.base == 0 ? 1 : 0;
}

Status StackLength(SqStack S) {
	return S.top - S.base;
}

