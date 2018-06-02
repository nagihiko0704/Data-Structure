#include <string.h>
#define MAX_USER 7500

typedef struct Word //��� ����ü
{
    char upload_date[40];   //�ø� ��¥
    char mention[270];      //����
    struct Word *next;      //�ٸ� ���
}Word;

typedef struct User //���� ����
{
    int id_num;     //������ȣ
    char sign_up_date[40];      //������
    char name[20];  //�г���
    Word *mentions; //���
    struct User *friends;   //ģ��
}User;

typedef struct UserType //���� �迭 ����ü
{
    int count;
    User *user[MAX_USER];
}UserType;

int get_month(char c[]);
void init_userType(UserType *u);
void insert_user(UserType *u);
void add_friends(UserType *u);
void add_mentions(UserType *u);