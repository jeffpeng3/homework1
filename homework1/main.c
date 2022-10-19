#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __linux__
#define strtok_s(s, tok, useless) strtok(s, tok)
#define fopen_s(ptr, path, mode) *ptr = fopen(path, mode)
#define strcpy_s(dest, len, src) strcpy(dest, src)
void strrev(char *str)
{
	char *temp = str;
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
#endif

typedef struct _node
{
	char *numString;
	uint64_t length;
	struct _node *next;
} node;
node *loadNumFromString(node *root, node *last, char *str)
{
	static char *token = " ,";
	static char *tempPtr = NULL;
	static char *strtokBuffer = NULL;
	node *current = NULL;
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
char *getStringFromFile(FILE *file)
{
	uint32_t size = 0;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *temp = calloc((uint64_t)size + 2, sizeof(char));
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
void printAllList(node *current)
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
void printNode(node *current)
{
	if (!current)
	{
		printf("linked list is not exist!\n");
		return;
	}
	printf("%s\n", current->numString);
}
node *getLargestNode(node *current)
{
	if (!current)
	{
		printf("linked list is not exist!\n");
		return NULL;
	}
	node *largest = current;
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
void deduplicate(node *root, node *current)
{
	char *map = calloc(1024, sizeof(char));
	if (!root)
	{
		printf("linked list is not exist!\n");
		return;
	}
	if (map)
	{
		for (node *last = current; current; current = last->next)
		{

			for (node *i = current->next; i; i = i->next)
			{
				if (current->length != i->length)
				{
					continue;
				}
				if (strcmp(current->numString, i->numString))
				{
					continue;
				}
				node *temp = current;
				if (last)
				{
					last->next = current->next;
				}
				else
				{
					root = current->next;
				}
				free(temp);
				current = last->next;
				break;
			}
			last = current;
		}
	}
}
void addToFirstNode(char *sum, char *target)
{
	char *predicate = sum;
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
void sumAndPrintList(node *root)
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
	strrev(sum.numString);
	for (; root; root = root->next)
	{
		if (sum.length <= root->length)
		{
			sum.numString = realloc(sum.numString, sizeof(char) * (root->length + 2));
			sum.length = root->length + 1;
		}
		strrev(root->numString);
		addToFirstNode(sum.numString, root->numString);
		strrev(root->numString);
	}
	strrev(sum.numString);
	printf("the sum is:");
	printNode(&sum);
}
int nodeCount(node *root)
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
	FILE *dataSource;

	node *root = NULL;
	char mode;
	const char *prompt =
		"=================================================================================\n\
	(a) Read an integer file to build the linked lists.\n\
	(b) Count the number of integers.\n\
	(c) Find the largest integer for all integers in the lists.\n\
	(d) Remove duplicate integers for each list and print out the resulting lists.\n\
	(e) Sum all the distinct integers\n\
	(q) Quit.\n\
please select mode:";
	while (1)
	{
		printf(prompt);
		scanf(" %c", &mode);
		switch (mode)
		{
		case 'a':
			printf("Loading......\n");
			fopen_s(&dataSource, "./number.txt", "r");
			char *string = getStringFromFile(dataSource);
			root = loadNumFromString(root, NULL, string);
			fclose(dataSource);
			printf("Load done.\n");
			break;
		case 'b':
			printf("node count is:%d\n", nodeCount(root));
			break;
		case 'c':
			printf("node list:\n=================================\n");
			printNode(getLargestNode(root));
			break;
		case 'd':
			printf("ready to deduplication...\n");
			deduplicate(root, root);
			printf("deduplication done.\n");
			break;
		case 'e':
			sumAndPrintList(root);
			break;
		case 'q':
			return 0;
			break;

		default:
			printf("unknown mode\n");
			continue;
		}
		printf("now list's data:\n");
		printf("===============================\n");
		printAllList(root);
		// printf("\nthe largest is:\n");
		// printNode(getLargestNode(root));
		// printf("\nafter duplicate:\n");
		// duplicate(root);
		// printAllList(root);
		// sumAndPrintList(root);
		// printf("\n350211429222974\n");
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