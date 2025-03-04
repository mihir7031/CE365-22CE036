#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_SYMBOLS 100

// Define keyword list
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"
};

const char *operators[] = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!",
    "&", "|", "^", "<<", ">>", "++", "--"
};

const char punctuations[] = "(){},;[]";

// Symbol Table
char symbolTable[MAX_SYMBOLS][50];
int symbolCount = 0;

// Lexical Errors
char lexicalErrors[MAX_TOKENS][50];
int errorCount = 0;

// Function to check if a token is a keyword
int isKeyword(char *token) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a token is an operator
int isOperator(char *token) {
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a token is punctuation
int isPunctuation(char ch) {
    return strchr(punctuations, ch) != NULL;
}

// Function to check if a token is an identifier
int isValidIdentifier(char *token) {
    if (!isalpha(token[0]) && token[0] != '_') {
        return 0;
    }
    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_') {
            return 0;
        }
    }
    return 1;
}

// Function to check if a token is a constant
int isConstant(char *token) {
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to remove comments from code
void removeComments(char *code) {
    int i = 0, j = 0;
    while (code[i] != '\0') {
        if (code[i] == '/' && code[i + 1] == '/') {
            while (code[i] != '\n' && code[i] != '\0') i++;
        }
        else if (code[i] == '/' && code[i + 1] == '*') {
            i += 2;
            while (!(code[i] == '*' && code[i + 1] == '/') && code[i] != '\0') i++;
            if (code[i] != '\0') i += 2;
        } else {
            code[j++] = code[i++];
        }
    }
    code[j] = '\0';
}

// Function to process tokens
void processTokens(char *line, int lineNumber) {
    char *token = strtok(line, " \t\n");
    while (token != NULL) {
        if (isKeyword(token)) {
            printf("Keyword: %s\n", token);
        } 
        else if (isOperator(token)) {
            printf("Operator: %s\n", token);
        } 
        else if (isPunctuation(token[0]) && strlen(token) == 1) {
            printf("Punctuation: %s\n", token);
        } 
        else if (isConstant(token)) {
            printf("Constant: %s\n", token);
        } 
        else if (isValidIdentifier(token)) {
            printf("Identifier: %s\n", token);
            // Add to symbol table if not already present
            int found = 0;
            for (int i = 0; i < symbolCount; i++) {
                if (strcmp(symbolTable[i], token) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && symbolCount < MAX_SYMBOLS) {
                strcpy(symbolTable[symbolCount++], token);
            }
        } 
        else {
            snprintf(lexicalErrors[errorCount++], 50, "Line %d: %s invalid lexeme", lineNumber, token);
        }
        token = strtok(NULL, " \t\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./LexicalAnalyzer <input_file>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    char code[1000], line[200];
    int lineNumber = 0;
    code[0] = '\0';

    while (fgets(line, sizeof(line), file)) {
        strcat(code, line);
    }
    fclose(file);

    // Remove comments
    removeComments(code);

    // Tokenize and process lines
    char *linePtr = strtok(code, "\n");
    while (linePtr != NULL) {
        lineNumber++;
        processTokens(linePtr, lineNumber);
        linePtr = strtok(NULL, "\n");
    }

    // Display Symbol Table
    printf("\nSYMBOL TABLE ENTRIES:\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%d) %s\n", i + 1, symbolTable[i]);
    }

    // Display Lexical Errors
    if (errorCount > 0) {
        printf("\nLEXICAL ERRORS:\n");
        for (int i = 0; i < errorCount; i++) {
            printf("%s\n", lexicalErrors[i]);
        }
    }

    return 0;
}
