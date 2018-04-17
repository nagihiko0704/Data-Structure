#include <stdio.h>
#include <stdlib.h>


typedef int element;

//������ ��带 ���� ����ü �� linkedstack ���� ����ü

typedef struct stacknode {
	element item;
	struct stacknode * link;
} stacknode;


//������ ���� ���� ����Ŵ. 

typedef struct {
	stacknode * top;
}linkedstacktype;

//�ʱ�ȭ �Լ�
void init(linkedstacktype * s) {

	s->top = NULL;
};


int is_empty(linkedstacktype *s) {
	
	return (s->top == NULL);
}


//push ���� 

void push(linkedstacktype*s, element item) {
	stacknode * temp = (stacknode*)malloc(sizeof(stacknode));

	if (temp == NULL) {
		printf("����");

		return;
	}

	else {
		temp->item = item;
		temp->link = s->top;
		s->top = temp;
	}
}

//POP����

element pop(linkedstacktype * s) {

	if (is_empty(s)) {
		printf("����");
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

//  ��ǥ ����� ����ü ����
typedef struct {

	int row;
	int column;

}pos;



int main(void) {


	//2���� �迭 �̷� ����
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