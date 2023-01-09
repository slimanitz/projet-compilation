#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"

int searchMethod(Automate automaton, int search_state, char character, RegroupedStates *regrouped_states, int size_regrouped_states, int longest_group);

void determinisationOfAutomaton(Automate automaton)
{

    Transitions *transitions_initial_state = malloc(sizeof(Transitions) * automaton.nb_transitions);

    RegroupedStates *regrouped_states = malloc(sizeof(RegroupedStates) * automaton.nbEtats);

    Automate new_automaton;
    new_automaton.transitions = malloc(sizeof(Transitions) * automaton.nb_transitions);
    new_automaton.characters = malloc(sizeof(char) * automaton.nbEtats);
    new_automaton.characters = automaton.characters;
    new_automaton.nb_characters = automaton.nb_characters;
    new_automaton.states = malloc(sizeof(int) * automaton.nbEtats);

    for (int i = 0; i < automaton.nbEtats; i++) // This for loop is for the initialisation of the size of the states
    {
        regrouped_states[i].states = malloc(sizeof(int) * (automaton.nbEtats * 2));
    }

    int increment = 0; // variable that will give total number of transition that has as starting state the initial state

    for (int i = 0; i < automaton.nb_transitions; i++) // This for loop is to extract all the transitions that have as starting state the initial state (0)
    {
        if (automaton.transitions[i].starting_state == 0)
        {
            transitions_initial_state[i].starting_state = automaton.transitions[i].starting_state;
            transitions_initial_state[i].character = automaton.transitions[i].character;
            transitions_initial_state[i].next_state = automaton.transitions[i].next_state;
            increment++;
        }
    }

    transitions_initial_state = realloc(transitions_initial_state, sizeof(Transitions) * increment);

    char **grouped_states = create_matrix(automaton.nb_characters, increment);

    int biggest_state = automaton.biggest_state;

    char character;
    int k;
    for (int i = 0; i < automaton.nb_characters; i++) // This for loop is to grouped states for the determinisation of the automaton
    {
        k = 0;
        character = automaton.characters[i];
        for (int j = 0; j < increment; j++)
        {
            if (character == automaton.transitions[j].character)
            {
                grouped_states[i][k] = automaton.transitions[j].next_state;
                k++;
            }
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

    for (int i = 0; i < automaton.nb_characters; i++)
        free(grouped_states[i]);
    free(grouped_states);

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
    for (int i = 0; i < size_regrouped_state; i++) // This for loop is to insert the new states from the struct regrouped_states
    {
        new_automaton.states[nb_etat] = regrouped_states[i].new_state;
        nb_etat++;
        temp++;
    }

    new_automaton.states[nb_etat] = biggest_state + 1;
    nb_etat++;
    new_automaton.nbEtats = nb_etat;
    int id = 0;
    int new_state = 0;
    int *next_states = malloc(sizeof(int) * longest_group);

    for (int i = 0; i < nb_etat; i++)
    {
        test = 0;
        for (int k = 0; k < automaton.nb_characters; k++)
        {
            increment = 0;

            for (int j = 0; j < automaton.nb_transitions; j++)
            {
                for (int t = 0; t < size_regrouped_state; t++)
                {
                    // printf(" %d   %d\n ", new_automaton.states[i], regrouped_states[t].new_state);
                    if (new_automaton.states[i] == regrouped_states[t].new_state)
                    {
                        for (int n = 0; n < regrouped_states[t].size; n++)
                        {
                            for (int f = 0; f < automaton.nb_characters; f++)
                            {
                                new_state = searchMethod(automaton, regrouped_states[t].states[n], automaton.characters[f], regrouped_states, size_regrouped_state, longest_group);
                                new_automaton.transitions[i].starting_state = new_automaton.states[i];
                                new_automaton.transitions[i].character = automaton.characters[f];
                                new_automaton.transitions[i].next_state = new_state;
                                // printf("De l'état %d a %d on a: %c\n", new_automaton.transitions[i].starting_state, new_automaton.transitions[i].next_state, new_automaton.transitions[i].character);
                            }
                        }
                        // printf(" %d   %d\n ", new_automaton.states[i], regrouped_states[t].new_state);
                        // printf("Hello \n");
                        test = 1;
                    }
                }
                if (new_automaton.states[i] == automaton.transitions[j].starting_state)
                {
                    if (automaton.characters[k] == automaton.transitions[j].character)
                    {
                        // printf("Third    %d\n", automaton.transitions[j].starting_state);
                        next_states[increment] = automaton.transitions[j].next_state;
                        increment++;
                    }
                }
            }

            if (test != 1)
            {
                // printf("Hello   %d \n", new_automaton.states[i]);
                if (increment > 1)
                {
                    for (int h = 0; h < temp; h++)
                    {
                        for (int j = 0; j < longest_group; j++)
                        {
                            if (next_states[h] == regrouped_states[h].states[j])
                            {
                                new_state = regrouped_states[h].new_state;
                            }
                        }
                    }
                    new_automaton.transitions[i].starting_state = new_automaton.states[i];
                    new_automaton.transitions[i].character = automaton.characters[k];
                    new_automaton.transitions[i].next_state = new_state;
                    // printf("First   %d \n", new_state);
                    // printf("First De l'état %d a %d on a: %c\n", new_automaton.transitions[i].starting_state, new_automaton.transitions[i].next_state, new_automaton.transitions[i].character);
                }
                else
                {
                    new_automaton.transitions[i].starting_state = new_automaton.states[i];
                    new_automaton.transitions[i].character = automaton.characters[k];
                    new_automaton.transitions[i].next_state = next_states[0];
                    // printf("second   %d \n", next_states[0]);
                    // printf("Second De l'état %d a %d on a: %c\n", new_automaton.transitions[i].starting_state, new_automaton.transitions[i].next_state, new_automaton.transitions[i].character);
                }
            }
        }
    }

    printf("\n");

    // for (int i = 0; i < size_regrouped_state; i++)
    // {
    //     for (int j = 0; j < longest_group; j++)
    //     {
    //         printf("%d ", regrouped_states[i].new_state);
    //     }
    // }

    for (int i = 0; i < new_automaton.nbEtats; i++)
    {
        // printf("%d   ", new_automaton.states[i]);
        // printf("De l'état %d a %d on a: %c\n", new_automaton.transitions[i].starting_state, new_automaton.transitions[i].next_state, new_automaton.transitions[i].character);
    }
}

int searchMethod(Automate automaton, int search_state, char character, RegroupedStates *regrouped_states, int size_regrouped_states, int longest_group)
{
    int value;
    int *next_state = malloc(sizeof(int) * longest_group);
    int increment = 0;
    int new_state;
    for (int i = 0; i < automaton.nb_transitions; i++)
    {
        if (automaton.transitions[i].starting_state == search_state)
        {
            for (int j = 0; j < automaton.nb_characters; j++)
            {
                if (automaton.transitions[i].character == character)
                {
                    next_state[increment] = automaton.transitions[i].next_state;
                    increment++;
                }
                if (increment == 1)
                {
                    new_state = automaton.transitions[i].next_state;
                    // printf("Hello \n");
                }
            }
        }
    }

    if (increment > 1)
    {
        for (int i = 0; i < size_regrouped_states; i++)
        {
            for (int j = 0; j < longest_group; j++)
            {
                if (regrouped_states[i].states[j] == next_state[i])
                {
                    new_state = regrouped_states[i].new_state;
                }
            }
        }
        // printf("Hello \n");
    }
    // printf("%d   \n", new_state);
    return new_state;
}
