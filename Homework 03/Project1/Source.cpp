#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1000
void GetNum(char* temp)
{
	printf("Infix : ");
	scanf("%s", temp);
}

int main()
{
	char* Infix = (char*)malloc(MAX_SIZE * sizeof(char));
	char* PostFix = (char*)malloc(MAX_SIZE * sizeof(char));
	GetNum(Infix);


}