#include "station.h"

typedef struct
{
	int dist;	// 시작점으로부터의 거리
	int num;	// 역 번호
	int short_station;	//가장 가까운 역
}HeapNode;

typedef struct
{
	HeapNode node[MAX_NODE];
	int node_num;
}Heap;

void init_heap(Heap *h);
void insert_node_min_heap(Heap *h, HeapNode node);
HeapNode delete_node_min_heap(Heap *h);
