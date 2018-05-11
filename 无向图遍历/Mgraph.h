#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"SQueue.h"
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
typedef char VertexType;
// ���ֵ
#define INFINITY INT_MAX   
// ��󶥵���
#define MAX_VERTEX_NUM 20
typedef enum { DG, DN, UDG,UDN }GraphKind;

//------------DFSʹ�õ�ȫ�ֱ���---------------------
bool visited[MAX_VERTEX_NUM];
Status(*VisitFunc)(int v);


typedef struct ArcCell {
	int adj;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	// ͼ�ĵ�ǰ�������ͻ���
	int vexnum, arcnum; 
	GraphKind kind;
}MGraph;


Status LocateVex(MGraph G, VertexType V) {
	for (int i = 0; i < G.vexnum; i++) {
		if (G.vexs[i] == V) {
			return i;
		}
	}
	return -1;
}

// ���
void show1(MGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		printf("%2c", G.vexs[i]);
	}
	printf("\n");
}

// ���
void show(MGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			printf("%d", G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

//  ����ͼ
Status CreatUDG(MGraph &G) {
	printf("����������ͼ�������ͱ���\n");
	scanf("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	printf("����������ͼ����(һ������һ�����㣬���س���)\n");
	for (int i = 0; i < G.vexnum; i++) {
		scanf("%c", &G.vexs[i]);
		getchar();
	}
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = 0;
		}
	}
	printf("����������ͼ��(һ������һ���ߵ��������㣬�Զ��Ÿ��������س���)\n");
	for (int k = 0; k < G.arcnum; k++) {
		VertexType V1, V2;
		scanf("%c,%c", &V1,&V2);
		getchar();
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);
		if (i!=-1&&j!=-1) {
			G.arcs[i][j].adj = 1;
		    G.arcs[j][i].adj = 1;
		}
	}
	return OK;
}

// Visit��ָ��ĺ���
Status PrintElement(MGraph G,int e) {
	printf("%4c", G.vexs[e]);
	return OK;
}


Status FirstAdjVex(MGraph G, int V) {
	for (int i = 0; i < G.vexnum; i++) {
		if (G.arcs[V][i].adj == 1) {
			return i;
		  }
	}
	return -1;
}


Status NextAdjVex(MGraph G, int V,int w) {
	for (int i = w+1; i < G.vexnum; i++) {
		if (G.arcs[V][i].adj == 1) {
			return i;
		}
	}
	return -1;
}


void DFS(MGraph G, int V, Status(*Visit)(MGraph G,int t)) {
	visited[V] = true;
	Visit(G,V);
	for (int w = FirstAdjVex(G, V); w >= 0; w = NextAdjVex(G, V, w)) {
		if (!visited[w]) {
			DFS(G, w,Visit);
		}
	}
		
}

// ��ȱ���
void DFSTravers(MGraph G, Status(*Visit)(MGraph G,int t)) {
	for (int v = 0; v < G.vexnum; v++) {
		visited[v] = false;
	}
	for (int v = 0; v < G.vexnum; v++) {
		if (!visited[v]) {
			DFS(G, v, Visit);
		}
	}
}

// �����������
void BFSTraverse(MGraph G, Status(*Visit)(MGraph G, int t) ){

	for (int v = 0; v < G.vexnum; v++) {
		visited[v] = false;
	}
	SqQueue Q;
	InitQueue(Q);
	for (int v = 0; v < G.vexnum; v++) {
		if (!visited[v]) {
			visited[v] = true;
			Visit(G, v);
			EnQueue(Q, v);
			while (!QueueEmpty(Q)) {
				int u;
				DeQueue(Q, u);
				for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) {
					if (!visited[w]) {
						visited[w] = true;
						Visit(G,w);
						EnQueue(Q, w);
					}
				}
			}
		}
	}
}



