#define MAX_NODE 1000
#define INF 100000
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
	StationNode *node[MAX_NODE];
}Station;

void init_station(Station *s);
void insert_station(Station *s);
void insert_edge(Station *s);
