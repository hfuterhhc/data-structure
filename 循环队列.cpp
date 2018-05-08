/*
循环队列
*/
#include<stdio.h>
#include<stdlib.h>

#define MAXQSIZDE 100
#define OK 0
#define ERROR 1
#define OVERFLOW -1

typedef int QElemtype;
typedef int Status;

typedef struct{
	QElemtype *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue &Q){
	Q.base = (QElemtype*)malloc(MAXQSIZDE*sizeof(QElemtype));
	if (!Q.base){
		exit(OVERFLOW);
	}
	Q.front = Q.rear = 0;
	return OK;
}

int QueueLength(SqQueue Q){
	return (Q.rear - Q.front + MAXQSIZDE) % MAXQSIZDE;
}

Status EnQueue(SqQueue &Q, QElemtype e){
	
	// 队列满
	if ((Q.rear + 1) % MAXQSIZDE == Q.front){
		return ERROR;
	}

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZDE;
	return OK;
}

Status DeQueue(SqQueue &Q, QElemtype &e){
	// 队列空
	if (Q.front == Q.rear){
		return ERROR;
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZDE;
	return OK;
}

void show(SqQueue Q){
	while (Q.front%MAXQSIZDE!=Q.rear){
		printf("%4d", Q.base[Q.front]);
		Q.front++;
	}
	printf("\n");
}

int main(){
	SqQueue sqQueue;
	InitQueue(sqQueue);
	int a;
	printf("-----------入队--------------\n");
	for (int i = 1; i <= 9; i++){
		EnQueue(sqQueue, i);
	}
	show(sqQueue);
	printf("-----------出队--------------\n");
	DeQueue(sqQueue, a);
	show(sqQueue);
	return 0;

}




