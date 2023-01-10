#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "determinisation.c"

Automate automate;

void parseAutomate(char *nomAutomate);
void executionAutomateSurMot(char *mot);

int main(int argc, char *argv[])
{
    char *nomAutomate = argv[1];
    parseAutomate(nomAutomate);
    // executionAutomateSurMot("aa");

    return 0;
}

// int checkIfTransitionPass(char *c, int etat)
// {
//     for (int i = 0; i < automate.nb_transactions; i++)
//     {
//         printf("Here: %d,There: %d\n", i, automate.nb_transactions);

//         if (etat == automate.transitions[i].starting_state)
//         {
//             if (strcmp(c, automate.transitions[i].transition))
//             {
//                 printf("L'etat: %d, fait passer la lettre: %c\n", etat, *c);
//                 return 1;
//             }
//         }
//         else if (etat < automate.transitions[i].starting_state)
//         {
//             printf("L'etat: %d, ne fait pas  passer la lettre: %c\n", etat, *c);
//             return 0;
//         }
//     }

//     return 0;
// }

void executionAutomateSurMot(char *mot)
{
    char lettreMot[strlen(mot) + 1];
    strcpy(lettreMot, mot);
    int etatDansLeMot = 0;

    if (automate.first_transition == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Transitions *transition = automate.first_transition->first;
}

void parseAutomate(char *nomAutomate)
{
    FILE *file = fopen(nomAutomate, "r");
    automate.first_transition = malloc(sizeof(*automate.first_transition));
    automate.transitions = malloc(sizeof(Transitions) * 20);
    automate.nb_characters = 0;
    // Check if the file was successfully opened
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    // Declare a buffer for reading the file
    char line[1024];
    int i = 0;
    int test = 1; // use to test if the character exists or not in the character arrays
    int nb_etats = 0;
    automate.biggest_state = 0;
    int increment = 0; // To increment the indexes of the array transitions in the automaton
    // Read the file line by line
    while (fgets(line, sizeof(line), file))
    {
        // Print the line to the console
        if (i == 0)
        {
            automate.nbEtats = atoi(line);
            // printf("Le nombre d'états est: %d\n\n", automate.nbEtats);
            automate.characters = malloc(sizeof(char) * automate.nbEtats); // Initialisation of the size of the array that will store that characters of the automate
            for (int i = 0; i < automate.nbEtats; i++)
            {
                automate.characters[i] = ' ';
            }
            automate.states = malloc(sizeof(int) * automate.nbEtats); // Initialisation of the size of the array that will store that characters of the automate
            for (int i = 0; i < (automate.nbEtats - 1); i++)
            {
                automate.states[i] = -1;
            }
            automate.accepted_states = malloc(sizeof(int) * automate.nbEtats);
        }
        if (i == 1)
        {
            // TEST IF THE LINE IS EMPTY AS WELL
            char *token = strtok(line, " ");
            int j = 0;
            while (token != NULL)
            {
                int len = strlen(token);
                if (token[len - 1] == '\n')
                {
                    token[len - 1] = '\0';
                }
                automate.accepted_states[j] = atoi(token);
                token = strtok(NULL, " "); // Get the next token (word)
                j++;
            }
            automate.accepted_states = realloc(automate.accepted_states, sizeof(int) * j);
            printf("\n");
            printf("Les etats accepteurs sont: ");
            for (int i = 0; i < j; i++)
                printf("%d ", automate.accepted_states[i]);
            printf("\n");
        }
        if (i >= 2)
        {
            automate.nb_transitions++;
            char *token = strtok(line, " ");
            int j = 0;
            int starting_state = 0;
            int next_state = 0;
            char transition;
            while (token != NULL)
            {
                int len = strlen(token);
                if (token[len - 1] == '\n')
                {
                    token[len - 1] = '\0';
                }
                test = 1;
                switch (j)
                {
                case 0:
                    starting_state = atoi(token);
                    if (starting_state > automate.biggest_state)
                    {
                        automate.biggest_state = starting_state;
                    }
                    test = 1;
                    for (int i = 0; i < automate.nbEtats; i++)
                    {
                        if (atoi(token) == automate.states[i])
                            ;
                        {
                            test = 0;
                        }
                    }
                    if (test)
                    {
                        automate.states[nb_etats] = atoi(token);
                        nb_etats++;
                    }
                    break;
                case 1:
                    transition = token[0];
                    for (int i = 0; i < automate.nbEtats; i++) // This for loop is to extract the characters of the automaton and store in the array character declared above
                    {
                        if (token[0] == automate.characters[i])
                        {
                            test = 0;
                        }
                    }
                    if (test)
                    {
                        if (automate.nbEtats <= automate.nb_characters)
                        {
                            automate.characters = malloc(sizeof(automate.nbEtats * 2));
                        }
                        automate.characters[automate.nb_characters] = token[0];
                        automate.nb_characters++;
                    }
                    break;
                case 2:
                    next_state = atoi(token);
                    if (next_state > automate.biggest_state)
                    {
                        automate.biggest_state = next_state;
                    }
                    test = 1;
                    for (int i = 0; i < automate.nbEtats; i++)
                    {
                        if (atoi(token) == automate.states[i])
                        {
                            test = 0;
                        }
                    }
                    if (test)
                    {
                        automate.states[nb_etats] = atoi(token);
                        nb_etats++;
                    }
                    break;
                default:
                    break;
                }
                token = strtok(NULL, " "); // Get the next token (word)
                j++;
            }
            automate.transitions[increment].starting_state = starting_state;
            automate.transitions[increment].character = transition;
            automate.transitions[increment].next_state = next_state;
            increment++;
        }
        i++;
    }
    automate.transitions = realloc(automate.transitions, sizeof(Transitions) * increment);
    printf("\n");
    printf("Les transitions sont: \n\n");
    for (int i = 0; i < automate.nb_transitions; i++)
    {
        printf("De l'état %d a %d on a: %c\n", automate.transitions[i].starting_state, automate.transitions[i].next_state, automate.transitions[i].character);
    }
    printf("\n");
    fclose(file);
}