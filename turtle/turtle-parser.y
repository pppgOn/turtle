%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  char *name;
  struct ast_node *node;
}

%token <value>    VALUE         "value"
%token <name>     NAME          "name"

%token            KW_SET        "set"
%token            KW_PROC       "proc"
%token            KW_CALL       "call"

%token            KW_FORWARD    "forward"
%token            KW_BACKWARD   "backward"
%token            KW_RIGHT      "right"
%token            KW_LEFT       "left"
%token            KW_HEADING    "heading"
%token            KW_POSITION   "position"
%token            KW_HOME       "home"
%token            KW_UP         "up"
%token            KW_DOWN       "down"
%token            KW_PRINT      "print"
%token            KW_REPEAT     "repeat"

%token            KW_SIN        "sin"
%token            KW_COS        "cos"
%token            KW_TAN        "tan"
%token            KW_SQRT       "sqrt"
%token            KW_RANDOM     "random"

%token            KW_COLOR      "color"
%token            COL_RED       "red"
%token            COL_GREEN     "green"
%token            COL_BLUE      "blue"
%token            COL_CYAN      "cyan"
%token            COL_MAGENTA   "magenta"
%token            COL_YELLOW    "yellow"
%token            COL_BLACK     "black"
%token            COL_GRAY      "gray"
%token            COL_WHITE     "white"

%left '+' '-'
%left '*' '/'
%left '^'
%left UMINUS

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_FORWARD expr   { $$ = make_cmd_forward($2);  }
   |KW_BACKWARD expr  { $$ = make_cmd_backward($2); }
   |KW_RIGHT expr     { $$ = make_cmd_right($2); }
   |KW_LEFT expr      { $$ = make_cmd_left($2); }
   |KW_HEADING expr   { $$ = make_cmd_heading($2); }
   |KW_POSITION expr ',' expr { $$ = make_cmd_position($2, $4); }
   |KW_HOME           { $$ = make_cmd_home(); }
   |KW_UP             { $$ = make_cmd_up(); }
   |KW_DOWN           { $$ = make_cmd_down(); }
   |KW_PRINT expr     { $$ = make_cmd_print($2); }
   |KW_PRINT cmd      { $$ = make_cmd_print($2); }
   |KW_COLOR expr ',' expr ',' expr { $$= make_cmd_color($2, $4, $6); }
   |COL_RED           { $$ = make_cmd_color_value(1.0, 0.0, 0.0); }
   |COL_GREEN         { $$ = make_cmd_color_value(0.0, 1.0, 0.0); }
   |COL_BLUE          { $$ = make_cmd_color_value(0.0, 0.0, 1.0); }
   |COL_CYAN          { $$ = make_cmd_color_value(0.0, 1.0, 1.0); }
   |COL_MAGENTA       { $$ = make_cmd_color_value(1.0, 0.0, 1.0); }
   |COL_YELLOW        { $$ = make_cmd_color_value(1.0, 1.0, 0.0); }
   |COL_BLACK         { $$ = make_cmd_color_value(0.0, 0.0, 0.0); }
   |COL_GRAY          { $$ = make_cmd_color_value(0.5, 0.5, 0.5); }
   |COL_WHITE         { $$ = make_cmd_color_value(1.0, 1.0, 1.0); }
   | '{' cmds '}'     { $$ = make_cmd_block($2); }
   |KW_REPEAT expr cmd  { $$ = make_cmd_repeat($2, $3); }
   |KW_SET NAME expr  { $$ = make_cmd_set($2, $3); }
   |KW_PROC NAME cmd  { $$ = make_cmd_proc($2, $3); }
   |KW_CALL NAME      { $$ = make_cmd_call($2); }
;

expr:
    VALUE 'e' VALUE    { $$ = make_expr_value_exp($1, $3); }
   |VALUE              { $$ = make_expr_value($1); }
   |NAME               { $$ = make_expr_name($1); }
   |KW_SIN '(' expr ')' { $$ = make_fcn_sin($3); }
   |KW_COS '(' expr ')' { $$ = make_fcn_cos($3); }
   |KW_TAN '(' expr ')' { $$ = make_fcn_tan($3); }
   |KW_SQRT '(' expr ')' { $$ = make_fcn_sqrt($3); }
   |KW_RANDOM '(' expr ',' expr ')' { $$ = make_fcn_random($3, $5); }
   | '(' expr ')'      { $$ = make_expr_unop($2, '+'); }
   | expr '+' expr     { $$ = make_expr_binop($1, $3, '+'); }
   | expr '-' expr     { $$ = make_expr_binop($1, $3, '-'); }
   | expr '*' expr     { $$ = make_expr_binop($1, $3, '*'); }
   | expr '/' expr     { $$ = make_expr_binop($1, $3, '/'); }
   | expr '^' expr     { $$ = make_expr_binop($1, $3, '^'); }
   | '-' expr %prec UMINUS         { $$ = make_expr_unop($2, '-'); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
