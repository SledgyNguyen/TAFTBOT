#include "Arduino.h"
#include "taftutils.h"

int dect(int cm, int th){
    if (cm <= th){
        return 1;
    }
    else {
        return 0;
    }
}

int randDec(){
    return random(0, 2);
}
