#include "funh.h"
#include "vector.h"

extern int hash_Lx;
extern double hash_cell_x, hash_cell_y;

int calcH(pez pececito){

    int x = (int)(pececito.pos.x/hash_cell_x);
    int y = (int)(pececito.pos.y/hash_cell_y);

    if(x < 0){x = 10;}
    else if(x > 10){x = 0;}
    if(y < 0){y = 10;}
    else if(y > 10){y = 0;}

    int H = hash_Lx*y + x;

    return H;
}
