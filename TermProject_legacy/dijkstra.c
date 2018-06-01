#include "dijkstra.h"

void init_heap(Heap *h)
{
	h->node_num = 0;
	for (int i = 0; i < MAX_NODE; i++) {
		h->node[i].dis = INF;
	}
}

/*
min heap�� ��� ���� key�� �Ÿ�
*/
void insert_node_min_heap(Heap *h, StationNode node)
{
	int index = ++(h->node_num);

    //�� ������ ��ġ���� �����ؼ� �����Ϸ��� ��尡 �θ� ��庸�� ������ ���� �Ž��� �ö�
    for (int index = ++(h->node_num); index != 1 && (node.dis < h->node[index / 2].dis); index /= 2)
    {
        h->node[index] = h->node[index / 2];
    }

	h->node[index] = node;
}

/*
min heap�� ��Ʈ ��� ����
*/
StationNode delete_node_min_heap(Heap *h)
{
	int parent, child;
	StationNode node, temp;

	node = h->node[1];              //��ȯ�� ��Ʈ ���
	temp = h->node[h->node_num--];  //�� ������ ���
	h->node[1] = temp;
	parent = 1;
	child = 2;

	while (child <= h->node_num)
	{
		//�ڽ� ��� �� ���� �� ����
		if (child < h->node_num && (h->node[child].dis > h->node[child + 1].dis))
		{
			child++;
		}

        //���� ���ϰ� �ִ� ��庸�� �� ������ ��尡 �� ������ ��������
		if (temp.dis <= h->node[child].dis) break;

		h->node[parent] = h->node[child];   //������ �ڸ��� �ڽĳ�� ����
		parent = child;
		child *= 2;     //�� ����� ��
	}
	h->node[parent] = temp; //������ �ڸ��� �� ������ ��� ����

	return node;
}