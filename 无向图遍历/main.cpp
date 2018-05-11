#include"Mgraph.h"
int main() {
	MGraph G;
	// 创建无向图
	CreatUDG(G);
	printf("\n无向图的顶点\n");
	// 展示无向图的顶点
	show1(G);
	// 展示无向图的邻接矩阵
	printf("\n无向图的邻接矩阵\n");
	show(G);
	// 深度遍历
	printf("\n深度遍历\n");
	DFSTravers(G, PrintElement);
	// 广度遍历
	printf("\n广度遍历\n");
	BFSTraverse(G, PrintElement);
	return 0;
}