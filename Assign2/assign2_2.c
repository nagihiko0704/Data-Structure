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
int is_empty(StackType *s);
void push(StackType *s, Point p);
Point pop(StackType *s);
void find_maze(StackType *s, int r, int c);
void print_maze();

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

	StackType stack;

	int x;
	int y;

	init_stack(&stack);

	while (temp.x != exit.x || temp.y != exit.y) 
	{
		x = temp.x;
		y = temp.y;
		maze[x][y] = 8;

		print_maze();
		printf("----------------------\n");

		//아래
		find_maze(&stack, x + 1, y);
		//위
		find_maze(&stack, x - 1, y);
		//왼쪽
		find_maze(&stack, x, y - 1);
		//오른쪽
		find_maze(&stack, x, y + 1);

		if (is_empty(&stack)) {
			printf("실패\n");
			return -1;
		}
		else
		{
			temp = pop(&stack);
		}
	}
	printf("성공\n");
	
	return 0;
}

void init_stack(StackType *s)
{
	s->top = NULL;
}

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

void find_maze(StackType *s, int x, int y)
{
	Point temp;

	if (x < 0 || x > MAZE_SIZE || y < 0 || y > MAZE_SIZE)
	{
		printf("error: out of maze range\n");
		return;
	}
	if (maze[x][y] != 1 && maze[x][y] != 8) {
		temp.x = x;
		temp.y = y;

		push(s, temp);
	}
}

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