#include <fstream>
#include "knuth-morris-pratt.h"
#include "boyer-moore.h"
#include <string>
#include <stdlib.h>
#include <time.h> 

//#define T 10;
//#define M 8;
//#define N 12350202;
char* generateString(int length);

int main()
{
	const int T = 10;
	const int M = 8;
	const int N = 12350202;
	ofstream g;

	g.open("results.txt");
	srand(time(NULL));
	long countKmp[T];
	long countKmpLps[T];
	long countBm[T];

	long totalKmp = 0;
	long totalKmpLps = 0;
	long totalBm = 0;

	for (int i = 0; i < T; i++) {

		char* pattern = generateString(M);
		char* text = generateString(N);
		g << "Test number " << i + 1 << endl;
		g << "Knuth-Morris-Pratt found at index: " << substring_search_kmp(text, pattern) << endl;
		g << "Knuth-Morris-Pratt LPS found at index: " << substring_search_kmp_lps(text, pattern) << endl;
		g << "Boyer-Moore found at index: " << substring_search_bm(text, pattern) << endl << endl;
		countKmp[i] = count_compare_kmp(text, pattern);
		countKmpLps[i] = count_compare_kmp_lps(text, pattern);
		countBm[i] = count_compare_bm(text, pattern);
		delete[] pattern;
		delete[] text;
	}

	for (int i = 0; i < T; i++) {

		totalKmp += countKmp[i];
		totalKmpLps += countKmpLps[i];
		totalBm += countBm[i];
	}

	g << "T = " << T << "\tM = " << M << "\tN = " << N << endl;
	g << "Average count Knuth-Morris-Pratt: \t\t" << totalKmp / T << endl;
	g << "Average count Knuth-Morris-Pratt Lps: \t" << totalKmpLps / T << endl;
	g << "Average count Boyer-Moore: \t\t\t\t" << totalBm / T << endl;

	return 0;
}

char* generateString(const int length) {
	char* result = new char[length];
	
	int t = ('z' - 'a') + 1;
	for (int i = 0; i < length; i++) {
		result[i] = 'a' + rand() % t;
	}
	
	result[length] = '\0';
	
	return result;
}