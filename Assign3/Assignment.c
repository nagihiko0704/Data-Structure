#include <stdio.h>
#define INF 100000
#define MAX_NODE 10

typedef struct {
    int n; //노드 개수
    int node[MAX_NODE][MAX_NODE];
}Graph;

enum Vertex
{
S = 0,
A = 1,
B = 2,
C = 3,
D = 4,
E = 5,
F = 6,
G = 7,
H = 8
};


void init_graph(Graph *g);

void insert_edge(Graph *g, int start_edge, int end_edge, int dis);

int main()
{
    Graph g;

    init_graph(&g);

    insert_edge(&g, S, A, 7);
    insert_edge(&g, S, F, 4);
    insert_edge(&g, A, B, 5);
    insert_edge(&g, A, E, 2);
    insert_edge(&g, B, C, 4);
    insert_edge(&g, C, D, 2);
    insert_edge(&g, C, H, 6);
    insert_edge(&g, H, G, 1);
    insert_edge(&g, D, G, 8);
    insert_edge(&g, E, D, 3);
    insert_edge(&g, E, F, 11);
    insert_edge(&g, G, F, 9);
    for (int i = 0; i < MAX_NODE; i++) {
        printf("%d ", g.node[i][i]);
        for (int j = i + 1; j < MAX_NODE; j++) {
            printf("%d ", g.node[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void init_graph(Graph *g) {
    for (int i = 0; i < MAX_NODE; i++) {
        g->node[i][i] = 0;
        for (int j = i + 1; j < MAX_NODE; j++) {
            g->node[i][j] = INF;
        }
    }
}


void insert_edge(Graph *g, int start_edge, int end_edge, int dis) {
    g->node[start_edge][end_edge] = dis;
    g->node[end_edge][start_edge] = dis;
}