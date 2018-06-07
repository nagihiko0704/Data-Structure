#pragma once
#define MAX_USER 7500

typedef struct TweetType //Ʈ�� ����ü
{
    char upload_date[40];   //�ø� ��¥
    char tweet[270];        //����
    struct TweetType *next_tweet;//�ٸ� Ʈ��
}TweetType;

typedef struct user //���� ����
{
    int id_num;					//������ȣ
    char sign_up_date[40];      //������
    char name[20];				//�г���
    TweetType *tweets;				//Ʈ��
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
void add_tweets(UserType *u);
int compare(const void *a, const void *b);