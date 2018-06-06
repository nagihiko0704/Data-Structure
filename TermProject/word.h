#pragma once
#include "user.h"
#define OVERLAP_WORD 120000 //�ߺ� ���� �ܾ� ����
#define MAX_WORD 50000     //�ߺ� ���� �ܾ� ����

typedef struct wordnode  //Ʈ�� �ܾ� ���� ����ü
{
    char *tweet;        //Ʈ�� ����
    int id_num[10000];    //Ʈ���� ����
    int count;          //Ʈ���� ��
}WordNode;

typedef struct word //�ܾ� ���� ����ü
{
    WordNode *node[MAX_WORD];    //Ʈ�� ����
    int size;       //�ܾ� ��
}Word;

typedef struct heapnode //�� Ʈ���� ���� ����ü
{
    char *tweet;    //Ʈ�� ����
    int id_num;     //Ʈ���� ����
}HeapNode;

typedef struct heap //Ʈ�� ��ü �ܾ� ���� ����ü
{
    HeapNode tweets[OVERLAP_WORD];
    int size;
}Heap;

void init_Heap(Heap *h);
void init_Word(Word *w);
void insert_word(Heap *h, UserType *u, Word *w);
void heap_sort(Heap *h, UserType *u);
void insert_min_heap(Heap *h, char *word, int id_num);
HeapNode delete_min_heap(Heap *h);
void find_user(Word *w, UserType *u, char find_word[]);
int find_word_index(Word *w, char find_word[], int left, int right);
void count_word(Word *w, char word[]);