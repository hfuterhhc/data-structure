/*
循环队列
*/

#include<stdio.h>
#include<stdlib.h>

#define MAXQSIZDE 100
#define OK2 1
#define ERROR2 0
#define OVERFLOW2 -1

typedef int QElemtype;
typedef int Status;

typedef struct {
	QElemtype *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue &Q) {
	Q.base = (QElemtype*)malloc(MAXQSIZDE * sizeof(QElemtype));
	if (!Q.base) {
		exit(OVERFLOW2);
	}
	Q.front = Q.rear = 0;
	return OK2;
}

int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + MAXQSIZDE) % MAXQSIZDE;
}

Status EnQueue(SqQueue &Q, QElemtype e) {

	// 队列满
	if ((Q.rear + 1) % MAXQSIZDE == Q.front) {
		return ERROR2;
	}

	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZDE;
	return OK2;
}

Status DeQueue(SqQueue &Q, QElemtype &e) {
	// 队列空
	if (Q.front == Q.rear) {
		return ERROR2;
	}
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZDE;
	return OK2;
}

void show(SqQueue Q) {
	while (Q.front%MAXQSIZDE != Q.rear) {
		printf("%4d", Q.base[Q.front]);
		Q.front++;
	}
	printf("\n");
}

Status QueueEmpty(SqQueue Q) {
	if (Q.front == Q.rear) {
		return OK2;
	}
	return ERROR2;
}
