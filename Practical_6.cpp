#include <iostream>
#include <string>

using namespace std;

bool S(string input);  
bool L(string input);  
bool LDash(string input); 

int index = 0;  

bool match(string input, char expected) {  
    if (index < input.length() && input[index] == expected) {
        index++;
        return true;
    }
    return false;
}

bool S(string input) { 
    if (match(input, '('))
     {
          
          if(L(input) && match(input, ')')){ 
             return true;
          }
          else
           return false;
    }
    if (match(input, 'a')) {
        return true; 
    }
    return false; 
}

bool L(string input) {  
    if (S(input))
    {
        return LDash(input);
       
    }
    else
    return false;

}

bool LDash(string input) {  
    if (match(input, ',')) 
    {  
        if (S(input)) 
        {
            return LDash(input);
        }
        else
        return false;
          
    }
    return true;  
}

bool parse(string input) {  
    bool result = S(input) && (index == input.length());  // Check if the entire input is consume
    return result;
}

int main() {
    string input;

    
    cout << "Enter the string to be validated: ";
    cin >> input;

    if (parse(input)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}
