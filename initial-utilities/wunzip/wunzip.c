#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main (int argc, char *argv[]) {
	if (argc == 1){
		printf("wunzip: file1 [file2 ...]\n");
		return 1;
	}

	FILE *file = NULL;
	char *fileName;

	uint32_t freq;
	int character;

	for (size_t i = 1; i < argc; i++) {
		fileName = argv[i];
		file = fopen(fileName, "r");

		if (file == NULL) {
			return 1;
		}

		while (fread(&freq, 1, 4, file) != 0 && fread(&character, 1, 1, file) != 0) {
			for (uint32_t j = 0; j < freq; j++) 
				printf("%c", (char)character);
		}

		fclose(file);
	}

	return 0;	
}
