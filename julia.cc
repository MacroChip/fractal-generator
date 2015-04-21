#define DIMENSION 300
#define MAX_ITERATIONS 256
#define BAILOUT 2
#define C_REAL .38921
#define C_IMAGINARY .2918
#define N_THREADS 4
//#define C_REAL .62772
//#define C_IMAGINARY .42193

#include <math.h>
#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

void process_pixel(int x, int y);

boost::mutex io_mutex;

int main(int argc, char* argv[]) {

    boost::asio::io_service service;
    boost::thread_group threadpool;
    
    auto_ptr<boost::asio::io_service::work> work(
        new boost::asio::io_service::work(service));
    
    for (int i = 0; i < N_THREADS; i++) {
        threadpool.create_thread(
            boost::bind(&boost::asio::io_service::run, &service));
    }
   
    
    for (int y = 0; y < DIMENSION; y++) {
        for (int x = 0; x < DIMENSION; x++) {
        
            service.post(boost::bind(process_pixel, x, y));
        
        }
    }
    
    //instead of calling service.stop(), call work.reset() to let
    //the unique_ptr be destroyed. Work
    //in progress and queued work will finish. service.stop() preempts jobs
    work.reset();
    threadpool.join_all();
}        

void process_pixel(int x, int y) {

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
    
    io_mutex.lock();
    cout << x << " " << y << " " << iterations << " " << endl;
    io_mutex.unlock();
}
            
                
                
    
