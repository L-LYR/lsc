%define parse.error verbose

%code requires{
    #include "ast.h"
}

%code top{
    #include <stdio.h>
    #include "ast.h"
    #include "panic.h"
    #include "text.h"
    void yyerror(const char *s);
    int yylex(void);
    int yylex_destroy(void);

    const char* yytext;
    AST t;
    Fmt fmt;
}

%union {
    ASTNode* node;
    // need a pointer to symbol table
    const char* str;
}

%token VOID "void" I32 "i32" F32 "f32" STRING "string" BOOL "bool"
%token IF "if" ELSE "else" FOR "for" RETURN "return" BREAK "break" CONTINUE "continue" 
%token PRINT "print" SCAN "scan"
%token BCONSTANT "Bool Constant" IDENTIFIER "Identifier"
%token ICONSTANT "Integer Constant" FCONSTANT "Float Constant" SCONSTANT "String Constant"
%token PLUS "+" MINUS "-" INC "++" DEC "--" BNOT "~" NOT "!" MUL "*" DIV "/" MOD "%"
%token LT "<" GT ">" LE "<=" GE ">=" EQ "==" NE "!=" SL "<<" SR ">>" 
%token BAND "&" BOR "|" BXOR "^" AND "&&" OR "||" ASSIGN "=" COMMA ","
%token LB "(" RB ")" LSB "[" RSB "]" LCB "{" RCB "}" SEMICOLON ";" 
/* %token COMMENT UNKNOWN */

%type <str> array_length
%type <node> program global_list global_declaration_or_definition declaration 
%type <node> type_specifiers init_declarator_list init_declarator declarator 
%type <node> parameter_type_list identifier initializer initializer_list
%type <node> function_definition parameter_declarator_list parameter_declarator
%type <node> compound_statement loop_statement selection_statement expression_statement io_statement
%type <node> jump_statement statement_list declaration_list statement
%type <node> expression assignment_expression unary_expression postfix_expression argument_list
%type <node> logical_and_expression logical_or_expression bitwise_and_expression bitwise_or_expression
%type <node> bitwise_xor_expression equality_expression relational_expression shift_expression
%type <node> additive_expression multiplicative_expression primary_expression

%start program

%%

program : global_list {t.root = $$;};

global_list
    : global_declaration_or_definition {
        $$ = NewASTNode(GlobalDeclOrDefList);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| global_list global_declaration_or_definition {
        $$ = NewASTNode(GlobalDeclOrDefList);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
    };

global_declaration_or_definition 
    : declaration 
    | function_definition
    ;

declaration
    : type_specifiers init_declarator_list SEMICOLON {
        $$ = NewASTNode(Declaration);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
        SpecifyType($2, $1->attr[0]);
    }| type_specifiers identifier LB parameter_type_list RB SEMICOLON {
        $$ = NewASTNode(FunctionDecl);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
        $$->attr[2] = $4;
    };

identifier
    : IDENTIFIER {
        $$ = NewASTNode(Identifier);
        $$->attr[0] = CopyStr(yytext);
    };

type_specifiers
    : VOID {
        $$ = NewASTNode(TypeSpecifier);
        $$->attr[0] = CopyStr("void");
    }| I32 {
        $$ = NewASTNode(TypeSpecifier);
        $$->attr[0] = CopyStr("i32");
    }| F32 {
        $$ = NewASTNode(TypeSpecifier);
        $$->attr[0] = CopyStr("f32");
    }| STRING {
        $$ = NewASTNode(TypeSpecifier);
        $$->attr[0] = CopyStr("string");
    }| BOOL {
        $$ = NewASTNode(TypeSpecifier);
        $$->attr[0] = CopyStr("bool");
    }| type_specifiers LSB array_length RSB {
        $$ = NewASTNode(TypeSpecifier);
        $$->attr[0] = ConcatenateStr($1->attr[0], "[", $3, "]", NULL);
        free((void*)($1->attr[0]));
        free($1);
        free((void*)$3);
    }

init_declarator_list
    : init_declarator {
        $$ = NewASTNode(DeclaratorList);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| init_declarator_list COMMA init_declarator {
        $$ = NewASTNode(DeclaratorList);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

init_declarator
    : declarator {
        $$ = $1;
    }| declarator ASSIGN initializer {
        $$ = $1;
        $$->attr[2] = $3;
    };

declarator
    : identifier {
        $$ = NewASTNode(Declarator);
        ASTNode* ts = NewASTNode(TypeSpecifier);
        ts->attr[0] = NULL;
        $$->attr[0] = ts;
        $$->attr[1] = $1;
        $$->attr[2] = NULL;
    }| declarator LSB array_length RSB {
        $$ = $1;
        ASTNode* ts = (ASTNode*)($$->attr[0]);
        if (ts->attr[0] == NULL) {
            ts->attr[0] = ConcatenateStr("[", $3, "]", NULL);
            free((void*)$3);
        } else {
            const char* t = (const char*)(ts->attr[0]);
            ts->attr[0] = ConcatenateStr(t, "[", $3, "]", NULL);
            free((void*)t);
            free((void*)$3);
        }
    };

array_length
    : ICONSTANT {
        $$ = CopyStr(yytext);
    };

initializer
    : assignment_expression {
        $$ = NewASTNode(Initializer);
        $$->attr[0] = $1;
    }| LCB initializer_list RCB {
        $$ = NewASTNode(ArrayInitializer);
        $$->attr[0] = $2;
    }| LCB initializer_list COMMA RCB {
        $$ = NewASTNode(ArrayInitializer);
        $$->attr[0] = $2;
    };

initializer_list
    : initializer {
        $$ = NewASTNode(InitializerList);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| initializer_list COMMA initializer {
        $$ = NewASTNode(InitializerList);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

parameter_type_list
    : type_specifiers {
        $$ = NewASTNode(ParameterTypeList);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| parameter_type_list COMMA type_specifiers {
        $$ = NewASTNode(ParameterTypeList);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

function_definition
    : type_specifiers identifier LB RB compound_statement {
        $$ = NewASTNode(FunctionDef);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
        $$->attr[2] = NULL;
        $$->attr[3] = $5;
    }| type_specifiers identifier LB parameter_declarator_list RB compound_statement {
        $$ = NewASTNode(FunctionDef);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
        $$->attr[2] = $4;
        $$->attr[3] = $6;
    };

parameter_declarator_list
    : parameter_declarator {
        $$ = NewASTNode(ParameterDeclList);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| parameter_declarator_list COMMA parameter_declarator {
        $$ = NewASTNode(ParameterDeclList);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

parameter_declarator
    :type_specifiers declarator {
        $$ = NewASTNode(ParameterDecl);
        ASTNode* ts = (ASTNode*)($2->attr[0]);
        const char* p = (const char*)(ts->attr[0]);
        if (p != NULL) {
            const char* t = $1->attr[0];
            $1->attr[0] = ConcatenateStr(t, p, NULL);
            free((void*)t);
            free((void*)p);
        }
        $$->attr[0] = $1;
        $$->attr[1] = $2->attr[1];
        free(ts);
        free($2);
    };

compound_statement
    : LCB RCB {
        $$ = NewASTNode(CompoundStm);
        $$->attr[0] = $$->attr[1] = NULL;
    }| LCB statement_list RCB {
        $$ = NewASTNode(CompoundStm);
        $$->attr[0] = NULL;
        $$->attr[1] = $2;
    }| LCB declaration_list RCB {
        $$ = NewASTNode(CompoundStm);
        $$->attr[0] = $2;
        $$->attr[1] = NULL;
    }| LCB declaration_list statement_list RCB {
        $$ = NewASTNode(CompoundStm);
        $$->attr[0] = $2;
        $$->attr[1] = $3;
    };

statement_list
    : statement {
        $$ = NewASTNode(StatementList);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| statement_list statement {
        $$ = NewASTNode(StatementList);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
    };

declaration_list
    : declaration {
        $$ = NewASTNode(DeclarationList);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| declaration_list declaration {
        $$ = NewASTNode(DeclarationList);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
    };

statement
    : compound_statement {
        $$ = $1;
    }| expression_statement {
        $$ = $1;
    }| jump_statement {
        $$ = $1;
    }| selection_statement {
        $$ = $1;
    }| loop_statement {
        $$ = $1;
    }| io_statement {
        $$ = $1;
    };

expression_statement 
    : SEMICOLON {
        $$ = NewASTNode(ExpressionStm);
        $$->attr[0] = NULL;
    }| expression SEMICOLON {
        $$ = NewASTNode(ExpressionStm);
        $$->attr[0] = $1;
    };

jump_statement
    : CONTINUE SEMICOLON {
        $$ = NewASTNode(JumpStm);
        $$->attr[0] = "continue";
        $$->attr[1] = NULL;
    }| BREAK SEMICOLON {
        $$ = NewASTNode(JumpStm);
        $$->attr[0] = "break";
        $$->attr[1] = NULL;
    }| RETURN SEMICOLON {
        $$ = NewASTNode(JumpStm);
        $$->attr[0] = "return";
        $$->attr[1] = NULL;
    }| RETURN expression SEMICOLON {
        $$ = NewASTNode(JumpStm);
        $$->attr[0] = "return";
        $$->attr[1] = $2;
    };

selection_statement
    : IF LB expression RB compound_statement {
        $$ = NewASTNode(SelectionStm);
        $$->attr[0] = $3;
        $$->attr[1] = $5;
        $$->attr[2] = NULL;
    }| IF LB expression RB compound_statement ELSE compound_statement {
        $$ = NewASTNode(SelectionStm);
        $$->attr[0] = $3;
        $$->attr[1] = $5;
        $$->attr[2] = $7;
    }| IF LB expression RB compound_statement ELSE selection_statement {
        $$ = NewASTNode(SelectionStm);
        $$->attr[0] = $3;
        $$->attr[1] = $5;
        $$->attr[2] = $7;
    };

loop_statement
    : FOR LB expression_statement expression_statement RB compound_statement {
        $$ = NewASTNode(LoopStm);
        $$->attr[0] = $3;
        $$->attr[1] = $4;
        $$->attr[2] = NULL;
        $$->attr[3] = $6;
    }| FOR LB expression_statement expression_statement expression RB compound_statement {
        $$ = NewASTNode(LoopStm);
        $$->attr[0] = $3;
        $$->attr[1] = $4;
        $$->attr[2] = $5;
        $$->attr[3] = $7;
    };

io_statement
    : PRINT LB argument_list RB SEMICOLON {
        $$ = NewASTNode(IOStm);
        $$->attr[0] = "print";
        $$->attr[1] = $3;
    }| SCAN LB argument_list RB SEMICOLON {
        $$ = NewASTNode(IOStm);
        $$->attr[0] = "scan";
        $$->attr[1] = $3;
    };

expression 
    : assignment_expression                     
    | expression COMMA assignment_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = ",";
        $$->attr[2] = $3;
    };

assignment_expression
    : logical_or_expression
    | unary_expression ASSIGN assignment_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "=";
        $$->attr[2] = $3;
    };

unary_expression
    : postfix_expression
    | INC unary_expression {
        $$ = NewASTNode(UnaryExpr);
        $$->attr[0] = "++";
        $$->attr[1] = $2;
    }| DEC unary_expression {
        $$ = NewASTNode(UnaryExpr);
        $$->attr[0] = "--";
        $$->attr[1] = $2;
    }| PLUS unary_expression {
        $$ = NewASTNode(UnaryExpr);
        $$->attr[0] = "+";
        $$->attr[1] = $2;
    }| MINUS unary_expression {
        $$ = NewASTNode(UnaryExpr);
        $$->attr[0] = "-";
        $$->attr[1] = $2;
    }| BNOT unary_expression {
        $$ = NewASTNode(UnaryExpr);
        $$->attr[0] = "~";
        $$->attr[1] = $2;
    }| NOT unary_expression {
        $$ = NewASTNode(UnaryExpr);
        $$->attr[0] = "!";
        $$->attr[1] = $2;
    };

postfix_expression
    : primary_expression
    | postfix_expression LSB expression RSB {
        $$ = NewASTNode(PostfixExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "[]";
        $$->attr[2] = $3;
    }| primary_expression LB RB {
        $$ = NewASTNode(FunctionCall);
        $$->attr[0] = $1;
        $$->attr[1] = NULL;
    }| primary_expression LB argument_list RB {
        $$ = NewASTNode(FunctionCall);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

primary_expression
    : IDENTIFIER {
        $$ = NewASTNode(Identifier);
        $$->attr[0] = CopyStr(yytext);
    }| BCONSTANT {
        $$ = NewASTNode(BoolConst);
        $$->attr[0] = CopyStr(yytext);
    }| ICONSTANT {
        $$ = NewASTNode(IntConst);
        $$->attr[0] = CopyStr(yytext);
    }| FCONSTANT {
        $$ = NewASTNode(FloatConst);
        $$->attr[0] = CopyStr(yytext);
    }| SCONSTANT {
        $$ = NewASTNode(StrConst);
        $$->attr[0] = CopyStr(yytext);
    }| LB expression RB {
        $$ = $2;
    };

argument_list
    : assignment_expression {
        $$ = NewASTNode(ArguementList);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| argument_list COMMA assignment_expression {
        $$ = NewASTNode(ArguementList);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR logical_and_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "||";
        $$->attr[2] = $3;
    };

logical_and_expression
    : bitwise_or_expression
    | logical_and_expression AND bitwise_or_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "&&";
        $$->attr[2] = $3;
    };

bitwise_or_expression
    : bitwise_xor_expression
    | bitwise_or_expression BOR bitwise_xor_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "|";
        $$->attr[2] = $3;
    };

bitwise_xor_expression
    : bitwise_and_expression
    | bitwise_xor_expression BXOR bitwise_and_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "^";
        $$->attr[2] = $3;
    };

bitwise_and_expression
    : equality_expression
    | bitwise_and_expression BAND equality_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "&";
        $$->attr[2] = $3;
    };

equality_expression
    : relational_expression
    | equality_expression EQ relational_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "==";
        $$->attr[2] = $3;
    }| equality_expression NE relational_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "!=";
        $$->attr[2] = $3;
    };

relational_expression
    : shift_expression
    | relational_expression LT shift_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "<";
        $$->attr[2] = $3;
    }| relational_expression GT shift_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = ">";
        $$->attr[2] = $3;
    }| relational_expression LE shift_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "<=";
        $$->attr[2] = $3;
    }| relational_expression GE shift_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = ">=";
        $$->attr[2] = $3;
    };

shift_expression
    : additive_expression
    | shift_expression SL additive_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "<<";
        $$->attr[2] = $3;
    }| shift_expression SR additive_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = ">>";
        $$->attr[2] = $3;
    };

additive_expression
    : multiplicative_expression
    | additive_expression PLUS multiplicative_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "+";
        $$->attr[2] = $3;
    }| additive_expression MINUS multiplicative_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "-";
        $$->attr[2] = $3;
    };

multiplicative_expression
    : unary_expression
    | multiplicative_expression MUL unary_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "*";
        $$->attr[2] = $3;
    }| multiplicative_expression DIV unary_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "/";
        $$->attr[2] = $3;
    }| multiplicative_expression MOD unary_expression {
        $$ = NewASTNode(BinaryExpr);
        $$->attr[0] = $1;
        $$->attr[1] = "%";
        $$->attr[2] = $3;
    };
%%

extern int yylineno;
void yyerror(const char *s) {
    fprintf(stderr, "Line %d: %s\n", yylineno, s);
}

int main(void) {
    int ret;
    if ((ret = yyparse()) != 0) {
        return ret;
    }

    fmt.out = fopen("./res/test.ast", "w");
    if (fmt.out == NULL) {
        PANIC("cannot open output file!");
    }

    DisplayAST(&t, &fmt);

    fclose(fmt.out);
    FreeAST(&t);
    yylex_destroy();
    return 0;
}