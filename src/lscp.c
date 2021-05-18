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
Fmt ASTDisplayFmt;
Fmt SymbolTableDisplayFmt;
_Bool ShowAST;         // print AST
_Bool ShowSymbolTable; // print Symbol Table
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
      fclose(SymbolTableDisplayFmt.out);
    }
  }

  fclose(yyin);

  yylex_destroy();
  ArenaClear();
  AtomReset();
  return ret;
}

const char *OptFmt = ":hv:i:s:";

const char *Usage = "Usage: lscp [-vh] -i <filename> -o <filename>\n"
                    "Options:\n"
                    "  -v <filename>\tTurn on verbose mode, display AST.\n"
                    "  -i <filename>\tInput file.\n"
                    "  -s <filename>\tShow symbol table.\n"
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
      ASTDisplayFmt.fileLoc = optarg;
      ASTDisplayFmt.out = fopen(optarg, "w");
      if (ASTDisplayFmt.out == NULL) {
        RAISE(OutFileOpenErr);
      }
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
      SymbolTableDisplayFmt.out = fopen(optarg, "w");
      if (SymbolTableDisplayFmt.out == NULL) {
        RAISE(OutFileOpenErr);
      }
      break;
    default:
    case 'h':
      notify(Usage);
    }
  }
  if (Filename == NULL) {
    notify(Usage);
  }
  if (ShowAST && ASTDisplayFmt.out == NULL) {
    notify(Usage);
  }
  if (ShowSymbolTable && SymbolTableDisplayFmt.out == NULL) {
    notify(Usage);
  }
  if (ShowSymbolTable && !ShowAST) {
    notify(Usage);
  }
}