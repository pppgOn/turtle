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
    KW_FORWARD expr   {  }
;

expr:
    VALUE             { $$ = make_expr_value($1); }
   |COL_RED           { $$ = make_cmd_color_value(1.0, 0.0, 0.0); }
   |COL_GREEN         { $$ = make_cmd_color_value(0.0, 1.0, 0.0); }
   |COL_BLUE          { $$ = make_cmd_color_value(0.0, 0.0, 1.0); }
   |COL_CYAN          { $$ = make_cmd_color_value(0.0 , 1.0, 1.0); }
   |COL_MAGENTA       { $$ = make_cmd_color_value(1.0, 0.0, 1.0); }
   |COL_YELLOW        { $$ = make_cmd_color_value(1.0, 1.0, 0.0); }
   |COL_BLACK         { $$ = make_cmd_color_value(0.0, 0.0, 0.0); }
   |COL_GRAY          { $$ = make_cmd_color_value(0.5, 0.5, 0.5); }
   |COL_WHITE         { $$ = make_cmd_color_value(1.0, 1.0, 1.0); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
