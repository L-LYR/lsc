#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/llsc.h"
#include "exception.h"
#include "lsc.tab.h"
#include "symbol_table.h"

// extern
int yylex_destroy(void);
FILE *yyin;

AST t;  // lsc.y

// static
Fmt ASTDisplayFmt;
Fmt SymbolTableDisplayFmt;
_Bool ShowAST;          // print AST
_Bool ShowSymbolTable;  // print Symbol Table
_Bool Pause;            // pause
static void SetOpts(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  SetOpts(argc, argv);

  AtomInit();
  ArenaInit();

  int ret = yyparse();
  if (ret == 0 && ShowAST) {
    DisplayAST(&t, &ASTDisplayFmt);
    if (ShowSymbolTable) {
      SymbolTable st = SymbolTableCreateFromAST(&t);
      DisplaySymbolTable(st, &SymbolTableDisplayFmt);
      FreeSymbolTable(st);
    }
  }

  fclose(yyin);

  yylex_destroy();
  ArenaClear();
  AtomReset();
  return ret;
}

const char *OptFmt = ":hv:i:s:p";

const char *Usage =
    "Usage: lscp [-vh] -i <filename> -o <filename>\n"
    "Options:\n"
    "  -v <filename>\tTurn on verbose mode, display AST.\n"
    "  -i <filename>\tInput file.\n"
    "  -s <filename>\tShow symbol table.\n"
    "  -h           \tPrint this help.\n"
    "  -p           \tPause for awhile when print symbol table.\n";
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
        ASTDisplayFmt.fileLoc = optarg;
        break;
      case 'i':
        Filename = optarg;
        yyin = fopen(optarg, "r");
        if (yyin == NULL) {
          RAISE(InFileOpenErr);
        }
        break;
      case 's':
        ShowSymbolTable = true;
        SymbolTableDisplayFmt.fileLoc = optarg;
        break;
      case 'p':
        Pause = true;
        break;
      default:
      case 'h':
        notify(Usage);
    }
  }
  if (Filename == NULL) {
    notify(Usage);
  }
  if (ShowAST && ASTDisplayFmt.fileLoc == NULL) {
    notify(Usage);
  }
  if (ShowSymbolTable && SymbolTableDisplayFmt.fileLoc == NULL) {
    notify(Usage);
  }
  if (ShowSymbolTable && !ShowAST) {
    notify(Usage);
  }
}