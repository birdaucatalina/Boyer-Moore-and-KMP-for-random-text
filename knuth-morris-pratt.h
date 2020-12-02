#pragma once

#include <iostream>

using namespace std;

long count_compare_kmp(const char* text, const char* pattern);
int substring_search_kmp(const char* text, const char* pattern);
int** compute_dfa(const char* pattern);
void freeMemory(int** dfa);
int substring_count_kmp(const char* text, const char* pattern, const int start = 0);

long count_compare_kmp_lps(const char* text, const char* pattern);
int substring_search_kmp_lps(const char* text, const char* pattern);
int* computeLps(const char* pattern);
void freeMemory(int* lps);
int substring_count_kmp_lps(const char* text, const char* pattern, const int start = 0);