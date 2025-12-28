#include "bank_sys.h"

int main(void) {
    if(!login())
        return 0;   
    menu();

    return 0;
} 
