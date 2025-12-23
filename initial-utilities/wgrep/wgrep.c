#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findTerm(char *searchTerm, char *line, size_t termLength, size_t lineLength) {
	if (termLength > lineLength) 
		return 0;
	for (size_t j = 0; j <= lineLength - termLength; j++)
		if (strncmp(searchTerm, line + j, termLength) == 0) {
			printf("%s", line);
			return 1;
		}

	return 0;
}
	
int main (int argc, char *argv[]) {
	if (argc == 1) {
		printf("wgrep: searchterm [file ...]\n");
		return 1;
	}	
	

	char *line = NULL;
	size_t len = 0;
	size_t nread;
	FILE *fp = stdin;
	char *searchTerm = argv[1];
	size_t slen = strlen(searchTerm);

	if (argc == 2) {
		while ((nread = getline(&line, &len, fp)) != -1)
			if(findTerm(searchTerm, line, slen, nread) == 1) continue;
		return 0;
	}

	for (size_t i = 2; i < argc; i++) {
		fp = fopen(argv[i], "r");

		if (fp == NULL) {
			printf("wgrep: cannot open file\n");
			return 1;
		}

		while ((nread = getline(&line, &len, fp)) != -1)
			if (findTerm(searchTerm, line, slen, nread) == 1) continue;

	}
	fclose(fp);
	free(line);
	return 0;
}
