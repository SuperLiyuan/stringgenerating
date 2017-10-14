#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include<string.h>

main()
{
	int i, length;
	int num, j = 0;
	//char string[] = { "\0" };
	char temp;
	char* A_Z = "abcdefghijklmnopqrstuvwxyz";
	srand((unsigned)time(NULL));
	FILE *pFile = fopen("string.txt", "w");

	//memset(string, 0, sizeof(string));
	for (i = 0; i <131072;i++) {

		length = rand() % 32 + 1;//length varies from 1 to 32
		//length = 32;//debug
		for (j = 0;j < length;j++) {
			num = rand() % 26;//0-25
			temp = A_Z[num];//temp is a certain character
							//string[j] = temp;
							//						fwrite(string[j], 1, 1, pFile);
			fputc(temp, pFile);
		}
		//string[j] = "\0";//no "面面面面"
		//fwrite(string[j],1,strlen(string), pFile);
		fwrite("\n", 1, 1, pFile);
		//memset(string,0,sizeof(string));//void *memset(void *s, int c, size_t n)
		//fclose(pFile); 
		fflush(pFile); 
	}

	system("pause");
}