#include<stdio.h>
#include <stdlib.h>
#include <string.h>
struct Automate
{
    int nbEtats;
    int etatsAccepteurs[20];
    struct Transitions{
        int etatDeparts;
        char *transition;
        int prochainEtat;
    } transitions[30];
};
struct Automate automate;


void parseAutomate(char *nomAutomate);




int main(int argc, char *argv[]) {
    char *nomAutomate = argv[1];
    parseAutomate(nomAutomate);
    return 0;
}



void parseAutomate(char *nomAutomate){
    FILE *file = fopen(nomAutomate, "r");

    // Check if the file was successfully opened
    if (file == NULL) {
        perror("Error opening file");
        return ;
    }

    // Declare a buffer for reading the file
    char line[1024];
    int i = 0;
    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Print the line to the console
        if ( i == 0)
        {
            automate.nbEtats = atoi(line);
            printf("Le nombre d'états est: %d\n",automate.nbEtats);
        }
        if (i == 1)
        {
            //TEST IF THE LINE IS EMPTY AS WELL
            char *token = strtok(line, " ");
            int j = 0;
            while (token != NULL) {
                int len = strlen(token);
                if (token[len -1] == '\n')
                {
                    token[len-1] = '\0';
                }
                automate.etatsAccepteurs[j] = atoi(token); //add the token to the list and convert it to an INT
                token = strtok(NULL, " ");  // Get the next token (word)
                j++;
            }
            int n = sizeof(automate.etatsAccepteurs) / sizeof(automate.etatsAccepteurs[0]);
            printf("Les etats accepteurs sont: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", automate.etatsAccepteurs[i]);
            }
            printf("\n");
        }
        if(i>=2){
            char *token = strtok(line, " ");
            int j = 0;
            while (token != NULL) {
                int len = strlen(token);
                 if (token[len -1] == '\n')
                {
                    token[len-1] = '\0';
                }
                switch (j)
                {
                case 0:
                    automate.transitions[i-2].etatDeparts = atoi(token);
                    break;
                case 1:
                    automate.transitions[i-2].transition = token;
                    break;
                case 2:
                    automate.transitions[i-2].prochainEtat = atoi(token);
                    break;
                
                default:
                    break;
                } 
                token = strtok(NULL, " ");  // Get the next token (word)
                j++;
            }

        }
        i++;
    }
    printf("Les transitions sont: \n");    
    for (int i = 0; i < automate.nbEtats -1; i++){
        printf("De l'état %d a %d on a %s\n",automate.transitions[i].etatDeparts,automate.transitions[i].prochainEtat,automate.transitions[i].transition);
    }
    // Close the file
    fclose(file);


}