#include "node.h"
node* loadNumFromString(node* root, node* last, char* str)  //use token to split string and transform string to node
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
			root->sign = 1;
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
				current->sign = 1;
				current->numString = NULL;
				last->next = current;
			}
			else
			{
				fprintf(stderr, "error at line %d,memory allocate failed", __LINE__);
				abort();
			}
		}
		if (*tempPtr == '-'){
			current -> sign = 0;
			tempPtr++;
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

void printAllList(node* current) // a recursion function to print linked list 
{
	if (!current)
	{
		printf("linked list is not exist!\n");
		return;
	}
	printf("%c%s\n",current-> sign ? 0:'-', current->numString);
	if (current->next)
	{
		printAllList(current->next);
	}
}

void printNode(node* current) //a normal function to print a single node
{
	if (!current)
	{
		printf("linked list is not exist!\n");
		return;
	}
	printf("%c%s\n",current-> sign ? 0:'-', current->numString);
}

node* getLargestNode(node* current) // use multiple conditions to find the largest node
{
	if (!current)
	{
		return NULL;
	}
	node* largest = current;
	current = current->next;
	for (; current; current = current->next)
	{
		if (largest -> sign > current -> sign){
			continue;
		}
		if (largest->length > current->length)
		{
			continue;
		}
		if (largest->length < current->length)
		{
			largest = current;
			continue;
		}
		int cmp = strcmp(largest->numString, current->numString);
		if ((largest -> sign && cmp < 0)||(!largest -> sign && cmp > 0))
		{
			largest = current;
			continue;
		}
	}
	return largest;
}

void addToFirstNode(char* sum, char* target) // add target to sum
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

node* deduplicate(node* current) // an O(n^2) deduplicate funcction
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
	sum.sign = 1;
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
