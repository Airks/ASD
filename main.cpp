#include <iostream>

using namespace std;

struct t_voie{
    char typeVoie;
    int numero;
    double traffic;
    t_voie * autre;
};

typedef t_voie * ptr_voie;

// Liste des fonctions utlisées
// **********************************************************************

void afficherVoies(t_voie * );
void afficherT_voie(t_voie);
void mettreAvant(ptr_voie , ptr_voie & );
bool plusPetitOuEgal(ptr_voie , ptr_voie );
ptr_voie ajoutTete(t_voie * , char , int , double );
ptr_voie retraitPremier(ptr_voie &);
void supprimerChainage(ptr_voie &);
void placerEnOrdre(ptr_voie , ptr_voie &);
void inserer (ptr_voie , ptr_voie );
void placerEnOrdreRec(ptr_voie, ptr_voie &);
void trierParInsertion(ptr_voie & );
ptr_voie unSurDeux(ptr_voie & );

// **********************************************************************
int main(int argc, char const *argv[])
{
    ptr_voie tete = nullptr;
    tete = ajoutTete(tete, 'f', 119, 600);
    tete = ajoutTete(tete, 'q', 221, 150);
    tete = ajoutTete(tete, 'p', 238, 500);
    tete = ajoutTete(tete, 'h', 964, 500);
    tete = ajoutTete(tete, 'a', 102, 500);
    tete = ajoutTete(tete, 'p', 221, 500);
    tete = ajoutTete(tete, 'o', 298, 500);
    tete = ajoutTete(tete, 'g', 238, 500);
    tete = ajoutTete(tete, 'x', 456, 500);
    // tete = ajoutTete(tete, 'n', 548, 921);

    cout << "Voici le 1er chaînage: " << endl;
    afficherVoies(tete);

    ptr_voie test = unSurDeux(tete);
        
    cout << "Voici la nouvelle chaîne: " << endl;
    afficherVoies(test);

    cout << "Voici la chaîne précédente: " << endl;
    afficherVoies(tete);

    cout << "Suppression des chaînages..." << endl;
    supprimerChainage(tete);
    supprimerChainage(test);
    cout << "Fait." << endl;
    afficherVoies(tete);

    return 0;
}

// **********************************************************************
bool plusPetitOuEgal(ptr_voie p1, ptr_voie p2){
// Vrai si p1 est <= à p2
    bool resultat = false; // Ça c'est moche.

    // Verification de l'ordre lexicographique des deux char
    if ( (*p1).typeVoie < (*p2).typeVoie ){
        resultat = true;
    }else if ( (*p1).typeVoie == (*p2).typeVoie){
        // Verification de l'ordre des int
        if ( (*p1).numero < (*p2).numero ){
            resultat = true;
        }else if ( (*p1).numero == (*p2).numero){
            // Verification de l'ordre des double
            if ( (*p1).traffic < (*p2).traffic){
                resultat = true;
            }else if ( (*p1).traffic == (*p2).traffic){
                resultat = true;
            }
        }
    }
    return resultat;
}
// *********************************************************************
void mettreAvant(ptr_voie p1, ptr_voie & tete){
    // Il faut que les deux pointeurs appartiennent au même chaînage
    // p2 doit être le pointeur de tête du chaînage
    ptr_voie temp = tete;

    while( (*temp).autre != p1){
        temp = (*temp).autre;
    }
    // Maintenant temp pointe sur le maillon précédant p1
    (*temp).autre = (*p1).autre;
    // p1 est maintenant "isolé"
    (*p1).autre = tete;
    // p1 est maintenant en tête du chaînage.
    // Pour finir on modifie le pointeur de tête pour qu'il pointe effectivement la tête.
    tete = p1;

}
// *********************************************************************
ptr_voie ajoutTete(t_voie * pointeur, char type, int numero, double traffic){
/* ATTENTION : La mauvaise utilisation de cette fonction provoquera des fuites mémoire */    
/* Précondition: il faut que le pointeur en paramètre soit le pointeur de tête */
    
    // Initialisation du pointeur vers le nouvel "objet"
    t_voie * voie = new t_voie;

    (* voie).typeVoie = type;
    (* voie).numero = numero;
    (* voie).traffic = traffic;

    /* Dans le cas où le pointeur est "vide", il ne faut pas placer un objet "devant" car il pointerait
    vers un objet non initialisé. Il s'agit donc de renvoyer tout simplement le nouvel objet créé */
    if (pointeur == nullptr){
        pointeur = voie;
        (* pointeur).autre = nullptr;
        return pointeur;
    }else{
        (* voie).autre = pointeur;
        return voie;
    }
}
// **********************************************************************
ptr_voie retraitPremier(ptr_voie & P1){
/* ATTENTION : La mauvaise utilisation de cette fonction provoquera des fuites mémoire */
    ptr_voie temp = P1;
    // Le pointeur de tête est décalé vers la nouvelle tête
    P1 = (*P1).autre;
    return temp;
}

// **********************************************************************
void afficherVoies(t_voie * pointeur){
    // Si le chaînage n'a pas été initialisé il n'y a rien à afficher
    if ( pointeur == nullptr ){
        cerr << "Le chaînage est vide." << endl;
        return;
    }

    t_voie * temp = pointeur;
    while ((*temp).autre != nullptr ){
        afficherT_voie(* temp);
        temp = (*temp).autre;
    }
    // Le problème de cette boucle est qu'elle n'affiche pas le dernier élément
    afficherT_voie(* temp);
}
// **********************************************************************
void afficherT_voie(t_voie voie){
    cout << "Type voie: " << voie.typeVoie << endl;
    cout << "Numéro: "    << voie.numero   << endl;
    // Les deux endl ici sont juste esthétiques ↓
    cout << "Traffic: "   << voie.traffic  <<endl << endl;
}
// **********************************************************************
void supprimerChainage(ptr_voie & tete){
    ptr_voie temp = tete;
    
    while( (*tete).autre != nullptr){
        tete = (*tete).autre;
        delete temp;
        temp = tete;
    }
    tete = nullptr;
}
// **********************************************************************
void placerEnOrdre(ptr_voie p1, ptr_voie & tete){
/* Cette procédure place un maillon à sa place dans un chaînage*/
    // Dans le cas où l'objet est plus petit que la tête
    if (plusPetitOuEgal(p1, tete)){
        tete = ajoutTete(tete, (*p1).typeVoie, (*p1).numero, (*p1).traffic);

    }else{
        ptr_voie temp = tete;
        while ( (*temp).autre != nullptr && (plusPetitOuEgal((*temp).autre , p1))){
            temp = (*temp).autre;
        }
        inserer(p1, temp);
    }

}

void placerEnOrdreRec(ptr_voie p1, ptr_voie & tete){
    
    if(tete == nullptr||plusPetitOuEgal(p1,tete)){
        tete = ajoutTete( tete, (*p1).typeVoie, (*p1).numero, (*p1).traffic);
    }else{
        placerEnOrdreRec (p1,(*tete).autre);
    }
}

// ***********************************************************************
void inserer (ptr_voie p1, ptr_voie p2){
/* Cette procédure insère p1 entre p2 et l'élément suivant */
    (*p1).autre = (*p2).autre;
    (*p2).autre = p1;
}

// ***********************************************************************

void trierParInsertion(ptr_voie & chaine){
    ptr_voie chaineFinale = nullptr;
    ptr_voie temp = nullptr;

    while( chaine != nullptr){
        temp = chaine;
        chaine = (*chaine).autre;
        placerEnOrdreRec(temp, chaineFinale);
    }
    chaine = chaineFinale;
}

// ***********************************************************************
ptr_voie unSurDeux(ptr_voie & chaine){
/* Retourne un chainage contenant la moitié du chaînage passé en paramètre,
   en en prenant un sur deux.
*/
    ptr_voie p1 = chaine;
    ptr_voie p2;
    ptr_voie chainePair = nullptr;
    while ( p1 != nullptr && (*p1).autre != nullptr ){ // comparaison logique paresseuse
        p2 = (*p1).autre;
        chainePair = ajoutTete (chainePair, (*p2).typeVoie, (*p2).numero, (*p2).traffic );
        (*p1).autre = (*p2).autre;
        p1 = (*p2).autre;
        delete p2;
    }
    return chainePair;
}
