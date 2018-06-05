#pragma once

#include <string.h>
#define MAX_USER 7500

typedef struct word //멘션 구조체
{
    char upload_date[40];   //올린 날짜
    char mention[270];      //내용
    struct word *next;      //다른 멘션
}Word;

typedef struct user //유저 정보
{
    int id_num;					//고유번호
    char sign_up_date[40];      //가입일
    char name[20];				//닉네임
    Word *mentions;				//멘션
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
void add_mentions(UserType *u);
int compare(const void *a, const void *b);