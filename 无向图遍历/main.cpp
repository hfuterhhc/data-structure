#include"Mgraph.h"
int main() {
	MGraph G;
	// ��������ͼ
	CreatUDG(G);
	printf("\n����ͼ�Ķ���\n");
	// չʾ����ͼ�Ķ���
	show1(G);
	// չʾ����ͼ���ڽӾ���
	printf("\n����ͼ���ڽӾ���\n");
	show(G);
	// ��ȱ���
	printf("\n��ȱ���\n");
	DFSTravers(G, PrintElement);
	// ��ȱ���
	printf("\n��ȱ���\n");
	BFSTraverse(G, PrintElement);
	return 0;
}