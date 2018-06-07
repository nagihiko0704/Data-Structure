#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "user.h"

/*
Heap �ʱ�ȭ
*/
void init_Heap(Heap *h)
{
    h->size = 0;
}

/*
Word �ʱ�ȭ
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
���ĵ� Heap���� �ߺ����� �ʰ� �ܾ� ����
*/
void insert_word(Heap *h, UserType *u, Word *w)
{
    heap_sort(h, u);

    int index = 0;

    //�� ó��
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

        //�������� �ܾ �̹� ����
        if (strcmp(w->node[index]->tweet, temp.tweet) == 0)
        {
            w->node[index]->id_num[w->node[index]->count] = temp.id_num;
            w->node[index]->count++;
        }
        //ó�� ���� �ܾ�
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
�Էµ� �ܾ ���� ������ Heap ����
*/
void heap_sort(Heap *h, UserType *u)
{
    TweetType *tweet = (TweetType*)malloc(sizeof(TweetType));

    if (tweet == NULL) return;

    //heap ����
    for (int i = 0; i < u->count; i++)
    {
        tweet = u->user[i]->tweets;

        while (tweet != NULL)
        {
            insert_min_heap(h, tweet->tweet, u->user[i]->id_num);   //�ܾ min_heap�� ����

            tweet = tweet->next_tweet;
        }
    }

    free(tweet);
}

/*
min_heap�� �ܾ� ���� ������ ����
*/
void insert_min_heap(Heap *h, char *word, int id_num)
{
    int index;

    //�� ������ ��ġ���� �����ؼ� �����Ϸ��� �ܾ �θ� �ܾ�� ���������� ���� ������ ���� �Ž��� �ö�
    for (index = ++(h->size); index != 1 && strcmp(word, h->tweets[index/2].tweet) < 0; index /= 2)
    {
        h->tweets[index] = h->tweets[index / 2];
    }

    //�ڸ����� ��ġ�� ���� ����
    h->tweets[index].tweet = word;
    h->tweets[index].id_num = id_num;
}

/*
min heap�� ��Ʈ ��� ����
*/
HeapNode delete_min_heap(Heap *h)
{
    int p, c;
    HeapNode node, temp;
    node = h->tweets[1];
    temp = h->tweets[(h->size)--];    //�� ������ ���
    p = 1;
    c = 2;

    while (c <= h->size)
    {
        //�� ���� ���ؼ� �� ���� �� ����
        if (c < h->size && strcmp(h->tweets[c].tweet, h->tweets[c+1].tweet) > 0) c++;
        //���� ���ϰ� �ִ� ��庸�� �� ������ ��尡 �� ������ ��������
        if (strcmp(temp.tweet, h->tweets[c].tweet) <= 0) break;


        h->tweets[p] = h->tweets[c];    //������ �ڸ��� ���� �ڽ� ��� ����
        p = c;
        c *= 2;     //�� ����� ��
    }

    h->tweets[p] = temp;  //������ �ڸ��� �� ������ ��� ����
    return node;
}

/*
word�� ���Ե� Ʈ���� �� ���� ã��
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
���� Ž������ �ܾ� �ε��� �˻�
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
�ܾ ���� Ƚ��
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
�ܾ ���� Ƚ���� ���� �������� ����
*/
Word *num_sort(Word *w)
{
    Word *sorted = (Word*)malloc(sizeof(Word));
    if (sorted == NULL) return;

    memcpy_s(sorted, sizeof(*sorted), w, sizeof(*w));    //�޸� ����

    quick_sort(sorted, 0, sorted->size-1);  //����

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

