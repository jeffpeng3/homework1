#include "node.h"

int main()
{
	char mode;
	while (1)
	{
		printf("%s",prompt);
		scanf_s(" %c", &mode, 1);                             // get user enter as mode select
		while ((getchar()) != '\n');
		clearOutput();                                        // clear the console output to make it look easier
		if (seleteOperation(mode))
		{
			return 0;
		}
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