# LSC（LiSubC）

## 保留字

```
<reserved-word> ::= 'void'|'i32'|'f32'|'string'|'bool'|'if'|'else'|'for'|'true'|'false'|'return'|'break'|'continue'|'print'|'scan'
```

## 字面量

### 整型数字面量

```
<integer-literal> ::= <decimal-literal> | <hexadecimal-literal>
<decimal-literal> ::= '0' | <nonzero-digit> {<digit>}
<hexadecimal-literal> ::= ('0x'|'0X') <hexadecimal-digit> {<hexadecimal-digit>}
<digit> ::= '0' | <nonzero-digit>
<nonzero-digit> ::= '1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9'
<hexadecimal-digit> ::= <digit> |'a'|'b'|'c'|'d'|'e'|'f'|'A'|'B'|'C'|'D'|'E'|'F'
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
<sign> ::= '+'|'-'
<digit-seq> ::= <digit> {<digit>}
<floating-literal> ::= [<digit-seq>]'.'<digit-seq>[<exponent>]
						|<digit-seq>'.'[<exponent>]
						|<digit-seq><exponent>
<exponent> ::= ('e'|'E')[<sign>]<digit-seq>
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
<string-literal> ::= '"'{<any-char>|<escape-seq>}'"'
<escape-seq> ::= '\\'|'\"'|'\n'|'\r'|'\t'|'\f'|'\v'
```

例子：

```
"HelloWorld!"
""
"Hello\tWorld\n!"
```

## 标识符

```
<nondigit> ::= 'a'|'b'|'c'|'d'|'e'|'f'|'g'|'h'|'i'|'j'|'k'|'l'|'m'|'n'|'o'|'p'|'q'|'r'|'s'|'t'|'u'|'v'|'w'|'x'|'y'|'z'|'A'|'B'|'C'|'D'|'E'|'F'|'G'|'H'|'I'|'J'|'K'|'L'|'M'|'N'|'O'|'P'|'Q'|'R'|'S'|'T'|'U'|'V'|'W'|'X'|'Y'|'Z'|'_'
<identifier> ::= <nondigit>{<nondigit>|<digit>}
```

例子：

```
x
matrixRow
```

## 运算符

```
<unary-operator> ::= '+'|'-'|'--'|'++'|'~'|'!'
<binary-operator> ::= <additive-operator>
						|<multiplicative-operator>
						|<relational-operator>
						|<assignment-operator>
						|<bitwise-operator>
<additive-operator> ::= '+'|'-'
<multiplicative-operator> ::= '*'|'/'|'%'
<relational-operator> ::= '<'|'<='|'>'|'>='|'!='|'=='|'||'|'&&'
<assignment-operator> ::= '='
<bitwise-operator> ::= '<<'|'>>'|'&'|'|'|'^'
```

## 界符

```
<seperator> ::= ';'|'{'|'}'|'('|')'|','|'['|']'
```

## 注释

```
<single-line-comment> ::= '//'{<any-char>}<LF>
```

例子：

```
// This is a comment
```

## 程序体

```
<program> ::= {<variable-declaration>}{<function-definition>}
```

### 变量声明

```
<declaration> ::= <type_specifier><init_declarator_list>';'
<type_specifier> ::= 'i32'|'f32'|'string'|'bool'|'void'
<init_declarator_list> ::= <init_declarator>
							|<init_declarator_list>','<init_declarator>
<init_declarator> ::= <declarator>
						|<declarator>'='<initializer>
<declarator> ::= <identifier>
				|<declarator>'['<integer-literal>']'
<initializer> ::= <assignment_expression>
					|'{'<initilizer_list>'}'
					|'{'<initilizer_list>',''}'
<initializer_list> ::= <initializer>
						|<initializer_list>','<initializer>
```

例子：

```
strings;
i32 x = 123;
i32 y = x = 2.3;
i32 arr[4][2] = {{0,1},{2,3},{4,5},{6,7}};
```

### 函数定义

```
<function-definition> ::= <type-specifier><identifier><parameter-clause><compound-statement>
```

#### 参数列表

```
<parameter-clause> ::= '('[<parameter-declaration-list>]')'
<parameter-declaration-list> ::= <parameter-declaration>{','<parameter-declaration>}
<parameter-declaration> ::= <type-specifier><identifier>
```

#### 语句

```
<statement> ::= <compound-statement>
				|<condition-statement>
				|<loop-statement>
				|<jump-statement>
				|<print-statement>
				|<scan-statement>
				|<array-statement>
				|<assignment-expression>';'
				|<function-call>';'
				|';'
```

##### 块语句

```
<compound-statement> ::= '{'{<variable-declaration>}<statement-seq>'}'
<statement-seq> ::= {<statement>}
```

##### 条件语句

```
<condition> ::= <expression>[<relational-operator><expression>]
<condition-statement> ::= 'if''('<condition>')'<compound-statement>['else'<compound-statement>]
```

##### 循环语句

```
<loop-statement> ::= 'for''('<for-init-statement>[<condition>]';'[<for-update-expression>]')'<compound-statement>
<for-init-statement> ::= [<assignment-expression>{','<assignment-expression>}]';'
<for-update-expression> ::= (<assignment-expression>|<function-call>){','(<assignment-expression>|<function-call>)}
```

##### 跳转语句

```
<jump-statement> ::= 'break'';'
					|'continue'';'
					|<return-statement>
<return-statement> ::= 'return'[<expression>]';'
```

##### IO语句

```EBNF
<scan-statement> ::= 'scan''('<identifier>')'';'
<print-statement> ::= 'print''('[<printable-list>]')'';'
<printable-list> ::= <printable>{','<printable>}
<printable> ::= <expression>|<string-literal>
```

#### 表达式

```
<expression> ::= <assignment_expression>
<assignment-expression> ::= <unary-expression>{<assignment-operator><assignment-expression>}
							|<logical-or-expression>
<logical-or-expression> ::= <logical-and-expression>
							|<logical-or-expression>'||'<logical-and-expression>
<logical-and-expression> ::= <bitwise-or-expression>
							|<logical-and-expression>'&&'<bitwise-or-expression>
<bitwise-or-expression> ::= <bitwise-xor-expression>
							|<bitwise-or-expression>'|'<bitwise-xor-expression>
<bitwise-xor-expression> ::= <bitwise-and-expression>
							|<bitwise-xor-expression>'^'<bitwise-and-expression>
<bitwise-and-expression> ::= <equality-expression>
							|<bitwise-and-expression>'&'<equality-expression>
<equality-expression> ::= <relational-expression>
					|<equality-expression><equality-operator><relational-expression>
<equality-operator> ::= '!='|'=='
<relational-expression> ::= <shift-expression>
				|<relational-expression><relational-operator><shift-expression>
<relational-expression> ::= '<'|'>'|'<='|'>='
<shift-expression> ::= <additive-expression>
						|<shift-expression><shift-operator><additive-expression>
<shift-operator> ::= '<<'|'>>'
<additive-expression> ::= <multiplicative-expression>
		|<multiplicative-expression><additive-operator><multiplicative-expression>
<multiplicative-expression> ::= <unary-expression>
					|<unary-expression><multiplicative-operator><unary-expression>
<unary-expression> ::= <postfix-expression>
						|<unary-operator><unary-expression>
<postfix-expression> ::= <primary-expression>
						|<postfix-expression>'['<expression>']'
<primary-expression> ::= '('<expression>')'|<identifier>|<literal>|<function-call>
<listeral> ::= <integer-literal>|<bool-literal>|<floating-literal>|<string-literal>
<function-call> ::=<identifier>'('[<expression-list>]')'
<expression-list>::=<expression>{','<expression>}
```

