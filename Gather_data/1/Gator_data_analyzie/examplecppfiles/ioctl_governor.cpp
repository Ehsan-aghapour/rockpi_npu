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
//#include <delay.h>
//#include <inttypes.h>
//#include <android/log.h>
//#define  LOG_TAG    "testjni" 
//#define  ALOG(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)




struct f{
        long unsigned int gf;
        unsigned int f1;
        unsigned int f2;
        bool capturing=false;
};

using namespace std;

#define next_state _IO('x','n')
//#define capture_freqs _IOR('p','c',struct f*)
#define next_freq _IOW('x','f',int*)
uint64_t diff_time(timespec start, timespec stop){
    uint64_t out;
    out=((uint64_t)stop.tv_sec*(uint64_t)1.0e9+(uint64_t)stop.tv_nsec)-((uint64_t)start.tv_sec*(uint64_t)1.0e9+(uint64_t)start.tv_nsec);
    return out;
}

int main(){
	ofstream myfile;
	myfile.open("./times.txt");
	int fddd;
	f freqs;
	int index=0;
	timespec t_p,t_n;
	unsigned long int ioctltime=0;
	fddd = open("/proc/pandoon", O_RDWR);
	if (fddd==0)
		return 0;
	while(true){
		clock_gettime(CLOCK_MONOTONIC, &t_p);		
		ioctl(fddd, next_state);
		//ioctl(fddd,next_freq,&index);
		//ioctl(fddd,capture_freqs, &freqs);
		clock_gettime(CLOCK_MONOTONIC, &t_n);	
		ioctltime=diff_time(t_p,t_n);
		myfile<<ioctltime<<endl;
		//printf("GPU:%lu, F1:%d, F2: %d",freqs.gf,freqs.f1,freqs.f2);
		index++;
		usleep(10000);
	}
	return 0;
	

}

