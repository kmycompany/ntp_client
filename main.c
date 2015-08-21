#include <stdio.h>
#include "ntp.h"

int main(void)
{
    if(SYNC_Time()<0)
        printf("sync time Failed!\n");
	else	
		printf("sync time Succeed!\n");
    
    return 0;
}
