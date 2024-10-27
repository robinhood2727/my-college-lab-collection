#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 30
#define MAX_TRANSITIONS 30
#define MAX_SYMBOLS 2 // Assuming binary alphabet {0, 1}

// Structure to hold NFA transitions
typedef struct {
    char fromState;
    char inputSymbol;
    char toState;
} Transition;

// NFA transitions array and other variables
Transition nfa[MAX_TRANSITIONS];
char dfa[MAX_STATES][MAX_STATES]; // DFA transition table
int nfaTransitionCount = 0;
int dfaStateCount = 0;
char initialState;
char finalStates[MAX_STATES];

// Function to add a DFA state
void addDFAState(char *state) {
    for (int i = 0; i < dfaStateCount; i++) {
        if (strcmp(dfa[i], state) == 0) {
            return; // State already exists
        }
    }
    strcpy(dfa[dfaStateCount++], state); // Add new state
}

void findTransitions(char *currentStates, char input, char *result) {
    result[0] = '\0'; // Clear result
    for (int i = 0; i < nfaTransitionCount; i++) {
        if (strchr(currentStates, nfa[i].fromState) && nfa[i].inputSymbol == input) {
            if (!strchr(result, nfa[i].toState)) { // Avoid duplicates
                strncat(result, &nfa[i].toState, 1);
            }
        }
    }
}
void convertNFAToDFA() {
    char queue[MAX_STATES][MAX_STATES];
    int front = 0, rear = 0;

    // Start with the initial state
    queue[rear][0] = initialState;
    queue[rear][1] = '\0'; // Null terminate
    rear++;
    addDFAState(queue[0]);

    while (front < rear) {
        char currentState[MAX_STATES];
        strcpy(currentState, queue[front++]);
        // Process each input symbol
        for (char input = '0'; input <= '1'; input++) {
            char nextState[MAX_STATES] = "";
            findTransitions(currentState, input, nextState);

            if (nextState[0] != '\0') {
                addDFAState(nextState);
               
                for (int i = 0; i < rear; i++) {
                    if (strcmp(queue[i], nextState) == 0) {
                        break; // State already in queue
                    }
                    if (i == rear - 1) {
                        strcpy(queue[rear++], nextState);
                    }
                }
            }
        }
    }
}

// Function to print the DFA transition table
void printDFA() {
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < dfaStateCount; i++) {
        printf("State %s:\n", dfa[i]);
        for (char input = '0'; input <= '1'; input++) {
            char nextState[MAX_STATES] = "";
            findTransitions(dfa[i], input, nextState);
            if (nextState[0] != '\0') {
                printf("  On input '%c' -> %s\n", input, nextState);
            } 

else {
                printf("  On input '%c' -> (undefined state)\n", input);
            }
        }
    }

    printf("\nFinal states in DFA:\n");
    for (int i = 0; i < dfaStateCount; i++) {
        for (int j = 0; j < strlen(finalStates); j++) {
            if (strchr(dfa[i], finalStates[j])) {
                printf("  %s\n", dfa[i]);
                break;
            }
        }
    }
}

int main() {
    int numStates;
    printf("Enter number of states in the NFA: ");
    scanf("%d", &numStates);

    printf("Enter number of transitions in NFA: ");
    scanf("%d", &nfaTransitionCount);

    printf("Enter transitions (format: fromState inputSymbol toState):\n");
    for (int i = 0; i < nfaTransitionCount; i++) {
        char transition[4]; // e.g., A0B
        scanf("%s", transition);
        nfa[i].fromState = transition[0];
        nfa[i].inputSymbol = transition[1];
        nfa[i].toState = transition[2];
    }

    printf("Enter initial state: ");
    scanf(" %c", &initialState);

    printf("Enter final states (as a string, e.g. C): ");
    scanf("%s", finalStates);

    convertNFAToDFA();
    printDFA();
    return 0;
}
