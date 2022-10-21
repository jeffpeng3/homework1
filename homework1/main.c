#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __linux__
#define strtok_s(s, tok, useless) strtok(s, tok)
#define fopen_s(ptr, path, mode) *ptr = fopen(path, mode)
#define strcpy_s(dest, len, src) strcpy(dest, src)
#define scanf_s(format,...) scanf(format,__VA_ARGS__)
#define clearOutput() system("clear")
#elif _WIN32
#define clearOutput() system("cls")
#else
#error Platform not supported
#endif
void myStrrev(char* str)
{
	char* temp = str;
	while (*(temp++))
		;
	temp -= 2;
	while (str < temp)
	{
		*str ^= *temp;
		*temp ^= *str;
		*str ^= *temp;
		str++;
		temp--;
	}
}

typedef struct _node
{
	char* numString;
	uint64_t length;
	struct _node* next;
} node;
node* loadNumFromString(node* root, node* last, char* str)
{
	static char* token = " ,";
	static char* tempPtr = NULL;
	static char* strtokBuffer = NULL;
	node* current = NULL;
	if (!root)
	{
		root = calloc(1, sizeof(node));
		if (root != NULL)
		{
			root->next = NULL;
			root->length = 0;
			root->numString = NULL;
			current = root;
		}
		else
		{
			fprintf(stderr, "error at line %d,memory allocate failed", __LINE__);
			abort();
		}
	}
	else if (!last)
	{
		last = root;
		while (last->next)
		{
			last = last->next;
		}
	}

	tempPtr = strtok_s(str, token, &strtokBuffer);
	if (tempPtr)
	{
		if (!current)
		{
			current = calloc(1, sizeof(node));
			if (current)
			{
				current->next = NULL;
				current->length = 0;
				current->numString = NULL;
				last->next = current;
			}
			else
			{
				fprintf(stderr, "error at line %d,memory allocate failed", __LINE__);
				abort();
			}
		}
		current->numString = calloc(strlen(tempPtr) + 1, sizeof(char));
		if (!current->numString)
		{
			exit(EXIT_FAILURE);
		}
		strcpy_s(current->numString, strlen(tempPtr) + 1, tempPtr);
		current->length = strlen(current->numString);
		return loadNumFromString(root, current, 0);
	}
	return root;
}
char* getStringFromFile(FILE* file)
{
	uint32_t size = 0;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* temp = calloc((uint64_t)size + 2, sizeof(char));
	if (temp)
	{
		fgets(temp, size + 2, file);
	}
	else
	{
		fprintf(stderr, "error at line %d,memory allocate failed", __LINE__);
		abort();
	}

	return temp;
}
void printAllList(node* current)
{
	if (!current)
	{
		printf("linked list is not exist!\n");
		return;
	}
	printf("%s\n", current->numString);
	if (current->next)
	{
		printAllList(current->next);
	}
}
void printNode(node* current)
{
	if (!current)
	{
		printf("linked list is not exist!\n");
		return;
	}
	printf("%s\n", current->numString);
}
node* getLargestNode(node* current)
{
	if (!current)
	{
		return NULL;
	}
	node* largest = current;
	current = current->next;
	for (; current; current = current->next)
	{
		if (largest->length > current->length)
		{
			continue;
		}
		if (largest->length < current->length)
		{
			largest = current;
			continue;
		}
		if (strcmp(largest->numString, current->numString) < 0)
		{
			largest = current;
			continue;
		}
	}
	return largest;
}
node* deduplicate(node* current)
{
	node* root = current;
	if (!root)
	{
		printf("linked list is not exist!\n");
		return NULL;
	}
	for (; current; current = current->next)
	{
		for (node* lastNode = current, *thisNode = current->next; thisNode; lastNode = thisNode, thisNode = thisNode->next)
		{
			if (current->length != thisNode->length)
			{
				continue;
			}
			if (strcmp(current->numString, thisNode->numString))
			{
				continue;
			}
			lastNode->next = thisNode->next;
			free(thisNode);
			thisNode = lastNode;
		}
	}
	return root;
}
void addToFirstNode(char* sum, char* target)
{
	char* predicate = sum;
	short sumEnd = 0, targetEnd = 0, carry = 0;
	while (!(sumEnd & targetEnd))
	{
		*sum -= '0';
		*sum += carry;
		if (!targetEnd)
		{
			*sum += *target - '0';
			target++;
			if (!*target)
			{
				targetEnd = 1;
			}
		}
		carry = *sum / 10;
		*sum = *sum % 10;
		*sum += '0';
		sum++;
		if (!*sum)
		{
			if (!targetEnd || carry)
			{
				*sum = '0';
				*(sum + 1) = 0;
			}
			else
			{
				sumEnd = 1;
			}
		}
	}
}
void sumAndPrintList(node* root)
{
	if (!root)
	{
		printf("linked list is not exist!\n");
		return;
	}
	node sum;
	sum.length = 1;
	sum.numString = calloc(2, sizeof(char));
	sum.numString[0] = '0';
	sum.next = NULL;
	myStrrev(sum.numString);
	for (; root; root = root->next)
	{
		if (sum.length <= root->length)
		{
			char* temp = realloc(sum.numString, sizeof(char) * (root->length + 2));
			if (temp)
			{
				sum.numString = temp;
			}
			sum.length = root->length + 1;
		}
		myStrrev(root->numString);
		addToFirstNode(sum.numString, root->numString);
		myStrrev(root->numString);
	}
	myStrrev(sum.numString);
	printf("the sum is:");
	printNode(&sum);
}
int nodeCount(node* root)
{
	int count = 0;
	while (root)
	{
		root = root->next;
		count++;
	}
	return count;
}
int main()
{
	FILE* dataSource;

	node* root = NULL;
	char mode;
	const char* prompt =
		"	(a) Read an integer file to build the linked lists.\n\
	(b) Count the number of integers.\n\
	(c) Find the largest integer for all integers in the lists.\n\
	(d) Remove duplicate integers for each list and print out the resulting lists.\n\
	(e) Sum all the distinct integers.\n\
	(f) Print all nodes.\n\
	(q) Quit.\n\
please select mode:";
	while (1)
	{
		printf(prompt);
		scanf_s(" %c", &mode, 1);
		clearOutput();
		node* temp;
		switch (mode)
		{
			case 'a':
				printf("Loading......\n");
				fopen_s(&dataSource, "./number.txt", "r");
				char* string = getStringFromFile(dataSource);
				root = loadNumFromString(root, NULL, string);
				if (dataSource)
				{
					fclose(dataSource);
				}
				printf("Load done.\n");
				break;
			case 'b':
				printf("Node count is:%d\n", nodeCount(root));
				break;
			case 'c':
				temp = getLargestNode(root);
				if (temp)
				{
					printf("largest node is:\n");
				}
				printNode(getLargestNode(root));
				break;
			case 'd':
				root = deduplicate(root);
				printf("Deduplication done.\n");
				break;
			case 'e':
				sumAndPrintList(root);
				break;
			case 'f':
				printf("Now list's data:\n");
				printf("===============================\n");
				printAllList(root);
				break;
			case 'q':
				return 0;
				break;
			default:
				printf("unknown mode\n");
				continue;
		}
		printf("========================================================================================\n");

	}
	return 0;
}
/*
EQ
NQ
HI
LS
GE
LT
GT
LE
*/