#include <string.h>
#define MAX_USER 7500

typedef struct Word //멘션 구조체
{
    char upload_date[40];   //올린 날짜
    char mention[270];      //내용
    struct Word *next;      //다른 멘션
}Word;

typedef struct User //유저 정보
{
    int id_num;     //고유번호
    char sign_up_date[40];      //가입일
    char name[20];  //닉네임
    Word *mentions; //멘션
    struct User *friends;   //친구
}User;

typedef struct UserType //유저 배열 구조체
{
    int count;
    User *user[MAX_USER];
}UserType;

int get_month(char c[]);
void init_userType(UserType *u);
void insert_user(UserType *u);
void add_friends(UserType *u);
void add_mentions(UserType *u);