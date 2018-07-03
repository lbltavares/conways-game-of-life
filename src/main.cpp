#include <iostream>
#include "System.h"

int main(int argn, char **args)
{
    System sys;
    sys.init();
    sys.loop();
    sys.quit();
    return 0;
}