#include <stdio.h>

int nbL = 6;
int nbC = 7;
extern char plateau[nbL][nbC];

void init(){
    for (int L=0; L<nbL; L++){
        for (int C=0; C<nbC; C++){
            plateau[L][C] = '.';
            printf("%c ", plateau[L][C]);
        }
    } 
}

int main(void){
    init();
    
    return 0;
}