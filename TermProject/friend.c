#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "friend.h"

//각 user에 대해 friend 수를 찾는 함수
int *get_friend_num(UserType *user)
{
	int friend_num[MAX_USER] = { 0 };
	int num = 0;

	User *temp = (User *)malloc(sizeof(User));
	if (temp == NULL) return;

	for (int i = 0; i < user->count; i++)
	{
		temp = user->user[i];

		while (!(temp->friends) == NULL)
		{
			temp = temp->friends;
			num++;
		}

		friend_num[i] = num;
		num = 0;
	}

	return &friend_num;
}

//총 friend 수
int get_total_friend_num(UserType *user)
{
	int friend_num[MAX_USER] = { 0 };
	int total_num = 0;

	memcpy(friend_num, get_friend_num(user), sizeof(get_friend_num(user)));

	for (int i = user->count; i > 0; i--)
	{
		total_num += friend_num[i - 1];
	}

	return total_num;
}

//평균 friend 수
float get_avg_friend_num(UserType *user)
{
	float total_num = (float) get_total_friend_num(user);

	return total_num / user->count;
}

int get_min_friend_num(UserType *user)
{
	int friend_num[MAX_USER] = { 0 };
	int min = 0;

	memcpy(friend_num, get_friend_num(user), sizeof(get_friend_num(user)));

	for (int i = 0; i < user->count; i++)
	{
		if (min > friend_num[i])
			min = friend_num[i];
	}

	return min;
}

int get_max_friend_num(UserType *user)
{
	int friend_num[MAX_USER] = { 0 };
	int max = 0;

	memcpy(friend_num, get_friend_num(user), sizeof(get_friend_num(user)));

	for (int i = 0; i < user->count; i++)
	{
		if (max < friend_num[i])
			max = friend_num[i];
	}

	return max;
}

/*
한 유저의 친구 찾기
*/
void find_friend(UserType *user, int id_num)
{
    int index = find_user_index(user, id_num, 0, user->count - 1);
    User *user_node = (User*)malloc(sizeof(User));
    if (user_node == NULL) return;

    user_node = user->user[index];
    printf("The friends of %s : ", user_node->name);
    user_node = user_node->friends;

    while (user_node != NULL)
    {
        printf("%s, ", user_node->name);
        user_node = user_node->friends;
    }

    printf("\n");
    free(user_node);
}

/*
두 유저의 공통 친구 찾기 있으면 출력하고 1 없으면 0 반환
*/
int find_common_friend(UserType *user, int id_num1, int id_num2)
{
    int flag = 0;
    int index1 = find_user_index(user, id_num1, 0, user->count - 1);
    int index2 = find_user_index(user, id_num2, 0, user->count - 1);

    User *user_node1 = (User*)malloc(sizeof(User));
    User *user_node2 = (User*)malloc(sizeof(User));
    if (user_node1 == NULL || user_node2 == NULL) return;

    user_node1 = user->user[index1];
    user_node2 = user->user[index2];

    user_node1 = user_node1->friends;
    while (user_node1 != NULL)
    {
        user_node2 = user->user[index2]->friends;
        while (user_node2 != NULL)
        {
            if (user_node1->id_num == user_node2->id_num)
            {
                if (flag == 0)
                {
                    printf("The common friends between %20s and %20s : ", user->user[index1]->name, user->user[index2]->name);
                }
                printf("%s, ", user_node1->name);
                flag = 1;
            }
            user_node2 = user_node2->friends;
        }
        user_node1 = user_node1->friends;
    }

    if (!flag) return 0;
    else
    {
        printf("\n");
        return 1;
    }
}