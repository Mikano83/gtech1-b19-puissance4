#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NBL 6
#define NBC 7
char plateau[NBL][NBC];
char joueur[2];
char token[] = "xo";
int lineChanged;

void init()
{
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

void update_plateau(int colonne, int player)
{
    for (int l = NBL; l >= 0; l--)
    {
        if (plateau[l][colonne] == '.')
        {
            plateau[l][colonne] = token[player];
            lineChanged = l;
            break;
        }
    }
    system("cls");
    print_plateau();
}

bool isWin(int player, int colonne)
{
    int gauche = 1;
    int droite = 1;
    int bas = 1;
    int dhGauche = 1;
    int dhDroite = 1;
    int dbGauche = 1;
    int dbDroite = 1;

    char pion = plateau[lineChanged][colonne];

    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la gauche*/
        if (plateau[lineChanged][colonne - verif] == pion)
        {
            gauche += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale haut-gauche*/
        if (plateau[lineChanged - verif][colonne - verif] == pion)
        {
            dhGauche += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la droite*/
        if (plateau[lineChanged][colonne + verif] == pion)
        {
            droite += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale haut-droit*/
        if (plateau[lineChanged - verif][colonne + verif] == pion)
        {
            dhDroite += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur le bas*/
        if (plateau[lineChanged + verif][colonne] == pion)
        {
            bas += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale bas-gauche*/
        if (plateau[lineChanged + verif][colonne - verif] == pion)
        {
            dbGauche += 1;
        }
        else
            break;
    }
    for (int verif = 1; verif <= 4; verif++)
    { /*Verification sur la diagonale bas-droit*/
        if (plateau[lineChanged + verif][colonne + verif] == pion)
        {
            dbDroite += 1;
        }
        else
            break;
    }
    if (gauche >= 4 || dhGauche >= 4 || droite >= 4 || dhDroite >= 4 || bas >= 4 || dbGauche >= 4 || dbDroite >= 4)
    {
        return true;
    }
    else
        return false;
}

void game()
{
    bool end = false;
    int player = 0;
    print_plateau();
    do
    {
        int colonne;
        printf("Joueur %d: ", player + 1);
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
                update_plateau(colonne, player);

                end = isWin(player, colonne);
                player = !player;
            }
        }
        else
        {
            printf("Veuillez entrer un nombre entier.\n\n");
            fflush(stdin);
        }
    } while (!end);
    printf("Felicitation joueur %d !\n\nAppuyez sur entree pour quitter.", !player + 1);
    char bye;
    scanf("%s", &bye);
}

int main(void)
{
    init();
    game();

    return 0;
}