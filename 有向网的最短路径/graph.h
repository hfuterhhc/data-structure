#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
typedef char VertexType;
// ���ֵ
#define INFINITY 10000   
// ��󶥵���
#define MAX_VERTEX_NUM 20
typedef enum { DG, DN, UDG, UDN }GraphKind;


bool visited[MAX_VERTEX_NUM];
Status(*VisitFunc)(int v);
bool final[MAX_VERTEX_NUM] ;

typedef struct ArcCell {
	int adj;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM],*PathMatrix,*shortPath;

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	// ���ĵ�ǰ�������ͻ���
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

// �������
void show1(MGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		printf("%2c", G.vexs[i]);
	}
	printf("\n");
}

// ����ڽӾ���
void show(MGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			printf("%15d", G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

//  ������
Status CreatUDG(MGraph &G) {
	printf("�������������������ͱ���\n");
	scanf("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	printf("����������������(һ������һ�����㣬���س���)\n");
	for (int i = 0; i < G.vexnum; i++) {
		scanf("%c", &G.vexs[i]);
		getchar();
	}
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = INFINITY;
		}
	}
	printf("��������������(һ������һ���ߵ����������Ȩֵ���Զ��Ÿ��������س���)\n");
	for (int k = 0; k < G.arcnum; k++) {
		VertexType V1, V2;
		int w;
		scanf("%c,%c,%d", &V1, &V2,&w);
		getchar();
		int i = LocateVex(G, V1);
		int j = LocateVex(G, V2);
		if (i != -1 && j != -1) {
			G.arcs[i][j].adj = w;
		}
	}
	return OK;
}

Status minnum(MGraph G,shortPath D) {
	for (int i = 0; i < G.vexnum; i++) {
		if (final[i]) {
			continue;
		}
		for (int j = 0; j < G.vexnum; j++) {
			if (final[j]) {
				continue;
			}
			if (i != j && D[i].adj > D[j].adj) {
				break;
			}
			if (j == G.vexnum - 1) {
				return i;
			}
		}
	}
	return -1;
}

// չʾdijkstra�Ͻ�˹�����㷨���·��
void show2(MGraph G,shortPath D) {
	for (int i = 0; i < G.vexnum; i++) {
		printf("%15d", D[i].adj);
	}
	printf("\n");
}

// ���floyd�㷨��������·��
void show4(MGraph G, AdjMatrix D) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			printf("%15d", D[i][j].adj);
		}
		printf("\n");
	}
}

// dijkstra�Ͻ�˹�����㷨
void shortPath1(MGraph G, int v, PathMatrix &p, shortPath &D) {
	for (int i = 0; i < G.vexnum; i++) {
		final[i] = false;
		p[i].adj = 0;
		D[i].adj = G.arcs[v][i].adj;
	}
	D[v].adj = 0;
	final[v] = true;
	for (int i = 1; i < G.vexnum; i++) {
		int k = minnum(G,D);
		if (k!= -1) {
			final[k] = true;
			for (int j = 0; j < G.vexnum; j++) {
				if (!final[j] && D[j].adj > G.arcs[v][k].adj + G.arcs[k][j].adj) {
					D[j].adj = G.arcs[v][k].adj + G.arcs[k][j].adj;
					G.arcs[v][j].adj = D[j].adj;
					p[j].adj = k;
				}
			}
		}
	}
}

// Floyd�㷨����
void ShortPath2(MGraph G, AdjMatrix &P, AdjMatrix&D) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			P[i][j].adj = -1;
			D[i][j].adj = G.arcs[i][j].adj;
			if (i == j) {
				D[i][j].adj = 0;
			}
		}
	}
	for (int k = 0; k < G.vexnum; k++) {
		for (int i = 0; i < G.vexnum; i++) {
			for (int j = 0; j < G.vexnum; j++) {
				if (D[i][j].adj > D[i][k].adj + D[k][j].adj) {
					D[i][j].adj = D[i][k].adj + D[k][j].adj;
					P[i][j].adj = k;
				}
			}
		}
	}
}
