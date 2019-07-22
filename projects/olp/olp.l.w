%{
 /*
OBJECT, WHATISTHIS
*/
%}

%p 9000

/*  Regular Definitions  */
delineator	"\n"
objdelineator	":"
space		" "
underscore	"_"
tie		"="
operator	("+"|"-"|"*"|"/"|"("|")")
punctuate	("."|","|"?"|"!"|"@"|"#"|"$"|"%"|"&")
whitespace	({space})+
digit		(0|1|2|3|4|5|6|7|8|9)
digits		({digit})+
character	(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)
characters	({character})+
string		({characters}|{digits}|{punctuate}|{operator}|{whitespace})+
value		({string})*
token		({characters}|{characters}{digits}|{characters}{underscore})+
nodevalue	{delineator}{token}{tie}{value}
nodevalues	({nodevalue})+
objname		({token})
object		({objname}{objdelineator}{nodevalues}{delineator})+

%%

{object}		{printf("object:`%s'\n",yytext);}


%%

install_object()  {/*
*/
}

