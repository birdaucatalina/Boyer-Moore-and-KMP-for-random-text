#include "boyer-moore.h"

int substring_search_bm(const char* text, const char* pattern) {
	// Simulate operation of DFA on txt.
	int textLen = strlen(text);
	int patternLen = strlen(pattern);
	int skip;
	int* right = computeRight(pattern);
	for (int i = 0; i <= textLen - patternLen; i += skip) {
		// Does the pattern match the text at position i ?
		skip = 0;
		for (int j = patternLen - 1; j >= 0; j--) {
			if (pattern[j] != text[i + j]) {
				skip = j - right[text[i + j]];
				if (skip < 1) skip = 1;
				break;
			}
		}
			
		if (skip == 0) {
			freeMemory1(right);
			return i; // found.
		}
	}
	freeMemory1(right);
	return -1;
}

int* computeRight(const char* pattern) {
	int R = 256;
	int patternLen = strlen(pattern);
	int* right = new int[R];
	right = new int[R];

	for (int c = 0; c < R; c++) {
		right[c] = -1; // -1 for chars not in pattern
	}
	for (int j = 0; j < patternLen; j++) {
		right[pattern[j]] = j;
	}
	return right;
}

void freeMemory1(int* right) {
	delete[] right;
}

int substring_count_bm(const char* text, const char* pattern, int start) {

	int count = 0;
	char* aux = new char[strlen(text)];

	strcpy(aux, text + start);

	while (substring_search_bm(aux, pattern) != -1) {
		start = substring_search_bm(aux, pattern);
		strcpy(aux, aux + (start + 1));
		count++;
	}

	return count;
}
long count_compare_bm(const char* text, const char* pattern) {
	long count = 0;
	int textLen = strlen(text);
	int patternLen = strlen(pattern);
	int skip;
	int* right = computeRight(pattern);
	for (int i = 0; i <= textLen - patternLen; i += skip) {
		// Does the pattern match the text at position i ?
		skip = 0;
		for (int j = patternLen - 1; j >= 0; j--) {
			count++;
			if (pattern[j] != text[i + j]) {
				skip = j - right[text[i + j]];
				if (skip < 1) skip = 1;
				break;
			}
		}

		if (skip == 0) {
			freeMemory1(right);
			return count; // found.
		}
	}
	freeMemory1(right);
	return count;
}