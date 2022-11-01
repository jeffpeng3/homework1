#include "utils.h"
#include "node.h"

node* root = NULL;

FILE* dataSource;
char fileName[51] = { 0 };
const char* prompt =
"code	description\n\
(a)	Read an integer file to build the linked lists.\n\
(b)	Count the number of integers.\n\
(c)	Find the largest integer for all integers in the lists.\n\
(d)	Remove duplicate integers for each list and print out the resulting lists.\n\
(e)	Sum all the distinct integers.\n\
(f)	Print all nodes.\n\
(q)	Quit.\n\
please select mode:";

void myStrrev(char* str) //reverse string
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


char* getStringFromFile(FILE* file) // allocate a char array to load file's string
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

int seleteOperation(char mode)
{
	switch (mode)
	{
		node* temp;
		case 'a':
			printf("Please enter a file name to load or only press enter to load default file.\ndefault is \"./number.txt\" (Max 50 Character):");
			fflush(stdin);
			*fileName = getchar();
			if (*fileName == '\n')// check is user custom or default
			{
				strcpy_s(fileName, 13, "./number.txt");
			}
			else
			{
				scanf_s(" %[^\n]", (fileName + 1), 50);
			}
			if (fopen_s(&dataSource, fileName, "r"))
			{
				printf("Load failed.\n");
				return 0;
			}    // open file
			printf("Loading...\n");
			char* string = getStringFromFile(dataSource); // try to load file
			root = loadNumFromString(root, NULL, string); // pharse string to linked list
			if (dataSource)
			{
				fclose(dataSource);                       // close file if file is opened
			}
			printf("Load done.\n");
			return 0;
		case 'b':
			printf("Node count is:%d\n", nodeCount(root));// call count function from root
			return 0;
		case 'c':
			temp = getLargestNode(root);                  // get largest node from root
			if (temp)
			{
				printf("largest node is:\n");
			}
			printNode(getLargestNode(root));              // use function to print node 
			return 0;
		case 'd':
			root = deduplicate(root);                     // use function to deduplicate linked list
			printf("Deduplication done.\n");
			return 0;
		case 'e':
			sumAndPrintList(root);                        // a simple implementation of a big number adder
			return 0;
		case 'f':
			printf("Now list's data:\n");
			printf("===============================\n");
			printAllList(root);                           // print all node in this linked list
			return 0;
		case 'q':
			return -1;
		default:
			printf("unknown mode\n");
			return 0;
	}
	printf("========================================================================================\n");
	return 0;
}