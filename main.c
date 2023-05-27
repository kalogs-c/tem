#include <regex.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: <search term> <csv file>\n");
    return 1;
  }

  char *term = argv[1];
  regex_t regex;
  int reti = regcomp(&regex, term, REG_EXTENDED);
  if (reti) {
    printf("Error compiling regex: %s\n", term);
    return 1;
  }

  char *filename = argv[2];
  char *output = argv[3];

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File %s not found\n", filename);
  }
  FILE *fp_out;
  if (output != NULL) {
    fp_out = fopen(output, "w");
  }

  char line[256];
  int line_count = 1;
  while (fgets(line, 256, fp) != NULL) {
    if (line_count == 1) {
      if (fp_out != NULL) {
        fprintf(fp_out, "%s", line);
      }
      printf("%s", line);
    }
    if (regexec(&regex, line, 0, NULL, 0) == 0) {
      printf("%s", line);
      if (fp_out != NULL) {
        fprintf(fp_out, "%s", line);
      }
    }
    line_count++;
  }

  fclose(fp);
  if (fp_out != NULL) {
    fclose(fp_out);
  }

  return 0;
}
