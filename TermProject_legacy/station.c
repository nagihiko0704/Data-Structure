#include <stdio.h>
#include <string.h>
#include "station.h"

/*
Station ����ü �ʱ�ȭ
*/
void init_station(Station *s)
{
	s->count = 0;
	for (int i = 0; i < MAX_NODE; i++)
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
	for (int i = 0; i < MAX_NODE && !feof(fp); i++)
	{
		StationNode *node = (StationNode*)malloc(sizeof(StationNode));
		if (node == NULL) return;

		node->link = NULL;

		//���̸�
		fscanf_s(fp, "%s", tmpName, _countof(tmpName));
		strcpy_s(node->name, sizeof(node->name), tmpName);
		//����ȣ
		fscanf_s(fp, "%d\t", &(node->num));
        //�� ȣ��
		fscanf_s(fp, "%d\t", &(node->line));

		node->dis = 0;

		//ȯ�¿���
		fscanf_s(fp, "%d\t", &(node->transfer));
		//������ �� ȭ��� ����
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

		while (TRUE)
		{
			int connectedStationNum = 0;    //�����Ϸ��� �� ��ȣ
			fscanf_s(fp, "%d\t", &connectedStationNum);

			StationNode *connectedNode = (StationNode*)malloc(sizeof(StationNode));
			if (connectedNode == NULL) return;

            //Station ��忡�� �� ���� ����
            memcpy_s(connectedNode, sizeof(StationNode), s->node[connectedStationNum], sizeof(StationNode));
			fscanf_s(fp, "%f", &(connectedNode->dis));
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