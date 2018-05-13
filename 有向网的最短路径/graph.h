#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
typedef char VertexType;
// 最大值
#define INFINITY 10000   
// 最大顶点数
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
	// 网的当前顶点数和弧数
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

// 输出顶点
void show1(MGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		printf("%2c", G.vexs[i]);
	}
	printf("\n");
}

// 输出邻接矩阵
void show(MGraph G) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			printf("%15d", G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

//  有向网
Status CreatUDG(MGraph &G) {
	printf("请输入有向网顶点数和遍数\n");
	scanf("%d%d", &G.vexnum, &G.arcnum);
	getchar();
	printf("请输入有向网顶点(一行输入一个顶点，按回车键)\n");
	for (int i = 0; i < G.vexnum; i++) {
		scanf("%c", &G.vexs[i]);
		getchar();
	}
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = INFINITY;
		}
	}
	printf("请输入有向网边(一行输入一个边的两个顶点和权值，以逗号隔开，按回车键)\n");
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

// 展示dijkstra迪杰斯特拉算法最短路径
void show2(MGraph G,shortPath D) {
	for (int i = 0; i < G.vexnum; i++) {
		printf("%15d", D[i].adj);
	}
	printf("\n");
}

// 输出floyd算法结果的最短路径
void show4(MGraph G, AdjMatrix D) {
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			printf("%15d", D[i][j].adj);
		}
		printf("\n");
	}
}

// dijkstra迪杰斯特拉算法
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

// Floyd算法代码
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
