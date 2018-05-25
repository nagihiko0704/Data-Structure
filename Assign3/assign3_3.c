#include <stdio.h>
#define INF 100000
#define MAX_NODE 9

typedef struct
{
    int n; //노드 개수
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

//탐색한 노드 - 0은 미탐색, 1은 탐색
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
그래프의 모든 행렬을 INF로 초기화
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
서로 다른 두 노드 사이를 연결
*/
void insert_edge(Graph *g, int start_edge, int end_edge, int dis)
{
    g->node[start_edge][end_edge] = dis;
    g->node[end_edge][start_edge] = dis;
    g->n++;
}

/*
힙 초기화
*/
void init_heap(HeapType *h)
{
    h->size = 0;
}

/*
min heap에 노드 삽입 key는 거리
*/
void insert_min_heap(HeapType *h, int start_edge, int end_edge, int dis)
{
    int index;

    //맨 마지막 위치에서 시작해서 삽입하려는 노드가 부모 노드보다 작으면 위로 거슬러 올라감
    for (index = ++(h->size); index != 1 && dis < h->heap[index / 2].dis; index /= 2)
    {
        h->heap[index] = h->heap[index / 2];
    }

    //자리잡은 위치에 삽입할 정보 입력
    h->heap[index].start_edge = start_edge;
    h->heap[index].end_edge = end_edge;
    h->heap[index].dis = dis;
}

/*
min heap의 루트 노드 삭제
*/
Heap delete_min_heap(HeapType *h)
{
    int p, c;
    Heap node, temp;
    node = h->heap[1];
    temp = h->heap[(h->size)--];    //맨 마지막 노드
    p = 1;
    c = 2;

    while (c <= h->size)
    {
        //옆 노드와 비교해서 더 작은 걸 선택
        if (c < h->size && h->heap[c].dis > h->heap[c + 1].dis) c++;
        //현재 비교하고 있는 노드보다 맨 마지막 노드가 더 작으면 빠져나감
        if (temp.dis <= h->heap[c].dis) break;
        
        
        h->heap[p] = h->heap[c];    //삭제된 자리에 작은 자식 노드 삽입
        p = c;
        c *= 2;     //밑 세대로 감
    }

    h->heap[p] = temp;  //삭제된 자리에 맨 마지막 노드 삽입
    return node;
}

/*
최단 경로 찾기
*/
void find_path(Graph *g, HeapType *h, int start_edge)
{
    //시작 노드의 경로 초기화
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
        Heap shortest = delete_min_heap(h); //시작 노드에서 가장 짧은 경로로 갈 수 있는 노드
        found[shortest.end_edge] = 1;   //탐색 표시

        //현재 가지고 있는 경로보다 더 짧은 경로가 있으면 더 짧은 경로로 대체
        if (g->node[start_edge][shortest.end_edge] > shortest.dis)
        {
            g->node[start_edge][shortest.end_edge] = shortest.dis;
        }
       
        //현재 탐색하고 있는 노드와 이어진 노드를 heap에 삽입
        for (int i = 0; i < MAX_NODE; i++)
        {
            //삽입하려는 노드는 현재 탐색하고 있는 노드와 이어져있어야함
            if (g->node[shortest.end_edge][i] > 0 && g->node[shortest.end_edge][i] != INF)
            {
                //이미 탐색한 노드는 삽입 안 함
                if (found[i] != 1)
                {
                    //탐색 노드와 이어진 노드의 경로는 = 시작 노드에서 현재 탐색하고 있는 노드까지의 거리 + 탐색하고 있는 노드에서 이어진 노드까지의 거리
                    insert_min_heap(h, shortest.end_edge, i, g->node[shortest.end_edge][i] + g->node[start_edge][shortest.end_edge]);
                }
            }
        }
    }
}

/*
플로이드 알고리즘
*/
void floyd(Graph *g)
{
    //가운데 노드
    for (int k = 0; k < MAX_NODE; k++)
    {
        //시작 노드
        for (int i = 0; i < MAX_NODE; i++)
        {
            //끝 노드
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
한 노드의 최단 거리 출력
*/
void display(Graph *g, int start_edge, int end_edge)
{
    printf("%c에서 %c까지의 최단 거리 : %d\n", enum_string(start_edge), enum_string(end_edge), g->node[start_edge][end_edge]);
}

/*
모든 최단 거리 출력
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