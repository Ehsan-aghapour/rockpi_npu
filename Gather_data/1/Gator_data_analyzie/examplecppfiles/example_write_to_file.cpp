#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    int sum = 0;
    int x;
    ifstream inFile;
    
    inFile.open("geps.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
   // while (inFile >> x) {
     //   sum = sum + x;
   // }
    inFile>>x;
    inFile>>sum;

    inFile.close();
    cout <<"x= "<<x<< ",Sum = " << sum << endl; 
    return 0;
}
