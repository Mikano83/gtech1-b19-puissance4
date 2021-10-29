#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int NBL = 6;
int NBC = 7;
char **plateau = NULL;
char joueur[2];
char token[] = "xo";
int lineChanged;

void printTitle() //  Permet d'afficher le titre
{
    printf("\e[1;97m ______ _______ _______ _______ _______ _______ _______ ______ _______ _____  \n");
    printf("|   __ \\   |   |_     _|     __|     __|   _   |    |  |      |    ___|  |  | \n");
    printf("|    __/   |   |_|   |_|__     |__     |       |       |   ---|    ___|__    |\n");
    printf("|___|  |_______|_______|_______|_______|___|___|__|____|______|_______|  |__| \n");
    printf("\n\n\n\n\e[0m");
}

void clearConsole() //  Permet d'effacer la console selon le système d'exploitation
{
#ifdef _WIN32 //  Si c'est sous windows
    system("cls");
#else //  Les autres (à améliorer si un jour une autre plateforme que linux fait tourner le jeu)
    system("clear");
#endif
    printTitle(); //  Permet qu'à chaque appel de cet fonction, on ne rappelle pas la fonction printTitle()
}

void flushstdin() //  Permet de vider le buffer selon le système d'exploitation
{
#ifdef _WIN32 //  Si c'est sous windows
    fflush(stdin);
#else //  Les autres (à améliorer si un jour une autre plateforme que linux fait tourner le jeu)
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
#endif
}

char **plateau_malloc() //  Fonction d'allocation mémoire pour tableau dynamique
{
    char **plateau = (char **)malloc(NBL * sizeof(char *));
    for (int l = 0; l < NBL; l++)
        plateau[l] = (char *)malloc(NBC * sizeof(char));
    return plateau;
}

void init() //  Permet d'initaliser le jeu selon la taille décidée par le joueur
{
    clearConsole();
    printf("Sur combien de lignes souhaitez vous jouer ?\n");
    scanf("%d", &NBL);
    clearConsole();
    printf("Sur combien de colonnes souhaitez vous jouer ?\n");
    scanf("%d", &NBC);

    plateau = plateau_malloc(); //  Création du plateau(tableau) dynamique du jeu

    for (int L = 0; L < NBL; L++) //  Boucle qui sert à remplir notre tableau de points
    {
        for (int C = 0; C < NBC; C++)
        {
            plateau[L][C] = '.';
        }
    }
}

void print_plateau() //  Permet d'afficher le plateau de jeu
{
    for (int C = 0; C < NBC; C++) //  Boucle qui permet de rendre esthétique le plateau
    {
        if (C == 0)
            printf("    ----");
        else
            printf("----");
    }
    printf("---\n ");

    for (int L = 0; L < NBL; L++) //  Boucle qui permet d'afficher notre tableau dynamique 2D ainsi qu'une partie esthétique séparant chaque "cases"
    {
        if (L != 0)
            printf("\n ");
        for (int C = 0; C < NBC; C++)
        {
            char case_tableau = plateau[L][C];
            if (C == 0)
                printf("    | %c | ", case_tableau);
            else
                printf("%c | ", case_tableau);
        }
    }
    printf("\n");
    for (int C = 0; C < NBC; C++) //  Boucle qui permet de rendre esthétique le plateau
    {
        if (C == 0)
            printf("    ----");
        else
            printf("----");
    }
    printf("---\n   ");
    for (int C = 1; C <= NBC; C++) //  Boucle permettant d'afficher les numéros de chaques colonnes
    {
        if (C < 10) //  Prise en charge des espacements entre chaque numéros pour soucis d'esthétisme
        {
            if (C == 1)
                printf("    %d   ", C);
            else
                printf("%d   ", C);
        }
        else
        {
            if (C == 1)
                printf("    %d  ", C);
            else
                printf("%d  ", C);
        }
    }
    printf("\n\n");
}

int update_plateau(int colonne, int player) //  Permet de mettre à jour le plateau de jeu | Retourne un entier pour savoir si une colonne ou le plateau est plein
{
    int checkFullPlateau = 0;

    for (int l = NBL - 1; l >= 0; l--)
    {
        if (plateau[0][colonne] != '.')
        {
            return 1; //  Si la colonne est pleine
        }
        if (plateau[l][colonne] == '.')
        {
            plateau[l][colonne] = token[player];
            lineChanged = l;
            for (int i = 0; i < NBC; i++)
            {
                if (plateau[0][i] != '.')
                    checkFullPlateau++;
            }
            if (checkFullPlateau == NBC) //  Si le plateau est plein
            {
                clearConsole();
                print_plateau();
                return 2;
            }
            clearConsole();
            print_plateau();
            return 0; //  Si tout c'est bien passé
        }
    }
}

bool isWin(int player, int colonne, char pion) //  Permet de vérifier si il y a un puissance 4 | Retourne un booléen pour savoir si il y a puissance 4 ou non
{
    int tabNBL = NBL - 1;
    int tabNBC = NBC - 1;

    int gauche = 1;
    int droite = 1;
    int bas = 1;
    int dhGauche = 1;
    int dhDroite = 1;
    int dbGauche = 1;
    int dbDroite = 1;

    for (int verif = 1; verif <= 4; verif++)
    {                            /*Verification sur la gauche*/
        if (colonne - verif < 0) //  Permet de ne pas sortir du plateau(tableau) et donc d'éviter les erreurs
            break;

        if (plateau[lineChanged][colonne - verif] == pion) //  Vérifie pion par pion en partant de celui qui vient d'être posé
        {
            gauche += 1; //  Compteur de pions alignés
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale haut-gauche*/
        if (lineChanged - verif < 0 || colonne - verif < 0)
            break;

        if (plateau[lineChanged - verif][colonne - verif] == pion)
        {
            dhGauche += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la droite*/
        if (colonne + verif > tabNBC)
            break;

        if (plateau[lineChanged][colonne + verif] == pion)
        {
            droite += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale haut-droit*/
        if (lineChanged - verif < 0 || colonne + verif > tabNBC)
            break;

        if (plateau[lineChanged - verif][colonne + verif] == pion)
        {
            dhDroite += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur le bas*/
        if (lineChanged + verif > tabNBL)
            break;

        if (plateau[lineChanged + verif][colonne] == pion)
        {
            bas += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale bas-gauche*/
        if (lineChanged + verif > tabNBL || colonne - verif < 0)
            break;

        if (plateau[lineChanged + verif][colonne - verif] == pion)
        {
            dbGauche += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale bas-droit*/
        if (lineChanged + verif > tabNBL || colonne + verif > tabNBC)
            break;

        if (plateau[lineChanged + verif][colonne + verif] == pion)
        {
            dbDroite += 1;
        }
        else
            break;
    }
    if (gauche + droite - 1 >= 4 || dhGauche + dbDroite - 1 >= 4 || dhDroite + dbGauche - 1 >= 4 || bas >= 4) //  Si l'addition des pions dans les lignes de verifications respectives > 4 alors victoire(champagne!)
    {
        return true;
    }
    else
        return false; //  :sad:
}

void game(); //  Permet d'éviter les erreurs de compilations (l'initialiser pour pouvoir l'appeler avant de lui insérer son code)

bool playAgain(void) //  Permet de demander à l'utilisateur s'il souhaite rejouer ou quitter le jeu
{
    bool endIT = false;
    do //  Pas sur d'avoir grand chose à expliquer sur celui ci, le code parle de lui même
    {
        char play_again;
        printf("Souhaitez vous rejouer ? [o/n]\n");
        flushstdin();
        scanf("%c", &play_again);
        if (play_again == 'o' || play_again == 'O')
        {
            endIT = true;
            game();
        }
        else if (play_again == 'n' || play_again == 'N')
            endIT = true;
        else
            continue;
    } while (!endIT);
}

void game(void) //  Boucle du jeu
{
    init();
    flushstdin();
    clearConsole();
    bool end = false;
    bool victory;
    int player = 0;
    print_plateau();
    do //  Fait... Tant que la partie n'est pas finie(!end)
    {
        int colonne;
        printf("[%c] Joueur %d: ", token[player], player + 1);
        int nbEnt = scanf("%d", &colonne); //  Correspond au code retour du choix de colonne du joueur
        if (nbEnt > 0)                     //  S'il n'est pas trop bête le jeu passe par ici
        {
            if (colonne < 1 || colonne > NBC) //  Bon ok il peut quand même l'être un peu mais ça arrive de se tromper après tout
            {
                printf("Les colonnes vont de 1 a %d.\n\n", NBC);
                flushstdin();
            }
            else //  Quel boss il a réussi à entrer un numéro de colonne valable
            {
                colonne -= 1;
                int isError = update_plateau(colonne, player);

                switch (isError)
                {
                case 0: //  Tout se déroule sans accro
                    victory = end = isWin(player, colonne, token[player]);
                    player = !player;
                    break;

                case 1: //  Simple erreur d'inattention, ne le jugez pas
                    printf("Cette colonne est pleine, veuillez en saisir une autre.\n\n");
                    break;
                case 2: //  Ah la, ils ont fait fort :clap:
                    printf("Partie terminee, aucun gagnant !\n\n");
                    end = true;
                    break;
                }
            }
        }
        else //  QI < Moyenne
        {
            printf("Veuillez entrer un nombre entier.\n\n");
            flushstdin();
        }
    } while (!end);
    if (!victory) //  victory est forcément égal à end mais pas l'inverse, on vérifie donc si une fois que la partie est terminée s'il y a un vainqueur | Dans ce cas la match nul
    {
        playAgain();
    }
    else //  CHAMPAGNE!
    {
        printf("Felicitation joueur %d !\n\n", !player + 1);
        playAgain();
    }
}

void main(void) //  Fonction main, classique quoi
{
    game();
    free(plateau);
}