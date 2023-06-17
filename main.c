// Presentation du projet :

// Projet realise dans le cadre de ma deuxieme annee de cycle preparatoire a l'ESIREM, c'est un script code en langage C implementant un jeu de dames simple dans la console. Le jeu utilise un tableau a deux dimensions pour representer le plateau, et les joueurs peuvent effectuer des mouvements en fonction des regles du jeu de dames. Le projet comprend des fonctions pour initialiser le plateau, afficher le plateau a l'ecran, verifier la validite des mouvements et gerer le deroulement du jeu.



// Presentation des Fonctions :

// La fonction positionnement est utilisee pour initialiser un tableau a deux dimensions (plateau) avec une longueur donnee. Elle prend en parametre un pointeur vers un pointeur de caracteres (char**) representant le tableau et la longueur du tableau (longueur).
// La fonction affichage est utilisee pour afficher le contenu du tableau plateau a l'ecran. Elle prend en parametre un pointeur vers un pointeur de caracteres (char**) representant le tableau et la longueur du tableau (longueur).
// La fonction hors_plateau est utilisee pour verifier si des coordonnees (x et y) sont valides dans le tableau plateau. Elle renvoie 0 si les coordonnees sont en dehors des limites du tableau et 1 sinon.
// Les fonctions getX et getY sont utilisees pour extraire les coordonnees x et y a partir d'une chaine de caracteres (coordonne). Ces fonctions utilisent des operations de conversion de chaines en entiers pour obtenir les coordonnees numeriques
// La fonction mouvement_pion verifie si un mouvement d'un joueur (joueur) a partir de la position (x, y) a la position (a, b) est valide dans le tableau plateau. Elle renvoie 1 si le mouvement est valide et 0 sinon.
// La fonction mouvement_dame est similaire a mouvement_pion, mais elle est specifiquement utilisee pour verifier les mouvements d'une dame.
// La fonction jeu est la fonction principale du jeu. Elle prend en parametre le tableau plateau, sa longueur (longueur) et l'indice du tour du joueur (tourjoueur). Elle gere le deroulement du jeu en fonction des mouvements des joueurs.
// Les fonctions clear_screen et touche_entree servent juste pour l'affichage et la presentation du projet.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Liste des fonctions
void positionnement(char** plateau, int longueur_plateau);
void affichage(char** plateau, int longueur_plateau);
int hors_plateau(char** plateau, int longueur_plateau, int x, int y);
int getX(char coordonne[]);
int getY(char coordonne[]);
int mouvement_pion(char** plateau, int longueur_plateau, int x, int y, int a, int b, char joueur);
int mouvement_dame(char** plateau, int longueur_plateau, int x, int y, int a, int b, char joueur);
void jeu(char** plateau, int longueur_plateau, int tour_joueur);


void clear_screen() {
    #ifdef _WIN32                 // Windows
        system("cls");
    #else                         // Unix
        system("clear");
    #endif
}

void touche_entree() {
    printf("\nAPPUYER SUR ENTREE POUR JOUER\n");
    getchar(); // Attendre que l'utilisateur appuie sur "Entree"
}


int main(void) {
	clear_screen();
	printf("JEU DE DAMES\n"); // Attend l'appui sur la touche Entree
	printf("REY THEOPHILE 2A - PROJET ELECTRONIQUE S4\n"); // Efface l'ecran
	touche_entree();
	clear_screen();
	// Declaration et allocation dynamique d'un tableau 2D pour representer le plateau de jeu
	char** arr;
	int longueur_plateau = 8;
	arr = malloc(longueur_plateau * sizeof(char*));
	for (int i = 0; i < longueur_plateau; i++) {
		arr[i] = malloc(longueur_plateau * sizeof(char));
		for (int j = 0; j < longueur_plateau; j++)
			arr[i][j] = ' ';
	}
	// Initialise le plateau de jeu avec des espaces vides
	positionnement(arr, longueur_plateau);
	// Affiche le plateau de jeu
	affichage(arr, longueur_plateau);
	// Joue le jeu de dames
	jeu(arr, longueur_plateau, 1);
	// Libere la memoire allouee pour le plateau de jeu
	for (int i = 0; i < longueur_plateau - 1; i++) {
		free(arr[i]);
	}
	free(arr);
	return 0;


}


void positionnement(char** plateau, int longueur_plateau) {
    for (int i = 0; i < longueur_plateau; i += 2) {  // Parcours des rangees du plateau avec un pas de 2
        for (int j = 0; j < longueur_plateau; j++) {  // Parcours des colonnes du plateau
            if (j == 0 || j == 2) {  // Si la colonne est 0 ou 2
                plateau[i][j] = 'N';  // Positionne un pion noir (N)
            }
            else if (j == 1) {  // Si la colonne est 1
                plateau[i + 1][j] = 'N';  // Positionne un pion noir (N) dans la rangee suivante
            }
            if (j == 7 || j == 5) {  // Si la colonne est 7 ou 5
                plateau[i + 1][j] = 'B';  // Positionne un pion blanc (B) dans la rangee suivante
            }
            else if (j == 6) {  // Si la colonne est 6
                plateau[i][j] = 'B';  // Positionne un pion blanc (B)
            }
        }
    }
}


void affichage(char** plateau, int longueur_plateau) {
    // Affichage du plateau de jeu
	printf("   ---------------------------------\n");
    for (int i = longueur_plateau - 1; i >= 0; i--) {  // Parcours des rangees du plateau de haut en bas
        for (int j = 0; j < longueur_plateau; j++) {  // Parcours des colonnes du plateau de gauche a droite
            if (j == 0) {  // Si la colonne est la premiere colonne
                printf("%d  | %c ", i, plateau[j][i]);  // Affiche le numero de la rangee suivi du contenu de la case
            }
            else if (j == longueur_plateau - 1) {  // Si la colonne est la derniere colonne
                printf("| %c |", plateau[j][i]);  // Affiche le contenu de la case entre des barres verticales
            }
            else {  // Pour les autres colonnes
                printf("| %c ", plateau[j][i]);  // Affiche le contenu de la case entre des barres verticales
            }
        }
        printf("\n");  // Nouvelle ligne apres avoir affiche une rangee
		printf("   ---------------------------------"); // Nouvelle ligne de separation du plateau
		printf("\n"); // Nouvelle ligne apres avoir affiche une rangee
    }

    // Affichage des indices de colonnes
    for (int i = 0; i < longueur_plateau; i++) {  // Parcours des colonnes du plateau
        if (i == 0) {  // Si c'est la premiere colonne
            printf("     %c ", i + 'A');  // Affiche l'indice de colonne sous forme de lettre
        }
        else if (i == 9) {  // Si c'est la derniere colonne
            printf("  %c\n", i + 'A');  // Affiche l'indice de colonne sous forme de lettre avec un retour a la ligne
        }
        else {  // Pour les autres colonnes
            printf("  %c ", i + 'A');  // Affiche l'indice de colonne sous forme de lettre suivie d'un espace
        }
    }
    printf("\n");  // Nouvelle ligne a la fin de l'affichage du plateau
}


int hors_plateau(char** plateau, int longueur_plateau, int x, int y) {
    if (x < 0 || x >= longueur_plateau || y < 0 || y >= longueur_plateau) {
        // Si les coordonnees (x, y) sont en dehors des limites du plateau
        return 0;  // Renvoyer 0 pour indiquer que les coordonnees sont hors du plateau
    }
    else {
        // Si les coordonnees (x, y) sont a l'interieur des limites du plateau
        return 1;  // Renvoyer 1 pour indiquer que les coordonnees sont a l'interieur du plateau
    }
}


int getX(char coordonne[]) {
    return coordonne[0] - 'A';
    // Soustraire le caractere 'A' de la premiere lettre de la chaine pour obtenir la valeur de la coordonnee X
    // 'A' - 'A' = 0, 'B' - 'A' = 1, 'C' - 'A' = 2, etc.
}


int getY(char coordonne[]) {
    char* i = &coordonne[1];
    // Pointeur i pointe vers le deuxieme caractere de la chaine (apres la premiere lettre)
    int y = atoi(i);
    // Convertir la sous-chaine apres la premiere lettre en un entier
    // Exemple : "A10" -> y = 10
    return y;
}


int mouvement_pion(char** plateau, int longueur_plateau, int x, int y, int a, int b, char joueur) {
    // Les parametres x, y representent les coordonnees de depart du pion
    // Les parametres a, b representent les coordonnees d'arrivee du pion
    // Le parametre joueur indique le joueur actuel (N pour noir, B pour blanc)
    if (plateau[x][y] == joueur && plateau[a][b] == ' ') {
        // Verifier si le pion aux coordonnees de depart appartient au joueur et que la case d'arrivee est vide
        if (abs(x - a) == 1) {
            // Si le deplacement est d'une case en diagonale
            if ((joueur == 'N') && (b - y == 1))
                // Si le joueur noir se deplace vers le haut (increment de 1 en y)
                return 1;
            else if ((joueur == 'B') && (b - y == -1))
                // Si le joueur blanc se deplace vers le bas (decrement de 1 en y)
                return 1;
        }
        else if (abs(x - a) == 2) {
            // Si le deplacement est de deux cases en diagonale
            if (joueur == 'N' && (b - y == 2) &&
                (plateau[(x + a) / 2][(y + b) / 2] == 'B' || plateau[(x + a) / 2][(y + b) / 2] == '$'))
                // Si le joueur noir effectue un kill en sautant par-dessus un pion blanc ('B') ou une dame blanche ('$')
                return 1;
            else if (joueur == 'B' && (b - y == -2) &&
                (plateau[(x + a) / 2][(y + b) / 2] == 'N' || plateau[(x + a) / 2][(y + b) / 2] == '#'))
                // Si le joueur blanc effectue un kill en sautant par-dessus un pion noir ('N') ou une dame noire ('#')
                return 1;
        }
    }
    return 0; // Retourne 0 si le mouvement n'est pas valide
}


int mouvement_dame(char** plateau, int longueur_plateau, int x, int y, int a, int b, char joueur) {
    // Les parametres x, y representent les coordonnees de depart de la dame
    // Les parametres a, b representent les coordonnees d'arrivee de la dame
    // Le parametre joueur indique le joueur actuel ('#' pour les dames noires, '$' pour les dames blanches)
    if (plateau[x][y] == joueur && plateau[a][b] == ' ') {
        // Verifier si la dame aux coordonnees de depart appartient au joueur et que la case d'arrivee est vide
        // Verifier le cas d'un deplacement simple
        if (abs(x - a) == 1) {
            // Si le deplacement est d'une seule case en diagonale
            if ((joueur == '#') && (abs(b - y) == 1))
                // Si la dame noire se deplace d'une case dans n'importe quelle direction diagonale
                return 1;
            else if ((joueur == '$') && (abs(b - y) == 1))
                // Si la dame blanche se deplace d'une case dans n'importe quelle direction diagonale
                return 1;
        }
        // Verifier le cas d'un saut (kill)
        else if (abs(x - a) == 2) {
            // Si le deplacement est de deux cases en diagonale
            if (joueur == '#' && (abs(b - y) == 2) &&
                (plateau[(x + a) / 2][(y + b) / 2] == 'B' || plateau[(x + a) / 2][(y + b) / 2] == '$'))
                // Si la dame noire effectue un kill en sautant par-dessus un pion blanc ('B') ou une dame blanche ('$')
                return 1;
            else if (joueur == '$' && (abs(b - y) == 2) &&
                (plateau[(x + a) / 2][(y + b) / 2] == 'N' || plateau[(x + a) / 2][(y + b) / 2] == '#'))
                // Si la dame blanche effectue un kill en sautant par-dessus un pion noir ('N') ou une dame noire ('#')
                return 1;
        }
    }
    return 0; // Retourne 0 si le mouvement n'est pas valide
}


void jeu(char** plateau, int longueur_plateau, int tour_joueur) {//0 for white and 1 for black
	int pionnoir_restant = 12;
	int pionblanc_restant = 12;
	// Tant qu'il reste des pions noirs ou blancs sur le plateau
	while (pionnoir_restant != 0 || pionblanc_restant != 0) {
    	// Au tour du Joueur 2 (blanc)
    	if (tour_joueur == 0) {
        	printf("\nC'est au tour du Joueur 2\n");
        	char coordoneeDepuis[10];
        	printf("Entrez la postion de la piece a bouger (exemple: 'A1'): ");
        	fgets(coordoneeDepuis, 10, stdin);
        	int xBlancDepuis = getX(coordoneeDepuis);
        	int yBlancDepuis = getY(coordoneeDepuis);
	   	// Verifier si la position de depart est valide
       		if (hors_plateau(plateau, longueur_plateau, xBlancDepuis, yBlancDepuis) == 0) {
           			printf("Erreur: Position invalide\n");
           			continue;
    		}
	
       		// Verifier si la case de depart contient un pion ennemi ou est vide
       		if (plateau[xBlancDepuis][yBlancDepuis] != 'B' && plateau[xBlancDepuis][yBlancDepuis] != '$') {
       			printf("Erreur: Pion ennemi / Case vide\n");
       			continue;
        	}
	
	   		char coordonneVers[10];
       		printf("Entrez la postion de destination (exemple: 'A1'): ");
       		fgets(coordonneVers, 10, stdin);
       		int xBlancVers = getX(coordonneVers);
       		int yBlancVers = getY(coordonneVers);
	
	   	// Verifier si la position de destination est valide
       		if (hors_plateau(plateau, longueur_plateau, xBlancVers, yBlancVers) == 0) {
       			printf("Erreur: Position invalide\n");
       			continue;
    		}
	
       		// Verifier si la case de destination est vide
       		if (plateau[xBlancVers][yBlancVers] != ' ') {
       			printf("Erreur: Case occupee\n");
       			continue;
    		}
  		
       		// Si la piece a bouger est un pion noir ('B') et que le mouvement est valide
       		if (plateau[xBlancDepuis][yBlancDepuis] == 'B' && mouvement_pion(plateau, longueur_plateau, xBlancDepuis, yBlancDepuis, xBlancVers, yBlancVers, 'B') == 1) {
            	// Si la piece ne se deplace pas vers la rangee superieure (promouvoir en dame)
            	if (yBlancVers != 0) {
            		plateau[xBlancDepuis][yBlancDepuis] = ' ';
            		plateau[xBlancVers][yBlancVers] = 'B';
	       			// Si un kill a ete effectuee
           			if (abs(xBlancVers - xBlancDepuis) == 2) {
       	    			plateau[(xBlancDepuis + xBlancVers) / 2][(yBlancDepuis + yBlancVers) / 2] = ' ';
       	    			pionnoir_restant--;
       	    			printf("Pion noir elimine, nombre de pion(s) noir(s) restant(s): %d\n", pionnoir_restant);
       				}
    			}
            	// Si la piece se deplace vers la rangee superieure (promouvoir en dame)
            		else if (yBlancVers == 0) {
                		plateau[xBlancDepuis][yBlancDepuis] = ' ';
                		plateau[xBlancVers][yBlancVers] = '$';
                		printf("Promotion du pion blanc en dame blanche\n");
	
                		// Si un kill a ete effectuee
                		if (abs(xBlancVers - xBlancDepuis) == 2) {
                	    	plateau[(xBlancDepuis + xBlancVers) / 2][(yBlancDepuis + yBlancVers) / 2] = ' ';
                	    	pionnoir_restant--;
                	    	printf("Pion noir elimine, nombre de pion(s) noir(s) restant(s): %d\n", pionnoir_restant);
                		}
            		}
        	}
        	// Si la piece a bouger est une dame blanche ('$') et que le mouvement est valide
        	else if (plateau[xBlancDepuis][yBlancDepuis] == '$' && mouvement_dame(plateau, longueur_plateau, xBlancDepuis, yBlancDepuis, xBlancVers, yBlancVers, '$') == 1) {
            	plateau[xBlancDepuis][yBlancDepuis] = ' ';
            	plateau[xBlancVers][yBlancVers] = '$';

            	// Si un kill a ete effectuee
            	if (abs(xBlancVers - xBlancDepuis) == 2) {
               		plateau[(xBlancDepuis + xBlancVers) / 2][(yBlancDepuis + yBlancVers) / 2] = ' ';
               		pionnoir_restant--;
               		printf("Pion noir elimine, nombre de pion(s) noir(s) restant(s): %d\n", pionnoir_restant);
            		}
        	}
        	else {
            		printf("Erreur: Mouvement invalide\n");
            		continue;
        	}

        	// Si tous les pions noirs ont ete elimines, sortir de la boucle
        	if (pionnoir_restant == 0)
        		break;

        	clear_screen(); // Effacer l'ecran
        	affichage(plateau, longueur_plateau); // Affichage du nouveau plateau
        	tour_joueur = 1; // Passer au tour du Joueur 1 (noir)
    	}

	
	else if (tour_joueur == 1) {
    		printf("\nC'est au tour du Joueur 1\n");
		char coordoneeDepuis[10];
    		printf("Entrez la postion de la piece a bouger (exemple: 'A1'): ");
    		fgets(coordoneeDepuis, 10, stdin);
    		int xNoirDepuis = getX(coordoneeDepuis);
    		int yNoirDepuis = getY(coordoneeDepuis);
	    	// Verifier si la position de depart est valide
    		if (hors_plateau(plateau, longueur_plateau, xNoirDepuis, yNoirDepuis) == 0) {
        		printf("Erreur: Position invalide\n");
        		continue;
    		}

    		// Verifier si la case de depart contient un pion ennemi ou est vide
    		if (plateau[xNoirDepuis][yNoirDepuis] != 'N' && plateau[xNoirDepuis][yNoirDepuis] != '#') {
        		printf("Erreur: Pion ennemi / Case vide\n");
        		continue;
    		}

    		char coordonneVers[10];
    		printf("Entrez la postion de destination (exemple: 'A1'): ");
    		fgets(coordonneVers, 10, stdin);
    		int xNoirVers = getX(coordonneVers);
    		int yNoirVers = getY(coordonneVers);

    		// Verifier si la position de destination est valide
			if (hors_plateau(plateau, longueur_plateau, xNoirVers, yNoirVers) == 0) {
    			printf("Erreur: Position invalide\n");
        		continue;
    		}

    		// Verifier si la case de destination est vide
    		if (plateau[xNoirVers][yNoirVers] != ' ') {
        	printf("Erreur: Case occupee\n");
        	continue;
    		}

    		// Si la piece a bouger est un pion noir ('N') et que le mouvement est valide
    		if (plateau[xNoirDepuis][yNoirDepuis] == 'N' && mouvement_pion(plateau, longueur_plateau, xNoirDepuis, yNoirDepuis, xNoirVers, yNoirVers, 'N') == 1) {
        		// Si la piece ne se deplace pas vers la rangee inferieure (promouvoir en dame)
        		if (yNoirVers != longueur_plateau - 1) {
            		plateau[xNoirDepuis][yNoirDepuis] = ' ';
            		plateau[xNoirVers][yNoirVers] = 'N';

            		// Si un kill a ete effectuee
            		if (abs(xNoirVers - xNoirDepuis) == 2) {
                		plateau[(xNoirDepuis + xNoirVers) / 2][(yNoirDepuis + yNoirVers) / 2] = ' ';
                		pionblanc_restant--;
                		printf("Pion blanc elimine, nombre de pion(s) blanc(s) restant(s): %d\n", pionblanc_restant);
            		}
        		}
        		// Si la piece se deplace vers la rangee inferieure (promouvoir en dame)
        		else if (yNoirVers == longueur_plateau - 1) {
            		plateau[xNoirDepuis][yNoirDepuis] = ' ';
            		plateau[xNoirVers][yNoirVers] = '#';
            		printf("Promotion du pion noir en dame noire\n");

            		// Si un kill a ete effectuee
            		if (abs(xNoirVers - xNoirDepuis) == 2) {
                		plateau[(xNoirDepuis + xNoirVers) / 2][(yNoirDepuis + yNoirVers) / 2] = ' ';
                		pionblanc_restant--;
                		printf("Pion blanc elimine, nombre de pion(s) blanc(s) restant(s): %d\n", pionblanc_restant);
            		}
        		}
    		}
    		// Si la piece a bouger est une dame noire ('#') et que le mouvement est valide
    		else if (plateau[xNoirDepuis][yNoirDepuis] == '#' && mouvement_dame(plateau, longueur_plateau, xNoirDepuis, yNoirDepuis, xNoirVers, yNoirVers, '#') == 1) {
        		plateau[xNoirDepuis][yNoirDepuis] = ' ';
        		plateau[xNoirVers][yNoirVers] = '#';

        		// Si un kill a ete effectuee
        		if (abs(xNoirVers - xNoirDepuis) == 2) {
            		plateau[(xNoirDepuis + xNoirVers) / 2][(yNoirDepuis + yNoirVers) / 2] = ' ';
            		pionblanc_restant--;
            		printf("Pion blanc elimine, nombre de pion(s) blanc(s) restant(s): %d\n", pionblanc_restant);
        		}
    		}
    		else {
        		printf("Erreur: Mouvement invalide\n");
        		continue;
    		}

    		// Si tous les pions blancs ont ete elimines, sortir de la boucle
    		if (pionblanc_restant == 0)
        		break;

    		clear_screen(); // Effacer l'ecran
    		affichage(plateau, longueur_plateau); // Affichage du nouveau plateau
    		tour_joueur = 0; // Passer au tour du Joueur 2 (blanc)
		}
	}
	// Fin de partie, on determine le gagnant ou l'egalite 
	if (pionnoir_restant == 0) {
		printf("Victoire du Joueur 2\n");
	}
	else if (pionblanc_restant == 0) {
		printf("Victoire du Joueur 1\n");
	}
	else {
		printf("La partie semble infinie\n");
	}
}

