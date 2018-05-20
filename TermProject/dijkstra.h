#include "station.h"

typedef struct
{
	int dist;	// ���������κ����� �Ÿ�
	int num;	// �� ��ȣ
	int short_station;	//���� ����� ��
}HeapNode;

typedef struct
{
	HeapNode node[MAX_NODE];
	int node_num;
}Heap;

void init_heap(Heap *h);
void insert_node_min_heap(Heap *h, HeapNode node);
HeapNode delete_node_min_heap(Heap *h);
