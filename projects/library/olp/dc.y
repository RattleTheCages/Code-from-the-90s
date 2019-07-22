%{
#include <ctype.h>
#include <stdio.h>

#define YYSTYPE double
%}

%token NUMBER

%%
line	:	expr '\n'	{printf("%d\n",$1);}
	;
expr	:	expr '+' expr	{ $$ = $1 + $3; }
	|	term
	;
term	:	term '*' factor	{$$ = $1 * $3;}
	|	factor
	;
factor	:	'(' expr ')'	{$$ = $2;}
	|	NUMBER
	;

%%
yylex()  {
    int c;
    while((c=getchar()) == ' ');
    if( c == '.' || isdigit(c))  {
        ungetc(c, stdin);
        scanf("%lf",&yylval);
        return NUMBER;
    }
    return c;
}


