#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main (int argc, char *argv[]) {
	if (argc == 1) {
		printf("wzip: file1 [file2 ...]\n");
		return 1;
	}
		
	FILE *file = NULL;
	char *fileName;

	char *linePtr = NULL;
	size_t	len;
	ssize_t nread;

	int current = -1;
	uint32_t freq = 0;

	for (size_t i = 1; i < argc; i++) {
		fileName = argv[i];
		file = fopen(fileName, "r");
		if (file == NULL)
			return 1;

		while ((nread = getline(&linePtr, &len, file)) != -1) {
			for (size_t j = 0; j < nread; j++){
				
				if (current == -1) {
					current = linePtr[j];
					freq = 1;
				}
				else if (linePtr[j] == current) {
					freq = freq + 1;
				}
				else {
					fwrite(&freq, sizeof(freq), 1, stdout);
					fwrite(&current, 1, 1, stdout);

					current = linePtr[j];
					freq = 1;
				}
			}

		}

		fclose(file);
	}
	
	if (freq > 0){
		fwrite(&freq, sizeof(freq), 1, stdout);
		fwrite(&current, 1, 1, stdout);
	}

	free(linePtr);

	return 0;
}
