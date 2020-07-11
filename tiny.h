#define _GNI_SOURCE
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// tokenize.c
//

// Token
typedef enum {
  TK_RESERVED, // Keywords or punctuators
  TK_NUM,      // Integer literals
  TK_EOF,      // End-of-file markers
  TK_IDENT,    // Identifiers
} TokenKind;

// Token type
typedef struct Token Token;
struct Token {
  TokenKind kind; // Token kind
  Token *next;    // Next token
  long val;       // If kind is TK_NUM, its value
  char *str;      // Token string
  int len;        // Token length
};

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);
bool consume(char *op);
Token *consume_ident(void);
void expect(char *op);
long expect_number(void);
bool at_eof(void);
Token *tokenize(void);

extern char *user_input;
extern Token *token;

//
// parse.c
//

// Local variable
typedef struct Var Var;
struct Var {
    Var *next;
    char *name; // Variable name
    int offset; // Offset from RBP
};

// AST node
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT,  // <
  ND_LE,  // <=
  ND_NUM, // Integer
  ND_RETURN, // Return
  ND_EXPR_STMT, // Expression statement
  ND_IDENT,  // Ident
  ND_ASSIGN, // =
  ND_VAR, // Variable
} NodeKind;

// AST node type
typedef struct Node Node;
struct Node {
  NodeKind kind; // Node kind
  Node *next;
  Node *lhs;     // Left-hand side
  Node *rhs;     // Right-hand side
  Var *var;
  long val;      // Used if kind == ND_NUM
};

typedef struct Function Function;
struct Function {
    Node *node;
    Var *locals;
    int stack_size;
};

//
// codegen.c
//

void codegen(Function *prog);
