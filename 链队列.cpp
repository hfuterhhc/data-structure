/*
链队列
*/
#include<stdio.h>
#include<stdlib.h>

#define OK 0
#define ERROR 1
#define OVERFLOW -1

typedef int Status;
typedef int QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}Qnode,*QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q);
Status DestroyQueue(LinkQueue &Q);
Status ClearQueue(LinkQueue &Q);
Status QueueEmpty(LinkQueue Q);
Status QueueLength(LinkQueue Q);
Status GetHead(LinkQueue Q, QElemType &e);
Status EnQueue(LinkQueue &Q, QElemType e);
Status DeQueue(LinkQueue &Q, QElemType &e);
void show(LinkQueue Q);


Status InitQueue(LinkQueue &Q){
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(Qnode));
	if (!Q.front){
		exit(OVERFLOW);
	}
	Q.front->next = NULL;
	return OK;
}

// 插入元素e
Status enQueue(LinkQueue &Q,QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p){
		exit(OVERFLOW);
	}
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

// 删除Q的队头元素
Status DeQueue(LinkQueue &Q, QElemType &e){
	if (Q.front == Q.rear){
		exit(OVERFLOW);
	}
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p){
		Q.rear = Q.front;
	}
	free(p);
	return OK;
}

// 销毁队列
Status DestroyQueue(LinkQueue &Q){
	while (Q.front){
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}


void show(LinkQueue Q){
	Q.front = Q.front->next;
	while (Q.front!=Q.rear){
		printf("%4d", Q.front->data);
		Q.front = Q.front->next;
	}
	printf("%4d", Q.front->data);
	printf("\n");
}

int main(){
	LinkQueue Q;
	InitQueue(Q);
	int a;
	printf("------------测试入队-------------\n");
	for (int i = 1; i <= 5; i++){
		enQueue(Q, i);
	}
	show(Q);
	printf("------------测试出队-------------\n");
	DeQueue(Q, a);
	show(Q);
	return 0;
}