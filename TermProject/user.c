#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

/*
UserType에 정보 입력
*/
void init(UserType *u)
{
	init_userType(u);
	insert_user(u);
	add_friends(u);
	add_tweets(u);
}

/*
UserType초기화
*/
void init_userType(UserType *u)
{
    u->count = 0;
}


/*
유저 정보 입력
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

        //고유번호
        fscanf_s(fp, "%d\n", &user->id_num);

        //가입날짜
        fscanf_s(fp, "%[^\n]\n", temp, sizeof(temp));
        strcpy_s(user->sign_up_date, sizeof(temp), temp);

        //닉네임
        fscanf_s(fp, "%s\n", temp, sizeof(temp));
        strcpy_s(user->name, sizeof(temp), temp);

        user->friends = NULL;
        user->tweets = NULL;

        u->user[i] = user;

        u->count++;
    }

    qsort(u->user, u->count, sizeof(User*), compare);

    fclose(fp);
}

/*
비교 함수
*/
int compare(const void *a, const void *b)
{
    User **ua = (User**)a;
    User **ub = (User**)b;
    return ((*ua)->id_num - (*ub)->id_num);
}

/*
이진 탐색으로 유저 인덱스 검색
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
친구 추가
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

        User *temp = (User*)malloc(sizeof(User));           //친구를 연결할 임시 변수
        User *friendUser = (User*)malloc(sizeof(User));     //연결할 친구

        if (temp == NULL || friendUser == NULL) return;

        temp = u->user[find_user_index(u, friend_id, 0, u->count - 1)];

        //friends를 NULL로 만들기 위한 구조체 복사
        memcpy_s(friendUser, sizeof(friendUser), temp, sizeof(temp));

        //요소 복사
        strcpy_s(friendUser->name , sizeof(friendUser->name), temp->name);
        strcpy_s(friendUser->sign_up_date, sizeof(friendUser->sign_up_date), temp->sign_up_date);
        friendUser->tweets = NULL;
        friendUser->friends = NULL;

        //유저
        temp = u->user[find_user_index(u, user_id, 0, u->count - 1)];
        //끝을 찾음
        while (temp->friends != NULL) temp = temp->friends;

        //끝에 연결
        temp->friends = friendUser;

        //메모리 해제
        temp = NULL;
        free(temp);
    }

    fclose(fp);
}

/*
트윗 추가
*/
void add_tweets(UserType *u)
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
        TweetType *tweet = (TweetType*)malloc(sizeof(TweetType));
        User *user = (User*)malloc(sizeof(User));
        TweetType *temp = (TweetType*)malloc(sizeof(TweetType));

        if (user == NULL || tweet == NULL || temp == NULL) return;

        int user_id = 0;
        char date[35];
        char temp_tweet[270];

        //트윗한 유저ID
        fscanf_s(fp, "%d\n", &user_id);
        //트윗한 날짜
        fscanf_s(fp, "%[^\n]\n", date, sizeof(date));
        //트윗 내용
        fscanf_s(fp, "%[^\n]\n", temp_tweet, sizeof(temp_tweet));

        //유저
        user = u->user[find_user_index(u, user_id, 0, u->count - 1)];
        temp = user->tweets;

        //맨 처음 트윗이면 바로 연결
        if (temp == NULL) user->tweets = tweet;
        //아니면 끝을 찾음
        else
        {
            while (temp->next_tweet != NULL) temp = temp->next_tweet;
            temp->next_tweet = tweet;
        }
        
        //내용 복사
        strcpy_s(tweet->tweet, sizeof(tweet->tweet), temp_tweet);
        strcpy_s(tweet->upload_date, sizeof(tweet->upload_date), date);
        tweet->next_tweet = NULL;

        //메모리 해제
        user = NULL;
        temp = NULL;
        free(user);
        free(temp);
    }

    fclose(fp);
}