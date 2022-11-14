#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include<iostream>
#include <fstream> 
#include <stdint.h>
using namespace std;


uint64_t diff_time(timespec start, timespec stop){
    uint64_t out;
    out=((uint64_t)stop.tv_sec*(uint64_t)1.0e9+(uint64_t)stop.tv_nsec)-((uint64_t)start.tv_sec*(uint64_t)1.0e9+(uint64_t)start.tv_nsec);
    return out;
}

int main(){
	timespec t_start, t_end;
	clock_gettime(CLOCK_MONOTONIC, &t_start);
	int h;
	for ( h=0;h<10000;h++)
		h++;
	clock_gettime(CLOCK_MONOTONIC, &t_end);
	cout<<diff_time(t_start,t_end)<<endl;
	return 0;


}
