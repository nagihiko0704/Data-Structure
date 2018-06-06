#pragma once
#include "user.h"
#define OVERLAP_WORD 120000 //중복 포함 단어 개수
#define MAX_WORD 50000     //중복 제외 단어 개수

typedef struct wordnode  //트윗 단어 모음 구조체
{
    char *tweet;        //트윗 내용
    int id_num[10000];    //트윗한 유저
    int count;          //트윗된 수
}WordNode;

typedef struct word //단어 관리 구조체
{
    WordNode *node[MAX_WORD];    //트윗 내용
    int size;       //단어 수
}Word;

typedef struct heapnode //힙 트리에 넣을 구조체
{
    char *tweet;    //트윗 내용
    int id_num;     //트윗한 유저
}HeapNode;

typedef struct heap //트윗 전체 단어 모음 구조체
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