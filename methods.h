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
void insertionOfAcceptedState(FirstAcceptedState *first_accepted_state, int new_state)
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
        state = state->next;
    }
}

FirstTransition *initTransitions()
{
    FirstTransition *first_transition = malloc(sizeof(*first_transition));
    Transitions *transitions = malloc(sizeof(*transitions));

    if (first_transition == NULL || transitions == NULL)
    {
        exit(EXIT_FAILURE);
    }

    transitions->starting_state = 0;
    transitions->character = 0;
    transitions->next_state = 0;
    transitions->next_transition = NULL;
    first_transition->first = transitions;

    return first_transition;
}

// Function that insert an acceted state in the
void insertOfTransition(FirstTransition *first_transition, int starting_state, char character, int next_state)
{
    /* Création du nouvel élément */
    Transitions *new = malloc(sizeof(*new));
    if (first_transition == NULL || first_transition == NULL)
    {
        exit(EXIT_FAILURE);
    }
    new->starting_state = starting_state;
    new->next_state = next_state;
    new->character = character;

    /* Insertion de l'élément au début de la first_accepted_statee */
    new->next_transition = first_transition->first;
    first_transition->first = new;
    first_transition->list_size = first_transition->list_size + 1;
}

// Function that deletes the first element of the first_accepted_state
void deleteTransition(FirstTransition *first_transition)
{
    if (first_transition == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (first_transition->first != NULL)
    {
        Transitions *to_delete = first_transition->first;
        first_transition->first = first_transition->first->next_transition;
        free(to_delete);
        first_transition->list_size = first_transition->list_size - 1;
    }
}

// Fucntion to display the element of the first_accepted_state
void displayTransitions(FirstTransition *first_transition)
{
    if (first_transition == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Transitions *transition = first_transition->first;

    while (transition != NULL)
    {
        printf("De l'état %d a %d on a: %c\n", transition->starting_state, transition->next_state, transition->character);
        transition = transition->next_transition;
    }
}

// Function that creates a two dimensional matrix
int **create_matrix(int m, int n)
{
    int **matrix;

    matrix = malloc(sizeof(int *) * m);

    for (int i = 0; i < m; i++)
        matrix[i] = malloc(sizeof(int) * n);

    return matrix;
}