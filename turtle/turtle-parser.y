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

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token            KW_FORWARD  "forward"
%token            KW_BACKWARD "backward"
%token            KW_RIGHT    "right"
%token            KW_LEFT     "left"
%token            KW_HOME     "home"
%token            KW_POS      "position"
%token            KW_HEAD     "heading"
%token            KW_UP       "up"
%token            KW_DOWN     "down"



/*%token*/

%token            KW_COLOR    "color"
%token            COL_RED     "red"
%token            COL_GREEN   "green"
%token            COL_BLUE    "blue"
%token            COL_CYAN    "cyan"
%token            COL_MAGENTA "magenta"
%token            COL_YELLOW  "yellow"
%token            COL_BLACK   "black"
%token            COL_GRAY    "gray"
%token            COL_WHITE   "white"

%left '+' '-'
%left '*' '/'
%left '^'
%left UMINUS
/* TODO: add other tokens */

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
    KW_FORWARD expr   { $$= make_cmd_forward($2);  }
   |KW_RIGHT expr     { $$ = make_cmd_right($2); }
   /*|KW_LEFT expr      { $$ = make_cmd_left($2); }
   |KW_BACKWARD expr  { $$ = make_cmd_backward($2);}*/
   |KW_COLOR expr expr expr { $$= make_cmd_color($2, $3, $4); }
   |COL_RED           { $$ = make_cmd_color_value(1.0, 0.0, 0.0); }
   |COL_GREEN         { $$ = make_cmd_color_value(0.0, 1.0, 0.0); }
   |COL_BLUE          { $$ = make_cmd_color_value(0.0, 0.0, 1.0); }
   |COL_CYAN          { $$ = make_cmd_color_value(0.0, 1.0, 1.0); }
   |COL_MAGENTA       { $$ = make_cmd_color_value(1.0, 0.0, 1.0); }
   |COL_YELLOW        { $$ = make_cmd_color_value(1.0, 1.0, 0.0); }
   |COL_BLACK         { $$ = make_cmd_color_value(0.0, 0.0, 0.0); }
   |COL_GRAY          { $$ = make_cmd_color_value(0.5, 0.5, 0.5); }
   |COL_WHITE         { $$ = make_cmd_color_value(1.0, 1.0, 1.0); }
;

expr:
    VALUE             { $$ = make_expr_value($1); }
   /*| '(' expr ')'      { $$ = make_expr_value($2); }
   | expr '+' expr     { $$ = make_expr_value($1 + $3); }
   | expr '-' expr     { $$ = make_expr_value($1 - $3); }
   | expr '*' expr     { $$ = make_expr_value($1 * $3); }
   | expr '/' expr     { $$ = make_expr_value($1 / $3); }
   | expr '^' expr     { $$ = make_expr_value($1 ^ $3); }
   | '-' expr %prec UMINUS         { $$ = make_expr_value(-$2); }*/
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
