#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdarg.h>
#include<stdbool.h>
#include<string.h>

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
};

Token *token;
// Reports an error and exit
void error(char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// Consume the current token if it matches `op`
bool consume(char op) {
    if (token -> kind != TK_RESERVED || token->str[0] != op) {
        return false;
    }
    token = token->next;
    return true;
}

// Ensure that the current token is `op`
void expect(char op) {
    if (token->kind != TK_RESERVED || token->str[0] != op) {
        error("expected '%c", op);
    }
    token = token->next;
}

// Ensure that the current token is TK_NUM
long expect_number(void) {
    if (token->kind != TK_NUM) {
        error("expected number");
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
Token *new_token(TokenKind kind, Token *cur, char *str) {
    Token *tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str = str;
    cur->next = tok;
    return tok;
}

// Tokenize `p` and returns new tokens;
Token *tokenize(char *p) {
    Token head = {};
    Token *cur = &head;

    while(*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (*p == '+' ||
            *p == '-') {
                cur = new_token(TK_RESERVED, cur, p++);
                continue;
        }

        if (isdigit(*p)) {
            cur = new_token(TK_NUM, cur, p);
            cur->val = strtol(p, &p, 10);
            continue;
        }

        error("invalid token");
    }

    new_token(TK_EOF, cur, p);
    return head.next;
}

int main(int argc, char **argv) {
  if (argc != 2)
    error("%s: invalid number of arguments", argv[0]);

  token = tokenize(argv[1]);

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // The first token must be a number
  printf("  mov rax, %ld\n", expect_number());

  // ... followed by either `+ <number>` or `- <number>`.
  while (!at_eof()) {
    if (consume('+')) {
      printf("  add rax, %ld\n", expect_number());
      continue;
    }
    expect('-');
    printf("  sub rax, %ld\n", expect_number());
  }

  printf("  ret\n");

  return 0;
}
