#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

int compare(const void *a, const void *b);

/*
���ڿ��� ���ڷ� �ٲ���
*/
int get_month(char c[])
{
    const char *DAY_STR[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    for (int i = 0; i < 12; i++)
    {
        if (strcmp(DAY_STR[i], c) == 0)
        {
            return i + 1;
        }
    }

    return -1;
}

/*
UserType�ʱ�ȭ
*/
void init_userType(UserType *u)
{
    u->count = 0;
}


/*
���� ���� �Է�
*/
void insert_user(UserType *u)
{
    FILE *fp;
    fopen_s(&fp, "user.txt", "r");

    if (fp == NULL)
    {
        printf("Fail to open the user.txt file.\n");
        return -1;
    }
    printf("Success to open the user.txt file!\n");

    char temp[35] = " ";

    for (int i = 0; !feof(fp); i++)
    {
        User *user = (User*)malloc(sizeof(User));

        if (user == NULL) return;

        //������ȣ
        fscanf_s(fp, "%d\n", &user->id_num);

        //���Գ�¥
        fscanf_s(fp, "%[^\n]\n", temp, sizeof(temp));
        strcpy_s(user->sign_up_date, sizeof(temp), temp);
        //�г���
        fscanf_s(fp, "%s\n", temp, sizeof(temp));
        strcpy_s(user->name, sizeof(temp), temp);

        user->friends = NULL;
        user->mentions = NULL;

        u->user[i] = user;

        u->count++;
    }

    qsort(u->user, u->count, sizeof(User*), compare);

    fclose(fp);
}

/*
�� �Լ�
*/
int compare(const void *a, const void *b)
{
    User **ua = (User**)a;
    User **ub = (User**)b;
    return ((*ua)->id_num - (*ub)->id_num);
}

/*
���� Ž������ ���� �ε��� �˻�
*/
int find_user_index(UserType *u, int id, int left, int right)
{
    if (left > right) return -1;

    int mid = (left + right) / 2;
    if (u->user[mid]->id_num == id) return mid;

    if (id < u->user[mid]->id_num) find_user_index(u, id, left, mid - 1);
    else find_user_index(u, id, mid + 1, right);
}

/*
ģ�� �߰�
*/
void add_friends(UserType *u)
{
    FILE *fp;
    fopen_s(&fp, "friend.txt", "r");

    if (fp == NULL)
    {
        printf("Fail to open the friend.txt file.\n");
        return -1;
    }
    printf("Success to open the friend.txt file!\n");


    for (int i = 0; !feof(fp); i++)
    {
        int user_id = 0;
        int friend_id = 0;

        fscanf_s(fp, "%d\n", &user_id);
        fscanf_s(fp, "%d\n", &friend_id);

        User *temp = (User*)malloc(sizeof(User));   //ģ���� ������ �ӽ� ����
        User *friendUser = (User*)malloc(sizeof(User)); //������ ģ��

        if (temp == NULL || friendUser == NULL) return;

        temp = u->user[find_user_index(u, friend_id, 0, u->count - 1)];

        //friends�� NULL�� ����� ���� ����ü ����
        memcpy_s(friendUser, sizeof(friendUser), temp, sizeof(temp));
        //��� ����
        strcpy_s(friendUser->name , sizeof(friendUser->name), temp->name);
        strcpy_s(friendUser->sign_up_date, sizeof(friendUser->sign_up_date), temp->sign_up_date);
        friendUser->mentions = NULL;
        friendUser->friends = NULL;

        //����
        temp = u->user[find_user_index(u, user_id, 0, u->count - 1)];
        //���� ã��
        while (temp->friends != NULL) temp = temp->friends;

        //���� ����
        temp->friends = friendUser;

        //�޸� ����
        temp = NULL;
        free(temp);
    }

    fclose(fp);
}


void add_mentions(UserType *u)
{
    FILE *fp;
    fopen_s(&fp, "word.txt", "r");

    if (fp == NULL)
    {
        printf("Fail to open the word.txt file.\n");
        return -1;
    }
    printf("Success to open the word.txt file!\n");


    for (int i = 0; !feof(fp); i++)
    {
        Word *word = (Word*)malloc(sizeof(Word));
        User *user = (User*)malloc(sizeof(User));
        Word *temp = (Word*)malloc(sizeof(Word));

        if (user == NULL || word == NULL || temp == NULL) return;

        int user_id = 0;
        char date[35];
        char mention[270];

        //����� ����ID
        fscanf_s(fp, "%d\n", &user_id);
        //����� ��¥
        fscanf_s(fp, "%[^\n]\n", date, sizeof(date));
        //��� ����
        fscanf_s(fp, "%[^\n]\n", mention, sizeof(mention));

        //����
        user = u->user[find_user_index(u, user_id, 0, u->count - 1)];
        temp = user->mentions;

        //�� ó�� ����̸� �ٷ� ����
        if (temp == NULL) user->mentions = word;
        //�ƴϸ� ���� ã��
        else
        {
            while (temp->next != NULL) temp = temp->next;
            temp->next = word;
        }
        
        //���� ����
        strcpy_s(word->mention, sizeof(word->mention), mention);
        strcpy_s(word->upload_date, sizeof(word->upload_date), date);
        word->next = NULL;

        //�޸� ����
        user = NULL;
        temp = NULL;
        free(user);
        free(temp);
    }

    fclose(fp);
}