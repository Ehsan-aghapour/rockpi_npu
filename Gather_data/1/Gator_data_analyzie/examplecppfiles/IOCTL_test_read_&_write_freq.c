#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include <iostream>

struct f{
        long unsigned int gf;
        unsigned int f1;
        unsigned int f2;
};

#define next_state _IO('p','n')
#define capture_freqs _IOR('p','c',struct f*)
 
int main()
{

	struct f freqs;
        int fd;
        int32_t value, number;
        printf("*********************************\n");
        printf("*******WWW.EmbeTronicX.com*******\n");
 
        printf("\nOpening Driver\n");
        fd = open("/proc/pandoon", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
 	while (number != 8){

		printf("Enter 4 to change frequencies, and 8 to exit\n");
		scanf("%d",&number);
		if (number ==4){
			printf("chaging frequencies\n");
			ioctl(fd, next_state); 
		}
	 
		printf("Reading Value from Driver\n");
		ioctl(fd, capture_freqs, (struct f*) &freqs);
		printf("GPU frequency is: %lu\n", freqs.gf);
		printf("CPU freq is: %d\n", freqs.f1);
		printf("CPU2 freq is: %d\n", freqs.f2);
	}	 
        printf("Closing Driver\n");
        close(fd);
}
