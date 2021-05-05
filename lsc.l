Digit           [0-9]
NonzeroDigit    [1-9]
HexDigit        [0-9a-fA-F]
Exp             [Ee][+-]?{Digit}+
BoolLiteral     (true|false)
NonDigit        [a-zA-Z_]
Blank           [ \n\t\f\v\r]
Escape          (\\(["\\ntfvr]))

%option noyywrap yylineno

%{
#include "def.h"
#include "opt.h"

void VerboseInfo(TokenType tt);
%}

%%
{Blank}+                            {/* skip */}

"//".*                              {VerboseInfo(TK_T_COMMENT); /* skip comments */}

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

"0"|{NonzeroDigit}{Digit}*          {return ICONSTANT;}
"0"[xX]{HexDigit}+                  {return ICONSTANT;}

{Digit}*"."{Digit}+{Exp}?           {return FCONSTANT;}
{Digit}+"."{Exp}?                   {return FCONSTANT;}

\"([^"\\\n]|{Escape})*\"            {return SCONSTANT;}

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
";"                                 {return SEMECOLON;}
","                                 {return COMMA;}

/* {Digit}+{NonDigit}+                 {VerboseInfo(TK_T_UNKNOWN);} */
.                                   {VerboseInfo(TK_T_UNKNOWN);/* skip unknown chars */}
%%

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf(Usage, argv[0]);
        exit(-1);
    }
    SetOpts(argc, argv);
    if (Filename == NULL) {
        printf(Usage, argv[0]);
        exit(-1);
    }
    yyin = fopen(Filename, "r");
    if (yyin == NULL) {
        printf("cannot open input file %s\n", Filename);
        exit(-1);
    }
    if (OutputFile == NULL)
        OutputFile = stdout;
    int t;
    while ((t = yylex())) {
        if (t <= BCONSTANT) {
            VerboseInfo(TK_T_KEYWORD);
        } else if (t == IDENTIFIER) {
            VerboseInfo(TK_T_IDENTIFIER);
        } else if (t == ICONSTANT) {
            VerboseInfo(TK_T_INTEGER_CONSTANT);
        } else if (t == FCONSTANT) {
            VerboseInfo(TK_T_FLOAT_CONSTANT);
        } else if (t == SCONSTANT) {
            VerboseInfo(TK_T_STRING_CONSTANT);
        } else if (t <= ASSIGN) {
            VerboseInfo(TK_T_OPERATOR);
        } else {
            VerboseInfo(TK_T_DELIMITER);
        }
    }
    return 0;
}

void VerboseInfo(TokenType tt) {
    if (Verbose) {
        fprintf(OutputFile, "Line %3d: %16s: %s\n", yylineno, TokenTypeToString(tt), yytext);
    }
}