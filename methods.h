#include <stdio.h>
#include <stdlib.h>
#include "datatypes.h"

// Function that initialises an EtatAccepteur datatype
FirstAcceptedState *initialisation()
{
    FirstAcceptedState *first_accepted_state = malloc(sizeof(*first_accepted_state));
    AcceptedStates *accepted_states = malloc(sizeof(*accepted_states));

    if (first_accepted_state == NULL || accepted_states == NULL)
    {
        exit(EXIT_FAILURE);
    }

    accepted_states->state = 0;
    accepted_states->next = NULL;
    first_accepted_state->first = accepted_states;

    return first_accepted_state;
}

// Function that insert an acceted state in the
void insertion(FirstAcceptedState *first_accepted_state, int new_state)
{
    /* Création du nouvel élément */
    AcceptedStates *new = malloc(sizeof(*new));
    if (first_accepted_state == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new->state = new_state;

    /* Insertion de l'élément au début de la first_accepted_statee */
    new->next = first_accepted_state->first;
    first_accepted_state->first = new;
    first_accepted_state->list_size = first_accepted_state->list_size + 1;
}

// Function that deletes the first element of the first_accepted_state
void deletion(FirstAcceptedState *first_accepted_state)
{
    if (first_accepted_state == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (first_accepted_state->first != NULL)
    {
        AcceptedStates *to_delete = first_accepted_state->first;
        first_accepted_state->first = first_accepted_state->first->next;
        free(to_delete);
        first_accepted_state->list_size = first_accepted_state->list_size - 1;
    }
}

// Fucntion to display the element of the first_accepted_state
void displayFirstAcceptedState(FirstAcceptedState *first_accepted_state)
{
    if (first_accepted_state == NULL)
    {
        exit(EXIT_FAILURE);
    }

    AcceptedStates *state = first_accepted_state->first;

    while (state != NULL)
    {
        printf("%d ", state->state);
        state = state->next;
    }
}