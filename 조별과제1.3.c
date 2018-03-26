/*
�������� �������� �켱 �����¿�� Ž���Ͽ� 0�� 1�� �ٲ� ��, 
�������� �밢�� �������� Ž���մϴ�.
�� �� �� �밢���� �������� �����¿츦 Ž���Ͽ� 0�� 1�� �ٲߴϴ�.
Ž���� �ϴ� ���� ������ �����մϴ�.
*/
#include <stdio.h>


/*
�»� == 0, ���� == 1, ��� == 2, ���� == 3
�� == 4, ���� == 5, �Ʒ� == 6, ������ == 7
*/
enum {
    LFUP, LFDN, RTUP, RTDN,
    UP, LEFT, DOWN, RIGHT	
};

/*
�迭�� ������ ��� ����ü
*/
struct Arr {
    int num[11][10];//NULL�� ����Ͽ� ����
    int end_row;    //���� ��
    int end_col;    //���� ��
};

/*
�����¿츦 Ž���Ͽ� 1�� ä��
*/
void full_one(struct Arr *arr, int row, int column, int direction) {
    //Ž������ ���̳� ���� ���� ������ ����
    if (row < 0 || arr->end_row <= row || column < 0 || arr->end_col <= column) return;
    //�ش� ĭ�� 0�̸� 1�� ����
    if (arr->num[row][column] == 0) arr->num[row][column] = 1;
    //Ž������ ���̳� �� �� �� �ϳ��� ���� �����ϸ� ����
    if (row == 0 || column == 0 || row == (arr->end_row) - 1 || column == (arr->end_col) - 1) return;

    //���ư��� �������� ��� Ž��
    switch (direction) {
    case UP:
        full_one(arr, row - 1, column, UP);	
        break;
    case LEFT:
        full_one(arr, row, column - 1, LEFT);
        break;
    case DOWN:
        full_one(arr, row+1, column, DOWN);
        break;
    case RIGHT:
        full_one(arr, row, column + 1, RIGHT);
        break;

    //�� ó�� �������� �������� �����¿� Ž��
    case -1:
        full_one(arr, row - 1, column, UP);
        full_one(arr, row, column - 1, LEFT);
        full_one(arr, row + 1, column, DOWN);
        full_one(arr, row, column + 1, RIGHT);
	}
}

/*
�밢������ ������ ����
*/
void find_dir(struct Arr *arr, int row, int column, int direction) {
    //Ž������ ���̳� ���� ���� ������ ����
    if (row < 0 || arr->end_row <= row || column < 0 || arr->end_col <= column) return;
    //�ش� ĭ�� 0�̸� 1�� ����
    if (arr->num[row][column] == 0) arr->num[row][column] = 1;

    //�� �밢���� �´� �����¿� ������ Ž��
    switch (direction) {
	case LFUP:										
        full_one(arr, row - 1, column, UP);
        full_one(arr, row, column - 1, LEFT);
        break;
    case LFDN:
        full_one(arr, row, column - 1, LEFT);
        full_one(arr, row + 1, column, DOWN);
        break;
       case RTUP:
        full_one(arr, row - 1, column, UP);
        full_one(arr, row, column + 1, RIGHT);
        break;
    case RTDN:
        full_one(arr, row + 1, column, DOWN);
        full_one(arr, row, column + 1, RIGHT);
        break;
    }

    //Ž������ ���̳� �� �� �� �ϳ��� ���� �����ϸ� ����
	if (row == 0 || column == 0 || row == arr->end_row - 1 || column == arr->end_col - 1) return;	

    //���ư��� �������� ��� Ž��
    switch (direction) {							
    case LFUP:										
        find_dir(arr, row - 1, column - 1, LFUP);
        break;
    case LFDN:										
        find_dir(arr, row + 1, column - 1, LFDN);
        break;
    case RTUP:										
        find_dir(arr, row - 1, column + 1, RTUP);
        break;
    case RTDN:										
        find_dir(arr, row + 1, column + 1, RTDN);
        break;
    }
}


int main() {
    //�־��� �迭
    int src_arr[10][10] = { { 2,2,2,2,2,2,2,2,2,2 },
                            { 2,2,2,2,2,2,2,2,2,2 },
                            { 2,2,2,0,0,0,0,2,2,2 },
                            { 2,2,2,2,0,0,0,2,2,2 },
                            { 2,2,2,2,0,0,0,2,2,2 },
                            { 2,2,2,2,0,0,0,0,2,2 },
                            { 2,2,2,2,0,2,2,2,2,2 },
                            { 2,2,2,2,0,2,2,2,2,2 },
                            { 2,2,2,2,0,2,2,2,2,2 },
                            { 2,2,2,2,2,2,2,2,2,2 }, };
							

	//����ü �ʱ�ȭ
    //���� ���� ���� ���� ����
	struct Arr *arr = {src_arr};
	int k = 0, p = 0;
    arr->end_row = sizeof(src_arr) / sizeof(src_arr[0]);
	arr->end_col = sizeof(src_arr[0]) / sizeof(src_arr[0][0]);
	

    //Ž���� �����ϴ� ���� ��
    int start_row = 5;
    int start_col = 4;
	//index
    int i = 0;
    int j = 0;
	
    //���� ��ġ�� �������� �����¿츦 Ž���Ͽ� 0 -> 1�� �ٲ�
    full_one(arr, start_row, start_col, -1);		

	//���� ��ġ�� �������� ���� �밢�� �»�, ����, ���, ���ϸ� Ž���Ͽ� 0 -> 1�� �ٲ�
    find_dir(arr, start_row - 1, start_col - 1, LFUP);
    find_dir(arr, start_row + 1, start_col - 1, LFDN);
    find_dir(arr, start_row - 1, start_col + 1, RTUP);
    find_dir(arr, start_row + 1, start_col + 1, RTDN);

	
    //Ȯ�ο� ���
    for (i = 0; i < arr->end_row; i++) {
        for (j = 0; j < arr->end_col; j++) {
            printf("%d ", arr->num[i][j]);
		}
        printf("\n");
    }
	
	return 0;
}
