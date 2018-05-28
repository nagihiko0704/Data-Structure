#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BUCKETS 10
#define DIGITS 3


typedef struct
{
    char name[100];
    int student_number;
    int score;
} Student;

typedef struct
{
    Student node[100];
} StudentNode;

typedef struct
{
    Student node;
    struct Queue *link;
}Queue;

typedef struct
{
    Queue *front, *rear;
}QueueType;

int size;
Student sorted[100];

void init_student(Student s[]);
void init_score(StudentNode *s);
void insert_node(StudentNode *s, Student node[]);
void display(StudentNode *s);
void swap(StudentNode *s, int i, int j);
void selection_sort(StudentNode *s);
void insertion_sort(StudentNode *s);
void bubble_sort(StudentNode *s);
void shell_sort(StudentNode *s);
void dec_insertion_sort(StudentNode *s, int start, int gap);
void merge(StudentNode *s, int left, int mid, int right);
void merge_sort(StudentNode *s, int left, int right);
int partition(StudentNode *s, int left, int right);
void quick_sort(Student s[], int left, int right);
void init_queue(QueueType *q);
int is_empty(QueueType *q);
void enqueue(QueueType *q, Student s);
Student dequeue(QueueType *q);
void radix_sort(StudentNode *s, QueueType q[]);

int main(void)
{
    Student student[100];
    StudentNode *s = (StudentNode*)malloc(sizeof(StudentNode));
    QueueType q[BUCKETS];
    
    int testcount = 1000;
    size = sizeof(student) / sizeof(student[0]);

    //student 구조체 초기화
    init_student(student);
    //StudentNode의 node에 student 정보 저장
    insert_node(s, student);
    //점수 초기화
    init_score(s);

    //확인용 출력
    display(s);

    //큐 초기화
    for (int i = 0; i < BUCKETS; i++)
    {
        init_queue(&q[i]);
    }

    //Selection_sort
    clock_t t_selection;
    t_selection = clock();
    for (int i = 0; i < testcount; i++)
    {
        init_score(s);
        selection_sort(s);
    }
    t_selection = (double)clock() - t_selection;
    display(s);

    //Insertion_sort
    clock_t t_insertion;
    t_insertion = clock();
    for (int i = 0; i < testcount; i++)
    {
        init_score(s);
        insertion_sort(s);
    }
    t_insertion = (double)clock() - t_insertion;
    display(s);

    //Bubble_sort
    clock_t t_bubble;
    t_bubble = clock();
    for (int i = 0; i < testcount; i++)
    {
        init_score(s);
        bubble_sort(s);
    }
    t_bubble = (double)clock() - t_bubble;
    display(s);
    
    //Shell_sort
    clock_t t_shell;
    t_shell = clock();
    for (int i = 0; i < testcount; i++)
    {
        init_score(s);
        shell_sort(s);
    }
    t_shell = (double)clock() - t_shell;
    display(s);
    
    //Merge_sort
    clock_t t_merge;
    t_merge = clock();
    for (int i = 0; i < testcount; i++)
    {
        init_score(s);
        merge_sort(s, 0, size - 1);
    }
    t_merge = (double)clock() - t_merge;
    display(s);

    //Quick_sort
    clock_t t_quick;
    t_quick = clock();
    for (int i = 0; i < testcount; i++)
    {
        init_score(s);
        quick_sort(s, 0, size - 1);
    }
    t_quick = (double)clock() - t_quick;
    display(s);

    //Radix_sort
    clock_t t_radix;
    t_radix = clock();
    for (int i = 0; i < testcount; i++)
    {
        init_score(s);
        radix_sort(s, q);
    }
    t_radix = (double)clock() - t_radix;
    display(s);



    printf("Selection sort \t* %d = %.fms\taverage : %.fms\n", testcount, (double)t_selection, (double)t_selection/testcount);
    printf("Insertion sort \t* %d = %.fms\taverage : %.fms\n", testcount, (double)t_insertion, (double)t_insertion / testcount);
    printf("Bubble sort \t* %d = %.fms\taverage : %.fms\n", testcount, (double)t_bubble, (double)t_bubble / testcount);
    printf("Shell sort \t* %d = %.fms\taverage : %.fms\n", testcount, (double)t_shell, (double)t_shell / testcount);
    printf("Merge sort \t* %d = %.fms\taverage : %.fms\n", testcount, (double)t_merge, (double)t_merge / testcount);
    printf("Quick sort \t* %d = %.fms\taverage : %.fms\n", testcount, (double)t_quick, (double)t_quick / testcount);
    printf("Radix sort \t* %d = %.fms\taverage : %.fms\n", testcount, (double)t_radix, (double)t_radix / testcount);
    return 0;
}

//student 구조체 초기화 함수
void init_student(Student s[])
{
    FILE *fp;

    fopen_s(&fp, "Student_info.txt", "r"); //Student_info.txt 파일 열기

    if (fp == NULL)
    {
        printf("망함\n");
        return;
    } //파일 열기에 실패할경우 망함을 출력하고 리턴
    else
    {
        printf("열림\n");
        for (int i = 0; i < 100 && !feof(fp); i++)
        {
            //학번을 읽어옴
            fscanf_s(fp, "%d \t", &s[i].student_number);

            //공백도 포함해서 이름을 읽어옴
            fscanf_s(fp, "%[^\n]", &s[i].name, _countof(s[i].name));
        }
    }

    fclose(fp);
}

void init_score(StudentNode *s)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
    {
        s->node[i].score = rand() % 100;
    }
}

void insert_node(StudentNode *s, Student node[])
{
    for (int i = 0; i < size; i++)
    {
        s->node[i] = node[i];
    }
}

void display(StudentNode *s)
{
    for (int i = 0; i < 100; i++)
    {
        printf("%d \t %-20s \t %d\n", s->node[i].student_number, s->node[i].name, s->node[i].score);
    }
    printf("---------------------------------\n");
}

void swap(StudentNode *s, int i, int j)
{
    Student temp = s->node[i];
    s->node[i] = s->node[j];
    s->node[j] = temp;
}

void selection_sort(StudentNode *s)
{
    int most = 0;
    for (int i = 0; i < size; i++)
    {
        most = i;
        for (int j = i+1; j < size; j++)
        {
            if (s->node[most].score < s->node[j].score)
            {
                most = j;
            }
        }
        swap(s, i, most);
    }
}

void insertion_sort(StudentNode *s)
{
    Student key;
    int most;
    
    for (int i = 1; i < size; i++)
    {
        key = s->node[i];
        for (most = i - 1; most >= 0 && key.score > s->node[most].score; most--)
        {
            s->node[most + 1] = s->node[most];
        }
        s->node[most + 1] = key;
    }
}

void bubble_sort(StudentNode *s)
{
    for (int i = size-1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (s->node[j].score < s->node[j+1].score)
            {
                swap(s, j, j+1);
            }
        }
    }
}

void shell_sort(StudentNode *s)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        if (gap % 2 == 0) gap++;
        for (int i = 0; i < gap; i++)
        {
            dec_insertion_sort(s, i, gap);
        }
    }
}

void dec_insertion_sort(StudentNode *s, int start, int gap)
{
    Student key;
    int most;

    for (int i = start + gap; i < size; i += gap)
    {
        key = s->node[i];
        for (most = i - gap; most >= 0 && key.score > s->node[most].score; most -= gap)
        {
            s->node[most + gap] = s->node[most];
        }
        s->node[most + gap] = key;
    }
}

void merge(StudentNode *s, int left, int mid, int right)
{
    int i, j, k;
    i = left;
    j = mid + 1;
    k = left;

    while (i <= mid && j <= right)
    {
        if (s->node[i].score >= s->node[j].score) sorted[k++] = s->node[i++];
        else sorted[k++] = s->node[j++];
    }

    if (i <= mid)
    {
        for (int l = i; l <= mid; l++)
        {
            sorted[k++] = s->node[l];
        }
    }
    else
    {
        for (int l = j; l <= right; l++)
        {
            sorted[k++] = s->node[l];
        }
    }

    for (int l = left; l <= right; l++)
    {
        s->node[l] = sorted[l];
    }
}

void merge_sort(StudentNode *s, int left, int right)
{
    int mid;
    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort(s, left, mid);
        merge_sort(s, mid + 1, right);
        merge(s, left, mid, right);
    }
}

int partition(StudentNode *s, int left, int right)
{
    Student pivot;
    int low, high, mid;

    high = left;
    low = right+1;
    mid = (left + right) / 2;
    swap(s, left, mid);
    pivot = s->node[left];
    do
    {
        do
        {
            high++;
        } while (high <= right && s->node[high].score > pivot.score);
        do
        {
            low--;
        } while (low >= left && s->node[low].score < pivot.score);
        if (high < low)
        {
            swap(s, high, low);
        }
    } while (high < low);

    swap(s, left, low);
    return low;
}

void quick_sort(Student s[], int left, int right)
{
    if (left < right)
    {
        int q = partition(s, left, right);
        quick_sort(s, left, q-1);
        quick_sort(s, q + 1, right);
    }
}

void init_queue(QueueType *q)
{
    q->front = NULL;
    q->rear = NULL;
}

int is_empty(QueueType *q)
{
    return q->front == NULL;
}

void enqueue(QueueType *q, Student s)
{
    Queue *node = (Queue*)malloc(sizeof(Queue));
    
    if (node == NULL) return;

    node->node = s;
    node->link = NULL;
    
    if (is_empty(q))
    {
        q->front = node;
        q->rear = node;
    }
    else
    {
        q->rear->link = node;
        q->rear = node;
    }
}

Student dequeue(QueueType *q)
{
    if (is_empty(q)) return;

    Queue *temp = q->front;
    Student node = temp->node;

    q->front = q->front->link;
    if (q->front == NULL) q->rear = NULL;
    
    free(temp);
    return node;
}

void radix_sort(StudentNode *s, QueueType q[])
{
    int factor = 1;

    for (int d = 0; d < DIGITS; d++)
    {
        for (int i = 0; i < size; i++)
        {
            enqueue(&q[(s->node[i].score / factor) % 10], s->node[i]);
        }
        for (int i = BUCKETS - 1, j = 0; i >= 0; i--)
        {
            while (!is_empty(&q[i]))
            {
                s->node[j++] = dequeue(&q[i]);
            }
        }
        factor *= 10;
    }
}