#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int compare(vector<int> string, int shift1, int shift2) {
	int N = string.size();
	for (int i = 0; i < N; i++) {
		int j1 = (i + shift1) % N;
		int j2 = (i + shift2) % N;
		if (string[j1] > string[j2]) return shift1;
		if (string[j1] < string[j2]) return shift2;
	}
	return shift1;
}

int max_value_shift(vector<int> string) {
	int N = string.size();
	int max_shift = 0;
	for (int i = 0; i < N; i++) {
		max_shift = compare(string, i, max_shift);
	}
	return max_shift;
}


int no_of_maxima(vector<int> string) {
	int N = string.size();
	int max_shift = max_value_shift(string);
	int maximas = 0;
	for (int shift = 0; shift < N; shift++) {
		int count = 0;
		for (int i = 0; i < N; i++) {
			int j1 = (i + shift) % N;
			int j2 = (i + max_shift) % N;
			if (string[j1] == string[j2]) count++;
		}
		if (count == N) maximas++;
	}
	return maximas;
}

bool same(vector<int> string, int shift1, int shift2) {
	int N = string.size();

	int count = 0;
	for (int i = 0; i < N; i++) {
		int j1 = (i + shift1) % N;
		int j2 = (i + shift2) % N;
		if (string[j1] == string[j2]) count++;
	}
	if (count == N) return true;
	else return false;

}

int main() {
	int cases;
	cin >> cases;

	for (int i = 0; i < cases; i++) {
		int len; long k; string s;  vector<int> num;
		cin >> len >> k >> s;

		for (int i = 0; i < s.size(); i++) {
			num.push_back(s[i] - 48);
		}
		int N = len;

		int max_times_in_one = no_of_maxima(num);

		int a = ((int)k) / max_times_in_one;
		int b = ((int)k) % max_times_in_one;
		if (b == 0) {
			b = max_times_in_one;
			a = a - 1;
		}
		int shiftsinone = 0;
		int maxes = 0;
		int max_shift = max_value_shift(num);

		while (maxes < b) {
			if (same(num,shiftsinone,max_shift)) maxes++;
			shiftsinone++;
		}shiftsinone--;
		double aa = a;
		double shifts = (aa * N + shiftsinone);
		

		cout << (long long)shifts << endl;
	}
}