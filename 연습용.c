#include <stdio.h>
#include <stdlib.h>


typedef int element;

//스택의 노드를 위한 구조체 및 linkedstack 관련 구조체

typedef struct stacknode {
	element item;
	struct stacknode * link;
} stacknode;


//스택의 가장 위를 가리킴. 

typedef struct {
	stacknode * top;
}linkedstacktype;

//초기화 함수
void init(linkedstacktype * s) {

	s->top = NULL;
};


int is_empty(linkedstacktype *s) {
	
	return (s->top == NULL);
}


//push 연산 

void push(linkedstacktype*s, element item) {
	stacknode * temp = (stacknode*)malloc(sizeof(stacknode));

	if (temp == NULL) {
		printf("에러");

		return;
	}

	else {
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}

//POP연산

element pop(linkedstacktype * s) {

	if (is_empty(s)) {
		printf("에러");
		exit(1);
	}

	else {
		stacknode * temp = s->top;
		int item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}

//  좌표 저장용 구조체 선언
typedef struct {

	int row;
	int column;

}pos;



int main(void) {


	//2차원 배열 미로 선언
	int maze[10][10] = {
		
						{1,1,1,1,1,1,1,1,1,1},
						{0,0,0,0,1,0,0,0,0,1},
						{1,0,0,0,1,0,0,0,0,1},
						{1,0,1,1,1,0,0,1,0,1},
						{1,0,0,0,1,0,0,1,0,1},
						{1,0,1,0,1,0,0,1,0,1},
						{1,0,1,0,1,0,0,1,0,1},
						{1,0,1,0,1,0,0,1,0,1},
						{1,0,1,0,0,0,0,1,0,0},
						{1,1,1,1,1,1,1,1,1,1}
	};
	





	return 0;

}