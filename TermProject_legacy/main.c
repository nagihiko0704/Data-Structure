#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "station.h"
#include "dijkstra.h"

int main()
{
    int from, to;
    Station s;
    init_station(&s);
    insert_station(&s);
    insert_edge(&s);
    
	Heap h;
    init_heap(&h);
    
    while (TRUE)
    {
        printf("종료하려면 -1을 입력해주세요\n");
        printf("출발역을 입력해주세요 : ");
        scanf_s("%d", &from);
        printf("도착역을 입력해주세요 : ");
        scanf_s("%d", &to);
        if (from == -1 || to == -1) break;
        if (0 > from || from > MAX_NODE || 0 > to ||to > MAX_NODE)
        {
            printf("입력이 잘못 되었습니다.\n");
            continue;
        }
    }

    // 확인용 출력
    int viewNum = 68;
    printf("From %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');
    s.node[viewNum] = s.node[viewNum]->link;
    printf("to %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');
    s.node[viewNum] = s.node[viewNum]->link;
    printf("to %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');

    return 0;
}
