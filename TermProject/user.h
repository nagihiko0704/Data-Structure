#pragma once
#define MAX_USER 7500

typedef struct TweetType //트윗 구조체
{
    char upload_date[40];   //올린 날짜
    char tweet[270];        //내용
    struct TweetType *next_tweet;//다른 트윗
}TweetType;

typedef struct user //유저 정보
{
    int id_num;					//고유번호
    char sign_up_date[40];      //가입일
    char name[20];				//닉네임
    TweetType *tweets;				//트윗
    struct user *friends;		//친구
}User;

typedef struct UserType //유저 배열 구조체
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