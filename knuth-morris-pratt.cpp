#include "knuth-morris-pratt.h"

int substring_search_kmp(const char* text, const char* pattern) {
	// Simulate operation of DFA on txt.
	int i, j;
	int textLen = strlen(text);
	const int patternLen = strlen(pattern);
	const int R = 256;
	int** dfa = compute_dfa(pattern);

	for ( i = 0, j = 0; i < textLen && j < patternLen; i++) {
		j = dfa[text[i]][j];
	}
	if (j == patternLen) {
		freeMemory(dfa);
		return i - patternLen; // found (hit end of pattern)
	}
	else {
		freeMemory(dfa);
		return -1; // not found (hit end of text)
	}
}

int** compute_dfa(const char* pattern) {
	int patternLen = strlen(pattern);
	int R = 256;
	int** dfa = new int*[R];
	for (int i = 0; i < R; i++) {
		dfa[i] = new int[patternLen];
		for (int j = 0; j < patternLen; j++) {
			dfa[i][j] = 0;
		}
	}

	dfa[pattern[0]][0] = 1;
	for (int X = 0, j = 1; j < patternLen; j++)
	{ // Compute dfa[][j].
		for (int c = 0; c < R; c++)
			dfa[c][j] = dfa[c][X]; // Copy mismatch cases.
		dfa[pattern[j]][j] = j + 1; // Set match case.
		X = dfa[pattern[j]][X]; // Update restart state.
	}
	return dfa;
}

void freeMemory(int** dfa) {
	int rows = sizeof dfa / sizeof dfa[0];
	for (int i = 0; i < rows; ++i) {
		delete[] dfa[i];//deletes an inner array of integer;
	}
	delete[] dfa;

}

int substring_count_kmp(const char* text, const char* pattern, int start) {

	int count = 0;
	char* aux = new char[strlen(text)];

	strcpy(aux, text + start);

	while (substring_search_kmp(aux, pattern) != -1) {
		start = substring_search_kmp(aux, pattern);
		strcpy(aux, aux + (start + 1));
		count++;
	}

	return count;
}

int substring_search_kmp_lps(const char* text, const char* pattern)
{
	int patternLen = strlen(pattern);
	int textLen = strlen(text);

	// create lps[] that will hold the longest prefix suffix 
	// values for pattern 
	int* lps = computeLps(pattern);

	int i = 0; // index for txt[] 
	int j = 0; // index for pat[] 
	while (i < textLen) {
		if (pattern[j] == text[i]) {
			j++;
			i++;
		}

		if (j == patternLen) {
			freeMemory(lps);
			return i - j;
		}

		// mismatch after j matches 
		else if (i < textLen && pattern[j] != text[i]) {
			// Do not match lps[0..lps[j-1]] characters, 
			// they will match anyway 
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
	freeMemory(lps);
	return -1;
}

// Fills lps[] for given patttern pat[0..M-1] 
int* computeLps(const char* pattern)
{
	// length of the previous longest prefix suffix 
	int len = 0;
	int patternLen = strlen(pattern);
	int * lps = new int[patternLen];
	lps[0] = 0; // lps[0] is always 0 

	// the loop calculates lps[i] for i = 1 to M-1 
	int i = 1;
	while (i < patternLen) {
		if (pattern[i] == pattern[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else // (pat[i] != pat[len]) 
		{
			// This is tricky. Consider the example. 
			// AAACAAAA and i = 7. The idea is similar 
			// to search step. 
			if (len != 0) {
				len = lps[len - 1];

				// Also, note that we do not increment 
				// i here 
			}
			else // if (len == 0) 
			{
				lps[i] = 0;
				i++;
			}
		}
	}
	return lps;
}

int substring_count_kmp_lps(const char* text, const char* pattern, int start) {

	int count = 0;
	char* aux = new char[strlen(text)];

	strcpy(aux, text + start);

	while (substring_search_kmp_lps(aux, pattern) != -1) {
		start = substring_search_kmp_lps(aux, pattern);
		strcpy(aux, aux + (start + 1));
		count++;
	}

	return count;
}

void freeMemory(int* lps) {
	delete[] lps;
}

long count_compare_kmp(const char* text, const char* pattern) {
	long count = 0;
	int i, j;
	int textLen = strlen(text);
	const int patternLen = strlen(pattern);
	const int R = 256;
	int** dfa = compute_dfa(pattern);

	for (i = 0, j = 0; i < textLen && j < patternLen; i++) {
		count++;
		j = dfa[text[i]][j];
	}
	if (j == patternLen) {
		freeMemory(dfa);
		return count; // found (hit end of pattern)
	}
	else {
		freeMemory(dfa);
		return count; // not found (hit end of text)
	}
}

long count_compare_kmp_lps(const char* text, const char* pattern) {
	long count = 0;
	int patternLen = strlen(pattern);
	int textLen = strlen(text);

	// create lps[] that will hold the longest prefix suffix 
	// values for pattern 
	int* lps = computeLps(pattern);

	int i = 0; // index for txt[] 
	int j = 0; // index for pat[] 
	while (i < textLen) {
		if (pattern[j] == text[i]) {
			count++;
			j++;
			i++;
		}

		if (j == patternLen) {
			count++;
			freeMemory(lps);
			return count;
		}

		// mismatch after j matches 
		else if (i < textLen && pattern[j] != text[i]) {
			// Do not match lps[0..lps[j-1]] characters, 
			// they will match anyway 
			if (j != 0) {
				count++;
				j = lps[j - 1];
			}
			else {
				i = i + 1;
				count++;
			}
		}
	}
	freeMemory(lps);
	return count;
}