#include <iostream>
#include <fstream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
int main( int argc, char* argv[] )
{
    std::ofstream myfile;
    myfile.open ("example.csv");
    for(int i=0;i<1000;i++){
	myfile<<", "<<rand();	
    }
    myfile<<'\n';
    for(int i=0;i<1000;i++){
	myfile<<", "<<rand()*1000;	
    }

    myfile.close();
    return 0;
}
