#include"graph.h"
int main() {
	MGraph G;
	// ����������
	CreatUDG(G);
	printf("\n�������Ķ���\n");
	// չʾ�������Ķ���
	show1(G);
	// չʾ���������ڽӾ���
	printf("\n���������ڽӾ���\n");
	show(G);

	// dijkstra�Ͻ�˹�����㷨
	PathMatrix D=(PathMatrix)malloc(MAX_VERTEX_NUM*sizeof(ArcCell));
	shortPath P=(PathMatrix)malloc(MAX_VERTEX_NUM * sizeof(ArcCell));
	printf("\n��������dijkstra�Ͻ�˹�����㷨\n");
	shortPath1(G, 0, P, D);
	show2(G, D);

	// Floyd�㷨����
    AdjMatrix P1,D2;
	ShortPath2(G,P1,D2);
	printf("\n��������Floyd�㷨\n");
	show4(G, D2);
	return 0;
}