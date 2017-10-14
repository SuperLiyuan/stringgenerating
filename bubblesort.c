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
	printf("开始生成2的5次方的字符串数据");
	fopen("origin_num.txt", "w");
	

	fopen("number.txt", "r");

	atoi()     //将字符串转换为整型值
}