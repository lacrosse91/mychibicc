#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
typedef enum {
  TK_RESERVED, // Keywords or punctuators
  TK_NUM,      // Numeric literals
  TK_EOF,      // End-of-file markers
} TokenKind;

typedef struct Token Token;
struct Token {
  TokenKind kind; // Token kind
  Token *next;    // Next token
  long val;       // If kind is TK_NUM, its value
  char *loc;      // Token location
  int len;        // Token length
};



// Reports an error and exit.
static void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

// Consumes the current token if it matches `s`.
static bool equal(Token *tok, char *s) {
  return strlen(s) == tok->len &&
         !strncmp(tok->loc, s, tok->len);
}

// Ensure that the current token is TK_NUM.
static long get_number(Token *tok) {
  if (tok->kind != TK_NUM)
    error("expected a number");
  return tok->val;
}

// Ensure that the current token is `s`.
static Token *skip(Token *tok, char *s) {
  if (!equal(tok, s))
    error("expected '%s'", s);
  return tok->next;
}

// Create a new token and add it as the next token of `cur`.
static Token *new_token(TokenKind kind, Token *cur, char *str, int len) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->loc = str;
  tok->len = len;
  cur->next = tok;
  return tok;
}

// Tokenize `p` and returns new tokens.
static Token *tokenize(char *p) {
    Token head = {};
    Token *cur = &head;
    head.next = NULL;

    while (*p) {
        // pが空白ならスキップ
        if (isspace(*p)) {
            p++;
            continue;
        }

        // 数値かどうか判定
        if (isdigit(*p)) {
            cur = new_token(TK_NUM, cur, p, 0);
            char *q = p;
            cur->val = strtol(p, &p, 10);
            cur->len = p - q;
            continue;
        }

        // '+' か '-'か判定
        if (*p == '+' || *p == '-') {
            cur = new_token(TK_RESERVED, cur, p, 1);
            p++;
            continue;
        }

        error("invalid token");
    }

    cur = new_token(TK_EOF, cur, p, 0);

    return head.next;

}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "%s: invalid number of arguments\n", argv[0]);
    return 1;
  }

  Token *tok = tokenize(argv[1]);

  printf(".globl main\n");
  printf("main:\n");
  printf("  mov $%ld, %%rax\n", get_number(tok));
  tok = tok->next;

  while (tok->kind != TK_EOF) {

      if (equal(tok, "+")) {
          printf("  add $%ld, %%rax\n", get_number(tok->next));
          tok = tok->next->next;
          continue;
      }

      tok = skip(tok, "-");
      printf("  sub $%ld, %%rax\n", get_number(tok));
      tok = tok->next;

  }

  printf("  ret\n");
  return 0;
}
