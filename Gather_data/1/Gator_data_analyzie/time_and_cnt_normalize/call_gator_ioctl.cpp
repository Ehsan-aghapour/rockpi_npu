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

union ptr32{
 int* a;
 uint64_t padding;
};
struct s_data{
	uint64_t cnt[158];
	uint64_t sum[158];
	//uint64_t uu[400];
	//uint64_t uu2[400];
};

#define capture_data _IOR('g','c',union ptr32)
//#define capture_data _IOR('g','c',struct s_data)

using namespace std;

uint64_t diff_time(timespec start, timespec stop){
    uint64_t out;
    out=((uint64_t)stop.tv_sec*(uint64_t)1.0e9+(uint64_t)stop.tv_nsec)-((uint64_t)start.tv_sec*(uint64_t)1.0e9+(uint64_t)start.tv_nsec);
    return out;
}



int main(){
	ofstream myfile;
	myfile.open("./gator_data.csv");
	int fddd;
	timespec t_p,t_n,t_n2;
	unsigned long int ioctltime=0;
	int Gat = open("/proc/gator_data", O_RDWR);
	if (Gat==0)
		return 0;
	int data_state[158];
	struct s_data cr;
	uint64_t out1,out2,out2_2;
	while(true){
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_p);	
		ioctl(Gat,capture_data,data_state);
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_n);			
		//myfile<<'\n';
		/*
		for(int i=0;i<400;i++){
			myfile<<", "<<cr.uu[i];
		}
		myfile<<'\n';

		for(int i=0;i<400;i++){
			myfile<<", "<<cr.uu2[i];
		}
		myfile<<'\n';
		*/
		for(int i=0;i<158;i++){
			myfile<<", "<<data_state[i];
		}
		
		myfile<<'\n';
		/*for(int i=0;i<158;i++){
			myfile<<", "<<cr.cnt[i];
		}
		myfile<<'\n';*/
		clock_gettime(CLOCK_MONOTONIC_RAW, &t_n2);	
    		out1=((uint64_t)t_p.tv_sec*(uint64_t)1.0e9+(uint64_t)t_p.tv_nsec);
		out2=((uint64_t)t_n.tv_sec*(uint64_t)1.0e9+(uint64_t)t_n.tv_nsec);
		out2_2=((uint64_t)t_n2.tv_sec*(uint64_t)1.0e9+(uint64_t)t_n2.tv_nsec);
		myfile<<out1<<','<<out2<<','<<out2_2<<endl;
		//usleep(1000-((out2_2-out1)/1000)-70);
		usleep(300000);

	}

	return 0;
}

