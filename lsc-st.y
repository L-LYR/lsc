%define parse.error verbose

%code requires{
    #include "st.h"
}

%code top{
    #include <stdio.h>
    #include "st.h"
    #include "panic.h"
    #include "text.h"
    void yyerror(const char *s);
    int yylex(void);
    int yylex_destroy(void);

    const char* yytext;
    ST t;
    Fmt fmt;
}

%union {
    STNode* node;
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

%type <node> array_length
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
        $$ = NewSTNode(GLOBAL_LIST, 1);
        AddAttrs($$, $1);
    }| global_list global_declaration_or_definition {
        $$ = NewSTNode(GLOBAL_LIST, 2);
        AddAttrs($$, $1, $2);
    };

global_declaration_or_definition 
    : declaration {
        $$ = NewSTNode(GLOBAL_DECLARATION_OR_DEFINITION, 1);
        AddAttrs($$, $1);
    }| function_definition {
        $$ = NewSTNode(GLOBAL_DECLARATION_OR_DEFINITION, 1);
        AddAttrs($$, $1);
    };

declaration
    : type_specifiers init_declarator_list SEMICOLON {
        $$ = NewSTNode(DECLARATION, 3);
        AddAttrs($$, $1, $2, CopyStr("delimiter ;"));
    }| type_specifiers identifier LB parameter_type_list RB SEMICOLON {
        $$ = NewSTNode(DECLARATION, 6);
        AddAttrs($$, $1, $2, CopyStr("delimiter ("), $4, CopyStr("delimiter )"), CopyStr("delimiter ;"));
    };

identifier
    : IDENTIFIER {
        $$ = NewSTNode(ID, 1);
        AddAttrs($$, CopyStr(yytext));
    };

type_specifiers
    : VOID {
        $$ = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs($$, CopyStr("void"));
    }| I32 {
        $$ = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs($$, CopyStr("i32"));
    }| F32 {
        $$ = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs($$, CopyStr("f32"));
    }| STRING {
        $$ = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs($$, CopyStr("string"));
    }| BOOL {
        $$ = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs($$, CopyStr("bool"));
    }| type_specifiers LSB array_length RSB {
        $$ = NewSTNode(TYPE_SPECIFIERS, 1);
        AddAttrs($$, $1, CopyStr("delimiter ["), $3, CopyStr("delimiter ]"));
    }

init_declarator_list
    : init_declarator {
        $$ = NewSTNode(INIT_DECLARATOR_LIST, 1);
        AddAttrs($$, $1);
    }| init_declarator_list COMMA init_declarator {
        $$ = NewSTNode(INIT_DECLARATOR_LIST, 3);
        AddAttrs($$, $1, CopyStr("delimiter ,"), $3);
    };

init_declarator
    : declarator {
        $$ = NewSTNode(INIT_DECLARATOR, 1);
        AddAttrs($$, $1);
    }| declarator ASSIGN initializer {
        $$ = NewSTNode(INIT_DECLARATOR, 3);
        AddAttrs($$, $1, CopyStr("operator ="), $3);
    };

declarator
    : identifier {
        $$ = NewSTNode(DECLARATOR, 1);
        AddAttrs($$, $1);
    }| declarator LSB array_length RSB {
        $$ = NewSTNode(DECLARATOR, 4);
        AddAttrs($$, $1, CopyStr("delimiter ["), $3, CopyStr("delimiter ]"));
    };

array_length
    : ICONSTANT {
        $$ = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs($$, CopyStr(yytext));
    };

initializer
    : assignment_expression {
        $$ = NewSTNode(INITIALIZER, 1);
        AddAttrs($$, $1);
    }| LCB initializer_list RCB {
        $$ = NewSTNode(INITIALIZER, 3);
        AddAttrs($$, CopyStr("delimiter ["), $2, CopyStr("delimiter ]"));
    }| LCB initializer_list COMMA RCB {
        $$ = NewSTNode(INITIALIZER, 4);
        AddAttrs($$, CopyStr("delimiter ["), $2, CopyStr("delimiter ,"), CopyStr("delimiter delimiter ]"));
    };

initializer_list
    : initializer {
        $$ = NewSTNode(INITIALIZER_LIST, 1);
        AddAttrs($$, $1);
    }| initializer_list COMMA initializer {
        $$ = NewSTNode(INITIALIZER_LIST, 3);
        AddAttrs($$, $1, CopyStr("delimiter ,"), $3);
    };

parameter_type_list
    : type_specifiers {
        $$ = NewSTNode(PARAMETER_TYPE_LIST, 1);
        AddAttrs($$, $1);
    }| parameter_type_list COMMA type_specifiers {
        $$ = NewSTNode(PARAMETER_TYPE_LIST, 3);
        AddAttrs($$, $1, CopyStr("delimiter ,"), $3);
    };

function_definition
    : type_specifiers identifier LB RB compound_statement {
        $$ = NewSTNode(FUNCTION_DEFINITION, 5);
        AddAttrs($$, $1, $2, CopyStr("delimiter ("), CopyStr("delimiter )"), $5);
    }| type_specifiers identifier LB parameter_declarator_list RB compound_statement {
        $$ = NewSTNode(FUNCTION_DEFINITION, 6);
        AddAttrs($$, $1, $2, CopyStr("delimiter ("), $4, CopyStr("delimiter )"), $6);
    };

parameter_declarator_list
    : parameter_declarator {
        $$ = NewSTNode(PARAMETER_DECLARATOR_LIST, 1);
        AddAttrs($$, $1);
    }| parameter_declarator_list COMMA parameter_declarator {
        $$ = NewSTNode(PARAMETER_DECLARATOR_LIST, 3);
        AddAttrs($$, $1, CopyStr("delimiter ,"), $3);
    };

parameter_declarator
    :type_specifiers declarator {
        $$ = NewSTNode(PARAMETER_DECLARATOR, 2);
        AddAttrs($$, $1, $2);
    };

compound_statement
    : LCB RCB {
        $$ = NewSTNode(COMPOUND_STATEMENT, 2);
        AddAttrs($$, CopyStr("delimiter {"), CopyStr("delimiter }"));
    }| LCB statement_list RCB {
        $$ = NewSTNode(COMPOUND_STATEMENT, 3);
        AddAttrs($$, CopyStr("delimiter {"), $2, CopyStr("delimiter }"));
    }| LCB declaration_list RCB {
        $$ = NewSTNode(COMPOUND_STATEMENT, 3);
        AddAttrs($$, CopyStr("delimiter {"), $2, CopyStr("delimiter }"));
    }| LCB declaration_list statement_list RCB {
        $$ = NewSTNode(COMPOUND_STATEMENT, 4);
        AddAttrs($$, CopyStr("delimiter {"), $2, $3, CopyStr("delimiter }"));
    };

statement_list
    : statement {
        $$ = NewSTNode(STATEMENT_LIST, 1);
        AddAttrs($$, $1);
    }| statement_list statement {
        $$ = NewSTNode(STATEMENT_LIST, 2);
        AddAttrs($$, $1, $2);
    };

declaration_list
    : declaration {
        $$ = NewSTNode(DECLARATION_LIST, 1);
        AddAttrs($$, $1);
    }| declaration_list declaration {
        $$ = NewSTNode(DECLARATION_LIST, 2);
        AddAttrs($$, $1, $2);
    };

statement
    : compound_statement {
        $$ = NewSTNode(STATEMENT, 1);
        AddAttrs($$, $1);
    }| expression_statement {
        $$ = NewSTNode(STATEMENT, 1);
        AddAttrs($$, $1);
    }| jump_statement {
        $$ = NewSTNode(STATEMENT, 1);
        AddAttrs($$, $1);
    }| selection_statement {
        $$ = NewSTNode(STATEMENT, 1);
        AddAttrs($$, $1);
    }| loop_statement {
        $$ = NewSTNode(STATEMENT, 1);
        AddAttrs($$, $1);
    }| io_statement {
        $$ = NewSTNode(STATEMENT, 1);
        AddAttrs($$, $1);
    };

expression_statement 
    : SEMICOLON {
        $$ = NewSTNode(EXPRESSION_STATEMENT, 1);
        AddAttrs($$, CopyStr("delimiter ;"));
    }| expression SEMICOLON {
        $$ = NewSTNode(EXPRESSION_STATEMENT, 2);
        AddAttrs($$, $1, CopyStr("delimiter ;"));
    };

jump_statement
    : CONTINUE SEMICOLON {
        $$ = NewSTNode(JUMP_STATEMENT, 2);
        AddAttrs($$, CopyStr("continue"), CopyStr("delimiter ;"));
    }| BREAK SEMICOLON {
        $$ = NewSTNode(JUMP_STATEMENT, 2);
        AddAttrs($$, CopyStr("break"), CopyStr("delimiter ;"));
    }| RETURN SEMICOLON {
        $$ = NewSTNode(JUMP_STATEMENT, 2);
        AddAttrs($$, CopyStr("return"), CopyStr("delimiter ;"));
    }| RETURN expression SEMICOLON {
        $$ = NewSTNode(JUMP_STATEMENT, 2);
        AddAttrs($$, CopyStr("return"), $2, CopyStr("delimiter ;"));
    };

selection_statement
    : IF LB expression RB compound_statement {
        $$ = NewSTNode(SELECTION_STATEMENT, 5);
        AddAttrs($$, CopyStr("if"), CopyStr("delimiter ("), $3, CopyStr("delimiter )"), $5);
    }| IF LB expression RB compound_statement ELSE compound_statement {
        $$ = NewSTNode(SELECTION_STATEMENT, 7);
        AddAttrs($$, CopyStr("if"), CopyStr("delimiter ("), $3, CopyStr("delimiter )"), $5, CopyStr("else"), $7);
    }| IF LB expression RB compound_statement ELSE selection_statement {
        $$ = NewSTNode(SELECTION_STATEMENT, 7);
        AddAttrs($$, CopyStr("if"), CopyStr("delimiter ("), $3, CopyStr("delimiter )"), $5, CopyStr("else"), $7);
    };

loop_statement
    : FOR LB expression_statement expression_statement RB compound_statement {
        $$ = NewSTNode(LOOP_STATEMENT, 6);
        AddAttrs($$, CopyStr("for"), CopyStr("delimiter ("), $3, $4, CopyStr("delimiter )"), $6);
    }| FOR LB expression_statement expression_statement expression RB compound_statement {
        $$ = NewSTNode(LOOP_STATEMENT, 7);
        AddAttrs($$, CopyStr("for"), CopyStr("delimiter ("), $3, $4, $5, CopyStr("delimiter )"), $7);
    };

io_statement
    : PRINT LB argument_list RB SEMICOLON {
        $$ = NewSTNode(IO_STATEMENT, 5);
        AddAttrs($$, CopyStr("print"), CopyStr("delimiter ("), $3, CopyStr("delimiter )"), CopyStr("delimiter ;"));
    }| SCAN LB argument_list RB SEMICOLON {
        $$ = NewSTNode(IO_STATEMENT, 5);
        AddAttrs($$, CopyStr("scan"), CopyStr("delimiter ("), $3, CopyStr("delimiter )"), CopyStr("delimiter ;"));
    };

expression 
    : assignment_expression {
        $$ = $1;
    }| expression COMMA assignment_expression {
        $$ = NewSTNode(EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator ,"), $3);
    };

assignment_expression
    : logical_or_expression {
        $$ = $1;
    }| postfix_expression ASSIGN assignment_expression {
        $$ = NewSTNode(ASSIGNMENT_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator ="), $3);
    };

unary_expression
    : postfix_expression {
        $$ = $1;
    }| INC unary_expression {
        $$ = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs($$, CopyStr("operator ++"), $2);
    }| DEC unary_expression {
        $$ = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs($$, CopyStr("operator --"), $2);
    }| PLUS unary_expression {
        $$ = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs($$, CopyStr("operator +"), $2);
    }| MINUS unary_expression {
        $$ = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs($$, CopyStr("operator -"), $2);
    }| BNOT unary_expression {
        $$ = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs($$, CopyStr("operator ~"), $2);
    }| NOT unary_expression {
        $$ = NewSTNode(UNARY_EXPRESSION, 2);
        AddAttrs($$, CopyStr("operator !"), $2);
    };

postfix_expression
    : primary_expression {
        $$ = $1;
    }| postfix_expression LSB expression RSB {
        $$ = NewSTNode(POSTFIX_EXPRESSION, 4);
        AddAttrs($$, $1, CopyStr("delimiter ["), $3, CopyStr("delimiter ]"));
    }| primary_expression LB RB {
        $$ = NewSTNode(POSTFIX_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("delimiter ("), CopyStr("delimiter )"));
    }| primary_expression LB argument_list RB {
        $$ = NewSTNode(POSTFIX_EXPRESSION, 4);
        AddAttrs($$, $1, CopyStr("delimiter ("), $3, CopyStr("delimiter )"));
    };

primary_expression
    : identifier {
        $$ = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs($$, $1);
    }| BCONSTANT {
        $$ = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs($$, CopyStr(yytext));
    }| ICONSTANT {
        $$ = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs($$, CopyStr(yytext));
    }| FCONSTANT {
        $$ = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs($$, CopyStr(yytext));
    }| SCONSTANT {
        $$ = NewSTNode(PRIMARY_EXPRESSION, 1);
        AddAttrs($$, CopyStr(yytext));
    }| LB expression RB {
        $$ = NewSTNode(PRIMARY_EXPRESSION, 3);
        AddAttrs($$, CopyStr("delimiter ("), $2, CopyStr("delimiter )"));
    };

argument_list
    : assignment_expression {
        $$ = NewSTNode(ARGUMENT_LIST, 1);
        AddAttrs($$, $1);
    }| argument_list COMMA assignment_expression {
        $$ = NewSTNode(ARGUMENT_LIST, 3);
        AddAttrs($$, $1, CopyStr("delimiter ,"), $3);
    };

logical_or_expression
    : logical_and_expression {
        $$ = $1;
    }| logical_or_expression OR logical_and_expression {
        $$ = NewSTNode(LOGICAL_OR_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator ||"), $3);
    };

logical_and_expression
    : bitwise_or_expression {
        $$ = $1;
    }| logical_and_expression AND bitwise_or_expression {
        $$ = NewSTNode(LOGICAL_AND_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator &&"), $3);
    };

bitwise_or_expression
    : bitwise_xor_expression {
        $$ = $1;
    }| bitwise_or_expression BOR bitwise_xor_expression {
        $$ = NewSTNode(BITWISE_OR_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator |"), $3);
    };

bitwise_xor_expression
    : bitwise_and_expression {
        $$ = $1;
    }| bitwise_xor_expression BXOR bitwise_and_expression {
        $$ = NewSTNode(BITWISE_XOR_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator ^"), $3);
    };

bitwise_and_expression
    : equality_expression {
        $$ = $1;
    }| bitwise_and_expression BAND equality_expression {
        $$ = NewSTNode(BITWISE_AND_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator &"), $3);
    };

equality_expression
    : relational_expression {
        $$ = $1;
    }| equality_expression EQ relational_expression {
        $$ = NewSTNode(EQUALITY_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator =="), $3);
    }| equality_expression NE relational_expression {
        $$ = NewSTNode(EQUALITY_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator !="), $3);
    };

relational_expression
    : shift_expression {
        $$ = $1;
    }| relational_expression LT shift_expression {
        $$ = NewSTNode(RELATIONAL_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator <"), $3);
    }| relational_expression GT shift_expression {
        $$ = NewSTNode(RELATIONAL_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator >"), $3);
    }| relational_expression LE shift_expression {
        $$ = NewSTNode(RELATIONAL_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator <="), $3);
    }| relational_expression GE shift_expression {
        $$ = NewSTNode(RELATIONAL_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator >="), $3);
    };

shift_expression
    : additive_expression {
        $$ = $1;
    }| shift_expression SL additive_expression {
        $$ = NewSTNode(SHIFT_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator <<"), $3); 
    }| shift_expression SR additive_expression {
        $$ = NewSTNode(SHIFT_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator >>"), $3);
    };

additive_expression
    : multiplicative_expression {
        $$ = $1;
    }| additive_expression PLUS multiplicative_expression {
        $$ = NewSTNode(ADDITIVE_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator +"), $3);
    }| additive_expression MINUS multiplicative_expression {
        $$ = NewSTNode(ADDITIVE_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator -"), $3);
    };

multiplicative_expression
    : unary_expression {
        $$ = $1;
    }| multiplicative_expression MUL unary_expression {
        $$ = NewSTNode(MULTIPLICATIVE_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator *"), $3);
    }| multiplicative_expression DIV unary_expression {
        $$ = NewSTNode(MULTIPLICATIVE_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator /"), $3);
    }| multiplicative_expression MOD unary_expression {
        $$ = NewSTNode(MULTIPLICATIVE_EXPRESSION, 3);
        AddAttrs($$, $1, CopyStr("operator %"), $3);
    };
%%

extern int yylineno;
void yyerror(const char *s) {
    fprintf(stderr, "Line %d: %s\n", yylineno, s);
}