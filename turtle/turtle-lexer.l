%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]


%%
"#".*          /*do nothing*/

"color"       { return KW_COLOR; }
"red"         { return COL_RED;}
"green"       { return COL_GREEN;}
"blue"        { return COL_BLUE;}
"cyan"        { return COL_CYAN;}
"magenta"     { return COL_MAGENTA;}
"yellow"      { return COL_YELLOW;}
"black"       { return COL_BLACK;}
"gray"        { return COL_GRAY;}
"white"       { return COL_WHITE;}

"^"           { return '^'; }
"+"           { return '+'; }
"-"           { return '-'; }
"*"           { return '*'; }
"/"           { return '/'; }

"sin"
"cos"
"tan"
"sqrt"
"random"

"forward"       { return KW_FORWARD; }


{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
