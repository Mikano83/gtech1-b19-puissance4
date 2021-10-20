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

int update_plateau(int colonne, int player)
{
    int checkFullPlateau = 0;

    for (int l = NBL; l >= 0; l--)
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
        /*Verification sur la diagonale haut-gauche*/
        else if (plateau[lineChanged - verif][colonne - verif] == pion)
        {
            dhGauche += 1;
        }
        /*Verification sur la droite*/
        else if (plateau[lineChanged][colonne + verif] == pion)
        {
            droite += 1;
        }
        /*Verification sur la diagonale haut-droit*/
        else if (plateau[lineChanged - verif][colonne + verif] == pion)
        {
            dhDroite += 1;
        }
        /*Verification sur le bas*/
        else if (plateau[lineChanged + verif][colonne] == pion)
        {
            bas += 1;
        }
        /*Verification sur la diagonale bas-gauche*/
        else if (plateau[lineChanged + verif][colonne - verif] == pion)
        {
            dbGauche += 1;
        }
        /*Verification sur la diagonale bas-droit*/
        else if (plateau[lineChanged + verif][colonne + verif] == pion)
        {
            dbDroite += 1;
        }
    }
    if (gauche + droite - 1 >= 4 || dhGauche + dbDroite - 1 >= 4 || dhDroite + dbGauche - 1 >= 4 || bas >= 4)
    {
        return true;
    }
    else
        return false;
}

void game()
{
    init();
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
                int isError = update_plateau(colonne, player);

                switch (isError)
                {
                case 0:
                    end = isWin(player, colonne);
                    player = !player;
                    break;

                case 1:
                    printf("Cette colonne est pleine, veuillez en saisir une autre.\n\n");
                    break;
                case 2:
                    printf("Partie terminee, aucun gagnant !");
                    end = true;
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
    printf("Felicitation joueur %d !\n\nAppuyez sur entree pour quitter.", !player + 1);
    char bye;
    scanf("%s", &bye);
}

void main(void)
{
    game();
}