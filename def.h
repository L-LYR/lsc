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

const char *TokenTypeToString(TokenType t) {
  switch (t) {
  case TK_T_KEYWORD:
    return "Keyword";
  case TK_T_INTEGER_CONSTANT:
    return "Integer Constant";
  case TK_T_FLOAT_CONSTANT:
    return "Float Constant";
  case TK_T_BOOL_CONSTANT:
    return "Bool Constant";
  case TK_T_STRING_CONSTANT:
    return "String Literal";
  case TK_T_IDENTIFIER:
    return "Identifier";
  case TK_T_OPERATOR:
    return "Operator";
  case TK_T_DELIMITER:
    return "Delimiter";
  case TK_T_COMMENT:
    return "Comment";
  case TK_T_UNKNOWN:
    return "Unkown";
  default:
    return "Panic!";
  }
}

typedef enum {
  VOID = 1,
  I32,
  F32,
  STRING,
  BOOL,
  IF,
  ELSE,
  FOR,
  RETURN,
  BREAK,
  CONTINUE,
  PRINT,
  SCAN,
  BCONSTANT,
  IDENTIFIER,
  ICONSTANT, // Integer Constant
  FCONSTANT, // Float Constant
  SCONSTANT, // String Constant
  PLUS,
  MINUS,
  INC,
  DEC,
  BNOT,
  NOT,
  MUL,
  DIV,
  MOD,
  LT,
  GT,
  LE,
  GE,
  EQ,
  NE,
  SL,
  SR,
  BAND,
  BOR,
  BXOR,
  AND,
  OR,
  ASSIGN,
  LB,  // Left Bracket
  RB,  // Right Bracket
  LSB, // Left Square Bracket
  RSB, // Right Square Bracket
  LCB, // Left Curly Bracket
  RCB, // Right Curly Bracket
  SEMECOLON,
  COMMA,
} SpecifiedType;