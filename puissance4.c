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

// Fonction d'allocation mémoire:
char **plateau_malloc()
{
    // Allocation tableau de "pointeurs sur pointeurs" (1D):
    char **plateau = (char **)malloc(NBL * sizeof(char *)); // "Les lignes"
    // Pour chaque pointeur de premier niveau, on alloue un tableau de pointeurs (1D):
    for (int l = 0; l < NBL; l++)                        // Pour chaque "ligne"
        plateau[l] = (char *)malloc(NBC * sizeof(char)); // Les colonnes sont "attachées" à =tab[l]=
    // On retourne le ponteur =tab= pour l'utiliser ailleurs
    return plateau;
}

void init()
{
    printf("Combien de lignes souhaitez vous ?\n");
    scanf("%d", &NBL);
    printf("Combien de colonnes souhaitez vous ?\n");
    scanf("%d", &NBC);

    plateau = plateau_malloc();

    for (int L = 0; L < NBL; L++)
    {
        for (int C = 0; C < NBC; C++)
        {
            plateau[L][C] = '.';
        }
    }
}

void print_plateau()
{
    for (int C = 0; C < NBC; C++)
    {
        printf("--");
    }
    printf("-\n ");

    for (int L = 0; L < NBL; L++)
    {
        if (L != 0)
            printf("\n ");
        for (int C = 0; C < NBC; C++)
        {
            char case_tableau = plateau[L][C];
            printf("%c ", case_tableau);
        }
    }
    printf("\n");
    for (int C = 0; C < NBC; C++)
    {
        printf("--");
    }
    printf("-\n ");
    for (int C = 1; C <= NBC; C++)
    {
        printf("%d ", C);
    }
    printf("\n\n");
}

int update_plateau(int colonne, int player)
{
    int checkFullPlateau = 0;

    for (int l = NBL - 1; l >= 0; l--)
    {
        if (plateau[0][colonne] != '.')
        {
            return 1;
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
            if (checkFullPlateau == NBC)
                return 2;
            system("cls");
            print_plateau();
            return 0;
        }
    }
}

bool isWin(int player, int colonne, char pion)
{
    int gauche = 1;
    int droite = 1;
    int bas = 1;
    int dhGauche = 1;
    int dhDroite = 1;
    int dbGauche = 1;
    int dbDroite = 1;

    lineChanged++;

    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la gauche*/
        if (colonne < 3)
            break;

        if (plateau[lineChanged][colonne - verif] == pion)
        {
            gauche += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale haut-gauche*/
        if (lineChanged < 3)
            break;
        if (colonne < 3)
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
        if (colonne > NBC - 3)
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
        if (lineChanged < 3)
            break;
        if (colonne > NBC - 3)
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
        if (lineChanged > NBL - 4)
            break;

        printf("l: %d\ncolonne: %d\n", lineChanged + verif, colonne);
        if (plateau[lineChanged + verif][colonne] == pion)
        {
            bas += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale bas-gauche*/
        if (lineChanged > NBL - 3)
            break;
        if (colonne < 3)
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
        if (lineChanged > NBL - 3)
            break;
        if (colonne > NBC - 3)
            break;

        if (plateau[lineChanged + verif][colonne + verif] == pion)
        {
            dbDroite += 1;
        }
        else
            break;
    }
    if (gauche + droite - 1 >= 4 || dhGauche + dbDroite - 1 >= 4 || dhDroite + dbGauche - 1 >= 4 || bas >= 4)
    {
        return true;
    }
    else
        return false;
}

void game(void);

bool playAgain(void)
{
    bool endIT = false;
    do
    {
        char play_again;
        printf("Souhaitez vous rejouer ? [o/n]\n");
        fflush(stdin);
        scanf("%c", &play_again);
        if (play_again == 'o' || play_again == 'O')
            game();
        else if (play_again == 'n' || play_again == 'N')
        {
            endIT = true;
        }
        else
            continue;
    } while (!endIT);
}

void game(void)
{
    init();
    system("cls");
    bool end = false;
    int player = 0;
    print_plateau();
    do
    {
        int colonne;
        printf("[%c] Joueur %d: ", token[player], player + 1);
        int nbEnt = scanf("%d", &colonne);
        if (nbEnt > 0)
        {
            if (colonne < 1 || colonne > NBC)
            {
                printf("Les colonnes vont de 1 a %d.\n\n", NBC);
                fflush(stdin);
            }
            else
            {
                colonne -= 1;
                int isError = update_plateau(colonne, player);

                switch (isError)
                {
                case 0:
                    end = isWin(player, colonne, token[player]);
                    player = !player;
                    break;

                case 1:
                    printf("Cette colonne est pleine, veuillez en saisir une autre.\n\n");
                    break;
                case 2:
                    printf("Partie terminee, aucun gagnant !");
                    break;
                }
            }
        }
        else
        {
            printf("Veuillez entrer un nombre entier.\n\n");
            fflush(stdin);
        }
    } while (!end);
    printf("Felicitation joueur %d !\n\n", !player + 1);
    playAgain();
}

void main(void)
{
    game();
}