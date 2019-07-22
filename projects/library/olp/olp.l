%{
 /*
OBJECT, WHATISTHIS
*/
#include "y.tab.h"
int lines = 1;
%}
%p 5000




delineator	"\n"
objdelineator	":\n"
space		" "
underscore	"_"
tie		"="
operator	("+"|"-"|"*"|"/"|"("|")")
punctuate	("."|","|"?"|"!"|"@"|"#"|"$"|"%"|"&")
digit		(0|1|2|3|4|5|6|7|8|9)
character	(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)
id		^({character}|{character}{digit}|{character}{underscore})+

%%

{id}			{printf("id:`%s'.\n",yytext);
			return ID;
			}

{delineator}		{printf("delineator.\n");
			return DELINEATOR;
			}

{objdelineator}		{printf("objdelineator.\n");
			return OBJDELINEATOR;
			}

{space}			{printf("space.\n");
			return OBJDELINEATOR;
			}

{underscore}		{printf("underscore.\n");
			return UNDERSCORE;
			}

{tie}			{printf("tie.\n");
			return TIE;
			}

{operator}		{printf("operator:`%s'.\n",yytext);
			return OPERATOR;
			}

{punctuate}		{printf("punctuate:`%s'.\n",yytext);
			return PUNCTUATE;
			}

{digit}			{printf("digit:`%s'.\n",yytext);
			return DIGIT;
			}

{character}		{printf("character:`%s'.\n",yytext);
			return CHARACTER;
			}



%%

install_object()  {/*
*/
}

