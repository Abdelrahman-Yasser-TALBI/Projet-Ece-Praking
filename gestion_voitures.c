#include <stdio.h>
#include <string.h>
#include "gestion_voitures.h"

// Variables globales
Voiture parking[MAX_VOITURES];
int nbVoitures = 0;

/**
 * Verifie si une voiture existe deja dans le parking (non sortie)
 * Retourne 1 si existe, 0 sinon
 */
int verifierExistence(const char* plaque) {
    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(parking[i].plaque, plaque) == 0 && parking[i].heureSortie == -1) {
            return 1;
        }
    }
    return 0;
}

/**
 * Recherche une voiture par sa plaque
 * Retourne l'index si trouvee, -1 sinon
 */
int rechercherVoiture(const char* plaque) {
    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(parking[i].plaque, plaque) == 0 && parking[i].heureSortie == -1) {
            return i;
        }
    }
    return -1;
}

/**
 * Ajoute une nouvelle voiture dans le parking
 * Retourne 1 si succes, 0 si echec
 */
int ajouterVoiture(const char* plaque, int heureEntree) {
    // Verification de la capacite
    if (nbVoitures >= MAX_VOITURES) {
        printf("x Parking complet !\n");
        return 0;
    }
    
    // Verification si la voiture est deja presente
    if (verifierExistence(plaque)) {
        printf("x Cette voiture est dejq dans le parking !\n");
        return 0;
    }
    
    // Validation de l'heure
    if (heureEntree < 0 || heureEntree > 23) {
        printf("x Heure invalide (doit etre entre 0 et 23) !\n");
        return 0;
    }
    
    // Ajout de la voiture
    strcpy(parking[nbVoitures].plaque, plaque);
    parking[nbVoitures].heureEntree = heureEntree;
    parking[nbVoitures].heureSortie = -1;
    parking[nbVoitures].montant = 0.0;
    nbVoitures++;
    
    printf("a Voiture %s enregistree a %dh\n", plaque, heureEntree);
    return 1;
}

/**
 * Enregistre la sortie d'une voiture et calcule le montant
 * Retourne 1 si succes, 0 si echec
 */
int enregistrerSortie(const char* plaque, int heureSortie) {
    int index = rechercherVoiture(plaque);
    
    if (index == -1) {
        printf("x Voiture non trouvee dans le parking !\n");
        return 0;
    }
    
    // Validation de l'heure
    if (heureSortie < 0 || heureSortie > 23) {
        printf("x Heure invalide (doit etre entre 0 et 23) !\n");
        return 0;
    }
    
    // Calcul de la duree
    int duree = heureSortie - parking[index].heureEntree;
    if (duree < 0) {
        duree += 24;  // Gestion du passage a minuit
    }
    
    // Calcul du montant (2e par heure)
    parking[index].heureSortie = heureSortie;
    parking[index].montant = duree * 2.0;
    
    printf("\n===============================\n");
    printf("       TICKET DE SORTIE\n");
    printf("===============================\n");
    printf("Plaque      : %s\n", parking[index].plaque);
    printf("Entree      : %dh\n", parking[index].heureEntree);
    printf("Sortie      : %dh\n", parking[index].heureSortie);
    printf("Duree       : %d heure(s)\n", duree);
    printf("Montant     : %.2f e\n", parking[index].montant);
    printf("===============================\n\n");
    
    return 1;
}

/**
 * Affiche toutes les voitures actuellement presentes
 */
void afficherVoituresPresentes() {
    int compteur = 0;
    
    printf("\n===================================\n");
    printf("|   VOITURES DANS LE PARKING      |\n");
    printf("===================================\n\n");
    
    for (int i = 0; i < nbVoitures; i++) {
        if (parking[i].heureSortie == -1) {
            printf("  Plaque: %-10s | Entree: %2dh\n", 
                        parking[i].plaque, 
                        parking[i].heureEntree);
            compteur++;
        }
    }
    
    if (compteur == 0) {
        printf("   Aucune voiture dans le parking.\n");
    }
    
    printf("\n   Total: %d voiture(s) presente(s)\n\n", compteur);
}