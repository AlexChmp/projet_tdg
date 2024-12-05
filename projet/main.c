#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define taille 20

// Fonction pour lire le graphe depuis un fichier
void lecturetxt(const char *filename, int *n, char especes[][taille], double matriceajd[][100]) {
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

    // Lire la matrice d'adjacence avec les poids
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%lf", &matriceajd[i][j]);
        }
    }

    fclose(file);
}

// Fonction pour afficher les sommets (les animaux du réseau choisi)
void afficher_sommets(int n, char especes[][taille]) {
    printf("\n=== Liste des animaux du reseau ===\n");
    for (int i = 0; i < n; i++) {
        printf("- %s\n", especes[i]);
    }
    printf("===================================\n");
}

// Fonction pour afficher le réseau trophique (les arcs et les poids)
void afficher_reseau(int n, char especes[][taille], double matriceajd[][100]) {
    printf("\n=== Reseau trophique (arcs) ===\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriceajd[i][j] > 0) {
                printf("%s -> %s (poids: %.1f)\n", especes[i], especes[j], matriceajd[i][j]);
            }
        }
    }
    printf("===============================\n");
}

// Fonction pour rechercher un animal et afficher ce qu'il mange et ce qui le mange
void rechercher_animal(int n, char especes[][taille], double matriceajd[][100]) {
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

    // Afficher ce qu'il mange (successeurs)
    printf("%s mange : ", animal);
    int has_prey = 0;
    for (int j = 0; j < n; j++) {
        if (matriceajd[index][j] > 0) {
            printf("%s (poids: %.1f) ", especes[j], matriceajd[index][j]);
            has_prey = 1;
        }
    }
    if (!has_prey) {
        printf("Rien");
    }
    printf("\n");

    // Afficher ce qui le mange (prédécesseurs)
    printf("Les animaux qui mangent %s : ", animal);
    int has_predators = 0;
    for (int i = 0; i < n; i++) {
        if (matriceajd[i][index] > 0) {
            printf("%s (poids: %.1f) ", especes[i], matriceajd[i][index]);
            has_predators = 1;
        }
    }
    if (!has_predators) {
        printf("Rien");
    }
    printf("\n");
}

// Fonction pour afficher le menu et gérer les choix
void afficher_menu(int n, char especes[][taille], double matriceajd[][100]) {
    int choix;
    do {
        printf("\n=============== MENU ===============\n");
        printf("1. Afficher les sommets\n");
        printf("2. Afficher le reseau trophique (les arcs)\n");
        printf("3. Verifier la connexite\n");
        printf("4. Demander des renseignements sur un animal\n");
        printf("5. Simuler la disparition d'une espece\n");
        printf("6. Sauvegarder le reseau\n");
        printf("8. Rechercher un sommet particulier\n");
        printf("9. Quitter\n");
        printf("10. Afficher les chaines alimentaires d'une espece\n");
        printf("11. Calculer et afficher les niveaux trophiques\n");
        printf("====================================\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficher_sommets(n, especes);
                break;
            case 2:
                afficher_reseau(n, especes, matriceajd); // Affichage du réseau trophique
                break;
            case 3:
                printf("\nOption non implementee pour le moment.\n");
                break;
            case 4:
                rechercher_animal(n, especes, matriceajd); // Recherche de l'animal et affichage des prédateurs et proies
                break;
            case 5:
                printf("Retour au choix du reseau.\n");
                break;
            default:
                printf("Option invalide ou non implementee. Veuillez reessayer.\n");
        }
    } while (choix != 5);
}

// Fonction principale
int main() {
    double matriceajd[100][100];
    int n; // Nombre d'espèces
    char especes[100][taille];
    int choix;

    while (1) {
        printf("\nChoisissez le reseau trophique :\n");
        printf("1. Reseau trophique de la jungle\n");
        printf("2. Reseau trophique du monde marin\n");
        printf("3. Reseau trophique de la savane\n");
        printf("4. Quitter\n");
        printf("Entrez votre choix (1, 2, 3 ou 4) : ");
        scanf("%d", &choix);

        const char *filename;

        if (choix == 1) {
            filename = "matricejungle.txt";
        } else if (choix == 2) {
            filename = "matricemondemarin.txt";
        } else if (choix == 3) {
            filename = "matricesavane.txt";
        } else if (choix == 4) {
            printf("Au revoir !\n");
            break;
        } else {
            printf("Choix invalide. Veuillez reessayer.\n");
            continue;
        }

        // Charger le fichier dans la matrice
        lecturetxt(filename, &n, especes, matriceajd);

        // Afficher le menu pour ce réseau
        afficher_menu(n, especes, matriceajd);
    }

    return 0;
}
