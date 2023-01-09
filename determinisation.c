#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"

void determinisationOfAutomaton(Automate automaton)
{
    if (automaton.first_transition == NULL)
    {
        exit(EXIT_FAILURE);
    }

    FirstTransition *first_transition = malloc(sizeof(*first_transition));

    Transitions *transitions = automaton.first_transition->first;

    RegroupedStates *regrouped_states = malloc(sizeof(RegroupedStates) * automaton.nbEtats);
    for (int i = 0; i < automaton.nbEtats; i++)
    {
        regrouped_states[i].states = malloc(sizeof(int) * automaton.nbEtats);
    }

    Automate new_automaton;
    new_automaton.first_transition = malloc(sizeof(char) * automaton.nbTransitions);
    new_automaton.characters = malloc(sizeof(char) * automaton.nbEtats);
    new_automaton.characters = automaton.characters;
    new_automaton.nb_characters = automaton.nb_characters;
    new_automaton.states = malloc(sizeof(int) * 20);

        for (int i = 0; i < automaton.nbEtats; i++) // This for loop is for the initialisation of the size of the states
    {
        regrouped_states[i].states = malloc(sizeof(int) * (automaton.nbEtats * 2));
    }

    int increment = 0; // variable that will give total number of transition that has as starting state the initial state
    int k;

    char character;

    while (transitions != NULL) // This while loop is to extract all the transitions that have as starting state the initial state (0)
    {
        if (transitions->starting_state == 0)
        {
            insertionOfTransition(first_transition, transitions->starting_state, transitions->character, transitions->next_state);
            increment++;
        }
        transitions = transitions->next_transition;
    }

    transitions = first_transition->first;
    int b = 3;
    char a;
    char **grouped_states = create_matrix(automaton.nb_characters, increment);
    int biggest_state = automaton.biggest_state;

    for (int i = 0; i < automaton.nb_characters; i++) // This for loop is to grouped states for the determinisation of the automaton
    {
        k = 0;
        character = automaton.characters[i];
        if (transitions == NULL)
        {
            transitions = first_transition->first;
        }
        while (transitions != NULL)
        {
            if (character == transitions->character)
            {
                grouped_states[i][k] = transitions->next_state;
                k++;
            }
            transitions = transitions->next_transition;
        }
    }

    int size_regrouped_state = 0;
    int longest_group = 0;
    for (int i = 0; i < automaton.nb_characters; i++) // This for loop is to insert the regrouped state in two dimensional array grouped_states into the new struct RegroupedStates
    {
        increment = 0;
        for (int j = 0; j < automaton.nb_characters; j++)
        {
            regrouped_states[i].states[j] = grouped_states[i][j];
            increment++;
        }
        biggest_state = biggest_state + 1;
        regrouped_states[i].new_state = biggest_state;
        regrouped_states[i].size = increment;
        if (i == 0)
            longest_group = increment;
        if (regrouped_states[i - 1].size < increment) // This if state is to catch the longest grouped state
            longest_group = increment;
        size_regrouped_state++;
    }

    int nb_etat = 0;
    int test = 1;
    for (int i = 0; i < automaton.nbEtats; i++) // This for loop is to insert all the old states into the new automaton except the states that have been regrouped (they will be inserted in the next for loop)
    {
        test = 1;
        for (int h = 0; h < automaton.nb_characters; h++)
        {
            for (int j = 0; j < automaton.nb_characters; j++)
            {
                if (automaton.states[i] == regrouped_states[h].states[j])
                {
                    // printf("%d", regrouped_states[h].states[j]);
                    test = 0;
                }
            }
        }
        if (test)
        {
            new_automaton.states[nb_etat] = automaton.states[i];
            nb_etat++;
        }
    }
    int temp = 0;
    for (int i = 0; i < size_regrouped_state; i++) // This for loop is to insert the new states in the struct regrouped_states
    {
        new_automaton.states[nb_etat] = regrouped_states[i].new_state;
        nb_etat++;
        temp++;
    }

    int null_state = nb_etat;
    new_automaton.states[nb_etat] = null_state;
    nb_etat++;
    int new_state = 0;
    transitions = first_transition->first;
    int *next_states = malloc(sizeof(int) * longest_group);
    for (int i = 0; i < nb_etat; i++)
    {
        for (int k = 0; k < automaton.nb_characters; k++)
        {
            increment = 0;
            if (transitions == NULL)
            {
                transitions = first_transition->first;
            }
            while (transitions != NULL)
            {
                if (new_automaton.states[i] == transitions->starting_state)
                {
                    if (automaton.characters[k] == transitions->character)
                    {
                        next_states[increment] = transitions->next_state;
                        increment++;
                    }
                }
                transitions = transitions->next_transition;
            }
            if (increment > 1)
            {
                for (int j = 0; j < 4; j++)
                    insertionOfTransition(new_automaton.first_transition, new_automaton.states[i], automaton.characters[k], next_states[0]);
            }
        }
    }
    printf("\n");
    displayTransitions(new_automaton.first_transition);
}