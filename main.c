#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX 100
#define DELIM "," 

char *ifile, *ofile;
unsigned filter_age_max;
FILE *istream, *ostream;

const char USAGE[] =
    R"(Filters CSV rows, keeping only those with provided maximum age
%1$s max-age [input-file] [output-file]

Example: 
%1$s max-age 17 input.csv output.csv
%1$s max-age 10 input.csv (outputs to stdout)
%1$s max-age 54           (inputs from stdin, outputs to stdout)
)";

void filter_stream(FILE *istream, FILE *ostream) {
  char line[LINE_MAX];
  char *fgets_return;
  char *name, *age_str;
  size_t line_no = 0;

  while (
      fgets_return = fgets(line, LINE_MAX, istream)  
  ) {
    ++line_no;

    line[strcspn(line, "\r\n")] = 0;

    if (fgets_return && *fgets_return != '\n') {
      if (strlen(line) > 1) {
        name = strtok(line, DELIM);
        age_str = strtok(NULL, DELIM);

        if (age_str) {
            while (*age_str == ' ') age_str++;
        }

        if (!age_str) {
          printf("Error: Age missing on line %zu\n", line_no);
          continue;
        }
      }
    } else {
      printf("Warning: Blank line at line %zu\n", line_no);
      continue;
    }

    unsigned age;
    int recognized_count = sscanf(age_str, "%u", &age);
    if (recognized_count == 1) {
      if (age <= filter_age_max) {
        fprintf(ostream, "%s,%s\n", name, age_str);
      }
    } else {
      printf("Error: Age not recognized on line %zu\n", line_no);
    }
  }
}

int main(int argc, char *argv[]) {
  switch (argc) {
  case 4:
    ofile = argv[3];
  case 3:
    ifile = argv[2];
  case 2:
    if (!sscanf(argv[1], "%u", &filter_age_max)) {
      puts("First argument is not an age.");
      exit(EXIT_FAILURE);
    }
    break;
  default:
    printf(USAGE, argv[0]);
    return EXIT_SUCCESS;
  }

  if (ifile) {
    istream = fopen(ifile, "r");

    if (!istream) {
      printf("Error: Could not open input file %s\n", ifile);
      exit(EXIT_FAILURE);
    }
  } else {
    istream = stdin;
  }

  if (ofile) {
    ostream = fopen(ofile, "w");

    if (!ostream) {
      printf("Error: Could not open output file %s\n", ofile);
      exit(EXIT_FAILURE);
    }
  } else {
    ostream = stdout;
  }

  filter_stream(istream, ostream);

  if (ifile) fclose(istream);
  if (ofile) fclose(ostream);
}
