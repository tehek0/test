#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));

    int kol = 5;
    int mass[5] = { 3,1,5,2,4 };
    int exm[5] = { 1,2,3,4,5 };


    ofstream file_out("resFI.txt");
    
    short i = 0;
    long long s = 1;
    while (i < kol) {
        int tmp = (rand()%kol);
        int j = mass[tmp];
        mass[tmp] = mass[i];
        mass[i] = j;
        ++i;
        if (i == kol) {

            int rightplace = 0;
            for (int m = 0; m < kol; ++m) {
                if (mass[m] == exm[m]) 
                    ++rightplace;
            }
            file_out << rightplace << endl;

            for (int k = 0; k < kol; ++k) {
                if (mass[k] != exm[k]) {
                    i = 0;
                    ++s;
                    break;
                }
            }
        }
    }
    cout << s;
    file_out << s << endl;
    file_out.close();
}
