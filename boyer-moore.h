#pragma once

#include <iostream>

using namespace std;


long count_compare_bm(const char* text, const char* pattern);
int substring_search_bm(const char* text, const char* pattern);
int substring_count_bm(const char* text, const char* pattern, const int start = 0);
void freeMemory1(int* right);
int* computeRight(const char* pattern);