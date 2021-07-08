Digit           [0-9]
NonzeroDigit    [1-9]
DecDigits       ({NonzeroDigit}{Digit}*|[0])
HexDigit        [0-9a-fA-F]
Exp             [Ee][+-]?{Digit}+
BoolLiteral     (true|false)
NonDigit        [a-zA-Z_]
Blank           [ \n\t\f\v\r]
Escape          (\\(["\\ntfvr]))

%option noyywrap yylineno

%{
#include "lsc.tab.h"
#include <stdio.h>
#include <stdbool.h>

extern _Bool Verbose;
_Bool Verbose = false; // this can only be set in lscl.

%}

%%
{Blank}+                            {/* skip */}

"//".*                              {
    /* skip comments */
    if (Verbose) {
        fprintf(yyout, "Line %3d: %16s: %s\n", yylineno, "Comment", yytext);
    }
}
\"(\\.|[^\\"])*\"            {return SCONSTANT;}
"void"                              {return VOID;}
"i32"                               {return I32;}
"f32"                               {return F32;}
"string"                            {return STRING;}
"bool"                              {return BOOL;}
"if"                                {return IF;}
"else"                              {return ELSE;}
"for"                               {return FOR;}
"return"                            {return RETURN;}
"break"                             {return BREAK;}
"continue"                          {return CONTINUE;}
"print"                             {return PRINT;}
"scan"                              {return SCAN;}

{BoolLiteral}                       {return BCONSTANT;}

{NonDigit}({Digit}|{NonDigit})*     {return IDENTIFIER;}

{DecDigits}                         {return ICONSTANT;}
"0"[xX]{HexDigit}+                  {return ICONSTANT;}

{DecDigits}{Exp}                    {return FCONSTANT;}
{DecDigits}"."{Digit}*{Exp}?        {return FCONSTANT;}
"."{Digit}+{Exp}?                   {return FCONSTANT;}



"+"                                 {return PLUS;}
"-"                                 {return MINUS;}
"++"                                {return INC;}
"--"                                {return DEC;}
"~"                                 {return BNOT;}
"!"                                 {return NOT;}
"*"                                 {return MUL;}
"/"                                 {return DIV;}
"%"                                 {return MOD;}
"<"                                 {return LT;}
">"                                 {return GT;}
"<="                                {return LE;}
">="                                {return GE;}
"=="                                {return EQ;}
"!="                                {return NE;}
"<<"                                {return SL;}
">>"                                {return SR;}
"&"                                 {return BAND;}
"|"                                 {return BOR;}
"^"                                 {return BXOR;}
"&&"                                {return AND;}
"||"                                {return OR;}
"="                                 {return ASSIGN;}

"("                                 {return LB;}
")"                                 {return RB;}
"["                                 {return LSB;}
"]"                                 {return RSB;}
"{"                                 {return LCB;}
"}"                                 {return RCB;}
";"                                 {return SEMICOLON;}
","                                 {return COMMA;}
.                                   {
    /* skip unknown */
    if (Verbose) {
        fprintf(yyout, "Line %3d: %16s: %s\n", yylineno, "Unknown", yytext);
    }
}
%%