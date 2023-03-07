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
BACKWARD        bw|backward
RIGHT           rt|right
LEFT            lt|left
HEADING         hd|heading
POSITION        pos|posiition



%%
"#".*          /*do nothing*/

"up"                {return KW_UP; }
"down"              {return KW_DOWN; }
"home"              {return KW_HOME; }
"color red"         { return COL_RED;}
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
{BACKWARD}            {return KW_BACKWARD; }
{RIGHT}               {return KW_RIGHT; }
{LEFT}                {return KW_LEFT; }
{HEADING}             {return KW_HEAD; }
{POSITION}            {return KW_POS; }
{DIGIT}+              { yylval.value = strtod(yytext, NULL); return VALUE; }
[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
