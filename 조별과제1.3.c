#include <stdio.h>

enum {
	LFUP, LFDN, RTUP, RTDN, //�»� == 0, ���� == 1, ��� == 2, ���� == 3
	UP, LEFT, DOWN, RIGHT	//�� == 4, ���� == 5, �Ʒ� == 6, ������ == 7
};

/*
�迭�� ������ ��� ����ü
*/
struct Arr {
	int num[11][10];//NULL�� ����Ͽ� ����
	int end_row;	//���� ��
	int end_col;	//���� ��
};

/*
�����¿츦 Ž���Ͽ� 1�� ä��
*/
void full_one(struct Arr *arr, int row, int column, int direction) {
	if (row < 0 || arr->end_row <= row || column < 0 || arr->end_col <= column) return;				//Ž������ ���̳� ���� ���� ������ ����
	if (arr->num[row][column] == 0) arr->num[row][column] = 1;		//�ش� ĭ�� 0�̸� 1�� ����
	if (row == 0 || column == 0 || row == (arr->end_row) - 1 || column == (arr->end_col) - 1) return;//Ž������ ���̳� �� �� �� �ϳ��� ���� �����ϸ� ����

	switch (direction) {						//���ư��� �������� ��� Ž��
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

	case -1:									//�� ó�� �������� �������� �����¿� Ž��
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
	if (row < 0 || arr->end_row <= row || column < 0 || arr->end_col <= column) return;				//Ž������ ���̳� ���� ���� ������ ����
	if (arr->num[row][column] == 0) arr->num[row][column] = 1;		//�ش� ĭ�� 0�̸� 1�� ����

	switch (direction) {
	case LFUP:										//�»��̸� ���ʰ� ������ ä��
		full_one(arr, row - 1, column, UP);
		full_one(arr, row, column - 1, LEFT);
		break;
	case LFDN:										//���ϸ� ���ʰ� �Ʒ����� ä��
		full_one(arr, row, column - 1, LEFT);
		full_one(arr, row + 1, column, DOWN);
		break;
	case RTUP:										//����̸� �����ʰ� ������ ä��
		full_one(arr, row - 1, column, UP);
		full_one(arr, row, column + 1, RIGHT);
		break;
	case RTDN:										//���ϸ� �����ʰ� �Ʒ����� ä��
		full_one(arr, row + 1, column, DOWN);
		full_one(arr, row, column + 1, RIGHT);
		break;
	}

	if (row == 0 || column == 0 || row == arr->end_row - 1 || column == arr->end_col - 1) return;	//Ž������ ���̳� �� �� �� �ϳ��� ���� �����ϸ� ����

	switch (direction) {							//���ư��� �������� ��� Ž��
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
	int src_arr[10][10] = { { 2,2,2,2,2,2,2,2,2,2 },
							{ 2,2,2,2,2,2,2,2,2,2 },
							{ 2,2,2,0,0,0,0,2,2,2 },
							{ 2,2,2,2,0,0,0,2,2,2 },
							{ 2,2,2,2,0,0,0,2,2,2 },
							{ 2,2,2,2,0,0,0,0,2,2 },
							{ 2,2,2,2,0,2,2,2,2,2 },
							{ 2,2,2,2,0,2,2,2,2,2 },
							{ 2,2,2,2,0,2,2,2,2,2 },
							{ 2,2,2,2,2,2,2,2,2,2 } };	//�־��� �迭
							

	//����ü �ʱ�ȭ
	struct Arr *arr = {src_arr};
	int k = 0, p = 0;
	arr->end_row = sizeof(src_arr) / sizeof(src_arr[0]);		//���� ��
	arr->end_col = sizeof(src_arr[0]) / sizeof(src_arr[0][0]);	//���� ��
	


	int start_row = 5;			//Ž���� �����ϴ� ��
	int start_col = 4;			//Ž���� �����ϴ� ��
	
	int i = 0;					//index
	int j = 0;
	
	full_one(arr, start_row, start_col, -1);		//���� ��ġ�� �������� �����¿츦 Ž���Ͽ� 0 -> 1�� �ٲ�

	//���� ��ġ�� �������� ���� �밢�� �»�, ����, ���, ���ϸ� Ž���Ͽ� 0 -> 1�� �ٲ�
	find_dir(arr, start_row - 1, start_col - 1, LFUP);
	find_dir(arr, start_row + 1, start_col - 1, LFDN);
	find_dir(arr, start_row - 1, start_col + 1, RTUP);
	find_dir(arr, start_row + 1, start_col + 1, RTDN);

	
	for (i = 0; i < arr->end_row; i++) {			//Ȯ�ο� ���
		for (j = 0; j < arr->end_col; j++) {
			printf("%d ", arr->num[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
