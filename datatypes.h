struct AcceptedStates
{
    int state;
    struct AcceptedStates *next;
};
typedef struct AcceptedStates AcceptedStates;


struct Item
{
    AcceptedStates *first;
    int list_size;
};
typedef struct Item Item;

