#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct student 
{
	char name[100] ;
	int student_number;
	int score;
} Student;

void init_student(Student s[]);
double get_mean(Student s[], int std_num);
double get_square_mean(Student s[], int std_num);
double get_deviation(Student s[], int std_num);

int main(void)
{
	Student s[100];

	init_student(s);  //����ü �迭 �ʱ�ȭ

	double mean = get_mean(s, 100); //��� ���ϱ�
	double standard_deviation = get_deviation(s, 100); //ǥ������ ���ϱ�
	
	printf("�л��� ������ ���: %f \n", mean);
	printf("�л��� ������ ǥ������ %f \n", standard_deviation);

	return 0;
}

void init_student(Student s[]) 
{
	FILE *fp;

	fopen_s(&fp, "C:\\Student_info.txt","r"); //Student_info.txt ���� ����

	srand(time(NULL));

	if (fp == NULL) { 
		printf("����\n");
		return 1;
	} //���� ���⿡ �����Ұ�� ������ ����ϰ� 1 ����
	else {
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

//����� ���ϴ� �Լ� 
double get_mean(Student s[], int std_num) 
{
	double sum = 0;

	for (int i = 0; i < std_num; i++) 
	{
		sum = sum + s[i].score;
	}

	return sum / std_num;
}

//���� ����� ���ϴ� �Լ�
double get_square_mean(Student s[], int std_num) 
{
	double sum = 0;

	for (int i = 0; i < std_num; i++) 
	{
		sum = sum + pow(s[i].score, 2);
	}

	return sum / std_num;
}

//ǥ�������� ���ϴ� �Լ�
double get_deviation(Student s[], int std_num) 
{
	double mean = get_mean(s, std_num);
	double sqr_mean = get_square_mean(s, std_num);
	double std_dev = sqrt(sqr_mean - (pow(mean, 2)));

	return std_dev;
}