#include <stdio.h>
//#include"file.h"


void bubbleSort(int arr[], int count)
{
	int i = count, j;
	int temp;
	for (i = count;i > 0;i--) 
	{
		for (j = 0; j < i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main(int arc, char* const argv[])
{
	printf("��ʼ����2��5�η����ַ�������");
	fopen("origin_num.txt", "w");
	

	fopen("number.txt", "r");

	atoi()     //���ַ���ת��Ϊ����ֵ
}