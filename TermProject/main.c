#include <stdio.h>

#define USER_NUM 1200000

typedef struct user
{
	char id[20];
	char signup_date[35];
	char screen_name[20];

	struct user *follow;
}User;

typedef struct userGraph
{
	int count;
	User *users[USER_NUM];
}UserGraph;

void init_user(UserGraph *ug);
void init_friend(UserGraph *ug);
void init_tweet();
void init();

int main(void)
{
	
}

void init_user(UserGraph *ug)
{
	FILE *fp;

	fopen_s(fp, "user.txt", "r");

	if (fp == NULL)
	{
		printf("fail to open user.txt\n");
		return;
	}

	for (int i = 0; i < USER_NUM && !feof(fp); i++)
	{
		fscanf_s(fp, "%s",		ug->users[i]->id);				//get user id
		fscanf_s(fp, "[^/n]",	ug->users[i]->signup_date);		//get user's sign-up date
		fscanf_s(fp, "%s",		ug->users[i]->screen_name);		//get user's screen name
		getc(fp);

		ug->count++;
	}

	fclose(fp);
}

void init_friend(UserGraph *ug)
{
	FILE *fp;

	fopen_s(fp, "friend.txt", "r");

	if (fp == NULL)
	{
		printf("fail to open friend.txt\n");
		return;
	}

	for (int i = 0; i < USER_NUM && !feof(fp); i++)
	{
		
	}
}

void init_tweet()
{
	FILE *fp;

	fopen_s(fp, "word.txt", "r");

	if (fp == NULL)
	{
		printf("fail to open word.txt\n");
		return;
	}
}

void init()
{
	init_user();
	init_friend();
	init_tweet();
}