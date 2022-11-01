#pragma once 
#include "utils.h"

typedef struct _node
{
	char* numString;
	uint64_t length;
	short sign;
	struct _node* next;
} node;

node* loadNumFromString(node* root, node* last, char* str);

void printNode(node* current);

node* getLargestNode(node* current);

void printAllList(node* current);

node* deduplicate(node* current);

void addToFirstNode(char* sum, char* target);

void sumAndPrintList(node* root);

int nodeCount(node* root);
