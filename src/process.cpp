#include "../include/declaration.h"


int main()
{
   CreateSemaphore();
   CreateSHM();

   //SHM_Monitor();

   do_process();

   SemaUnlink();
   return 0;
}