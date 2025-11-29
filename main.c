/**
 * PARKING INTELLIGENT
 * * Programme de gestion d'un parking avec:
 * - Enregistrement des entrees/sorties
 * - Calcul automatique des montants (2e/heure)
 * - Statistiques
 * - Sauvegarde persistante
 * * Auteurs: [Noms des etudiants]
 * Date: [Date]
 */

#include <stdio.h>
#include "gestion_voitures.h"
#include "menu_logique.h"
#include "statistiques.h"

int main() {
    printf("\n");
    printf("========================================\n");
    printf("|   Bienvenue au Parking Intelligent !   |\n");
    printf("========================================\n");
    printf("\n");
    
    // Lancement du menu principal
    executerMenu();
    
    return 0;
}