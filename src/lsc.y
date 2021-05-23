%define parse.error verbose

%code requires{
    #include "ast.h"
}

%code top{
    #include <stdio.h>
    #include "ast.h"
    #include "../lib/llsc.h"
    void yyerror(const char *s);
    int yylex(void);
    int yylineno;

    const char* yytext;
    AST t;
}

%union {
    ASTNode* node;
    // need a pointer to symbol table
    const char* str;
}

%token VOID "void" I32 "i32" F32 "f32" STRING "string" BOOL "bool"
%token IF "if" ELSE "else" FOR "for" RETURN "return" BREAK "break" CONTINUE "continue" 
%token PRINT "print" SCAN "scan"
%token PLUS "+" MINUS "-" INC "++" DEC "--" BNOT "~" NOT "!" MUL "*" DIV "/" MOD "%"
%token LT "<" GT ">" LE "<=" GE ">=" EQ "==" NE "!=" SL "<<" SR ">>" 
%token BAND "&" BOR "|" BXOR "^" AND "&&" OR "||" ASSIGN "=" COMMA ","
%token LB "(" RB ")" LSB "[" RSB "]" LCB "{" RCB "}" SEMICOLON ";" 

%token BCONSTANT "Bool Constant" IDENTIFIER "Identifier"
%token ICONSTANT "Integer Constant" FCONSTANT "Float Constant" SCONSTANT "String Constant"
/* %token COMMENT UNKNOWN */

%type <str> array_length
%type <str> type_specifiers
%type <node> program global_list global_declaration_or_definition declaration 
%type <node> init_declarator_list init_declarator declarator 
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

program : global_list {
    t.root = $$;
};

global_list
    : global_declaration_or_definition {
        $$ = NewASTNode(GlobalDeclOrDefList, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| global_list global_declaration_or_definition {
        $$ = NewASTNode(GlobalDeclOrDefList, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
    };

global_declaration_or_definition 
    : declaration 
    | function_definition
    ;

declaration
    : type_specifiers init_declarator_list SEMICOLON {
        $$ = NewASTNode(Declaration, yylineno);
        $$->attr[0] = NewASTNode(TypeSpecifier, yylineno);
        ((ASTNode*)($$->attr[0]))->attr[0] = (void*)$1;
        $$->attr[1] = $2;
        SpecifyType($2, $1);
    }| type_specifiers identifier LB parameter_type_list RB SEMICOLON {
        $$ = NewASTNode(FunctionDecl, yylineno);
        $$->attr[0] = NewASTNode(TypeSpecifier, yylineno);
        ((ASTNode*)($$->attr[0]))->attr[0] = (void*)$1;
        $$->attr[1] = $2;
        $$->attr[2] = $4;
    };

identifier
    : IDENTIFIER {
        $$ = NewASTNode(Identifier, yylineno);
        $$->attr[0] = (void*)AtomString(yytext);
    };

type_specifiers
    : VOID {
        $$ = (void*)AtomString("void");
    }| I32 {
        $$ = (void*)AtomString("i32");
    }| F32 {
        $$ = (void*)AtomString("f32");
    }| STRING {
        $$ = (void*)AtomString("string");
    }| BOOL {
        $$ = (void*)AtomString("bool");
    }| type_specifiers LSB array_length RSB {
        $$ = (void*)AtomConcatenate($1, "[", $3, "]", NULL);
    }

init_declarator_list
    : init_declarator {
        $$ = NewASTNode(DeclaratorList, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| init_declarator_list COMMA init_declarator {
        $$ = NewASTNode(DeclaratorList, yylineno);
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
        $$ = NewASTNode(Declarator, yylineno);
        ASTNode* ts = NewASTNode(TypeSpecifier, yylineno);
        ts->attr[0] = NULL;
        $$->attr[0] = ts;
        $$->attr[1] = $1;
        $$->attr[2] = NULL;
    }| declarator LSB array_length RSB {
        $$ = $1;
        ASTNode* ts = (ASTNode*)($$->attr[0]);
        if (ts->attr[0] == NULL) {
            ts->attr[0] = (void*)AtomConcatenate("[", $3, "]", NULL);
        } else {
            const char* t = (const char*)(ts->attr[0]);
            ts->attr[0] = (void*)AtomConcatenate(t, "[", $3, "]", NULL);
        }
    };

array_length
    : ICONSTANT {
        $$ = (void*)AtomString(yytext);
    };

initializer
    : assignment_expression {
        $$ = NewASTNode(Initializer, yylineno);
        $$->attr[0] = $1;
    }| LCB initializer_list RCB {
        $$ = NewASTNode(ArrayInitializer, yylineno);
        $$->attr[0] = $2;
    }| LCB initializer_list COMMA RCB {
        $$ = NewASTNode(ArrayInitializer, yylineno);
        $$->attr[0] = $2;
    };

initializer_list
    : initializer {
        $$ = NewASTNode(InitializerList, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| initializer_list COMMA initializer {
        $$ = NewASTNode(InitializerList, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

parameter_type_list
    : type_specifiers {
        $$ = NewASTNode(ParameterTypeList, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = NewASTNode(TypeSpecifier, yylineno);
        ((ASTNode*)($$->attr[1]))->attr[0] = (void*)$1;
    }| parameter_type_list COMMA type_specifiers {
        $$ = NewASTNode(ParameterTypeList, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = NewASTNode(TypeSpecifier, yylineno);
        ((ASTNode*)($$->attr[1]))->attr[0] = (void*)$3;
    };

function_definition
    : type_specifiers identifier LB RB compound_statement {
        $$ = NewASTNode(FunctionDef, yylineno);
        $$->attr[0] = NewASTNode(TypeSpecifier, yylineno);
        ((ASTNode*)($$->attr[0]))->attr[0] = (void*)$1;
        $$->attr[1] = $2;
        $$->attr[2] = NULL;
        $$->attr[3] = $5;
    }| type_specifiers identifier LB parameter_declarator_list RB compound_statement {
        $$ = NewASTNode(FunctionDef, yylineno);
        $$->attr[0] = NewASTNode(TypeSpecifier, yylineno);
        ((ASTNode*)($$->attr[0]))->attr[0] = (void*)$1;
        $$->attr[1] = $2;
        $$->attr[2] = $4;
        $$->attr[3] = $6;
    };

parameter_declarator_list
    : parameter_declarator {
        $$ = NewASTNode(ParameterDeclList, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| parameter_declarator_list COMMA parameter_declarator {
        $$ = NewASTNode(ParameterDeclList, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

parameter_declarator
    :type_specifiers declarator {
        $$ = $2;
        ASTNode* ts = (ASTNode*)($$->attr[0]);
        const char* p = (const char*)(ts->attr[0]);
        if (p != NULL) {
            ts->attr[0] = (void*)AtomConcatenate($1, p, NULL);
        } else {
            ts->attr[0] = (void*)$1;
        }
    };

compound_statement
    : LCB RCB {
        $$ = NewASTNode(CompoundStm, yylineno);
        $$->attr[0] = $$->attr[1] = NULL;
    }| LCB statement_list RCB {
        $$ = NewASTNode(CompoundStm, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = $2;
    }| LCB declaration_list RCB {
        $$ = NewASTNode(CompoundStm, yylineno);
        $$->attr[0] = $2;
        $$->attr[1] = NULL;
    }| LCB declaration_list statement_list RCB {
        $$ = NewASTNode(CompoundStm, yylineno);
        $$->attr[0] = $2;
        $$->attr[1] = $3;
    };

statement_list
    : statement {
        $$ = NewASTNode(StatementList, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| statement_list statement {
        $$ = NewASTNode(StatementList, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
    };

declaration_list
    : declaration {
        $$ = NewASTNode(DeclarationList, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| declaration_list declaration {
        $$ = NewASTNode(DeclarationList, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = $2;
    };

statement
    : compound_statement 
    | expression_statement 
    | jump_statement 
    | selection_statement 
    | loop_statement 
    | io_statement
    ;

expression_statement 
    : SEMICOLON {
        $$ = NewASTNode(ExpressionStm, yylineno);
        $$->attr[0] = NULL;
    }| expression SEMICOLON {
        $$ = NewASTNode(ExpressionStm, yylineno);
        $$->attr[0] = $1;
    };

jump_statement
    : CONTINUE SEMICOLON {
        $$ = NewASTNode(JumpStm, yylineno);
        $$->attr[0] = (void*)AtomString("continue");
        $$->attr[1] = NULL;
    }| BREAK SEMICOLON {
        $$ = NewASTNode(JumpStm, yylineno);
        $$->attr[0] = (void*)AtomString("break");
        $$->attr[1] = NULL;
    }| RETURN SEMICOLON {
        $$ = NewASTNode(JumpStm, yylineno);
        $$->attr[0] = (void*)AtomString("return");
        $$->attr[1] = NULL;
    }| RETURN expression SEMICOLON {
        $$ = NewASTNode(JumpStm, yylineno);
        $$->attr[0] = (void*)AtomString("return");
        $$->attr[1] = $2;
    };

selection_statement
    : IF LB expression RB compound_statement {
        $$ = NewASTNode(SelectionStm, yylineno);
        $$->attr[0] = $3;
        $$->attr[1] = $5;
        $$->attr[2] = NULL;
    }| IF LB expression RB compound_statement ELSE compound_statement {
        $$ = NewASTNode(SelectionStm, yylineno);
        $$->attr[0] = $3;
        $$->attr[1] = $5;
        $$->attr[2] = $7;
    }| IF LB expression RB compound_statement ELSE selection_statement {
        $$ = NewASTNode(SelectionStm, yylineno);
        $$->attr[0] = $3;
        $$->attr[1] = $5;
        $$->attr[2] = $7;
    };

loop_statement
    : FOR LB expression_statement expression_statement RB compound_statement {
        $$ = NewASTNode(LoopStm, yylineno);
        $$->attr[0] = $3;
        $$->attr[1] = $4;
        $$->attr[2] = NULL;
        $$->attr[3] = $6;
    }| FOR LB expression_statement expression_statement expression RB compound_statement {
        $$ = NewASTNode(LoopStm, yylineno);
        $$->attr[0] = $3;
        $$->attr[1] = $4;
        $$->attr[2] = $5;
        $$->attr[3] = $7;
    };

io_statement
    : PRINT LB argument_list RB SEMICOLON {
        $$ = NewASTNode(IOStm, yylineno);
        $$->attr[0] = (void*)AtomString("print");
        $$->attr[1] = $3;
    }| SCAN LB argument_list RB SEMICOLON {
        $$ = NewASTNode(IOStm, yylineno);
        $$->attr[0] = (void*)AtomString("scan");
        $$->attr[1] = $3;
    };

expression 
    : assignment_expression                     
    | expression COMMA assignment_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString(",");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

assignment_expression
    : logical_or_expression
    | unary_expression ASSIGN assignment_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("=");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

unary_expression
    : postfix_expression
    | INC unary_expression {
        $$ = NewASTNode(UnaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("++");
        $$->attr[1] = $2;
    }| DEC unary_expression {
        $$ = NewASTNode(UnaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("--");
        $$->attr[1] = $2;
    }| PLUS unary_expression {
        $$ = NewASTNode(UnaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("+");
        $$->attr[1] = $2;
    }| MINUS unary_expression {
        $$ = NewASTNode(UnaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("-");
        $$->attr[1] = $2;
    }| BNOT unary_expression {
        $$ = NewASTNode(UnaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("~");
        $$->attr[1] = $2;
    }| NOT unary_expression {
        $$ = NewASTNode(UnaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("!");
        $$->attr[1] = $2;
    };

postfix_expression
    : primary_expression
    | postfix_expression LSB expression RSB {
        $$ = NewASTNode(PostfixExpr, yylineno);
        $$->attr[0] = (void*)AtomString("[]");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| primary_expression LB RB {
        $$ = NewASTNode(FunctionCall, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = NULL;
    }| primary_expression LB argument_list RB {
        $$ = NewASTNode(FunctionCall, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

primary_expression
    : IDENTIFIER {
        $$ = NewASTNode(Identifier, yylineno);
        $$->attr[0] = (void*)AtomString(yytext);
    }| BCONSTANT {
        $$ = NewASTNode(BoolConst, yylineno);
        $$->attr[0] = (void*)AtomString(yytext);
    }| ICONSTANT {
        $$ = NewASTNode(IntConst, yylineno);
        $$->attr[0] = (void*)AtomString(yytext);
    }| FCONSTANT {
        $$ = NewASTNode(FloatConst, yylineno);
        $$->attr[0] = (void*)AtomString(yytext);
    }| SCONSTANT {
        $$ = NewASTNode(StrConst, yylineno);
        $$->attr[0] = (void*)AtomString(yytext);
    }| LB expression RB {
        $$ = $2;
    };

argument_list
    : assignment_expression {
        $$ = NewASTNode(ArguementList, yylineno);
        $$->attr[0] = NULL;
        $$->attr[1] = $1;
    }| argument_list COMMA assignment_expression {
        $$ = NewASTNode(ArguementList, yylineno);
        $$->attr[0] = $1;
        $$->attr[1] = $3;
    };

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR logical_and_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("||");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

logical_and_expression
    : bitwise_or_expression
    | logical_and_expression AND bitwise_or_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("&&");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

bitwise_or_expression
    : bitwise_xor_expression
    | bitwise_or_expression BOR bitwise_xor_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("|");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

bitwise_xor_expression
    : bitwise_and_expression
    | bitwise_xor_expression BXOR bitwise_and_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("^");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

bitwise_and_expression
    : equality_expression
    | bitwise_and_expression BAND equality_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("&");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

equality_expression
    : relational_expression
    | equality_expression EQ relational_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("==");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| equality_expression NE relational_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("!=");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

relational_expression
    : shift_expression
    | relational_expression LT shift_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("<");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| relational_expression GT shift_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString(">");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| relational_expression LE shift_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("<=");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| relational_expression GE shift_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString(">=");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

shift_expression
    : additive_expression
    | shift_expression SL additive_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("<<");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| shift_expression SR additive_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString(">>");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

additive_expression
    : multiplicative_expression
    | additive_expression PLUS multiplicative_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("+");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| additive_expression MINUS multiplicative_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("-");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };

multiplicative_expression
    : unary_expression
    | multiplicative_expression MUL unary_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("*");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| multiplicative_expression DIV unary_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("/");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    }| multiplicative_expression MOD unary_expression {
        $$ = NewASTNode(BinaryExpr, yylineno);
        $$->attr[0] = (void*)AtomString("%");
        $$->attr[1] = $1;
        $$->attr[2] = $3;
    };
%%

extern int yylineno;
void yyerror(const char *s) {
    fprintf(stderr, "Line %d: %s\n", yylineno, s);
}
