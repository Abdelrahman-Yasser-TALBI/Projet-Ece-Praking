#ifndef GESTION_VOITURES_H
#define GESTION_VOITURES_H

#define MAX_VOITURES 100
#define TAILLE_PLAQUE 10

// Structure principale
typedef struct {
    char plaque[TAILLE_PLAQUE];
    int heureEntree;
    int heureSortie;  // -1 si pas encore sortie
    float montant;
} Voiture;

// Variables globales partagées
extern Voiture parking[MAX_VOITURES];
extern int nbVoitures;

// Prototypes des fonctions - Étudiant 1
int ajouterVoiture(const char* plaque, int heureEntree);
int rechercherVoiture(const char* plaque);
int verifierExistence(const char* plaque);
int enregistrerSortie(const char* plaque, int heureSortie);
void afficherVoituresPresentes();

#endif
