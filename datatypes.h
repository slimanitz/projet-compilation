struct AcceptedStates
{
    int state;
    AcceptedStates *next;
};
typedef struct AcceptedStates AcceptedStates;


struct Item
{
    AcceptedStates *first;
    int list_size = 0;
};
typedef struct Item Item;

