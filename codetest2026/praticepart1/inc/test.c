#include <stdio.h>
#include "inc.h"
int main()
{


/*测试bit_clear*/
     unsigned int r2 =
bit_clear(0x000000FF, 3);
     printf("bit_clear(0x000000FF,3)=0x%08X\n",
r2);
     return 0;

}
