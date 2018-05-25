#include <stdio.h>
#define INF 100000
#define MAX_NODE 9

typedef struct
{
    int n; //��� ����
    int node[MAX_NODE][MAX_NODE];
}Graph;

typedef struct
{
    int start_edge;
    int end_edge;
    int dis;
}Heap;

typedef struct
{
    Heap heap[MAX_NODE * 10];
    int size;
}HeapType;

enum Vertex
{
    S,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H
};

static char enum_string(enum Vertex v)
{
    static const char str[] = { 'S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
    return str[v];
}

//Ž���� ��� - 0�� ��Ž��, 1�� Ž��
int found[MAX_NODE];

void init_graph(Graph *g);
void insert_edge(Graph *g, int start_edge, int end_edge, int dis);
void init_heap(HeapType *h);
void insert_min_heap(HeapType *h, int start_edge, int end_edge, int dis);
Heap delete_min_heap(HeapType *h);
void find_path(Graph *g, HeapType *h, int start_edge);
void floyd(Graph *g);
void display(Graph *g, int start_edge, int end_edge);
void display_all(Graph *g);

int main()
{
    Graph g1, g2;
    HeapType h;

    init_graph(&g1);
    init_graph(&g2);
    init_heap(&h);

    find_path(&g1, &h, S);
    floyd(&g2);

    display(&g1, S, H);
    display_all(&g2);
    return 0;
}

/*
�׷����� ��� ����� INF�� �ʱ�ȭ
*/
void init_graph(Graph *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_NODE; i++)
    {
        for (int j = 0; j < MAX_NODE; j++)
        {
            if (i == j) g->node[i][j] = 0;
            else g->node[i][j] = INF;
        }
    }
    insert_edge(g, S, A, 7);
    insert_edge(g, S, F, 4);
    insert_edge(g, A, B, 5);
    insert_edge(g, A, E, 2);
    insert_edge(g, B, C, 4);
    insert_edge(g, C, D, 2);
    insert_edge(g, C, H, 6);
    insert_edge(g, D, G, 8);
    insert_edge(g, E, D, 3);
    insert_edge(g, E, F, 11);
    insert_edge(g, F, G, 9);
    insert_edge(g, G, H, 1);
}

/*
���� �ٸ� �� ��� ���̸� ����
*/
void insert_edge(Graph *g, int start_edge, int end_edge, int dis)
{
    g->node[start_edge][end_edge] = dis;
    g->node[end_edge][start_edge] = dis;
    g->n++;
}

/*
�� �ʱ�ȭ
*/
void init_heap(HeapType *h)
{
    h->size = 0;
}

/*
min heap�� ��� ���� key�� �Ÿ�
*/
void insert_min_heap(HeapType *h, int start_edge, int end_edge, int dis)
{
    int index;

    //�� ������ ��ġ���� �����ؼ� �����Ϸ��� ��尡 �θ� ��庸�� ������ ���� �Ž��� �ö�
    for (index = ++(h->size); index != 1 && dis < h->heap[index / 2].dis; index /= 2)
    {
        h->heap[index] = h->heap[index / 2];
    }

    //�ڸ����� ��ġ�� ������ ���� �Է�
    h->heap[index].start_edge = start_edge;
    h->heap[index].end_edge = end_edge;
    h->heap[index].dis = dis;
}

/*
min heap�� ��Ʈ ��� ����
*/
Heap delete_min_heap(HeapType *h)
{
    int p, c;
    Heap node, temp;
    node = h->heap[1];
    temp = h->heap[(h->size)--];    //�� ������ ���
    p = 1;
    c = 2;

    while (c <= h->size)
    {
        //�� ���� ���ؼ� �� ���� �� ����
        if (c < h->size && h->heap[c].dis > h->heap[c + 1].dis) c++;
        //���� ���ϰ� �ִ� ��庸�� �� ������ ��尡 �� ������ ��������
        if (temp.dis <= h->heap[c].dis) break;
        
        
        h->heap[p] = h->heap[c];    //������ �ڸ��� ���� �ڽ� ��� ����
        p = c;
        c *= 2;     //�� ����� ��
    }

    h->heap[p] = temp;  //������ �ڸ��� �� ������ ��� ����
    return node;
}

/*
�ִ� ��� ã��
*/
void find_path(Graph *g, HeapType *h, int start_edge)
{
    //���� ����� ��� �ʱ�ȭ
    for (int i = 0; i < MAX_NODE; i++)
    {
        if (g->node[start_edge][i] != 0 && g->node[start_edge][i] != INF)
        {
            insert_min_heap(h, start_edge, i, g->node[start_edge][i]);
        }
    }
    g->node[start_edge][start_edge] = 0;
    found[start_edge] = 1;

    while (h->size != 0)
    {
        Heap shortest = delete_min_heap(h); //���� ��忡�� ���� ª�� ��η� �� �� �ִ� ���
        found[shortest.end_edge] = 1;   //Ž�� ǥ��

        //���� ������ �ִ� ��κ��� �� ª�� ��ΰ� ������ �� ª�� ��η� ��ü
        if (g->node[start_edge][shortest.end_edge] > shortest.dis)
        {
            g->node[start_edge][shortest.end_edge] = shortest.dis;
        }
       
        //���� Ž���ϰ� �ִ� ���� �̾��� ��带 heap�� ����
        for (int i = 0; i < MAX_NODE; i++)
        {
            //�����Ϸ��� ���� ���� Ž���ϰ� �ִ� ���� �̾����־����
            if (g->node[shortest.end_edge][i] > 0 && g->node[shortest.end_edge][i] != INF)
            {
                //�̹� Ž���� ���� ���� �� ��
                if (found[i] != 1)
                {
                    //Ž�� ���� �̾��� ����� ��δ� = ���� ��忡�� ���� Ž���ϰ� �ִ� �������� �Ÿ� + Ž���ϰ� �ִ� ��忡�� �̾��� �������� �Ÿ�
                    insert_min_heap(h, shortest.end_edge, i, g->node[shortest.end_edge][i] + g->node[start_edge][shortest.end_edge]);
                }
            }
        }
    }
}

/*
�÷��̵� �˰���
*/
void floyd(Graph *g)
{
    //��� ���
    for (int k = 0; k < MAX_NODE; k++)
    {
        //���� ���
        for (int i = 0; i < MAX_NODE; i++)
        {
            //�� ���
            for (int j = 0; j < MAX_NODE; j++)
            {
                if (g->node[i][j] > g->node[i][k] + g->node[k][j])
                {
                    g->node[i][j] = g->node[i][k] + g->node[k][j];
                }
            }
        }
    }
}

/*
�� ����� �ִ� �Ÿ� ���
*/
void display(Graph *g, int start_edge, int end_edge)
{
    printf("%c���� %c������ �ִ� �Ÿ� : %d\n", enum_string(start_edge), enum_string(end_edge), g->node[start_edge][end_edge]);
}

/*
��� �ִ� �Ÿ� ���
*/
void display_all(Graph *g)
{
    printf("   ");
    for (int i = 0; i < MAX_NODE; i++)
    {
        printf("%c  ", enum_string(i));
    }
    printf("\n");

    for (int i = 0; i < MAX_NODE; i++)
    {
        printf("%c  ", enum_string(i));
        for (int j = 0; j < MAX_NODE; j++)
        {
            printf("%-2d ", g->node[i][j]);
        }
        printf("\n");
    }

}