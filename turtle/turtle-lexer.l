%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT           [0-9]
FORWARD         fw|forward
BACKWARD        bw|backward
RIGHT           rt|right
LEFT            lt|left
POSITION        pos|position
HEADING         hd|heading
VAR             [A-Z]+[A-Z0-9]*

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
"("           { return '('; }
")"           { return ')'; }
"{"           { return '{'; }
"}"           { return '}'; }
","           { return ','; }

"sin"                 { return KW_SIN; }
"cos"                 { return KW_COS; }
"tan"                 { return KW_TAN; }
"sqrt"                { return KW_SQRT; }
"random"              { return KW_RANDOM; }
"repeat"              { return KW_REPEAT; }
"print"               { return KW_PRINT; }
"home"                { return KW_HOME; }
"up"                  { return KW_UP; }
"down"                { return KW_DOWN; }
"set"                 { return KW_SET; }
"proc"                { return KW_PROC; }
"call"                { return KW_CALL; }
{VAR}                 { yylval.name = strdup(yytext); return NAME; }
{POSITION}            { return KW_POSITION; }
{FORWARD}             { return KW_FORWARD; }
{BACKWARD}            { return KW_BACKWARD; }
{RIGHT}               { return KW_RIGHT; }
{HEADING}             { return KW_HEADING; }
{LEFT}                { return KW_LEFT; }
{DIGIT}+(.{DIGIT}+)?  { yylval.value = strtod(yytext, NULL); return VALUE; }
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
