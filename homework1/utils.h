#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include "node.h"
#include "compatiable.h"

extern const char* prompt;


extern struct _node* root;

int seleteOperation(char mode);
char* getStringFromFile(FILE* file);

void myStrrev(char* str);
