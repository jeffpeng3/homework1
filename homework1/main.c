#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __linux__
#define strtok_s(s,tok,useless) strtok(s,tok)
#define fopen_s(ptr,path,mode) *ptr = fopen(path,mode)
#define strcpy_s(dest,len,src) strcpy(dest,src)
#endif


typedef struct _node
{
	char* numString;
	uint64_t length;
	struct _node* next;
} node;
node* loadNumFromString(node* root, node* last, char* str, int* count)
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
		(*count)++;
		return loadNumFromString(root, current, 0, count);
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
	printf("%s\n", current->numString);
	if (current->next)
	{
		printAllList(current->next);
	}
}
void printNode(node* current)
{
	printf("%s\n", current->numString);
}
node* getLargestNode(node* current)
{
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
void duplicate(node* root)
{
	char* map = calloc(1024, sizeof(char));
	if (map)
	{
		for (node* last = root; root; root = last->next)
		{

			for (node* i = root->next; i; i = i->next)
			{
				if (root->length != i->length)
				{
					continue;
				}
				if (strcmp(root->numString, i->numString))
				{
					continue;
				}
				node* temp = root;
				last->next = root->next;
				free(temp);
				root = last->next;
				break;
			}
			last = root;
		}
	}

}
void sumAndPrintList(node* root)
{
	/* not implement yet*/
}

int main()
{
	FILE* dataSource;
	int count = 0;
	fopen_s(&dataSource, "./number.txt", "r");
	char* string = getStringFromFile(dataSource);
	node* root = loadNumFromString(NULL, NULL, string, &count);
	printAllList(root);
	printf("\nthe largest is:\n");
	printNode(getLargestNode(root));
	printf("\nafter duplicate:\n");
	duplicate(root);
	printAllList(root);

	return 0;
}