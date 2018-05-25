#include "station.h"

typedef struct
{
	StationNode node[MAX_NODE];
	int node_num;
}Heap;

void init_heap(Heap *h);
void insert_node_min_heap(Heap *h, StationNode node);
StationNode delete_node_min_heap(Heap *h);
