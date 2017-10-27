#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct Str_array{
	char* str;
	int len;
}Str_array; 
struct Str_array str_array[];

void Generate_origin_string(FILE *p, int size) {//and to calculate the length of every line
	int i, length;
	FILE *stream = p;
	int num, j = 0;
	char temp;
	char* A_Z = "abcdefghijklmnopqrstuvwxyz";
	srand((unsigned)time(NULL));
	for (i = 0; i < size;i++) {
		length = rand() % 32 + 1;//length varies from 1 to 32
		for (j = 0;j < length;j++) {
			num = rand() % 26;//0-25
			temp = A_Z[num];//temp is a certain character
			fputc(temp, p);
		}
		fwrite("\n", 1, 1, p);
		fflush(p);
	}
}


void insertionsort(FILE *p,int size) {
	int i, j,tmpnum;
	char* string;
	char* tmpstr;
	FILE *stream = p;
	struct Str_array temp;
	for (i = 0; i < size; i++) {
		fgets(tmpstr, 32, stream);//read a line from the file 
		str_array[i].str = tmpstr;
		str_array[i].len = strlen(tmpstr);
	}

	for (i=1;i<size;i++){//sorted by length
		temp =str_array[i];
		for (j = i; j > 0 && temp.len < str_array[j - 1].len; j--)
			if (temp.len <str_array[j - 1].len)
				str_array[j]= str_array[j - 1];
		
		str_array[j] = temp;
	}
	j = i;// for sorting
	int m;
	for (i = 1;i < size;i++) {//sort the strings with the same length
		while (str_array[j].len == str_array[j - 1].len)
			j++;
		//now j is the next
		for (int k = i + 1;k < j - 1;k++) {
			temp = str_array[k];
			for (m = k;m > 0 && strcmp(temp.str, str_array[m - 1].str) < 0;m--)
				if (strcmp(temp.str, str_array[m - 1].str) < 0)
					str_array[m] = str_array[m - 1];
			str_array[m] = temp;
		}
		i = j;
	}
}

int main()
{
	int size;
	int temp,n;
	while (1) {
		printf("input n:");
		scanf("%i", &n);
		printf("Begin to generate the origin strings in the number of the nth power of 2");
		size = pow(2, n);
		FILE *pFile = fopen("origin_num.txt", "w");
		Generate_origin_string(pFile, size);
		fclose(pFile);
		printf("generated successfully...");
		printf("1.insertion sort");
		printf("2.heapsort");
		printf("3.merge sort");
		printf("4.quick sort");
		scanf("%i", &n);
		switch (n) {
		case 1: {insertionsort(pFile, size);break;}
	//	case 2: {heapsort(pFile, size);break;}
	//	case 3: {mergesort(pFile, size);break;}
	//	case 4: {quicksort(pFile, size);break;}
		default: {printf("Error!");break;}
		}
		printf("sorted successfully...");
		printf("clearing the original strings...");
		//memset(str_array, 0, sizeof(str_array));
	}
}