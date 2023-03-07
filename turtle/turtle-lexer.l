%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
FORWARD         fw|forward
RIGHT           rt|right


%%
"#".*          /*do nothing*/


"color red"        { return COL_RED;}
"color green"       { return COL_GREEN;}
"color blue"        { return COL_BLUE;}
"color cyan"        { return COL_CYAN;}
"color magenta"     { return COL_MAGENTA;}
"color yellow"      { return COL_YELLOW;}
"color black"       { return COL_BLACK;}
"color gray"        { return COL_GRAY;}
"color white"       { return COL_WHITE;}
"color"             { return KW_COLOR; }

"^"           { return '^'; }
"+"           { return '+'; }
"-"           { return '-'; }
"*"           { return '*'; }
"/"           { return '/'; }

{FORWARD}             {return KW_FORWARD; }
{RIGHT}               {return KW_RIGHT; }
{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
