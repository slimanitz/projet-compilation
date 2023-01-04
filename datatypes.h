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
    int etatDeparts;
    char *transition;
    int prochainEtat;
    struct Transitions *next;
};
typedef struct Transitions Transitions;



struct FirstTransition
{
    Transitions *first;
    int list_size;
};
typedef struct FirstTransition FirstTransition;





