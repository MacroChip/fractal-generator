#define DIMENSION 300
#define MAX_ITERATIONS 256
#define BAILOUT 2
#define C_REAL .38921
#define C_IMAGINARY .2918
//#define C_REAL .62772
//#define C_IMAGINARY .42193

#include <math.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    
    
    for (int y = 0; y < DIMENSION; y++) {
        for (int x = 0; x < DIMENSION; x++) {
        
            double z_real_old = 1.5 * (x-DIMENSION/2) / (.5 * DIMENSION);
            double z_imaginary_old = (y-DIMENSION/2) / (.5*DIMENSION);
            int iterations = 0;
            double norm = 0;
            
            while (iterations <= MAX_ITERATIONS && norm <= BAILOUT) {
                double z_real_new = z_real_old * z_real_old - z_imaginary_old * z_imaginary_old + C_REAL; 
                double z_imaginary_new = 2 * z_imaginary_old * z_real_old + C_IMAGINARY; 
                
                norm = sqrt(z_real_new * z_real_new + z_imaginary_new * z_imaginary_new);
                
                z_real_old = z_real_new;
                z_imaginary_old = z_imaginary_new;
                iterations++;
            }
            
            cout << x << " " << y << " " << iterations << " " << endl;
            
        }
    }
}
            
                
                
    
