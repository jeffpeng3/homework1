#pragma once
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

