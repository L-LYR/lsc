# LSC（LiSubC）

## 保留字

```
<reserved-word> ::=  'void'|'i32'|'f32'|'string'|'bool'
                    |'if'|'else'|'for'|'true'|'false'
                    |'return'|'break'|'continue'
                    |'print'|'scan'
```

## 字面量

### 整型数字面量

```
<integer-literal>       ::= <decimal-literal> | <hexadecimal-literal>
<decimal-literal>       ::= '0' | <nonzero-digit> {<digit>}
<hexadecimal-literal>   ::= <hexadecimal-header><hexadecimal-digit> {<hexadecimal-digit>}
<hexadecimal-header>    ::= '0x'|'0X'
<digit>                 ::= '0' | <nonzero-digit>
<nonzero-digit>         ::= '1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9'
<hexadecimal-digit>     ::= <digit> |'a'|'b'|'c'|'d'|'e'|'f'|'A'|'B'|'C'|'D'|'E'|'F'
```

例子：

```
2000
9999
0xFFF
0Xabd
```

### 浮点数字面量

```
<digit-seq>         ::= <digit>{<digit>}
<floating-literal>  ::= <decimal-literal>'.'{<digit-seq>}[<exponent>]
                        | '.'<digit-seq>[<exponent>]
						| <decimal-literal><exponent>
<exponent>          ::= <exp>['+'|'-']<digit-seq>
<exp>               ::= 'e'|'E'
```

例子：

```
7.
9.8
.9e+7
9.3e-8
```

### 布尔值字面量

```
<bool-literal> ::= 'true'|'false'
```

### 字符串字面量

```
<string-literal>    ::= '"'{<any-char>|<escape-seq>}'"'
<any-char>          ::= <ASCII> // no '\' '"' '\n'
<escape-seq>        ::= '\\'|'\"'|'\n'|'\r'|'\t'|'\f'|'\v'

```

例子：

```
"HelloWorld!"
""
"Hello\tWorld\n!"
```

## 标识符

```
<nondigit>   ::= 'a'|'b'|'c'|'d'|'e'|'f'|'g'|'h'|'i'
                |'j'|'k'|'l'|'m'|'n'|'o'|'p'|'q'|'r'
                |'s'|'t'|'u'|'v'|'w'|'x'|'y'|'z'|'A'
                |'B'|'C'|'D'|'E'|'F'|'G'|'H'|'I'|'J'
                |'K'|'L'|'M'|'N'|'O'|'P'|'Q'|'R'|'S'
                |'T'|'U'|'V'|'W'|'X'|'Y'|'Z'|'_'
<identifier> ::= <nondigit>{<nondigit>|<digit>}
```

例子：

```
x
matrixRow
```

## 运算符

```
<unary-operator>            ::= '+'|'-'|'--'|'++'|'~'|'!'
<binary-operator>           ::= <additive-operator>
						        |<multiplicative-operator>
						        |<relational-operator>
						        |<assignment-operator>
						        |<bitwise-operator>
<additive-operator>         ::= '+'|'-'
<multiplicative-operator>   ::= '*'|'/'|'%'
<relational-operator>       ::= '<'|'<='|'>'|'>='|'!='|'=='|'||'|'&&'
<assignment-operator>       ::= '='
<bitwise-operator>          ::= '<<'|'>>'|'&'|'|'|'^'
```

## 界符

```
<seperator> ::= <semicolon>|<comma>|<LCB>|<RCB>|<LB>|<RB>|<LSB>|<RSB>
<semicolon> ::= ';'
<comma>     ::= ','
<LCB>       ::= '{'
<RCB>       ::= '}'
<LB>        ::= '('
<RB>        ::= ')'
<LSB>       ::= '['
<RSB>       ::= ']'
```

## 注释

```
<single-line-comment> ::= '//'{<ASCII>}[<LF>|<CRLF>|<LFCR>]
<CR>                  ::= '\r'
<LF>                  ::= '\n'
<CRLF>                ::= <CR><LF>
<LFCR>                ::= <LF><CR>
```

例子：

```
// This is a comment
```

## 程序

```
<program>                          ::= <global-list>
<global-list>                      ::= {<global-declaration-or-definition>}
<global-declaration-or-definition> ::= <declaration>|<function-definition>
```

### 声明

```
<declaration>          ::= <variable-declaration>|<function-declaration>
<variable-declaration> ::= <type-specifiers><init-declarator-list> <semicolon>
<function-declaration> ::= <type-specifiers><identifier><LB><parameter-type-list><RB><semicolon>
<type-specifiers>      ::= 'void'|'i32'|'f32'|'string'|'bool'|<type-specifiers><LSB><integer-literal><RSB>
<init-declarator-list> ::= <init-declarator>
                          |<init-declarator-list><comma><init-declarator>
<init-declarator>      ::= <declarator>
                          |<declarator>'='<initializer>
<declarator>           ::= <identifier>
                          |<declarator><LSB><integer-literal><RSB>
<initializer>          ::= <assignment-expression>
                          |<LCB><initializer-list><RCB>
                          |<LCB><initializer-list><comma><RCB>
<initializer-list>     ::= <initializer>
                          |<initializer-list><comma><initializer>
<parameter_type_list>  ::= <type-specifier>
                          |<parameter-type-list><comma><type-specifiers>
```

### 函数定义

```
<function-definition>       ::= <type-specifiers><identifier><LB><RB><compound-statement>
                         |<type-specifiers><identifier><LB><parameter-declarator-list><RB><compound-statement>
<parameter-declarator-list> ::= <parameter-declarator>
                               |<parameter-declarator-list><comma><parameter-declarator>
<parameter-declarator>      ::= <type-specifiers><declarator>
```

### 语句

```
<statement>             ::= <compound-statement>
                           |<expression-statement>
                           |<jump-statement>
                           |<selection-statement>
                           |<loop-statement>
                           |<io-statement>
<compound-statement>    ::= <LCB><RCB>
                           |<LCB><statement-list><RCB>
                           |<LCB><declaration-list><RCB>
                           |<LCB><declaration-list><statement-list><RCB>
<statement-list>        ::= <statement>
                           |<statement-list><statement>
<declaration-list>      ::= <declaration>
                           |<declaration-list><declaration>
<expression-statement>  ::= <semicolon>
                           |<expression><semicolon>
<jump-statement>        ::= 'continue'<semicolon>
                           |'break'<semicolon>
                           |'return'<semicolon>
                           |'return'<expression><semicolon>
<selection-statement>   ::= 'if'<LB><expression><RB><compound-statement>
                           |'if'<LB><expression><RB><compound-statement>'else'<compound-statement>
                           |'if'<LB><expression><RB><compound-statement>'else'<selection-statement>
<loop-statement>        ::= 'for'<LB><expression-statement><expression-statement><RB><compound-statement>
                           |'for'<LB><expression-statement><expression-statement><expression><RB><compound-statement>
<io-statement>          ::= 'print'<LB><argument-list><RB><semicolon>
                           |'scan'<LB><argument-list><RB><semicolon>
```

### 表达式

```
<expression>                ::= <assignment-expression>
                                |<expression><comma><assignment-expression>
<assignment-expression>     ::= <logical-or-expression>
                                |<unary-expression>'='<assignment-expression>
<logical-or-expression>     ::= <logical-and-expression>
                                |<logical-or-expression>'||'<logical-and-expression>
<logical-and-expression>    ::= <bitwise-or-expression>
                                |<logical-and-expression>'&&'<bitwise-or-expression>
<bitwise-or-expression>     ::= <bitwise-xor-expression>
                                |<bitwise-or-expression>'|'<bitwise-xor-expression>
<bitwise-xor-expression>    ::= <bitwise-and-expression>
                                |<bitwise-xor-expression>'^'<bitwise-and-expression>
<bitwise-and-expression>    ::= <equality-expression>
                                |<bitwise-and-expression>'&'<equality-expression>
<equality-expression>       ::= <relational-expression>
                                |<equality-expression>'=='<relational-expression>
                                |<equality-expression>'!='<relational-expression>
<relational-expression>     ::= <shift-expression>
                                |<relational-expression>'<'<shift-expression>
                                |<relational-expression>'>'<shift-expression>
                                |<relational-expression>'<='<shift-expression>
                                |<relational-expression>'>='<shift-expression>
<shift-expression>          ::= <additive-expression>
                                |<shift-expression>'<<'<additive-expression>
                                |<shift-expression>'>>'<additive-expression>
<additive-expression>       ::= <multiplicative-expression>
                                |<additive-expression>'+'<multiplicative-expression>
                                |<additive-expression>'-'<multiplicative-expression>
<multiplicative-expression> ::= <unary-expression>
                                |<multiplicative-expression>'*'<unary-expression>
                                |<multiplicative-expression>'/'<unary-expression>
                                |<multiplicative-expression>'%'<unary-expression>
<unary-expression>          ::= <postfix-expression>
                                |'++'<unary-expression>
                                |'--'<unray-expression>
                                |'+'<unray-expression>
                                |'-'<unray-expression>
                                |'~'<unray-expression>
                                |'!'<unray-expression>
<postfix-expression>        ::= <primary-expression>
                                |<postfix-expression><LSB><expression><RSB>
                                |<primary-expression><LB><RB>
                                |<primary-expression><LB><argument-list><RB>
<primary-expression>        ::= <identifier>
                                |<bool-literal>
                                |<integer-literal>
                                |<float-literal>
                                |<string-literal>
                                |<LB><expression><RB>
<argument-list>             ::= <assignment-expression>
                                |<argument-list><comma><assignment-expression>
```