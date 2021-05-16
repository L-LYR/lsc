#include "symbol_table.h"

static const char *ReservedSymbolList[] = {
    "void",   "i32",   "f32",      "string", "bool", "if", "else", "for",
    "return", "break", "continue", "print",  "scan", "+",  "-",    "++",
    "--",     "~",     "!",        "*",      "/",    "%", "<",    ">",
    "<=",     ">=",    "==",       "!=",     "<<",   ">>", "&",    "|",
    "^",      "&&",    "||",       "=",      ",",    "(",  ")",    "[",
    "]",      "{",     "}",        ";",      NULL,
};

void AtomInit() { AtomLoad(ReservedSymbolList); }
