#include "node.h"

FILE* dataSource;
int main()
{

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
		scanf_s(" %c", &mode, 1);                             // get user enter as mode select
		clearOutput();                                        // clear the console output to make it look easier
		node* temp;
		switch (mode)
		{
			case 'a':
				printf("Loading......\n");
				fopen_s(&dataSource, "./number.txt", "r");    // open file
				char* string = getStringFromFile(dataSource); // try to load file
				root = loadNumFromString(root, NULL, string); // pharse string to linked list
				if (dataSource)
				{
					fclose(dataSource);                       // close file if file is opened
				}
				printf("Load done.\n");
				break;
			case 'b':
				printf("Node count is:%d\n", nodeCount(root));// call count function from root
				break;
			case 'c':
				temp = getLargestNode(root);                  // get largest node from root
				if (temp)
				{
					printf("largest node is:\n");
				}
				printNode(getLargestNode(root));              // use function to print node 
				break;
			case 'd':
				root = deduplicate(root);                     // use function to deduplicate linked list
				printf("Deduplication done.\n");
				break;
			case 'e':
				sumAndPrintList(root);                        // a simple implementation of a big number adder
				break;
			case 'f':
				printf("Now list's data:\n");
				printf("===============================\n");
				printAllList(root);                           // print all node in this linked list
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