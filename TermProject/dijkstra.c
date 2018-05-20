#include "dijkstra.h"

void init_heap(Heap *h)
{
	h->node_num = 0;
	for (int i = 0; i < MAX_NODE; i++) {
		h->node[i].dist = INF;
	}
}

void insert_node_min_heap(Heap *h, HeapNode node)
{
	int i = ++(h->node_num);

	while (i != 1 && (node.dist < h->node[i / 2].dist))
	{
		h->node[i] = h->node[i / 2];
		i /= 2;
	}

	h->node[i] = node;
}

HeapNode delete_node_min_heap(Heap *h)
{
	int parent, child;
	HeapNode node, tmp;

	node = h->node[1];
	tmp = h->node[h->node_num--];
	h->node[1] = tmp;
	parent = 1;
	child = 2;

	while (child <= h->node_num)
	{
		// 자식 노드 중 작은 걸 선택
		if (child < h->node_num && (h->node[child].dist > h->node[child + 1].dist))
		{
			child++;
		}
		// 자식 노드가 더 크면 중지
		if (tmp.dist <= h->node[child].dist) break;

		h->node[parent] = h->node[child];
		parent = child;
		child *= 2;
	}
	h->node[parent] = tmp;

	return node;
}