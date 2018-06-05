#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "friend.h"

int main()
{
    UserType *user = (UserType*)malloc(sizeof(UserType));
	init(user);

	int friend_num[MAX_USER] = { 0 };
	memcpy(friend_num, get_friend_num(user), sizeof(friend_num));

    for (int i = 0; i < user->count; i++)
    {
        printf("%10d %20s \t친구수: %5d\n", user->user[i]->id_num, user->user[i]->name, friend_num[i]);
    }

    //확인용 출력
    for (int i = 0; i < 10; i++)
    {
        int random = rand() % 7000;
        User *temp = user->user[random];
        printf("%s 친구 :", temp->name);
        for (temp = temp->friends; temp->friends != NULL; temp = temp->friends)
        {
            printf(" %s,", temp->name);
        }
        printf("\n\n");
        temp = user->user[random];
        Word *w = temp->mentions;

        for (; w != NULL; w = w->next)
        {
            printf(" %s,", w->mention);
        }
        printf("\n");

    }


    return 0;
}

