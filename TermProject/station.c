#include <stdio.h>
#include <string.h>
#include "station.h"

/*
Station 구조체 초기화
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
노드 정보를 Station 구조체의 StationNode배열에 입력
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

	// 역 정보를 배열에 입력
	for (int i = 0; i < MAX_NODE && !feof(fp); i++)
	{
		StationNode *node = (StationNode*)malloc(sizeof(StationNode));
		if (node == NULL) return;

		node->link = NULL;

		//역이름
		fscanf_s(fp, "%s", tmpName, _countof(tmpName));
		strcpy_s(node->name, sizeof(node->name), tmpName);
		//역번호
		fscanf_s(fp, "%d\t", &(node->num));
        //역 호선
		fscanf_s(fp, "%d\t", &(node->line));

		node->dis = 0;

		//환승여부
		fscanf_s(fp, "%d\t", &(node->transfer));
		//개찰구 내 화장실 여부
		fscanf_s(fp, "%d\t", &(node->toilet));

		s->node[node->num] = node;
		s->count++;
	}

	fclose(fp);
}

/*
입력된 각 노드들을 서로 연결
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
			int connectedStationNum = 0;    //연결하려는 역 번호
			fscanf_s(fp, "%d\t", &connectedStationNum);

			StationNode *connectedNode = (StationNode*)malloc(sizeof(StationNode));
			if (connectedNode == NULL) return;

            //Station 노드에서 역 정보 복사
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