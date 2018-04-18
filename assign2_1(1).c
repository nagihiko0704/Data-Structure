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

	//student ����ü �ʱ�ȭ
	init_student(student);
	//list �ʱ�ȭ
	init_list(&head_node);

	for (int i = 0; i < 100; i++)
	{
		//StudentNode �����Ϳ� �޸� �Ҵ�
		s[i] = (StudentNode *)malloc(sizeof(StudentNode));
		//StudentNode�� node�� ���� ����
		s[i]->node = student[i];

		//score ������ ������ list�� �����ϴ� dinset_node�Լ� ȣ��
		dinsert_node(&head_node, s[i]);
	}

	//���� 10��� ���� 10�� ���
	print_list(&head_node);

	return 0;
}

//student ����ü �ʱ�ȭ �Լ�
void init_student(Student s[])
{
	FILE *fp;

	fopen_s(&fp, "Student_info.txt", "r"); //Student_info.txt ���� ����

	srand(1);

	if (fp == NULL) {
		printf("����\n");
		return;
	} //���� ���⿡ �����Ұ�� ������ ����ϰ� ����
	else {
		printf("����\n");
		for (int i = 0; i < 100 && fp != EOF; i++) {
			//�й��� �о��
			fscanf_s(fp, "%d \t", &s[i].student_number);
			printf("%d\t", s[i].student_number);

			//���鵵 �����ؼ� �̸��� �о��
			fscanf_s(fp, "%[^\n] \d", &s[i].name, _countof(s[i].name));
			printf("%-20s\t", s[i].name);

			//�л����� ������ 0~100 ���� �߿��� ���Ƿ� ����
			s[i].score = rand() % 101;
			printf("%d\n", s[i].score);
		}
	}

	fclose(fp);
}

//list�� �ʱ�ȭ
void init_list(StudentNode *head_node)
{
	head_node->prev = head_node;
	head_node->next = head_node;
}

//head_node�� new_node�� �޾� score�� �������� �����ϴ� �Լ�
void dinsert_node(StudentNode *head_node, StudentNode *new_node)
{
	StudentNode *temp;
	temp = head_node;

	//������ ����� score���� ���� score�� ���� ��尡 ��Ÿ���� ��
	//�׷��� ��尡 ���ٸ� ������ ������ �����͸� �̵���Ŵ
	while (temp->next != head_node
		&& temp->next->node.score >= new_node->node.score)
	{
		temp = temp->next;
	}

	//node ����
	new_node->next = temp->next;
	temp->next->prev = new_node;
	new_node->prev = temp;
	temp->next = new_node;
}

//���� 10��� ���� 10���� ����Ʈ �ϴ� �Լ�
void print_list(StudentNode *head_node)
{
	StudentNode *temp;
	temp = head_node;

	printf("\n���ĵ�\n");

	//���� 10�� ���
	printf("\n----------���� 10��----------\n");
	for (int i = 0; i < 10; i++)
	{
		temp = temp->next;
		printf("%d\t%-20s \t %d\n", temp->node.student_number, temp->node.name, temp->node.score);
	}

	temp = head_node;

	//���� 10�� ���
	printf("\n----------���� 10��----------\n");
	for (int i = 0; i < 10; i++)
	{
		temp = temp->prev;
		printf("%d\t%-20s \t %d\n", temp->node.student_number, temp->node.name, temp->node.score);
	}
}