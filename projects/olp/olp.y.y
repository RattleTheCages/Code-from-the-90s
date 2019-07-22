%{
 /*
OBJECT, WHATISTHIS
*/
%}

%token DIGIT

%%

object		:	objname objdelineator nodevalues delineator {printf("o:%s\n",yylval);}
objname		:	id
nodevalues	:	nodevalues nodevalue | nodevalue
nodevalue	:	id tie value delineator | id tie object delineator
id		:	characters | characters digits | characters underscore
value		:	string |
string		:	characters | digits | punctuate | operator | whitespace
characters	:	characters character | character
character	:	"A"|"B"|"C"|"D"|"E"|"F"|"G"|"H"|"I"|"J"|"K"|"L"|"M"|"N"|"O"|"P"|"Q"|"R"|"S"|"T"|"U"|"V"|"W"|"X"|"Y"|"Z"|"a"|"b"|"c"|"d"|"e"|"f"|"g"|"h"|"i"|"j"|"k"|"l"|"m"|"n"|"o"|"p"|"q"|"r"|"s"|"t"|"u"|"v"|"w"|"x"|"y"|"z"
digits		:	digits digit | digit
digit		:	"0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"
whitespace	:	whitespace space | space
punctuate	:	"."|","|"?"|"!"|"@"|"#"|"$"|"%"|"&"
operator	:	"+"|"-"|"*"|"/"|"("|")"
tie		:	"=" {printf("t:%c\n",yylval);}
underscore	:	"_"
space		:	" "
objdelineator	: ":"
delineator	: "\n";


%%

int main()  {
yyparse();
return 0;
}


