#include "dijkstra.h"

void init_heap(Heap *h)
{
	h->node_num = 0;
	for (int i = 0; i < MAX_NODE; i++) {
		h->node[i].dis = INF;
	}
}

/*
min heap에 노드 삽입 key는 거리
*/
void insert_node_min_heap(Heap *h, StationNode node)
{
	int index = ++(h->node_num);

    //맨 마지막 위치에서 시작해서 삽입하려는 노드가 부모 노드보다 작으면 위로 거슬러 올라감
    for (int index = ++(h->node_num); index != 1 && (node.dis < h->node[index / 2].dis); index /= 2)
    {
        h->node[index] = h->node[index / 2];
    }

	h->node[index] = node;
}

/*
min heap의 루트 노드 삭제
*/
StationNode delete_node_min_heap(Heap *h)
{
	int parent, child;
	StationNode node, temp;

	node = h->node[1];              //반환할 루트 노드
	temp = h->node[h->node_num--];  //맨 마지막 노드
	h->node[1] = temp;
	parent = 1;
	child = 2;

	while (child <= h->node_num)
	{
		//자식 노드 중 작은 걸 선택
		if (child < h->node_num && (h->node[child].dis > h->node[child + 1].dis))
		{
			child++;
		}

        //현재 비교하고 있는 노드보다 맨 마지막 노드가 더 작으면 빠져나감
		if (temp.dis <= h->node[child].dis) break;

		h->node[parent] = h->node[child];   //삭제된 자리에 자식노드 삽입
		parent = child;
		child *= 2;     //밑 세대로 감
	}
	h->node[parent] = temp; //삭제된 자리에 맨 마지막 노드 삽입

	return node;
}