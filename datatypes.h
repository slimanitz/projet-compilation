struct AcceptedStates
{
    int state;
    struct AcceptedStates *next;
};
typedef struct AcceptedStates AcceptedStates;


struct FirstAcceptedState
{
    AcceptedStates *first;
    int list_size;
};
typedef struct FirstAcceptedState FirstAcceptedState;


struct Transitions
{
    int starting_state;
    char character;
    int next_state;
    struct Transitions *next_transition;
};
typedef struct Transitions Transitions;



struct FirstTransition
{
    Transitions *first;
    int list_size;
};
typedef struct FirstTransition FirstTransition;

struct Automate
{
    int nbEtats;
    char *characters;   // One dimensional array to store characters
    int *states;     // One dimensional array to store the states of the automaton
    int biggest_state;
    int nb_characters;      // This variable will give us the total number of characters in the automaton
    FirstAcceptedState *first_accepted_state;
    int nbTransitions;
    FirstTransition *first_transition;
};
typedef struct Automate Automate;

struct RegroupedStates
{
    int *states;
    int size;
    int new_state;
};
typedef struct RegroupedStates RegroupedStates;