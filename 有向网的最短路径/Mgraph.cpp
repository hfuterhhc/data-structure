#include"graph.h"
int main() {
	MGraph G;
	// 创建有向网
	CreatUDG(G);
	printf("\n有向网的顶点\n");
	// 展示有向网的顶点
	show1(G);
	// 展示有向网的邻接矩阵
	printf("\n有向网的邻接矩阵\n");
	show(G);

	// dijkstra迪杰斯特拉算法
	PathMatrix D=(PathMatrix)malloc(MAX_VERTEX_NUM*sizeof(ArcCell));
	shortPath P=(PathMatrix)malloc(MAX_VERTEX_NUM * sizeof(ArcCell));
	printf("\n有向网的dijkstra迪杰斯特拉算法\n");
	shortPath1(G, 0, P, D);
	show2(G, D);

	// Floyd算法代码
    AdjMatrix P1,D2;
	ShortPath2(G,P1,D2);
	printf("\n有向网的Floyd算法\n");
	show4(G, D2);
	return 0;
}