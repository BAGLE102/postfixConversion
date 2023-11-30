#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<math.h>
#define AryLength 100
#define MAXSTACK 100
#define top 0
struct Node
{
	char* Data = (char*)malloc(AryLength * sizeof(char));
	Node* next;
};
bool isEmpty(char Stack[])
{
	return !Stack[top];
}
void push(char Stack[],char Data)
{
	if (Stack[top] == MAXSTACK)
	{
		puts("Stack is Full");
		exit(0);
	}
	Stack[top] += 1;
	Stack[(int)Stack[top]] = Data;
}
void push(double Stack[], double Data)
{
	if (Stack[top] == MAXSTACK)
	{
		puts("Stack is Full");
		exit(0);
	}
	Stack[top] += 1;
	Stack[(int)Stack[top]] = Data;
}
char pop(char Stack[])
{
	if (Stack[top]==0)
	{
		//puts("Stack is Empty");
		exit(0);
	}
	else
	{
		return Stack[(int)Stack[top]--];
	}
}
double pop(double Stack[])
{
	if (Stack[top] == 0)
	{
		exit(0);
	}
	else
	{
		return Stack[(int)Stack[top]--];
	}
}
bool HaveFile(const char* filename)
{
	FILE* file;
	if ((file = fopen(filename, "r+")) != NULL)
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}
int OperatorNum(char mark)
{
	switch (mark)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	}
	return -1;
}
void AddNode(Node* list, char* Data)
{
	char* temp = (char*)malloc(AryLength * sizeof(char));
	strcpy(temp, Data);
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->next = NULL;
	NewNode->Data = temp;
	while (list->next)
	{
		list = list->next;
	}
	list->next = NewNode;
}
void OpenFile(const char* filename,Node *list)
{
	FILE* file;
	if ((file = fopen(filename, "r+"))!=NULL)
	{
		while (!feof(file))
		{
			char* Data = (char*)malloc(AryLength * sizeof(char));
			fgets(Data, AryLength, file);
			AddNode(list, Data);
		}
		fclose(file);
	}
}
void FreeList(Node* list)
{
	if (!list)
		return;
	FreeList(list->next);
	free(list);
}
bool HaveNewLine(char* Data)
{
	return Data[strlen(Data)-1] == '\n';
}
void Calculate(char* postfix)
{
	double NumStack[MAXSTACK] = { 0 };
	char* ptr = strtok(postfix+1," ");
	while (ptr)
	{
		bool sw = false;
		double temp;
		for(int i=0;i<strlen(ptr);i++)
			switch (ptr[i])
			{
			case '+':
				push(NumStack, pop(NumStack) + pop(NumStack));
				break;
			case '-':
				temp = pop(NumStack);
				push(NumStack, pop(NumStack) - temp);
				break;
			case '*':
				push(NumStack, pop(NumStack) * pop(NumStack));
				break;
			case '/':
				temp = pop(NumStack);
				push(NumStack, pop(NumStack) / temp);
				break;
			case '^':
				temp = pop(NumStack);
				push(NumStack,pow(pop(NumStack),temp));
				break;
			default:
				if (!sw)
				{
					push(NumStack, atof(ptr+i));
					sw = true;
				}
				break;
			}
		ptr = strtok(NULL, " ");
	}	
	printf("Value : %f\n", NumStack[(int)NumStack[top]]);
}
void post(char* infix, Node* postfix)
{
	char Postfixtemp[MAXSTACK] = { 0 };;
	char Stack[MAXSTACK] = { 0 };//Àx¦s²Å¸¹
	int count = 1;
	for (int i = 0; infix[i] != '\0'; i++)
	{
		
		for (; infix[i] >= '0' && infix[i] <= '9' && i < strlen(infix) || infix[i] == '.'; i++)
		{
			push(Postfixtemp, infix[i]);

		}
		if (Postfixtemp[Postfixtemp[top]] >= '0' && Postfixtemp[Postfixtemp[top]] <= '9')
			push(Postfixtemp, ' ');
		switch (infix[i])
		{
		case '(':
			push(Stack, infix[i]);
			break;
		case '+':case '-': case '*': case '/':case'^':
			while (OperatorNum(Stack[Stack[top]]) >= OperatorNum(infix[i]) && !isEmpty(Stack))
				push(Postfixtemp, pop(Stack));
			push(Stack, infix[i]);
			break;
		case ')':
			while (Stack[Stack[top]] != '(')
				push(Postfixtemp, pop(Stack));
			pop(Stack);
			break;
		case '\n':
			break;
		default:
			break;
		}
	}
	while (Stack[top] != 0)
	{
		push(Postfixtemp, pop(Stack));
	}
	AddNode(postfix, Postfixtemp);
	printf("Postfix : %s\n", Postfixtemp + 1);
}
void IntoPost(Node* infix, Node* postfix)
{
	while (infix->next)
	{
		infix = infix->next;
		printf("Infix : %s", infix->Data);
		if (!HaveNewLine(infix->Data))
		{
			puts("");
		}
		post(infix->Data, postfix);
		postfix = postfix->next;
		Calculate(postfix->Data);
		puts("==========================");
	}
}
bool GetData(char* Data)
{
	printf("Infix : ");
	scanf("%s", Data);
	if (strcmp(Data, "stop") == 0)
		return false;
	return true;
}
void main(int argv, char* argc[])
{
	Node* Infix = (Node*)malloc(sizeof(Node));
	Infix->next = NULL;
	Node* Postfix = (Node*)malloc(sizeof(Node));
	Postfix->next = NULL;
	if (HaveFile(argc[1]))
	{
		OpenFile(argc[1], Infix);
		IntoPost(Infix, Postfix);
	}
	else
	{
		char* temp = (char*)malloc(AryLength * sizeof(char));
		puts("¿é¤Jstop°±¤î");
		while (true)
		{
			if (!GetData(temp))
				break;
			AddNode(Infix, temp);
			Infix = Infix->next;
			post(Infix->Data, Postfix);
			Postfix = Postfix->next;
			Calculate(Postfix->Data);
			puts("==========================");
		}
		free(temp);
	}
	FreeList(Infix);
	FreeList(Postfix);

}