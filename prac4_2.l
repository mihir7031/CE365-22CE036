%option noyywrap
%{
    #include<stdio.h>
%}
%%
Charusat  {printf("University");}
.       {printf("%s",yytext);}
%%
int main()
{
    printf("Enter the string : ");
    yylex();
}