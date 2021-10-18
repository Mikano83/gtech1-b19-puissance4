#include <stdio.h>

void drawTable(char[7][6]);
int placeMarker(char table[7][6], int column, char player);
int win(char table[7][6], int column);
int checkLine (char table[7][6], int column, int x, int y);

int main(){
        char table[7][6];
        char player[2] = {'X', 'O'};
        int column=0;
        int turn;
        int turnCount;
        
        for (int i = 0; i < 7; i++){
                for (int j = 0; j < 6; j++){
                        table[i][j] = ' ';
                }
        }
        drawTable(table);
        for (turnCount = 0;!win(table, column)&&turnCount<42; turn = (++turnCount)%2){
                do {
                        printf ("Turn %d, Player %c, enter column number: ", turnCount, player[turn]);
                        scanf ("%d", &column);
                } while (column < 0 || column > 6 || !placeMarker (table, column, player[turn]));          
                drawTable (table);
        }
        if (turnCount >= 41) printf ("\nDraw!\n\n");
        else printf ("\n%c wins!\n\n", player[turn*-1+1]);    
}


int checkLine (char table[7][6], int column, int x, int y){
        int i = column;
        int j;
        for (j = 0; j < 7 && table[i][j] == ' '; j++);
        if (j>5) return 0;
        int total = 0;
       
        for (int _i = i+x, _j = j+y;table[_i][_j] == table[i][j] && _i <7 && _j <6; _i+=x,_j+=y,total++);
        for (int _i = i-x, _j=j-y;table[_i][_j] == table[i][j] && _i >= 0 && _j >=0;_i-=x,_j-=y,total++);
        if (total >= 3) return 1;
        return 0;
}

int win (char table[7][6], int column){
        for (int x = 1, y = -1; x >= 0; x -= y == 1, y += y < 1) {
                if (checkLine (table, column, x, y)) return 1;
        }
        return 0;
}



void drawTable(char table[7][6]){
        printf ("\n\n.0.1.2.3.4.5.6.");
        for (int j = 0; j < 6; j++){
               
                printf ("\n|");
                for (int i = 0; i < 7; i++){
                        printf ("%c|", table[i][j]);
                }
        }
        printf ("\n\\^.^.^.^.^.^.^/");
        printf ("\n\n");
}

int placeMarker (char table[7][6], int column, char player){
        int i = column;
        for (int j = 0; j < 6; j++){
                if (table[i][j] != ' ') {
                        if (j == 0) return 0;
                        table[i][j-1] = player;
                        return 1;
                }
        }
        table[i][5] = player;
        return 1;
}