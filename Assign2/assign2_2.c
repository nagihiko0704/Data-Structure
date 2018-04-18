#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAZE_SIZE 10

typedef struct point
{
	int x;
	int y;
} Point;

typedef struct Stacknode
{
	Point node;
	struct Stacknode *link;
} StackNode;

typedef struct Stacktype
{
	StackNode *top;
} StackType;

void init_stack(StackType *s);
void init_path(Point *p, Point entry);
int is_empty(StackType *s);
void push(StackType *s, Point p);
Point pop(StackType *s);
void find_point(StackType *s, int r, int c);
void print_maze();
void print_path(Point *p);

int maze[MAZE_SIZE][MAZE_SIZE] = 
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };

int main(void)
{
	Point entry = { 1, 0 };
	Point exit = { 8, 9 };
	Point temp = entry;
	Point path[100] = {0,0};

	StackType stack;

	int x;
	int y;
	int i = 1;

	//stack 초기화
	init_stack(&stack);
	//경로 초기화
	init_path(&path, entry);

	//현재 위치가 출구가 아닌 동안 미로 탐색
	while (temp.x != exit.x || temp.y != exit.y) 
	{
		//지나간 곳은 8로 표시
		x = temp.x;
		y = temp.y;
		maze[x][y] = 8;

		printf("----------------------\n");
		print_maze();

		//아래
		find_point(&stack, x + 1, y);
		//위
		find_point(&stack, x - 1, y);
		//왼쪽
		find_point(&stack, x, y - 1);
		//오른쪽
		find_point(&stack, x, y + 1);
		
		//만약 stack이 비었다면 미로 찾기에 실패
		if (is_empty(&stack)) {
			printf("미로찾기 실패ㅜㅜ\n");
			return -1;
		}
		//find_point에서 탐색한 좌표들을 pop하여 길을 찾음
		else
		{
			temp = pop(&stack);

			//pop한 좌표가 곧 지나온 경로이므로 path에 저장
			path[i] = temp;
			i++;
		}
	}
	printf("미로찾기 성공!\n");

	//경로 출력
	print_path(&path);
	
	return 0;
}

//stack 초기화
void init_stack(StackType *s)
{
	s->top = NULL;
}

//path 초기화
void init_path(Point *p, Point entry)
{
	//입구 좌표는 pop되지 않으므로 첫 원소에 entry 삽입
	p[0] = entry;
}

//stack이 비었는지 검사
int is_empty(StackType *s)
{
	if (s->top == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//linked stack의 push
void push(StackType *s, Point p)
{
	StackNode *temp = (StackNode *) malloc(sizeof(StackNode));

	if (temp == NULL)
	{
		printf("memory allocation error\n");
		return;
	}
	else
	{
		temp->node = p;
		temp->link = s->top;
		s->top = temp;

		printf("push: (%d, %d)\n", s->top->node.x, s->top->node.y);
	}
}

//linked stack의 pop
Point pop(StackType *s)
{
	StackNode *temp = s->top;
	Point node = s->top->node;

	if (is_empty(s))
	{
		printf("empty stack\n");
		exit(1);
	}
	else
	{
		s->top = s->top->link;
		printf("pop: (%d, %d)\n", temp->node.x, temp->node.y);
		
		free(temp);

		return node;
	}
}

//갈 수 있는 좌표를 찾음
void find_point(StackType *s, int x, int y)
{
	Point temp;

	//입력받은 좌표가 maze안의 좌표가 아니라면 에러메시지를 출력하고 리턴
	if (x < 0 || x > MAZE_SIZE || y < 0 || y > MAZE_SIZE)
	{
		printf("error: out of maze range\n");
		return;
	}
	//벽이 아니고 갔던 곳이 아니라면 stack에 push
	if (maze[x][y] != 1 && maze[x][y] != 8) {
		temp.x = x;
		temp.y = y;

		push(s, temp);
	}
}

//확인용 maze 출력 함수
void print_maze()
{
	int i, j;
	for (i = 0; i<MAZE_SIZE; i++)
	{
		for (j = 0; j<MAZE_SIZE; j++) 
		{
			printf("%2d", maze[i][j]);
		}
		printf("\n");
	}
}

//경로 출력 함수
void print_path(Point *p)
{
	printf("\n----경로출력----\n");

	//path 배열을 (0,0)으로 초기화 했으므로 경로가 저장 되지 않은 곳은 (0, 0)으로 남아있음
	while (p->x != 0)
	{
		printf("(%d, %d)\n", p->x, p->y);
		p++;
	}
}