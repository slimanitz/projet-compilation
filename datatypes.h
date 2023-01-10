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
    int state_number;
    char *characters;  // One dimensional array to store characters
    int nb_characters; // This variable will give us the total number of characters in the automaton
    FirstAcceptedState *first_accepted_state;
    int transition_number;
    FirstTransition *first_transition;
};
typedef struct Automate Automate;