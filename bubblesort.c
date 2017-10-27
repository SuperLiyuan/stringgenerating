#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<sys/timeb.h>
#if defined(WIN32)
# define TIMEB _timeb
# define ftime _ftime
typedef __int64 TIME_T;
#else
#define TIMEB timeb
typedef long long TIME_T;
#endif

struct TIMEB ts1, ts2;
TIME_T t1, t2;
int ti;

#define RADIX_10 10    //整形排序  
#define KEYNUM_31 10     //关键字个数，这里为整形位数  

int c[65536];

int m;

int STN[200000] = { 0 };
int sorted[200000] = { 0 };


/*void Generate_origin_num(FILE *p, int size) {//and to calculate the length of every line
int i, length;
char* str = { '\0' };
int num, j = 0;
char temp;
srand((unsigned)time_t(NULL));
for (i = 0; i < pow(2,17);i++) {

num = rand() % 65535 + 1;
str = (char*)malloc(6 * sizeof(char));
itoa(num, str, 10);
fputs(str, p);
fwrite("\n", 1, 1, p);
fflush(p);
}
}*/


void Read_from_file(FILE *p, int size) {
	char* tmpstr = (char*)malloc(32 * sizeof(char));
	FILE *stream = p;

	char* test, test2;
	int num;
	int i;
	for (i = 0; i < size; i++) {
		test = fgets(tmpstr, 33, stream);
		tmpstr[strlen(tmpstr) - 1] = '\0';//not "\n" //grammar error.why???because i used "".
										  //test = fgets(tmpstr, 33, p);
		STN[i] = atoi(tmpstr);
		memset(tmpstr, 0, sizeof(tmpstr));

	}

}
int split(int low, int high)
{
	int part_element = STN[low];

	for (;;) {
		while (low < high && part_element <= STN[high]) {
			high--;
		}
		if (low >= high) break;
		STN[low++] = STN[high];

		while (low < high && STN[low] <= part_element) {
			low++;
		}
		if (low >= high) break;
		STN[high--] = STN[low];
	}

	STN[high] = part_element;
	return high;
}

void quicksort(int low, int high)
{
	int middle;
	if (low >= high) return;
	middle = split(low, high);
	quicksort(low, (middle - 1));
	quicksort((middle + 1), high);
}

int bubblesort(int arraySize)
{
	int i, m, temp;

	for (i = 1;i < arraySize;i++)
	{
		for (m = 0;m < (arraySize - i);m++)
		{
			if (STN[m] > STN[m + 1])
			{
				temp = STN[m];
				STN[m] = STN[m + 1];
				STN[m + 1] = temp;
			}
		}
	}
	return 1;
}



int output_file(int size, int n) {
	//char* name;
	char strnum[10];
	int i;
	char* str = (char*)malloc(32 * sizeof(char));
	FILE *pFile;
	char* p;
	switch (n) {
	case 1: {

		//char* name2 = (char*)malloc(250 * sizeof(char));
		itoa(m, strnum, 10);
		char name1[] = "D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\output\\bubblesort\\result_";
		//p=(char*)realloc(name1,150 * sizeof(char));
		char name2[200];
		strcpy(name2, name1);
		strcat(name2, strnum);
		strcat(name2, ".txt");
		pFile = fopen(name2, "w+");break;}
	case 2: {

		//char* name2 = (char*)malloc(250 * sizeof(char));
		itoa(m, strnum, 10);
		char name1[] = "D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\output\\quicksort\\result_";
		//p=(char*)realloc(name1,150 * sizeof(char));
		char name2[200];
		strcpy(name2, name1);
		strcat(name2, strnum);
		strcat(name2, ".txt");
		pFile = fopen(name2, "w+");break;}
	case 3: {

		//char* name2 = (char*)malloc(250 * sizeof(char));
		itoa(m, strnum, 10);
		char name1[] = "D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\output\\radixsort\\result_";
		//p=(char*)realloc(name1,150 * sizeof(char));
		char name2[200];
		strcpy(name2, name1);
		strcat(name2, strnum);
		strcat(name2, ".txt");
		pFile = fopen(name2, "w+");break;}

	case 4: {
		//char* name2 = (char*)malloc(250 * sizeof(char));
		itoa(m, strnum, 10);
		char name1[] = "D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\output\\countsort\\result_";
		//p=(char*)realloc(name1,150 * sizeof(char));
		char name2[200];
		strcpy(name2, name1);
		strcat(name2, strnum);
		strcat(name2, ".txt");
		pFile = fopen(name2, "w+");break;}
	}
	for (i = 0;i < size;i++) {
		itoa(STN[i], str, 10);
		fputs(str, pFile);
		fputs("\n", pFile);
		fflush(pFile);
	}
	fclose(pFile);
	if (i == size)
		return 0;
}




// 找到num的从低到高的第pos位的数据  
int GetNumInPos(int num, int pos)
{
	int temp = 1;
	for (int i = 0; i < pos - 1; i++)
		temp *= 10;

	return (num / temp) % 10;
}


//基数排序  pDataArray 无序数组；iDataNum为无序数据个数  
void radixsort(/*int* pDataArray, */int iDataNum)
{
	int *radixArrays[RADIX_10];    //分别为0~9的序列空间  
	for (int i = 0; i < 10; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * (iDataNum + 1));
		radixArrays[i][0] = 0;    //index为0处记录这组数据的个数  
	}

	for (int pos = 1; pos <= KEYNUM_31; pos++)    //从个位开始到31位  
	{
		for (int i = 0; i < iDataNum; i++)    //分配过程  
		{
			int num = GetNumInPos(STN[i], pos);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = STN[i];
		}

		for (int i = 0, j = 0; i < RADIX_10; i++)    //收集  
		{
			for (int k = 1; k <= radixArrays[i][0]; k++)
				STN[j++] = radixArrays[i][k];
			radixArrays[i][0] = 0;    //复位  
		}
	}
}



//获得未排序数组中最大的一个元素值  
int GetMaxVal(int* arr, int len)
{

	int maxVal = arr[0];

	for (int i = 1; i < len; i++)
	{
		if (arr[i] > maxVal)
			maxVal = arr[i];
	}

	return maxVal;
}

//计数排序  
// input为输入数组（未排序），output为输出数组（排序后，目前为空），len表示数组长度,k表示有所输入数字都介于0到k之间  
void countsort(int len)
{
	// 初始化  
	for (int i = 0; i <= 65536; i++)
	{
		c[i] = 0;
	}
	// 检查每个输入元素，如果一个输入元素的值为input[i],那么c[input[i]]的值加1，  
	// 此操作完成后，c[i]中存放了值为i的元素的个数  
	for (int i = 0; i < len; i++)
	{
		c[STN[i]]++;
	}
	// 通过在c中记录计数和，c[i]中存放的是小于等于i元素的数字个数  
	for (int i = 1; i <= 65536; i++)
	{
		c[i] = c[i] + c[i - 1];
	}
	// 把输入数组中的元素放在输出数组中对应的位置上  
	for (int i = len - 1; i >= 0; i--)
	{
		// 从后往前遍历
		sorted[c[STN[i]] - 1] = STN[i];
		c[STN[i]]--;// 该操作使得下一个值为input[i]的元素直接进入输出数组中input[i]的前一个位置  
	}
	for (int i = 0;i < len;i++)
		STN[i] = sorted[i];
}

int main()
{
	int size;
	char* strt = (char*)malloc(sizeof(t1));
	char strm[2];
	int temp, n;
	while (1) {
		printf("input m:\n");
		scanf("%i", &m);
		printf("Begin to prepare the origin numbers in the number of the nth power of 2\n");
		size = pow(2, m);
		int time;
		//FILE *pFile = fopen("D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\input\\input_strings.txt", "w+");
		//Generate_origin_num(pFile, size);
		//fclose(pFile);
		printf("generated successfully...\n");
		printf("1.bubble sort\n");
		printf("2.quick sort\n");
		printf("3.radix sort\n");
		printf("4.count sort\n");
		scanf("%i", &n);
		FILE *p2 = fopen("D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\input\\input_strings.txt", "r+");
		Read_from_file(p2, size);
		printf("start counting...\n");
		ftime(&ts1);
		switch (n) {
		case 1: { bubblesort(size);break;}
		case 2: {quicksort(/*pFile,*/ 0, size);break;}//把相同长度的分成小堆再排序咯
		case 3: {radixsort(size);break;}
		case 4: {countsort(size);break;}
		default: {printf("Error!\n");exit(0);}
		}
		ftime(&ts2);
		t1 = (TIME_T)ts1.time * 1000 + ts1.millitm;
		t2 = (TIME_T)ts2.time * 1000 + ts2.millitm;
		ti = t2 - t1;

		printf("sorted successfully...stop counting.generating outputs...\n");
		if (output_file(size, n) == 0)
			printf("output finished.Recording time...\n");

		switch (n) {
		case 1: {
			FILE *p = fopen("D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\output\\bubblesort\\time.txt", "a+ ");
			fputs("bubblesort-size=", p);
			int tst = fwrite(itoa(m, strm, 10), 1, 2, p);fflush(p);
			int tst2 = fputc(':', p);fflush(p);
			fputs(itoa(ti, strt, 10), p);fflush(p);
			fputc('\n', p);fflush(p);
			fclose(p);break;}
		case 2: {
			FILE *p = fopen("D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\output\\quicksort\\time.txt", "a+ ");
			fputs("quicksort-size=", p);
			fwrite(itoa(m, strm, 10), 1, 2, p);fflush(p);
			fputc(':', p);fflush(p);
			fputs(itoa(ti, strt, 10), p);fflush(p);
			fputc('\n', p);fflush(p);
			fclose(p);break;}

		case 3: {
			FILE *p = fopen("D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\output\\radixsort\\time.txt", "a+ ");
			fputs("radixsort-size=", p);
			fwrite(itoa(m, strm, 10), 1, 2, p);fflush(p);
			fputc(':', p);fflush(p);
			fputs(itoa(ti, strt, 10), p);fflush(p);
			fputc('\n', p);fflush(p);
			fclose(p);break;}

		case 4: {
			FILE *p = fopen("D:\\Major\\MajorCourses\\ITA\\PB15151774-project1\\ex1\\output\\countsort\\time.txt", "a+ ");
			fputs("countsort-size=", p);
			fwrite(itoa(m, strm, 10), 1, 2, p);fflush(p);
			fputc(':', p);fflush(p);
			fputs(itoa(ti, strt, 10), p);fflush(p);
			fputc('\n', p);fflush(p);
			fclose(p);break;}

		}
		printf("clearing the original strings...\n");
		//memset(str_array, 0, sizeof(str_array));
	}
}