#include <stdio.h>

int main (int argc, char* argv[]) {
  char buffer[40];
  for (int i = 1; i < argc; i++ ) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp))
      printf("%s", buffer);
    
    fclose(fp);
  }
  return 0;
}
