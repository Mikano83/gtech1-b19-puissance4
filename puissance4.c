#include <stdio.h>

#define NBL 6
#define NBC 7
char plateau[NBL+3][NBC];

void init(){
    for (int L=0; L<NBL; L++){
        for (int C=0; C<NBC; C++){
            plateau[L][C] = '.';
        }
    }
}


int main(void){
    init();
    
    return 0;
}