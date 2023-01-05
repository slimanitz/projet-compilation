#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"

struct Automate
{
    int nbEtats;
    FirstAcceptedState *first_accepted_state;
    int nbTransitions;
    FirstTransition *first_transition;
  
};
struct Automate automate;

void parseAutomate(char *nomAutomate);
void executionAutomateSurMot(char *mot);

int main(int argc, char *argv[])
{
    char *nomAutomate = argv[1];
    parseAutomate(nomAutomate);
    //executionAutomateSurMot("aa");

    return 0;
}

// int checkIfTransitionPass(char *c, int etat)
// {
//     for (int i = 0; i < automate.nbTransitions; i++)
//     {
//         printf("Here: %d,There: %d\n", i, automate.nbTransitions);

//         if (etat == automate.transitions[i].etatDeparts)
//         {
//             if (strcmp(c, automate.transitions[i].transition))
//             {
//                 printf("L'etat: %d, fait passer la lettre: %c\n", etat, *c);
//                 return 1;
//             }
//         }
//         else if (etat < automate.transitions[i].etatDeparts)
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


int checkIfStateAccepteur(int etat){


    if (automate.first_accepted_state == NULL)
    {
        exit(EXIT_FAILURE);
    }

    AcceptedStates *state = automate.first_accepted_state->first;

    while (state != NULL)
    {
        if(state->state == etat ){return 1;}
        state = state->next;
    }
    return 0;
}

// int checkIfAccepteur(int numeroEtat){

// }
void parseAutomate(char *nomAutomate)
{
    FILE *file = fopen(nomAutomate, "r");
    automate.first_accepted_state = malloc(sizeof(*automate.first_accepted_state));
    automate.first_transition = malloc(sizeof(*automate.first_transition));
    // Check if the file was successfully opened
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    // Declare a buffer for reading the file
    char line[1024];
    int i = 0;
    // Read the file line by line
    while (fgets(line, sizeof(line), file))
    {
        // Print the line to the console
        if (i == 0)
        {
            automate.nbEtats = atoi(line);
            printf("Le nombre d'états est: %d\n", automate.nbEtats);
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
                insertion(automate.first_accepted_state, atoi(token));  
                token = strtok(NULL, " ");                          // Get the next token (word)
                j++;
            }
            printf("Les etats accepteurs sont: ");
            displayFirstAcceptedState(automate.first_accepted_state);
            printf("\n");
        }
        if (i >= 2)
        {
            automate.nbTransitions++;
            char *token = strtok(line, " ");
            int j = 0;
            int etatDeparts =0;
            int prochainEtat =0;
            char transition;
            while (token != NULL)
            {
                int len = strlen(token);
                if (token[len - 1] == '\n')
                {
                    token[len - 1] = '\0';
                }

                switch (j)
                {
                case 0:
                    etatDeparts = atoi(token);
                    break;
                case 1:
                    transition = token[0];
                    break;
                case 2:
                    prochainEtat = atoi(token);
                    break;

                default:
                    break;
                }
                token = strtok(NULL, " "); // Get the next token (word)
                j++;
            }
            insertTransition(automate.first_transition,etatDeparts,transition,prochainEtat);

        }
        i++;
    }
    printf("Les transitions sont: \n");
    displayTransitions(automate.first_transition);
    fclose(file);
}


