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

