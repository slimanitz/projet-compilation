#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"
#include "datatypes.h"

Automate determinisationOfAutomaton(Automate automaton)
{
    if (automaton.first_transition == NULL)
    {
        exit(EXIT_FAILURE);
    }

    FirstTransition *first_transition = malloc(sizeof(*first_transition));

    Transitions *transitions = automaton.first_transition->first;

    int increment = 0; // variable that will give total number of transition that has as starting state the initial state

    while (transitions != NULL)
    {
        if (transitions->starting_state == 0)
        {
            insertionOfTransition(first_transition, transitions->starting_state, transitions->character, transitions->next_state);
            increment++;
        }
        transitions = transitions->next_transition;
    }

    int **grouped_states = create_matrix(automaton.nb_characters, increment);

    for (int i = 0; i < automaton.nb_characters; i++)
    {
        grouped_states[i] = automaton.characters[i];
    }

    while (first_transition != NULL)
    {
        
    }

    for (int i = 0; i < automaton.nb_characters; i++)
        free(grouped_states[i]);
    free(grouped_states);
}