#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

int main() {
    // Input symbols
    int numSymbols;
    cout << "Number of input symbols: ";
    cin >> numSymbols;

    set<char> symbols;
    cout << "Input symbols (space-separated): ";
    for (int i = 0; i < numSymbols; ++i) {
        char symbol;
        cin >> symbol;
        symbols.insert(symbol);
    }

    // States and transitions
    int numStates;
    cout << "Enter number of states: ";
    cin >> numStates;

    string initialState;
    cout << "Initial state: ";
    cin >> initialState;

    int numAcceptingStates;
    cout << "Number of accepting states: ";
    cin >> numAcceptingStates;

    set<string> acceptingStates;
    cout << "Accepting states (space-separated): ";
    for (int i = 0; i < numAcceptingStates; ++i) {
        string state;
        cin >> state;
        acceptingStates.insert(state);
    }

    // Transition table
    cout << "Transition table:\n";
    map<string, map<char, string>> transitions;
    for (int i = 0; i < numStates; ++i) {
        string state = to_string(i + 1);
        for (char symbol : symbols) {
            string nextState;
            cout << state << " to " << symbol << " -> ";
            cin >> nextState;
            transitions[state][symbol] = nextState;
        }
    }

    // Input string
    string inputString;
    cout << "Input string: ";
    cin >> inputString;

    // Validate the string
    string currentState = initialState;
    for (char ch : inputString) {
        if (symbols.find(ch) != symbols.end() && transitions[currentState].find(ch) != transitions[currentState].end()) {
            currentState = transitions[currentState][ch];
        } else {
            cout << "Invalid string\n";
            return 0;
        }
    }

    // Check if the final state is accepting
    if (acceptingStates.find(currentState) != acceptingStates.end()) {
        cout << "Valid string\n";
    } else {
        cout << "Invalid string\n";
    }

    return 0;
}
