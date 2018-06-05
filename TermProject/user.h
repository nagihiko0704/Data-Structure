#pragma once

#include <string.h>
#define MAX_USER 7500

typedef struct word //��� ����ü
{
    char upload_date[40];   //�ø� ��¥
    char mention[270];      //����
    struct word *next;      //�ٸ� ���
}Word;

typedef struct user //���� ����
{
    int id_num;					//������ȣ
    char sign_up_date[40];      //������
    char name[20];				//�г���
    Word *mentions;				//���
    struct user *friends;		//ģ��
}User;

typedef struct UserType //���� �迭 ����ü
{
    int count;
    User *user[MAX_USER];
}UserType;

void init(UserType *u);
void init_userType(UserType *u);
void insert_user(UserType *u);
void add_friends(UserType *u);
void add_mentions(UserType *u);
int compare(const void *a, const void *b);