#include "lsc.tab.h"
#include "panic.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  TK_T_KEYWORD,
  TK_T_INTEGER_CONSTANT,
  TK_T_FLOAT_CONSTANT,
  TK_T_BOOL_CONSTANT,
  TK_T_STRING_CONSTANT,
  TK_T_IDENTIFIER,
  TK_T_OPERATOR,
  TK_T_DELIMITER,
  TK_T_COMMENT,
  TK_T_UNKNOWN,
} TokenType;

// extern
int yylex(void);
FILE *yyout;
FILE *yyin;
char *yytext;
int yylineno;
_Bool Verbose; // lsc.l

// static
static void SetOpts(int argc, char *argv[]);
static void VerboseInfo(const char *s);

int main(int argc, char *argv[]) {
  SetOpts(argc, argv);

  int t;
  while ((t = yylex())) {
    // yytokentype is continuous
    if (t <= BCONSTANT) {
      VerboseInfo("Keyword");
    } else if (t == IDENTIFIER) {
      VerboseInfo("Identifier");
    } else if (t == ICONSTANT) {
      VerboseInfo("Integer Constant");
    } else if (t == FCONSTANT) {
      VerboseInfo("Float Constant");
    } else if (t == SCONSTANT) {
      VerboseInfo("String Literal");
    } else if (t <= COMMA) {
      VerboseInfo("Operator");
    } else if (t <= SEMICOLON) {
      VerboseInfo("Delimiter");
    } else {
      PANIC("Unreachable!");
    }
  }
  return 0;
}

const char *OptFmt = ":vho:i:";

const char *Usage = "Usage: lscl [-vh] -i <filename> -o <filename>\n"
                    "Options:\n"
                    "  -v           \tTurn on verbose mode, display the "
                    "lexical analysis results in pairs.\n"
                    "  -i <filename>\tInput file.\n"
                    "  -o <filename>\tOutput file.\n"
                    "  -h           \tPrint this help.\n";
void SetOpts(int argc, char *argv[]) {
  if (argc < 2) {
    PANIC(Usage);
  }
  int opt;
  const char *Filename = NULL;
  while ((opt = getopt(argc, argv, OptFmt)) != -1) {
    switch (opt) {
    case 'v':
      Verbose = true;
      break;
    case 'i':
      Filename = optarg;
      yyin = fopen(optarg, "r");
      if (yyin == NULL) {
        PANIC("cannot open input file!");
      }
      break;
    case 'o':
      yyout = fopen(optarg, "w");
      if (yyout == NULL) {
        PANIC("cannot open output file!");
      }
      break;
    default:
    case 'h':
      PANIC(Usage);
    }
  }
  if (Filename == NULL) {
    PANIC(Usage);
  }
}

void VerboseInfo(const char *s) {
  if (Verbose) {
    fprintf(yyout, "Line %3d: %16s: %s\n", yylineno, s, yytext);
  }
}