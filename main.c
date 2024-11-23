#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille 20

// Fonction pour lire le graph depuis un fichier
void lecturetxt(const char *filename, int *n, char especes[][taille], int matriceajd[][100]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n); // Lire le nombre d'espèces

    // Lire les noms des espèces
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%s", especes[i]);
    }

    // Lire la matrice d'adjacence
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%d", &matriceajd[i][j]);
        }
    }

    fclose(file);
}

// Fonction pour afficher le réseau trophique
void affichertxt(int n, char especes[][taille], int matriceajd[][100]) {
    printf("Reseau trophique :\n");
    for (int i = 0; i < n; i++) {
        printf("%s mange : ", especes[i]);
        int boolproie = 0;
        for (int j = 0; j < n; j++) {
            if (matriceajd[i][j] == 1) {
                printf("%s ", especes[j]);
                boolproie = 1;
            }
        }
        if (!boolproie) {
            printf("Rien");
        }
        printf("\n");
    }
}

// Fonction pour interroger une espèce spécifique
void recherche(int n, char especes[][taille], int matriceajd[][100]) {
    char animal[taille];
    printf("Entrez le nom de l'animal a interroger : ");
    scanf("%s", animal);

    // Trouver l'index de l'animal
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(especes[i], animal) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Animal non trouve dans le reseau.\n");
        return;
    }

    // Demander à l'utilisateur quel type de requête il souhaite
    int choice;
    printf("Que voulez-vous savoir sur %s ?\n", animal);
    printf("1. Que mange-t-il ?\n");
    printf("2. Qui mange-t-il ?\n");
    printf("3. Que mange-t-il et qui mange-t-il ?\n");
    printf("Entrez votre choix (1, 2 ou 3) : ");
    scanf("%d", &choice);

    if (choice == 1) {
        // Que mange-t-il ?
        printf("%s mange : ", animal);
        int boolproie = 0;
        for (int j = 0; j < n; j++) {
            if (matriceajd[index][j] == 1) {
                printf("%s ", especes[j]);
                boolproie = 1;
            }
        }
        if (!boolproie) {
            printf("Rien\n");
        } else {
            printf("\n");
        }
    } else if (choice == 2) {
        // Qui mange-t-il ?
        printf("Les animaux qui mangent %s : ", animal);
        int has_predators = 0;
        for (int i = 0; i < n; i++) {
            if (matriceajd[i][index] == 1) {
                printf("%s ", especes[i]);
                has_predators = 1;
            }
        }
        if (!has_predators) {
            printf("Rien\n");
        } else {
            printf("\n");
        }
    } else if (choice == 3) {
        // Que mange-t-il et qui mange-t-il ?
        // Que mange-t-il ?
        printf("%s mange : ", animal);
        int boolproie = 0;
        for (int j = 0; j < n; j++) {
            if (matriceajd[index][j] == 1) {
                printf("%s ", especes[j]);
                boolproie = 1;
            }
        }
        if (!boolproie) {
            printf("Rien\n");
        } else {
            printf("\n");
        }

        // Qui mange-t-il ?
        printf("Les animaux qui mangent %s : ", animal);
        int has_predators = 0;
        for (int i = 0; i < n; i++) {
            if (matriceajd[i][index] == 1) {
                printf("%s ", especes[i]);
                has_predators = 1;
            }
        }
        if (!has_predators) {
            printf("Rien\n");
        } else {
            printf("\n\n\n\n\n\n");
        }
    } else {
        printf("Choix invalide.\n");
    }
}
void conversion_dot(const char *filename, int n, char especes[][taille], int matriceajd[][100]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de la création du fichier DOT");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "graph trophic_network {\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriceajd[i][j] == 1) {
                fprintf(file, "    \"%s\" -- \"%s\";\n", especes[i], especes[j]);
            }
        }
    }

    fprintf(file, "}\n");
    fclose(file);
    printf("Fichier DOT genere : %s\n", filename);
}


int main() {
    int choice;
    const char *filename;
    const char *dotname;
    int n; // Nombre d'espèces
    char especes[100][taille]; // Tableau des noms des espèces
    int matriceajd[100][100]; // Matrice d'adjacence
    while (1){
        // Menu pour choisir le réseau trophique
        printf("Choisissez le reseau trophique :\n");
        printf("1. Reseau trophique de la jungle\n");
        printf("2. Reseau trophique du monde marin\n");
        printf("3. Quitter\n");
        printf("Entrez votre choix (1 , 2 , 3) : ");
        scanf("%d", &choice);

        if (choice == 1) {
            filename = "matricejungle.txt";
            dotname = "matricejungle.dot";
        } else if (choice == 2) {
            filename = "matricemondemarin.txt";
            dotname = "matricemondemarin.dot";

        }
        else if (choice == 3) {
            break;
        }
        else {
            printf("Choix invalide.\n");
            return 1;
        }

        // Lire le graph depuis le fichier
        lecturetxt(filename, &n, especes, matriceajd);
        // Afficher le réseau trophique choisi
        affichertxt(n, especes, matriceajd);
        conversion_dot(dotname, n, especes, matriceajd);
        // Interroger une espèce spécifique
        recherche(n, especes, matriceajd);

    }

    return 0;
}