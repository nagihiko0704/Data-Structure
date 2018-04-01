#include <stdio.h>

void reverse(char *s)  //역순으로 출력하는 재귀호출함수
{
	if (*s == 0)  //문자열 끝 0을 만나면 빠져 나감
		return;
	else  
	{
		reverse(s + 1);  //포인터를 1더해서 다시 재귀호출
		printf("%c", *s);  //현재 위치의 문자를 출력
	}
}

int main(void)
{
	char s[100];

	printf("입력 : ");
	scanf("%s", s); //문자열 입력

	reverse(s);  //역순 출력 재귀함수 호출
	printf("\n");
	return 0;
}