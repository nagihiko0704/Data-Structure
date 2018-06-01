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
        printf("�����Ϸ��� -1�� �Է����ּ���\n");
        printf("��߿��� �Է����ּ��� : ");
        scanf_s("%d", &from);
        printf("�������� �Է����ּ��� : ");
        scanf_s("%d", &to);
        if (from == -1 || to == -1) break;
        if (0 > from || from > MAX_NODE || 0 > to ||to > MAX_NODE)
        {
            printf("�Է��� �߸� �Ǿ����ϴ�.\n");
            continue;
        }
    }

    // Ȯ�ο� ���
    int viewNum = 68;
    printf("From %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');
    s.node[viewNum] = s.node[viewNum]->link;
    printf("to %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');
    s.node[viewNum] = s.node[viewNum]->link;
    printf("to %s Station(StationNum : %d, line %d) %.1fkm Can%s transer. Toilet in ticket gate %c\n", s.node[viewNum]->name, s.node[viewNum]->num, s.node[viewNum]->line, s.node[viewNum]->dis, s.node[viewNum]->transfer ? "" : "not", s.node[viewNum]->toilet ? 'O' : 'X');

    return 0;
}
