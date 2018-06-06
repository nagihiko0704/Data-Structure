#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "friend.h"
#include "word.h"

int main()
{
    UserType *user = (UserType*)malloc(sizeof(UserType));
	init(user);
    Heap *h = (Heap*)malloc(sizeof(Heap));
    init_Heap(h);
    Word *w = (Word*)malloc(sizeof(Word));
    init_Word(w);

    insert_word(h, user, w);

	int friend_num[MAX_USER] = { 0 };
	memcpy(friend_num, get_friend_num(user), sizeof(friend_num));
    
    for (int i = 0; i < user->count; i++)
    {
        printf("%10d %20s \t친구수: %5d\n", user->user[i]->id_num, user->user[i]->name, friend_num[i]);
    }

    for (int i = 0; i < w->size; i++)
    {
        find_user(w, user, w->node[i]->tweet);
        count_word(w, w->node[i]->tweet);
    }


    return 0;
}

