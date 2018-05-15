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

int main()
{
    Station s;
    init_station(&s);
    insert_station(&s);

    printf("%s %d %f %d %d\n", s.node[0]->name, s.node[0]->line, s.node[0]->dis, s.node[0]->transfer, s.node[0]->toilet);
    s.node[0] = s.node[0]->link;
    printf("%s %d %f %d %d\n", s.node[0]->name, s.node[0]->line, s.node[0]->dis, s.node[0]->transfer, s.node[0]->toilet);
    s.node[0] = s.node[0]->link;
    printf("%s %d %f %d %d\n", s.node[0]->name, s.node[0]->line, s.node[0]->dis, s.node[0]->transfer, s.node[0]->toilet);

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

    //������ ����Ʈ�� �Է�
    for (int i = 0; i < MAXNODE && !feof(fp); i++)
    {
        StationNode *node = (StationNode*)malloc(sizeof(StationNode));
        StationNode *end = (StationNode*)malloc(sizeof(StationNode));
        if (node == NULL || end == NULL) return;

        s->node[i] = node;
        node->link = NULL;
        fscanf_s(fp, "%s", tmpName, _countof(tmpName));
        strcpy_s(s->node[i]->name, sizeof(s->node[i]->name), tmpName);
        fscanf_s(fp, "%d\t", &(s->node[i]->line));
        node->dis = 0;
        fscanf_s(fp, "%d\t", &(s->node[i]->transfer));
        fscanf_s(fp, "%d\t", &(s->node[i]->toilet));
        s->count++;
        end = node;

        while(1)
        {
            StationNode *connectedNode = (StationNode*)malloc(sizeof(StationNode));
            connectedNode->link = NULL;
            fscanf_s(fp, "%s\t", tmpName, _countof(tmpName));
            strcpy_s(connectedNode->name, sizeof(connectedNode->name), tmpName);
            fscanf_s(fp, "%d\t", &(connectedNode->line));
            fscanf_s(fp, "%f\t", &(connectedNode->dis));
            fscanf_s(fp, "%d\t", &(connectedNode->transfer));
            fscanf_s(fp, "%d", &(connectedNode->toilet));

            end->link = connectedNode;
            end = end->link;
            char ch = fgetc(fp);
            if (ch == '\n' || ch == EOF) break;
        }

        end = NULL;
        free(end);
    }
}