#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "user.h"

/*
Heap 초기화
*/
void init_Heap(Heap *h)
{
    h->size = 0;
}

/*
Word 초기화
*/
void init_Word(Word *w)
{
    w->size = 0;
    for (int i = 0; i < MAX_WORD; i++)
    {
        w->node[i] = NULL;
    }
}

/*
정렬된 Heap에서 중복되지 않게 단어 삽입
*/
void insert_word(Heap *h, UserType *u, Word *w)
{
    heap_sort(h, u);

    int index = 0;

    //맨 처음
    HeapNode temp = delete_min_heap(h);
    w->node[index] = (WordNode*)malloc(sizeof(WordNode));
    if (w->node[index] == NULL) return;

    w->node[index]->tweet = temp.tweet;
    w->node[index]->id_num[0] = temp.id_num;
    w->node[index]->count = 1;
    w->size++;

    while(h->size > 0)
    {
        temp = delete_min_heap(h);

        //넣으려는 단어가 이미 있음
        if (strcmp(w->node[index]->tweet, temp.tweet) == 0)
        {
            w->node[index]->id_num[w->node[index]->count] = temp.id_num;
            w->node[index]->count++;
        }
        //처음 나온 단어
        else
        {
            w->node[++index] = (WordNode*)malloc(sizeof(WordNode));
            if (w->node[index] == NULL) return;

            w->node[index]->tweet = temp.tweet;
            w->node[index]->id_num[0] = temp.id_num;
            w->node[index]->count = 1;
            w->size++;
        }
    }
}

/*
입력된 단어를 사전 순으로 Heap 정렬
*/
void heap_sort(Heap *h, UserType *u)
{
    TweetType *tweet = (TweetType*)malloc(sizeof(TweetType));

    if (tweet == NULL) return;

    //heap 정렬
    for (int i = 0; i < u->count; i++)
    {
        tweet = u->user[i]->tweets;

        while (tweet != NULL)
        {
            insert_min_heap(h, tweet->tweet, u->user[i]->id_num);   //단어를 min_heap에 삽입

            tweet = tweet->next_tweet;
        }
    }

    free(tweet);
}

/*
min_heap에 단어 사전 순으로 삽입
*/
void insert_min_heap(Heap *h, char *word, int id_num)
{
    int index;

    //맨 마지막 위치에서 시작해서 삽입하려는 단어가 부모 단어보다 사전순으로 먼저 나오면 위로 거슬러 올라감
    for (index = ++(h->size); index != 1 && strcmp(word, h->tweets[index/2].tweet) < 0; index /= 2)
    {
        h->tweets[index] = h->tweets[index / 2];
    }

    //자리잡은 위치에 정보 삽입
    h->tweets[index].tweet = word;
    h->tweets[index].id_num = id_num;
}

/*
min heap의 루트 노드 삭제
*/
HeapNode delete_min_heap(Heap *h)
{
    int p, c;
    HeapNode node, temp;
    node = h->tweets[1];
    temp = h->tweets[(h->size)--];    //맨 마지막 노드
    p = 1;
    c = 2;

    while (c <= h->size)
    {
        //옆 노드와 비교해서 더 작은 걸 선택
        if (c < h->size && strcmp(h->tweets[c].tweet, h->tweets[c+1].tweet) > 0) c++;
        //현재 비교하고 있는 노드보다 맨 마지막 노드가 더 작으면 빠져나감
        if (strcmp(temp.tweet, h->tweets[c].tweet) <= 0) break;


        h->tweets[p] = h->tweets[c];    //삭제된 자리에 작은 자식 노드 삽입
        p = c;
        c *= 2;     //밑 세대로 감
    }

    h->tweets[p] = temp;  //삭제된 자리에 맨 마지막 노드 삽입
    return node;
}

/*
word가 포함된 트윗을 한 유저 찾기
*/
void find_user(Word *w, UserType *u, char find_word[])
{
    int index = find_word_index(w, find_word, 0, w->size - 1);
    if (index == -1)
    {
        printf("Cannot find out the word %s.", find_word);
        return;
    }

    printf("The user who used %s : ", find_word);

    for (int i = 0; i < w->node[index]->count; i++)
    {
        printf("%s, ", u->user[find_user_index(u, w->node[index]->id_num[i], 0, u->count-1)]->name);
    }
    printf("\n");
}

/*
이진 탐색으로 단어 인덱스 검색
*/
int find_word_index(Word *w, char find_word[], int left, int right)
{
    if (left > right) return -1;

    int mid = (left + right) / 2;
    if (strcmp(w->node[mid]->tweet, find_word) == 0) return mid;

    if (strcmp(w->node[mid]->tweet, find_word) < 0) find_word_index(w, find_word, mid + 1, right);
    else find_word_index(w, find_word, left, mid-1);
}

/*
단어가 사용된 횟수
*/
void count_word(Word *w, char word[])
{
    int index = find_word_index(w, word, 0, w->size - 1);
    if (index == -1)
    {
        printf("Cannot find out the word %s.", word);
        return;
    }
    
    printf("The number of %s used : %d\n", word, w->node[index]->count);
}

/*
단어가 사용된 횟수에 따라 오름차순 정렬
*/
Word *num_sort(Word *w)
{
    Word *sorted = (Word*)malloc(sizeof(Word));
    if (sorted == NULL) return;

    memcpy_s(sorted, sizeof(*sorted), w, sizeof(*w));    //메모리 복사

    quick_sort(sorted, 0, sorted->size-1);  //정렬

    return sorted;
}

int partition(Word *w, int left, int right)
{
    WordNode *pivot;
    int low, high, mid;

    high = left;
    low = right + 1;
    mid = (left + right) / 2;
    swap(w, left, mid);
    pivot = w->node[left];
    do
    {
        do
        {
            high++;
        } while (high <= right && w->node[high]->count > pivot->count);
        do
        {
            low--;
        } while (low >= left && w->node[low]->count < pivot->count);
        if (high < low)
        {
            swap(w, high, low);
        }
    } while (high < low);

    swap(w, left, low);
    return low;
}

void quick_sort(Word *w, int left, int right)
{
    if (left < right)
    {
        int q = partition(w, left, right);
        quick_sort(w, left, q - 1);
        quick_sort(w, q + 1, right);
    }
}

void swap(Word *w, int left, int mid)
{
    WordNode *temp = (WordNode*)malloc(sizeof(WordNode));
    temp = w->node[mid];
    w->node[mid] = w->node[left];
    w->node[left] = temp;

    temp = NULL;
    free(temp);
}

