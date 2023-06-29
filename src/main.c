#ifdef _WIN32
    #include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "fuggvenyek.h"
#include "menuk.h"
#include "econio.h"

#include "debugmalloc.h"

int main(){
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif //_WIN32
    econio_set_title("Telefonkonyv szerkeszto");
    Tomb menu;
    fomenu(menu);
    return 0;
}
