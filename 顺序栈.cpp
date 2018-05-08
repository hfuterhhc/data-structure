/*
˳��ջ
*/
#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK 0
#define ERROR 1
#define OVERFLOW -1

typedef int SElemType;
typedef int Status;

typedef struct{
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
Status InitStack(SqStack &S){
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base){
		exit(OVERFLOW);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

// ��ջ���գ�����e����S��ջ��Ԫ��
Status GetTop(SqStack S, SElemType &e){
	if (S.top == S.base){
		return ERROR;
	}
	e = *(S.top-1);
	return OK;
}

// ����Ԫ��eΪ�µ�ջ��Ԫ��
Status Push(SqStack &S, SElemType e){
	if (S.top - S.base >= S.stacksize){
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		if (!S.base){
			exit(OVERFLOW);
		}
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

// ��ջ���գ���ɾ��S��ջ��Ԫ��
Status Pop(SqStack &S, SElemType &e){
	if (S.top == S.base){
		return ERROR;
	}
	e = *--S.top;
	return OK;
}

void Show(SqStack S){
	for (int i = 1; i <=(S.top - S.base); i++){
		printf("%4d", *(S.top - i));
	}
	printf("\n");
}

Status StackEmpty(SqStack S){
	return S.top - S.base == 0 ? 1 : 0;
}


Status StackLength(SqStack S){
	return S.top - S.base;
}

// ����ת��
void conversion(){
	int N,e;
	SqStack S;
	InitStack(S);
	scanf("%d", &N);
	while (N)
	{
		Push(S, N % 8);
		N = N / 8;
	}
	while (!StackEmpty(S)){
		Pop(S, e);
		printf("%d", e);
	}
	printf("\n");
}


int main(){
	SqStack sqStack;
	int a;
	conversion();

	InitStack(sqStack);

	printf("------------���Ը�ֵ------------\n");
	for (int i = 1; i <= 5; i++){
		Push(sqStack, i);
	}
	Show(sqStack);

	printf("------------����ɾ��------------\n");
	Pop(sqStack, a);
	Show(sqStack);

	printf("------------���Գ���------------\n");
	printf("%4d\n", StackLength(sqStack));

	printf("------------����ȡջ��ֵ------------\n");
	GetTop(sqStack, a);
	printf("%4d\n", a);

	return 0;
}

