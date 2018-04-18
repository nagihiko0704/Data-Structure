#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
	char name[100];
	int student_number;
	int score;
} Student;

typedef struct studentNode
{
	Student node;
	struct studentNode *prev;
	struct studentNode *next;
} StudentNode;

void init_student(Student s[]);
void init_list(StudentNode *head_node);
void dinsert_node(StudentNode *head_node, StudentNode *new_node);
void print_list(StudentNode *head_node);

int main(void)
{
	Student student[100];
	StudentNode *s[100];
	StudentNode head_node;

	//student 구조체 초기화
	init_student(student);
	//list 초기화
	init_list(&head_node);

	for (int i = 0; i < 100; i++)
	{
		//StudentNode 포인터에 메모리 할당
		s[i] = (StudentNode *)malloc(sizeof(StudentNode));
		//StudentNode의 node에 정보 저장
		s[i]->node = student[i];

		//score 내림차 순으로 list에 삽입하는 dinset_node함수 호출
		dinsert_node(&head_node, s[i]);
	}

	//상위 10명과 하위 10명 출력
	print_list(&head_node);

	return 0;
}

//student 구조체 초기화 함수
void init_student(Student s[])
{
	FILE *fp;

	fopen_s(&fp, "Student_info.txt", "r"); //Student_info.txt 파일 열기

	srand(1);

	if (fp == NULL) {
		printf("망함\n");
		return;
	} //파일 열기에 실패할경우 망함을 출력하고 리턴
	else {
		printf("열림\n");
		for (int i = 0; i < 100 && fp != EOF; i++) {
			//학번을 읽어옴
			fscanf_s(fp, "%d \t", &s[i].student_number);
			printf("%d\t", s[i].student_number);

			//공백도 포함해서 이름을 읽어옴
			fscanf_s(fp, "%[^\n] \d", &s[i].name, _countof(s[i].name));
			printf("%-20s\t", s[i].name);

			//학생들의 성적을 0~100 사이 중에서 임의로 설정
			s[i].score = rand() % 101;
			printf("%d\n", s[i].score);
		}
	}

	fclose(fp);
}

//list를 초기화
void init_list(StudentNode *head_node)
{
	head_node->prev = head_node;
	head_node->next = head_node;
}

//head_node와 new_node를 받아 score의 내림차로 삽입하는 함수
void dinsert_node(StudentNode *head_node, StudentNode *new_node)
{
	StudentNode *temp;
	temp = head_node;

	//삽입할 노드의 score보다 작은 score를 가진 노드가 나타나기 전
	//그러한 노드가 없다면 마지막 노드까지 포인터를 이동시킴
	while (temp->next != head_node
		&& temp->next->node.score >= new_node->node.score)
	{
		temp = temp->next;
	}

	//node 삽입
	new_node->next = temp->next;
	temp->next->prev = new_node;
	new_node->prev = temp;
	temp->next = new_node;
}

//상위 10명과 하위 10명을 프린트 하는 함수
void print_list(StudentNode *head_node)
{
	StudentNode *temp;
	temp = head_node;

	printf("\n정렬됨\n");

	//상위 10명 출력
	printf("\n----------상위 10명----------\n");
	for (int i = 0; i < 10; i++)
	{
		temp = temp->next;
		printf("%d\t%-20s \t %d\n", temp->node.student_number, temp->node.name, temp->node.score);
	}

	temp = head_node;

	//하위 10명 출력
	printf("\n----------하위 10명----------\n");
	for (int i = 0; i < 10; i++)
	{
		temp = temp->prev;
		printf("%d\t%-20s \t %d\n", temp->node.student_number, temp->node.name, temp->node.score);
	}
}