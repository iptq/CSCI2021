#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check(int cookie) {
	if (cookie >> 28) {
		if ((unsigned) cookie == 10) return 0;
		int x = 8;
		while ((unsigned) (cookie >> x) != 10) {
			x += 8;
			if (x == 32) return 1;
		}
		return 0;
	} else return 0;
}

int hash(char* string) {
	int result = 0;
	for (int i = 0; i < strlen(string); ++i) {
		result = string[i] + 103 * result;
	}
	return result;
}

int gencookie(char* username) {
	int seed = hash(username);
	int cookie;
	srand(seed);
	do {
		cookie = rand();
	} while (!check(cookie));
	return cookie;
}

int main() {
	printf("0x%08x\n", gencookie("lol"));
	printf("0x%08x\n", gencookie("zhan4854"));
	return 0;
}