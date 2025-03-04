%{
    #include<stdio.h>

%}
%%
["int" "float" "if" "for" "else"]   {printf("Keyword : %s\n",yytext);}
[a-zA-Z_][a-zA-Z0-9_]*  {printf("Identifier : %s\n",yytext);}
["==" "&&" "||" ">=" "<=" "="]  {printf("Operators : %s\n",yytext);}
'[^']*' | "[^"]*"               {printf("String : %s\n",yytext);}
[\/\*([^*]|\*+[^*/])*\*+\/|\/\/.*]  {printf("Comments : *s\n",yytext);}
[ \t\n]+                            
.                                   {printf("Error");}

%%
int main() {
    printf("Enter C source code: \n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
