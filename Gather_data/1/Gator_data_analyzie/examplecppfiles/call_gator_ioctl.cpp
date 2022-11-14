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

#define capture_max _IO('g','m')
int8_t dfreqs[3]={0};

int main(){
	/*ofstream myfile;
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
	}*/
	int fddd;
	fddd=open("/proc/gator_data", O_RDWR);
	if (fddd==0)
		return 0;

	ioctl(fddd,capture_max);
	return 0;
	

}

/*
GPU
767000000-667000000-550000000-415000000-332000000-237000000-150909000-103750000
A73
682000-1018000-1210000-1364000-1498000-1652000-1863000-2093000-2362000
A53
509000-1018000-1210000-1402000-1556000-1690000-1844000




[  322.991682] for key:0, max sum is: 2620387857580282, max count is 463155
[  322.991688] for key:1, max sum is: 3736175320, max count is 110852
[  322.991691] for key:2, max sum is: 1746516969, max count is 99930
[  322.991693] for key:3, max sum is: 7633009281, max count is 128185
[  322.991694] for key:4, max sum is: 44608542907, max count is 359109
[  322.991695] for key:5, max sum is: 11778491436, max count is 372660
[  322.991696] for key:6, max sum is: 6877855374, max count is 203114
[  322.991698] for key:7, max sum is: 2095739779, max count is 115937
[  322.991698] for key:8, max sum is: 10508754301, max count is 344963
[  322.991700] for key:9, max sum is: 1714040823, max count is 93720
[  322.991701] for key:10, max sum is: 859512787, max count is 91346
[  322.991702] for key:11, max sum is: 3799991405, max count is 94233
[  322.991703] for key:12, max sum is: 45147888861, max count is 154969
[  322.991703] for key:13, max sum is: 6049957901, max count is 207672
[  322.991704] for key:14, max sum is: 4083775673, max count is 133472
[  322.991705] for key:15, max sum is: 1157288702, max count is 101805
[  322.991706] for key:16, max sum is: 346044890, max count is 344963
[  322.991707] for key:17, max sum is: 60701494, max count is 93720
[  322.991708] for key:18, max sum is: 30810563, max count is 91346
[  322.991708] for key:19, max sum is: 111136440, max count is 94233
[  322.991709] for key:20, max sum is: 1135854780, max count is 154969
[  322.991711] for key:21, max sum is: 547431761, max count is 207672
[  322.991712] for key:22, max sum is: 380855810, max count is 133472
[  322.991712] for key:23, max sum is: 151968329, max count is 101805
[  322.991713] for key:24, max sum is: 3139460181, max count is 344963
[  322.991714] for key:25, max sum is: 423717341, max count is 93720
[  322.991715] for key:26, max sum is: 300702099, max count is 91346
[  322.991716] for key:27, max sum is: 770711943, max count is 94233
[  322.991717] for key:28, max sum is: 16349327539, max count is 154969
[  322.991717] for key:29, max sum is: 3053215069, max count is 207672
[  322.991718] for key:30, max sum is: 2151859149, max count is 133472
[  322.991719] for key:31, max sum is: 634347038, max count is 101805
[  322.991720] for key:32, max sum is: 77279905, max count is 344963
[  322.991721] for key:33, max sum is: 14826638, max count is 93720
[  322.991721] for key:34, max sum is: 6453452, max count is 91346
[  322.991723] for key:35, max sum is: 26922095, max count is 94233
[  322.991724] for key:36, max sum is: 271780527, max count is 154969
[  322.991724] for key:37, max sum is: 77129053, max count is 207672
[  322.991725] for key:38, max sum is: 43550496, max count is 133472
[  322.991726] for key:39, max sum is: 13517700, max count is 101805
[  322.991727] for key:40, max sum is: 150067398, max count is 344963
[  322.991728] for key:41, max sum is: 32015638, max count is 93720
[  322.991728] for key:42, max sum is: 17793099, max count is 91346
[  322.991729] for key:43, max sum is: 55290721, max count is 94233
[  322.991730] for key:44, max sum is: 238837695, max count is 154969
[  322.991731] for key:45, max sum is: 113503979, max count is 207630
[  322.991732] for key:46, max sum is: 68035706, max count is 133472
[  322.991732] for key:47, max sum is: 15716622, max count is 101805
[  322.991733] for key:48, max sum is: 11148098, max count is 319146
[  322.991734] for key:49, max sum is: 6170872, max count is 93627
[  322.991735] for key:50, max sum is: 1985797, max count is 90714
[  322.991736] for key:51, max sum is: 12908710, max count is 94226
[  322.991737] for key:52, max sum is: 136870330, max count is 154961
[  322.991738] for key:53, max sum is: 70686021, max count is 207638
[  322.991738] for key:54, max sum is: 46060921, max count is 133462
[  322.991739] for key:55, max sum is: 15948232, max count is 101801
[  322.991740] for key:56, max sum is: 1402000000, max count is 1
[  322.991741] for key:57, max sum is: 1402000000, max count is 1
[  322.991741] for key:58, max sum is: 1402000000, max count is 1
[  322.991742] for key:59, max sum is: 1402000000, max count is 1
[  322.991743] for key:60, max sum is: 2362000000, max count is 1
[  322.991744] for key:61, max sum is: 2362000000, max count is 1
[  322.991744] for key:62, max sum is: 2362000000, max count is 1
[  322.991745] for key:63, max sum is: 2362000000, max count is 1
[  322.991746] for key:64, max sum is: 0, max count is 0
[  322.991747] for key:65, max sum is: 0, max count is 0
[  322.991748] for key:66, max sum is: 0, max count is 0
[  322.991749] for key:67, max sum is: 0, max count is 0
[  322.991749] for key:68, max sum is: 0, max count is 0
[  322.991750] for key:69, max sum is: 0, max count is 0
[  322.991751] for key:70, max sum is: 0, max count is 0
[  322.991751] for key:71, max sum is: 0, max count is 0
[  322.991752] for key:72, max sum is: 262368, max count is 344964
[  322.991753] for key:73, max sum is: 11123, max count is 93719
[  322.991754] for key:74, max sum is: 8749, max count is 91345
[  322.991755] for key:75, max sum is: 11638, max count is 94234
[  322.991755] for key:76, max sum is: 72373, max count is 154968
[  322.991756] for key:77, max sum is: 125075, max count is 207671
[  322.991757] for key:78, max sum is: 50875, max count is 133471
[  322.991758] for key:79, max sum is: 19208, max count is 101804
[  322.991759] for key:80, max sum is: 17584128, max count is 292
[  322.991759] for key:81, max sum is: 184995840, max count is 6908
[  322.991761] for key:82, max sum is: 96046239244288, max count is 281658
[  322.991762] for key:83, max sum is: 5024817520640, max count is 1308
[  322.991763] for key:84, max sum is: 0, max count is 0
[  322.991764] for key:85, max sum is: 0, max count is 0
[  322.991764] for key:86, max sum is: 23297085440, max count is 1308
[  322.991765] for key:87, max sum is: 0, max count is 1308
[  322.991766] for key:88, max sum is: 232192499712, max count is 1308
[  322.991767] for key:89, max sum is: 1623414846, max count is 32908
[  322.991768] for key:90, max sum is: 5558443, max count is 32908
[  322.991768] for key:91, max sum is: 2138293175, max count is 32908
[  322.991769] for key:92, max sum is: 261816841, max count is 32908
[  322.991770] for key:93, max sum is: 730589973, max count is 32908
[  322.991771] for key:94, max sum is: 0, max count is 0
[  322.991772] for key:95, max sum is: 0, max count is 0
[  322.991773] for key:96, max sum is: 0, max count is 0
[  322.991774] for key:97, max sum is: 23252083, max count is 32908
[  322.991775] for key:98, max sum is: 7389831, max count is 32908
[  322.991775] for key:99, max sum is: 3273417, max count is 32908
[  322.991776] for key:100, max sum is: 12607987, max count is 32908
[  322.991777] for key:101, max sum is: 608004950, max count is 32908
[  322.991778] for key:102, max sum is: 877045, max count is 32908
[  322.991779] for key:103, max sum is: 11730745, max count is 32908
[  322.991779] for key:104, max sum is: 46523121, max count is 32908
[  322.991780] for key:105, max sum is: 12151735, max count is 32908
[  322.991781] for key:106, max sum is: 4862029, max count is 32908
[  322.991782] for key:107, max sum is: 1556015676, max count is 32908
[  322.991782] for key:108, max sum is: 581082853, max count is 32908
[  322.991783] for key:109, max sum is: 534101792, max count is 32908
[  322.991784] for key:110, max sum is: 284040144, max count is 32908
[  322.991786] for key:111, max sum is: 162991284, max count is 32908
[  322.991786] for key:112, max sum is: 192242015, max count is 32908
[  322.991787] for key:113, max sum is: 167507512, max count is 32908
[  322.991788] for key:114, max sum is: 101415061, max count is 32908
[  322.991789] for key:115, max sum is: 14655180, max count is 32908
[  322.991789] for key:116, max sum is: 17596804, max count is 32908
[  322.991790] for key:117, max sum is: 242358064, max count is 32908
[  322.991791] for key:118, max sum is: 107556236, max count is 32908
[  322.991792] for key:119, max sum is: 389010582, max count is 32908
[  322.991792] for key:120, max sum is: 149963798, max count is 32908
[  322.991793] for key:121, max sum is: 93633513, max count is 32908
[  322.991794] for key:122, max sum is: 17671120, max count is 32908
[  322.991795] for key:123, max sum is: 31182310, max count is 32908
[  322.991795] for key:124, max sum is: 552110931, max count is 32908
[  322.991796] for key:125, max sum is: 1791899495, max count is 32908
[  322.991798] for key:126, max sum is: 1594592363, max count is 32908
[  322.991798] for key:127, max sum is: 1504932163, max count is 32908
[  322.991799] for key:128, max sum is: 8467708, max count is 32908
[  322.991800] for key:129, max sum is: 36720318, max count is 32908
[  322.991801] for key:130, max sum is: 17627797, max count is 32908
[  322.991802] for key:131, max sum is: 218117642, max count is 32908
[  322.991802] for key:132, max sum is: 7287277, max count is 32908
[  322.991803] for key:133, max sum is: 100193713, max count is 32908
[  322.991804] for key:134, max sum is: 35715038, max count is 32908
[  322.991805] for key:135, max sum is: 746287353, max count is 32908
[  322.991805] for key:136, max sum is: 965259362, max count is 32908
[  322.991806] for key:137, max sum is: 261109406, max count is 32908
[  322.991807] for key:138, max sum is: 97068, max count is 32908
[  322.991808] for key:139, max sum is: 5191630, max count is 32908
[  322.991808] for key:140, max sum is: 47610109, max count is 32908
[  322.991809] for key:141, max sum is: 10703844, max count is 32908
[  322.991811] for key:142, max sum is: 1702754, max count is 32908
[  322.991812] for key:143, max sum is: 7379414, max count is 32908
[  322.991812] for key:144, max sum is: 205205914, max count is 32908
[  322.991813] for key:145, max sum is: 10769267, max count is 32908
[  322.991814] for key:146, max sum is: 107717035, max count is 32908
[  322.991815] for key:147, max sum is: 21127559, max count is 32908
[  322.991815] for key:148, max sum is: 166546469, max count is 32908
[  322.991816] for key:149, max sum is: 9252239, max count is 32908
[  322.991817] for key:150, max sum is: 38890115, max count is 32908
[  322.991818] for key:151, max sum is: 1031806402, max count is 32908
[  322.991819] for key:152, max sum is: 97904601, max count is 32908
[  322.991819] for key:153, max sum is: 59960908, max count is 32908
[  322.991820] for key:154, max sum is: 1849658, max count is 32908
[  322.991821] for key:155, max sum is: 1136002, max count is 32908
[  322.991822] for key:156, max sum is: 43082248, max count is 32908
[  322.991823] for key:157, max sum is: 480197420, max count is 32908




*/
