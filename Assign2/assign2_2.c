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

	//stack �ʱ�ȭ
	init_stack(&stack);
	//��� �ʱ�ȭ
	init_path(&path, entry);

	//���� ��ġ�� �ⱸ�� �ƴ� ���� �̷� Ž��
	while (temp.x != exit.x || temp.y != exit.y) 
	{
		//������ ���� 8�� ǥ��
		x = temp.x;
		y = temp.y;
		maze[x][y] = 8;

		printf("----------------------\n");
		print_maze();

		//�Ʒ�
		find_point(&stack, x + 1, y);
		//��
		find_point(&stack, x - 1, y);
		//����
		find_point(&stack, x, y - 1);
		//������
		find_point(&stack, x, y + 1);
		
		//���� stack�� ����ٸ� �̷� ã�⿡ ����
		if (is_empty(&stack)) {
			printf("�̷�ã�� ���Ф̤�\n");
			return -1;
		}
		//find_point���� Ž���� ��ǥ���� pop�Ͽ� ���� ã��
		else
		{
			temp = pop(&stack);

			//pop�� ��ǥ�� �� ������ ����̹Ƿ� path�� ����
			path[i] = temp;
			i++;
		}
	}
	printf("�̷�ã�� ����!\n");

	//��� ���
	print_path(&path);
	
	return 0;
}

//stack �ʱ�ȭ
void init_stack(StackType *s)
{
	s->top = NULL;
}

//path �ʱ�ȭ
void init_path(Point *p, Point entry)
{
	//�Ա� ��ǥ�� pop���� �����Ƿ� ù ���ҿ� entry ����
	p[0] = entry;
}

//stack�� ������� �˻�
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

//linked stack�� push
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

//linked stack�� pop
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

//�� �� �ִ� ��ǥ�� ã��
void find_point(StackType *s, int x, int y)
{
	Point temp;

	//�Է¹��� ��ǥ�� maze���� ��ǥ�� �ƴ϶�� �����޽����� ����ϰ� ����
	if (x < 0 || x > MAZE_SIZE || y < 0 || y > MAZE_SIZE)
	{
		printf("error: out of maze range\n");
		return;
	}
	//���� �ƴϰ� ���� ���� �ƴ϶�� stack�� push
	if (maze[x][y] != 1 && maze[x][y] != 8) {
		temp.x = x;
		temp.y = y;

		push(s, temp);
	}
}

//Ȯ�ο� maze ��� �Լ�
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

//��� ��� �Լ�
void print_path(Point *p)
{
	printf("\n----������----\n");

	//path �迭�� (0,0)���� �ʱ�ȭ �����Ƿ� ��ΰ� ���� ���� ���� ���� (0, 0)���� ��������
	while (p->x != 0)
	{
		printf("(%d, %d)\n", p->x, p->y);
		p++;
	}
}