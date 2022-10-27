#include "node.h"

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