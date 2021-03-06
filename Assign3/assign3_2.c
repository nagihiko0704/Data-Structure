#include <stdio.h>
#include <stdlib.h>

/*
학생의 정보를 담는 구조체
*/
typedef struct {
    char name[100];
    int student_number;
    int score;
}Student;

/*
Student 구조체의 배열을 관리하는 구조체
*/
typedef struct {
    Student node[100];
}StudentNode;

/*
이진 탐색 트리
*/
typedef struct{
    Student key;
    struct TreeNode *left, *right;
}TreeNode;

void init_student(Student s[]);
void display(StudentNode *s);
void connect_node(StudentNode *s, Student node[]);
void init_tree(TreeNode **t);
void mix_node(StudentNode *s);
void insert_node(TreeNode **root, StudentNode *s);
void preorder(TreeNode *root);
Student search_node(TreeNode *root, int score);
void delete_node(TreeNode **root, int score);

int size;

int main(void)
{
    Student student[100];
    StudentNode *s = (StudentNode*)malloc(sizeof(StudentNode));
    TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    size = sizeof(student) / sizeof(student[0]);

    init_student(student);      //Student 배열에 정보 저장
    connect_node(s, student);   //StudentNode에 Student 연결
    init_tree(&root);       //트리 초기화
    mix_node(s);            //StudentNode를 섞음
    display(s);             //StudentNode에 담긴 노드 출력

    insert_node(&root, s);  //트리에 StudentNode의 노드를 삽입
    preorder(root);     //트리에 담긴 노드 전위순회로 출력

    //이진탐색
    search_node(root, 96);
    search_node(root, 98);
    search_node(root, 95);
    search_node(root, 100);


    /*
              ┌-----97-----98
    99-----96 ┤
              └-----93-----94-----95
    */
    delete_node(&root, 98); //단말 노드 삭제 - Case 1
    preorder(root);
    printf("------------------------------------------------------------\n");
    delete_node(&root, 94); //1개의 자식 노드가 있는 노드 삭제 - Case 2
    preorder(root);
    printf("------------------------------------------------------------\n");
    delete_node(&root, 96); //2개의 자식 노드가 있는 노드 삭제 - Case 3
    preorder(root);
    printf("------------------------------------------------------------\n");
    delete_node(&root, 100);    //삭제하려는 노드가 없음
    preorder(root);
    
    return 0;
}

/*
파일로부터 정보를 불러와 Student 구조체에 저장
*/
void init_student(Student s[])
{
    FILE *fp;
    fopen_s(&fp, "Student_info.txt", "r");
    
    //파일 열기 실패
    if (fp == NULL) {
        printf("failed to open file.\n");
        return;
    }
    printf("Success to open file!\n");

    //학생들의 정보를 불러옴
    for (int i = 0; i < 100 && !feof(fp); i++)
    {
        //학번을 불러옴
        fscanf_s(fp, "%d\t", &s[i].student_number);
        //공백을 포함한 이름을 불러옴
        fscanf_s(fp, "%[^\n]", &s[i].name, _countof(s[i].name));
        //점수는 순서대로 0~99점 부여
        s[i].score = i;
    }
}

/*
StudentNode에 담긴 학생 정보 출력
*/
void display(StudentNode *s)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\t %-20s\t %d\n", s->node[i].student_number, s->node[i].name, s->node[i].score);
    }
    printf("-------------------------------------------------\n");
}

/*
StudentNode에 Student 정보 저장
*/
void connect_node(StudentNode *s, Student node[])
{
    for (int i = 0; i < size; i++)
    {
        s->node[i] = node[i];
    }
}

/*
트리 초기화
*/
void init_tree(TreeNode **t)
{
    *t = NULL;
}

/*
Student 노드들을 섞음
*/
void mix_node(StudentNode *s)
{
    Student temp;
    int count = 1000;
    
    for (int i = 0; i < count; i++)
    {
        int val = rand() % 100;
        temp = s->node[0];
        s->node[0] = s->node[val];
        s->node[val] = temp;
    }
}

/*
트리에 점수 별로 노드 Student 노드 삽입
*/
void insert_node(TreeNode **root, StudentNode *s) {
    TreeNode *p, *t;
    TreeNode *n;

    for (int i = 0; i < size; i++)
    {
        t = *root;
        p = NULL;

        while (t != NULL)
        {
            if (s->node[i].score == t->key.score) return;

            p = t;
            if (s->node[i].score < t->key.score) t = t->left;
            else t = t->right;
        }

        n = (TreeNode*)malloc(sizeof(TreeNode));
        if (n == NULL) return;

        n->key = s->node[i];
        n->left = n->right = NULL;

        //삽입하려는 위치가 루트 노드
        if (p == NULL) (*root) = n;

        else
        {
            if (s->node[i].score < p->key.score) p->left = n;
            else p->right = n;
        }
    }
}

/*
트리를 전위 순회로 출력
*/
void preorder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d\t %-20s\t %d\n", root->key.student_number, root->key.name, root->key.score);
        preorder(root->left);
        preorder(root->right);
    }
}

/*
트리에서 노드를 탐색
탐색하면서 지나간 노드를 출력
*/
Student search_node(TreeNode *root, int score)
{
    while (root != NULL)
    {
        printf("%d - ", root->key.score);
        if (root->key.score == score)
        {
            printf("\n");
            return root->key;
        }
        if (score < root->key.score) root = root->left;
        else root = root->right;
    }
    
    printf("- - - - - - - - - - - - \n점수를 찾지 못했습니다.\n");
    return;
}

/*
트리에서 노드를 삭제
*/
void delete_node(TreeNode **root, int score)
{
    TreeNode *p, *c, *succ, *succ_p, *t;

    p = NULL;
    t = *root;

    //삭제하려는 노드 탐색
    while (t != NULL && t->key.score != score)
    {
        p = t;
        if (score < t->key.score) t = t->left;
        else t = t->right;
    }

    if (t == NULL)
    {
        printf("삭제하려는 key가 트리에 없습니다.\n");
        return;
    }

    //삭제하려는 노드가 단말 노드
    if (t->left == NULL && t->right == NULL)
    {
        printf("삭제하려는 노드는 자식이 없습니다.\n");
        //삭제하려는 노드가 루트 노드
        if (p == NULL) *root = NULL;
        else
        {
            if (p->left == t) p->left = NULL;
            else p->right = NULL;
        }
    }

    //삭제하려는 노드가 한 개의 자식을 가짐
    else if (t->left == NULL || t->right == NULL)
    {
        printf("삭제하려는 노드는 자식이 하나 있습니다.\n");
        c = (t->left != NULL) ? t->left : t->right;
        //삭제하려는 노드가 루트 노드
        if (p == NULL) *root = c;
        else
        {
            if (p->left == t) p->left = c;
            else p->right = c;
        }
    }

    //삭제하려는 노드가 두 개의 자식을 가짐
    else
    {
        printf("삭제하려는 노드는 자식이 둘 있습니다.\n");
        //삭제하려는 노드와 가장 가까운 key를 가진 노드 -> 후속자
        //후속자의 부모
        succ_p = t;
        //후속자
        succ = t->right;

        //후속자를 탐색
        while (succ->left != NULL)
        {
            succ_p = succ;
            succ = succ->left;
        }

        //후속자의 자리를 메움
        if (succ_p->left == succ) succ_p->left = succ->right;
        else succ_p->right = succ->right;

        //삭제하려는 노드 자리에 후속자를 저장
        t->key = succ->key;
        //원래 있던 후속자 삭제
        t = succ;
    }
    free(t);
}