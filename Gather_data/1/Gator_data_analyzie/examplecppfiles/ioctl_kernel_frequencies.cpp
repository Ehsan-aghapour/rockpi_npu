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

#define next_state _IO('p','n')
#define capture_freqs _IOR('p','c',struct f*)
#define next_freq _IOW('p','f',int*)
#define Apply_freqs _IOW('p','a', int**)

uint64_t diff_time(timespec start, timespec stop){
    uint64_t out;
    out=((uint64_t)stop.tv_sec*(uint64_t)1.0e9+(uint64_t)stop.tv_nsec)-((uint64_t)start.tv_sec*(uint64_t)1.0e9+(uint64_t)start.tv_nsec);
    return out;
}


int8_t dfreqs[3]={0};

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
		dfreqs[0]++;
		dfreqs[0]=dfreqs[0]%8;
		dfreqs[1]++;
		dfreqs[1]=dfreqs[1]%9;
		dfreqs[2]++;
		dfreqs[2]=dfreqs[2]%7;

		clock_gettime(CLOCK_MONOTONIC, &t_p);		
		//ioctl(fddd, next_state);
		///ioctl(fddd,next_freq,&index);
		//ioctl(fddd,capture_freqs, &freqs);
		ioctl(fddd,Apply_freqs,dfreqs);
		clock_gettime(CLOCK_MONOTONIC, &t_n);	
		//ioctltime=diff_time(t_p,t_n);
		//myfile<<ioctltime<<endl;
		//printf("GPU:%lu, F1:%d, F2: %d",freqs.gf,freqs.f1,freqs.f2);
		//index++;
		//usleep(1000);
		int a;
		cin>>a;
		ioctl(fddd,capture_freqs, &freqs);
		printf("GPU:%d,%lu, F1:%d,%d, F2:%d, %d",dfreqs[0],freqs.gf,dfreqs[1],freqs.f1,dfreqs[2],freqs.f2);
	}
	return 0;
	

}

/*
GPU
767000000-667000000-550000000-415000000-332000000-237000000-150909000-103750000
A73
682000-1018000-1210000-1364000-1498000-1652000-1863000-2093000-2362000
A53
509000-1018000-1210000-1402000-1556000-1690000-1844000


*/

