/*
시작점을 기준으로 우선 상하좌우로 탐색하여 0을 1로 바꾼 뒤, 
시작점의 대각선 방향으로 탐색합니다.
그 후 각 대각선을 기준으로 상하좌우를 탐색하여 0을 1로 바꿉니다.
탐색을 하다 끝을 만나면 종료합니다.
*/
#include <stdio.h>


/*
좌상 == 0, 좌하 == 1, 우상 == 2, 우하 == 3
위 == 4, 왼쪽 == 5, 아래 == 6, 오른쪽 == 7
*/
enum {
    LFUP, LFDN, RTUP, RTDN,
    UP, LEFT, DOWN, RIGHT	
};

/*
배열의 정보가 담긴 구조체
*/
struct Arr {
    int num[11][10];//NULL을 고려하여 선언
    int end_row;    //행의 끝
    int end_col;    //열의 끝
};

/*
상하좌우를 탐색하여 1을 채움
*/
void full_one(struct Arr *arr, int row, int column, int direction) {
    //탐색중인 행이나 열이 끝을 넘으면 정지
    if (row < 0 || arr->end_row <= row || column < 0 || arr->end_col <= column) return;
    //해당 칸이 0이면 1을 대입
    if (arr->num[row][column] == 0) arr->num[row][column] = 1;
    //탐색중인 행이나 열 둘 중 하나가 끝에 도달하면 정지
    if (row == 0 || column == 0 || row == (arr->end_row) - 1 || column == (arr->end_col) - 1) return;

    //나아가는 방향으로 계속 탐색
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

    //맨 처음 시작점을 기준으로 상하좌우 탐색
    case -1:
        full_one(arr, row - 1, column, UP);
        full_one(arr, row, column - 1, LEFT);
        full_one(arr, row + 1, column, DOWN);
        full_one(arr, row, column + 1, RIGHT);
	}
}

/*
대각선으로 방향을 지정
*/
void find_dir(struct Arr *arr, int row, int column, int direction) {
    //탐색중인 행이나 열이 끝을 넘으면 정지
    if (row < 0 || arr->end_row <= row || column < 0 || arr->end_col <= column) return;
    //해당 칸이 0이면 1을 대입
    if (arr->num[row][column] == 0) arr->num[row][column] = 1;

    //각 대각선에 맞는 상하좌우 방향을 탐색
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

    //탐색중인 행이나 열 둘 중 하나가 끝에 도달하면 정지
	if (row == 0 || column == 0 || row == arr->end_row - 1 || column == arr->end_col - 1) return;	

    //나아가는 방향으로 계속 탐색
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
    //주어진 배열
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
							

	//구조체 초기화
    //행의 끝과 열의 끝을 지정
	struct Arr *arr = {src_arr};
	int k = 0, p = 0;
    arr->end_row = sizeof(src_arr) / sizeof(src_arr[0]);
	arr->end_col = sizeof(src_arr[0]) / sizeof(src_arr[0][0]);
	

    //탐색을 시작하는 열과 행
    int start_row = 5;
    int start_col = 4;
	//index
    int i = 0;
    int j = 0;
	
    //시작 위치를 기준으로 상하좌우를 탐색하여 0 -> 1로 바꿈
    full_one(arr, start_row, start_col, -1);		

	//시작 위치를 기준으로 각각 대각선 좌상, 좌하, 우상, 우하를 탐색하여 0 -> 1로 바꿈
    find_dir(arr, start_row - 1, start_col - 1, LFUP);
    find_dir(arr, start_row + 1, start_col - 1, LFDN);
    find_dir(arr, start_row - 1, start_col + 1, RTUP);
    find_dir(arr, start_row + 1, start_col + 1, RTDN);

	
    //확인용 출력
    for (i = 0; i < arr->end_row; i++) {
        for (j = 0; j < arr->end_col; j++) {
            printf("%d ", arr->num[i][j]);
		}
        printf("\n");
    }
	
	return 0;
}
