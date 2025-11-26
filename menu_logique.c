#include <stdio.h>
#include <stdlib.h>
#include "menu_logique.h"
#include "gestion_voitures.h"
#include "statistiques.h"

/**
 * Affiche le menu principal
 */
void afficherMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║     PARKING INTELLIGENT v1.0           ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
    printf("  1. 🚗 Enregistrer une entrée\n");
    printf("  2. 🚙 Enregistrer une sortie\n");
    printf("  3. 📋 Voir les voitures présentes\n");
    printf("  4. 📜 Afficher l'historique complet\n");
    printf("  5. 📊 Afficher les statistiques\n");
    printf("  6. 💾 Sauvegarder et quitter\n");
    printf("\n");
    printf("  Votre choix : ");
}

/**
 * Lit et valide le choix de l'utilisateur
 */
int lireChoix() {
    int choix;
    if (scanf("%d", &choix) != 1) {
        // Nettoyage du buffer en cas d'entrée invalide
        while (getchar() != '\n');
        return -1;
    }
    // Nettoyage du buffer
    while (getchar() != '\n');
    return choix;
}

/**
 * Gère l'entrée d'une nouvelle voiture
 */
void traiterEntree() {
    char plaque[TAILLE_PLAQUE];
    int heure;
    
    printf("\n┌─────────────────────────────┐\n");
    printf("│   ENREGISTREMENT ENTRÉE     │\n");
    printf("└─────────────────────────────┘\n\n");
    
    printf("Plaque d'immatriculation : ");
    scanf("%s", plaque);
    
    printf("Heure d'entrée (0-23) : ");
    if (scanf("%d", &heure) != 1) {
        printf("❌ Entrée invalide !\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    ajouterVoiture(plaque, heure);
}

/**
 * Gère la sortie d'une voiture
 */
void traiterSortie() {
    char plaque[TAILLE_PLAQUE];
    int heure;
    
    printf("\n┌─────────────────────────────┐\n");
    printf("│   ENREGISTREMENT SORTIE     │\n");
    printf("└─────────────────────────────┘\n\n");
    
    printf("Plaque d'immatriculation : ");
    scanf("%s", plaque);
    
    printf("Heure de sortie (0-23) : ");
    if (scanf("%d", &heure) != 1) {
        printf("❌ Entrée invalide !\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    enregistrerSortie(plaque, heure);
}

/**
 * Affiche l'historique complet des tickets
 */
void afficherHistorique() {
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                    HISTORIQUE COMPLET                         ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    if (nbVoitures == 0) {
        printf("  Aucun ticket enregistré.\n\n");
        return;
    }
    
    printf("┌──────────┬────────┬────────┬─────────┬──────────┐\n");
    printf("│  Plaque  │ Entrée │ Sortie │  Durée  │  Montant │\n");
    printf("├──────────┼────────┼────────┼─────────┼──────────┤\n");
    
    for (int i = 0; i < nbVoitures; i++) {
        printf("│ %-8s │  %2dh   │", 
               parking[i].plaque, 
               parking[i].heureEntree);
        
        if (parking[i].heureSortie == -1) {
            printf("  --    │   --    │    --    │\n");
        } else {
            int duree = parking[i].heureSortie - parking[i].heureEntree;
            if (duree < 0) duree += 24;
            
            printf("  %2dh   │  %2dh    │  %.2f €  │\n",
                   parking[i].heureSortie,
                   duree,
                   parking[i].montant);
        }
    }
    
    printf("└──────────┴────────┴────────┴─────────┴──────────┘\n\n");
}

/**
 * Boucle principale du menu
 */
void executerMenu() {
    int choix;
    int continuer = 1;
    
    // Chargement des données au démarrage
    chargerDonnees();
    
    while (continuer) {
        afficherMenu();
        choix = lireChoix();
        
        switch (choix) {
            case 1:
                traiterEntree();
                break;
            case 2:
                traiterSortie();
                break;
            case 3:
                afficherVoituresPresentes();
                break;
            case 4:
                afficherHistorique();
                break;
            case 5:
                afficherStatistiques();
                break;
            case 6:
                sauvegarderDonnees();
                printf("\n✅ Données sauvegardées. Au revoir !\n\n");
                continuer = 0;
                break;
            default:
                printf("\n❌ Choix invalide ! Veuillez choisir entre 1 et 6.\n");
        }
        
        if (continuer) {
            printf("\nAppuyez sur ENTRÉE pour continuer...");
            getchar();
        }
    }
}
