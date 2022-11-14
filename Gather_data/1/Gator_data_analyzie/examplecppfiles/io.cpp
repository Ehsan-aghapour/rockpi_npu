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



#define capture_data _IOR('g','c',int *)


struct frequencies{
        long unsigned int gf;
        unsigned int f1;
        unsigned int f2;
	bool capturing;
};
//bool cap=false;
#define Pandoon_MAGIC (0xAA)
#define next_state _IO(Pandoon_MAGIC,'n')
#define capture_freqs _IOR(Pandoon_MAGIC,'c',struct frequencies *)
#define next_freq _IOW(Pandoon_MAGIC,'f', int*)
//new
#define Apply_freqs _IOW(Pandoon_MAGIC,'a', int8_t**)


struct frequencies freqs;

uint64_t diff_time(timespec start, timespec stop){
    uint64_t out;
    out=((uint64_t)stop.tv_sec*(uint64_t)1.0e9+(uint64_t)stop.tv_nsec)-((uint64_t)start.tv_sec*(uint64_t)1.0e9+(uint64_t)start.tv_nsec);
    return out;
}


int is_valid_fd(int fd)
{
    return fcntl(fd, F_GETFL) != -1 || errno != EBADF;
}


int Gov=0;
int main(){
	ofstream myfile;
	myfile.open("./dataaa.csv");
	int fddd;
	f freqs;
	int index=0;
	timespec t_p,t_n;
	unsigned long int ioctltime=0;
	int data_state[158];
	cout<<"GOVER:"<<Gov<<endl;
	Gov = open("/dev/pandoon_device", O_RDWR);
	if(Gov==-1){
		cout<<"not opened"<<endl;
		return -1;
	}

	cout<<"opened:"<<Gov<<endl;
	while(true){


	/*if(is_valid_fd(Gov)){
		Gov = open("/dev/pandoon_device", O_RDWR);
		//int Gat = open("/proc/gator_data", O_RDWR);
		if (Gov==0 )
			return 0;
		
		cout<<"again opened:"<<Gov<<endl;
	}*/

		clock_gettime(CLOCK_MONOTONIC, &t_p);		
		ioctl(Gov, next_state);
		//ioctl(fddd,next_freq,&index);
		int kkk=ioctl(Gov,capture_freqs, &freqs);
		if (kkk<0) {    /* use stdin */
        		fprintf(stderr,"ioctl(stdin, TIOCLINUX): %s\n",strerror(errno));
		        exit(1);
		}
		cout<<"KKK:"<<kkk<<","<<freqs.gf<<','<<freqs.f1<<','<<freqs.f2<<endl;
		clock_gettime(CLOCK_MONOTONIC, &t_n);	
		ioctltime=diff_time(t_p,t_n);
		myfile<<'\n'<<freqs.gf<<", " <<freqs.f1<<", "<<freqs.f2;
		//ioctl(Gat,capture_data,data_state);		
		myfile<<'\n';
		//for(int i=0;i<158;i++){
		//	myfile<<", "<<data_state[i];
		//}

		uint64_t out1,out2;
    		out1=((uint64_t)t_p.tv_sec*(uint64_t)1.0e9+(uint64_t)t_p.tv_nsec);
		out2=((uint64_t)t_n.tv_sec*(uint64_t)1.0e9+(uint64_t)t_n.tv_nsec);
		myfile<<out1<<','<<out2<<endl;
		//printf("GPU:%lu, F1:%d, F2: %d",freqs.gf,freqs.f1,freqs.f2);
		index++;
		usleep(100000);
		//close(Gov);

	}
	return 0;
	

}

