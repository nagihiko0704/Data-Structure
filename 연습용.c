#include <stdio.h>

void reverse(char *s)  //�������� ����ϴ� ���ȣ���Լ�
{
	if (*s == 0)  //���ڿ� �� 0�� ������ ���� ����
		return;
	else  
	{
		reverse(s + 1);  //�����͸� 1���ؼ� �ٽ� ���ȣ��
		printf("%c", *s);  //���� ��ġ�� ���ڸ� ���
	}
}

int main(void)
{
	char s[100];

	printf("�Է� : ");
	scanf("%s", s); //���ڿ� �Է�

	reverse(s);  //���� ��� ����Լ� ȣ��
	printf("\n");
	return 0;
}