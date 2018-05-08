/*
顺序栈
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
	// 当前已分配的存储空间，已元素为单位
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

// 初始化
Status InitStack(SqStack &S){
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base){
		exit(OVERFLOW);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

// 若栈不空，则用e返回S的栈顶元素
Status GetTop(SqStack S, SElemType &e){
	if (S.top == S.base){
		return ERROR;
	}
	e = *(S.top-1);
	return OK;
}

// 插入元素e为新的栈顶元素
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

// 若栈不空，则删除S的栈顶元素
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

// 数制转换
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

	printf("------------测试赋值------------\n");
	for (int i = 1; i <= 5; i++){
		Push(sqStack, i);
	}
	Show(sqStack);

	printf("------------测试删除------------\n");
	Pop(sqStack, a);
	Show(sqStack);

	printf("------------测试长度------------\n");
	printf("%4d\n", StackLength(sqStack));

	printf("------------测试取栈顶值------------\n");
	GetTop(sqStack, a);
	printf("%4d\n", a);

	return 0;
}

