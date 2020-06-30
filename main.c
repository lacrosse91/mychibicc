#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdarg.h>
#include<stdbool.h>
#include<string.h>

//
// Tokenizer
//
typedef enum {
    TK_RESERVED, //記号
    TK_NUM, //int literal
    TK_EOF, // EOF
} TokenKind;

typedef struct Token Token;
struct Token {
    TokenKind kind; //token kind
    Token *next;
    long val; // if kind is TK_NUM, its value
    char *str; // token string
    int len;
};

// Input program;
char *user_input;

Token *token;
// Reports an error and exit
void error(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// Reports an error location and exit.
void error_at(char *loc, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, ""); // print pos spaces.
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}
// Consume the current token if it matches `op`
bool consume(char *op) {
    if (token -> kind != TK_RESERVED || strlen(op) != token->len ||
        strncmp(token->str, op, token->len)) {
        return false;
    }
    token = token->next;
    return true;
}

// Ensure that the current token is `op`
void expect(char *op) {
    if (token->kind != TK_RESERVED || strlen(op) != token->len ||
        strncmp(token->str, op, token->len)) {
        error_at(token->str, "expected \"%s\"", op);
    }
    token = token->next;
}

// Ensure that the current token is TK_NUM
long expect_number(void) {
    if (token->kind != TK_NUM) {
        error_at(token->str, "expected number");
    }
    long val = token->val;
    token = token->next;
    return val;
}


// check eof
bool at_eof(void) {
    return token->kind == TK_EOF;
}

//Create a new token and add it as the next of `cur`
Token *new_token(TokenKind kind, Token *cur, char *str, int len) {
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    tok->len = len;
    cur->next = tok;
    return tok;
}

// Tokenize `p` and returns new tokens;
Token *tokenize(void) {
    char *p = user_input;
    Token head = {};
    Token *cur = &head;

    while(*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }
        // Single-letter punctuators
        if (ispunct(*p)) {
                cur = new_token(TK_RESERVED, cur, p++, 1);
                continue;
        }

        if (isdigit(*p)) {
            cur = new_token(TK_NUM, cur, p, 0);
            char *q = p;
            cur->val = strtol(p, &p, 10);
            cur->len = p - q;
            continue;
        }

        error_at(p, "invalid token");
    }

    new_token(TK_EOF, cur, p, 0);
    return head.next;
}

//
// parser
//

typedef enum {
    ND_ADD, // +
    ND_SUB, // -
    ND_MUL, // *
    ND_DIV, // /
    ND_NUM, // int
} NodeKind;

// ast node type
typedef struct Node Node;
struct Node {
    NodeKind kind; // Node kind
    Node *lhs; // left side
    Node *rhs; // right side
    long val; // if kind is ND_NUM, its value
};

static Node *new_node(NodeKind kind) {
    Node *node = calloc(1, sizeof(Node));
    node->kind = kind;
    return node;
}

static Node *new_binary(NodeKind kind, Node *lhs, Node *rhs) {
    Node *node = new_node(kind);
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

static Node *new_num(int val) {
    Node *node = new_node(ND_NUM);
    node->val = val;
    return node;
}

static Node *expr(void);
static Node *mul(void);
static Node *primary(void);
static Node *unary(void);

// expr = mul ("+" mul | "-" mul)
static Node *expr(void) {
    Node *node = mul();

    for(;;) {
        if (consume("+")) {
            node = new_binary(ND_ADD, node, mul());
        } else if (consume("-")) {
            node = new_binary(ND_SUB, node, mul());
        } else {
            return node;
        }
    }
}

// mul = unary ( "*" unary | "/" unary)*
static Node *mul (void) {
    Node *node = unary();
    for(;;) {
        if (consume("*")) {
            node = new_binary(ND_MUL, node, unary());
        } else if (consume("/")) {
            node = new_binary(ND_DIV, node, unary());
        } else {
            return node;
        }
    }
}

// unary = ("+" | "-") ? unary
//          | primary
static Node *unary(void) {
    if (consume("+")) {
        return unary();
    }
    if (consume("-")) {
        return new_binary(ND_SUB, new_num(0), unary());
    }
    return primary();
}

// primary = "(" expr ")" | num
static Node *primary(void) {
    if (consume("(")) {
        Node *node = expr();
        expect(")");
        return node;
    }

    return new_num(expect_number());
}

//
// code generator
//

static void gen(Node *node) {
    if (node->kind == ND_NUM) {
        printf("  push %ld\n", node->val);
        return;
    }


    gen(node->lhs);
    gen(node->rhs);

    printf("  pop rdi\n");
    printf("  pop rax\n");

    switch (node->kind) {
    case ND_ADD:
        printf("  add rax, rdi\n");
        break;
    case ND_SUB:
        printf("  sub rax, rdi\n");
        break;
    case ND_MUL:
        printf("  imul rax, rdi\n");
        break;
    case ND_DIV:
        printf("  cqo\n");
        printf("  idiv rdi\n");
        break;
    }

    printf("  push rax\n");
}
int main(int argc, char **argv) {
  if (argc != 2)
    error("%s: invalid number of arguments", argv[0]);

  // Tokennize and parse
  user_input = argv[1];
  token = tokenize();
  Node *node = expr();


  // print out the first half of assembly.
  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // tranverse AST to emit assembly
  gen(node);

  // pop
  printf("  pop rax\n");
  printf("  ret\n");

  return 0;
}
