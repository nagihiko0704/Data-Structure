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
void find_friend(UserType *user)
{
	
}
