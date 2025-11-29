#include <stdio.h>
#include "statistiques.h"
#include "gestion_voitures.h"

/**
 * Compte le nombre de voitures qui sont sorties
 */
int compterVoituresSorties() {
    int compteur = 0;
    for (int i = 0; i < nbVoitures; i++) {
        if (parking[i].heureSortie != -1) {
            compteur++;
        }
    }
    return compteur;
}

/**
 * Calcule le revenu total du parking
 */
float calculerRevenuTotal() {
    float total = 0.0;
    for (int i = 0; i < nbVoitures; i++) {
        if (parking[i].heureSortie != -1) {
            total += parking[i].montant;
        }
    }
    return total;
}

/**
 * Calcule la duree moyenne de stationnement
 */
float calculerDureeMoyenne() {
    int totalDuree = 0;
    int nbSorties = 0;
    
    for (int i = 0; i < nbVoitures; i++) {
        if (parking[i].heureSortie != -1) {
            int duree = parking[i].heureSortie - parking[i].heureEntree;
            if (duree < 0) duree += 24;
            totalDuree += duree;
            nbSorties++;
        }
    }
    
    return nbSorties > 0 ? (float)totalDuree / nbSorties : 0.0;
}

/**
 * Affiche les statistiques du parking
 */
void afficherStatistiques() {
    int nbSorties = compterVoituresSorties();
    int nbPresentes = nbVoitures - nbSorties;
    float revenu = calculerRevenuTotal();
    float dureeMoyenne = calculerDureeMoyenne();
    
    printf("\n=======================================\n");
    printf("|          STATISTIQUES               |\n");
    printf("=======================================\n\n");
    
    printf("M Nombre total de voitures accueillies : %d\n", nbVoitures);
    printf("v Voitures actuellement presentes      : %d\n", nbPresentes);
    printf("a Voitures sorties                     : %d\n", nbSorties);
    printf("e Revenu total genere                  : %.2f e\n", revenu);
    
    if (nbSorties > 0) {
        printf("t Duree moyenne de stationnement       : %.2f heure(s)\n", dureeMoyenne);
    } else {
        printf("t Duree moyenne de stationnement       : N/A\n");
    }
    
    printf("\n");
}

/**
 * Sauvegarde les donnees dans un fichier texte
 */
void sauvegarderDonnees() {
    FILE* fichier = fopen(FICHIER_DONNEES, "w");
    
    if (fichier == NULL) {
        printf("x Erreur lors de l'ouverture du fichier de sauvegarde !\n");
        return;
    }
    
    // En-tete du fichier
    fprintf(fichier, "# PARKING INTELLIGENT - HISTORIQUE\n");
    fprintf(fichier, "# Format: PLAQUE HEURE_ENTREE HEURE_SORTIE MONTANT\n");
    fprintf(fichier, "# HEURE_SORTIE = -1 si voiture encore presente\n");
    fprintf(fichier, "#\n");
    fprintf(fichier, "%d\n", nbVoitures);
    
    // Sauvegarde de chaque voiture
    for (int i = 0; i < nbVoitures; i++) {
        fprintf(fichier, "%s %d %d %.2f\n",
                parking[i].plaque,
                parking[i].heureEntree,
                parking[i].heureSortie,
                parking[i].montant);
    }
    
    fclose(fichier);
    printf("S Donnees sauvegardees dans %s\n", FICHIER_DONNEES);
}

/**
 * Charge les donnees depuis le fichier texte
 */
void chargerDonnees() {
    FILE* fichier = fopen(FICHIER_DONNEES, "r");
    
    if (fichier == NULL) {
        printf("i Aucun fichier de donnees trouve. Demarrage avec un parking vide.\n");
        return;
    }
    
    char ligne[100];
    
    // Ignorer les lignes de commentaire
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (ligne[0] != '#') {
            break;
        }
    }
    
    // Lire le nombre de voitures
    sscanf(ligne, "%d", &nbVoitures);
    
    // Lire chaque voiture
    for (int i = 0; i < nbVoitures; i++) {
        fscanf(fichier, "%s %d %d %f",
                parking[i].plaque,
                &parking[i].heureEntree,
                &parking[i].heureSortie,
                &parking[i].montant);
    }
    
    fclose(fichier);
    printf("a Donnees chargees : %d enregistrement(s)\n", nbVoitures);
}