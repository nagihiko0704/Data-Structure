#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNODE 1000
#define TRUE 1
#define FALSE 0

/*
����ö ���
*/
typedef struct
{
    int num;        // �� ��ȣ
    char name[20];  // ����
    int line;       // ȣ��
    float dis;      // �ش翪������ �Ÿ�
    int transfer;   // ȯ�� ���� ����
    int toilet;     // ������ �� ȭ��� ����
    struct StationNode *link;   // �ش翪�� ����� �ٸ� ��
}StationNode;

/*
����ö �� �迭 ����ü
*/
typedef struct
{
    int count;
    StationNode *node[MAXNODE];
}Station;


void init_station(Station *s);
void insert_station(Station *s);
void insert_edge(Station *s);

int main()
{
    Station s;
    init_station(&s);
    insert_station(&s);
    insert_edge(&s);

    // Ȯ�ο� ���
    int viewNum = 68;
    printf("From %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');
    s.node[viewNum] = s.node[viewNum]->link;
    printf("to %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');
    s.node[viewNum] = s.node[viewNum]->link;
    printf("to %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');

    return 0;
}

void init_station(Station *s)
{
    s->count = 0;
    for (int i = 0; i < MAXNODE; i++)
    {
        s->node[i] = NULL;
    }
}


/*
��� ������ Station ����ü�� StationNode�迭�� �Է�
*/
void insert_station(Station *s)
{
    FILE *fp;
    fopen_s(&fp, "Station_Info.txt", "r");

    if (fp == NULL)
    {
        printf("Fail to open the file.\n");
        return -1;
    }

    char tmpName[20] = " ";

    // �� ������ �迭�� �Է�
    for (int i = 0; i < MAXNODE && !feof(fp); i++)
    {
        StationNode *node = (StationNode*)malloc(sizeof(StationNode));
        if (node == NULL) return;

        node->link = NULL;
        fscanf_s(fp, "%s", tmpName, _countof(tmpName));
        strcpy_s(node->name, sizeof(node->name), tmpName);
        fscanf_s(fp, "%d\t", &(node->num));
        fscanf_s(fp, "%d\t", &(node->line));
        node->dis = 0;
        fscanf_s(fp, "%d\t", &(node->transfer));
        fscanf_s(fp, "%d\t", &(node->toilet));

        s->node[node->num] = node;
        s->count++;
    }

    fclose(fp);
}

/*
�Էµ� �� ������ ���� ����
*/
void insert_edge(Station *s)
{
    FILE *fp;
    fopen_s(&fp, "Station_Edge.txt", "r");

    if (fp == NULL)
    {
        printf("Fail to open the file.\n");
        return -1;
    }

    for (int i = 0; i < s->count && !feof(fp); i++)
    {
        int stationNum = 0;
        fscanf_s(fp, "%d\t", &stationNum);

        StationNode *end = (StationNode*)malloc(sizeof(StationNode));
        if (end == NULL) return;

        end = s->node[stationNum];
        while (1)
        {
            int connectedStationNum = 0;
            fscanf_s(fp, "%d\t", &connectedStationNum);

            StationNode *connectedNode = (StationNode*)malloc(sizeof(StationNode));
            if (connectedNode == NULL) return;

            connectedNode->num = s->node[connectedStationNum]->num;
            strcpy_s(connectedNode->name, sizeof(connectedNode->name), s->node[connectedStationNum]->name);
            connectedNode->line = s->node[connectedStationNum]->line;
            fscanf_s(fp, "%f", &(connectedNode->dis));
            connectedNode->transfer = s->node[connectedStationNum]->transfer;
            connectedNode->toilet = s->node[connectedStationNum]->toilet;
            connectedNode->link = NULL;

            end->link = connectedNode;
            end = end->link;
            char ch = fgetc(fp);
            if (ch == '\n' || ch == EOF) break;
        }

        end = NULL;
        free(end);
    }

    fclose(fp);
}