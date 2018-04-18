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

	init_student(s);  //구조체 배열 초기화

	double mean = get_mean(s, 100); //평균 구하기
	double standard_deviation = get_deviation(s, 100); //표준편차 구하기
	
	printf("학생들 성적의 평균: %f \n", mean);
	printf("학생들 성적의 표준편차 %f \n", standard_deviation);

	return 0;
}

void init_student(Student s[]) 
{
	FILE *fp;

	fopen_s(&fp, "C:\\Student_info.txt","r"); //Student_info.txt 파일 열기

	srand(time(NULL));

	if (fp == NULL) { 
		printf("망함\n");
		return 1;
	} //파일 열기에 실패할경우 망함을 출력하고 1 리턴
	else {
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

//평균을 구하는 함수 
double get_mean(Student s[], int std_num) 
{
	double sum = 0;

	for (int i = 0; i < std_num; i++) 
	{
		sum = sum + s[i].score;
	}

	return sum / std_num;
}

//제곱 평균을 구하는 함수
double get_square_mean(Student s[], int std_num) 
{
	double sum = 0;

	for (int i = 0; i < std_num; i++) 
	{
		sum = sum + pow(s[i].score, 2);
	}

	return sum / std_num;
}

//표준편차를 구하는 함수
double get_deviation(Student s[], int std_num) 
{
	double mean = get_mean(s, std_num);
	double sqr_mean = get_square_mean(s, std_num);
	double std_dev = sqrt(sqr_mean - (pow(mean, 2)));

	return std_dev;
}