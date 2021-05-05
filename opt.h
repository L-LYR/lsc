#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// _Bool LexicalOnly = false;
_Bool Verbose = false;
const char *OptFmt = ":vho:i:";

const char *Usage = "Usage: %s [-vh] -i <filename> -o <filename>\n"
                    "Options:\n"
                    "  -v           \tTurn on verbose mode, display the "
                    "lexical analysis results in pairs.\n"
                    "  -i <filename>\tInput file.\n"
                    "  -o <filename>\tOutput file.\n"
                    // "  -l           \tOnly do lexical analysis.\n"
                    "  -h           \tPrint this help.\n";
char *Filename = NULL;

FILE *OutputFile = NULL;

void SetOpts(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, OptFmt)) != -1) {
    switch (opt) {
    case 'v':
      Verbose = true;
      break;
    // case 'l':
    // LexicalOnly = true;
    // break;
    case 'i':
      Filename = optarg;
      break;
    case 'o':
      OutputFile = fopen(optarg, "w");
      if (OutputFile == NULL) {
        printf("cannot open output file %s", optarg);
        exit(-1);
      }
      break;
    default:
    case 'h':
      printf(Usage, argv[0]);
      exit(-1);
    }
  }
}