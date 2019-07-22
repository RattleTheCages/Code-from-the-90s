%{
 /*
OBJECT, WHATISTHIS
*/
#include <stdio.h>
%}

%token CHARACTER
%token DIGIT
%token PUNCTUATE
%token OPERATOR
%token TIE
%token UNDERSCORE
%token SPACE
%token OBJDELINEATOR
%token DELINEATOR
%token ID

%%

object		:	objname OBJDELINEATOR nodevalues DELINEATOR
objname		:	ID
nodevalues	:	nodevalues nodevalue | nodevalue
nodevalue	:	ID TIE value DELINEATOR | ID TIE object DELINEATOR
value		:	string |
strtype		:	CHARACTER | DIGIT | PUNCTUATE | OPERATOR | SPACE
string		:	string strtype | strtype


%%

int main()  {
yyparse();
return 0;
}

void yyerror(char* msg)  {
    fprintf(stderr,"%s\n",msg);
}


