%{
#include <stdio.h>

int char_count = 0, word_count = 0, line_count = 0;
%}

%%

\n          { line_count++; char_count++; }  

[ \t]+      { char_count += yyleng; }       

[^ \t\n]+   { word_count++; char_count += yyleng; }               



%%

int main() {
    
    
    yylex(); // Process input

    // Ensure that the last line is counted if input does not end with '\n'
    if (char_count > 0 && line_count == 0) {
        line_count = 1;
    }

    printf("\nCharacters : %d\nWords : %d\nLines : %d\n", char_count, word_count, line_count);
    fflush(stdout);  // Ensure output is printed immediately
    
    return 0;
}

int yywrap(){
    return 1;
}
