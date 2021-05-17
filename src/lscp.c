#include "../lib/llsc.h"
#include "exception.h"
#include "lsc.tab.h"
#include "symbol_table.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// extern
int yylex_destroy(void);
FILE *yyin;

AST t; // lsc.y

// static
Fmt fmt;
_Bool ShowAST; // print AST
static void SetOpts(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  SetOpts(argc, argv);

  AtomInit();
  ArenaInit();

  int ret = yyparse();
  if (ret == 0 && ShowAST) {
    DisplayAST(&t, &fmt);
  }

  fclose(yyin);

  yylex_destroy();
  ArenaClear();
  AtomReset();
  return ret;
}

const char *OptFmt = ":vho:i:";

const char *Usage = "Usage: lscp [-vh] -i <filename> -o <filename>\n"
                    "Options:\n"
                    "  -v           \tTurn on verbose mode, display AST.\n"
                    "  -i <filename>\tInput file.\n"
                    "  -o <filename>\tOutput file.\n"
                    "  -h           \tPrint this help.\n";
void SetOpts(int argc, char *argv[]) {
  if (argc < 2) {
    notify(Usage);
  }
  int opt;
  const char *Filename = NULL;
  while ((opt = getopt(argc, argv, OptFmt)) != -1) {
    switch (opt) {
    case 'v':
      ShowAST = true;
      break;
    case 'i':
      Filename = optarg;
      yyin = fopen(optarg, "r");
      if (yyin == NULL) {
        RAISE(InFileOpenErr);
      }
      break;
    case 'o':
      fmt.fileLoc = optarg;
      fmt.out = fopen(optarg, "w");
      if (fmt.out == NULL) {
        RAISE(OutFileOpenErr);
      }
      break;
    default:
    case 'h':
      notify(Usage);
    }
  }
  if (Filename == NULL || fmt.out == NULL) {
    notify(Usage);
  }
}