#define MAX_NODE 1000
#define INF 100000
#define TRUE 1
#define FALSE 0

/*
지하철 노드
*/
typedef struct
{
	int num;        // 역 번호
	char name[20];  // 역명
	int line;       // 호선
	float dis;      // 해당역부터의 거리
	int transfer;   // 환승 가능 여부
	int toilet;     // 개찰구 내 화장실 여부
	struct StationNode *link;   // 해당역과 연결된 다른 역
}StationNode;

/*
지하철 역 배열 구조체
*/
typedef struct
{
	int count;
	StationNode *node[MAX_NODE];
}Station;

void init_station(Station *s);
void insert_station(Station *s);
void insert_edge(Station *s);
