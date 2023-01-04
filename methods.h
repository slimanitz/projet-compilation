#include <stdio.h>
#include <stdlib.h>
#include <datatypes.h>

// Function that initialises an EtatAccepteur datatype
Item *initialisation()
{
    Item *item = malloc(sizeof(*item));
    AcceptedStates *accepted_states = malloc(sizeof(*accepted_states));

    if (item == NULL || accepted_states == NULL)
    {
        exit(EXIT_FAILURE);
    }

    accepted_states->state = 0;
    accepted_states->next = NULL;
    item->first = accepted_states;

    return item;
}

// Function that insert an acceted state in the
void insertion(Item *item, int new_state)
{
    /* Création du nouvel élément */
    AcceptedStates *new = malloc(sizeof(*new));
    if (item == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new->state = new;

    /* Insertion de l'élément au début de la iteme */
    new->next = item->first;
    item->first = new;
    item->list_size = item->list_size + 1;
}

// Function that deletes the first element of the item
void deletion(Item *item)
{
    if (item == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (item->first != NULL)
    {
        AcceptedStates *to_delete = item->first;
        item->first = item->first->next;
        free(to_delete);
        item->list_size = item->list_size - 1;
    }
}

// Fucntion to display the element of the item
void displayItem(Item *item)
{
    if (item == NULL)
    {
        exit(EXIT_FAILURE);
    }

    AcceptedStates *state = item->first;

    while (state != NULL)
    {
        printf("%d ", state->state);
        state = state->next;
    }
    printf("NULL\n");
}