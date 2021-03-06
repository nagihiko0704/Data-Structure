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
    
    Word *words_sorted_word = (Word*)malloc(sizeof(Word));  //단어 사전 순으로 정렬
    Word *words_sorted_num = (Word*)malloc(sizeof(Word));   //단어 횟수 순으로 정렬
    init_Word(words_sorted_word);
    init_Word(words_sorted_num);

    insert_word(h, user, words_sorted_word);
    words_sorted_num = num_sort(words_sorted_word);

	int friend_num[MAX_USER] = { 0 };
	memcpy(friend_num, get_friend_num(user), sizeof(friend_num));
    
    
    for (int i = 0; i < 100; i++)
    {
        printf("%s : %d\n", words_sorted_num->node[i]->tweet, words_sorted_num->node[i]->count);
    }
    

    find_friend(user, user->user[0]->id_num);
    for (int i = 1; i < user->count; i++)
    {
        if (!find_common_friend(user, user->user[0]->id_num, user->user[i]->id_num)) continue;
    }

    return 0;
}

