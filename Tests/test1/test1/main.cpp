//
//  main.cpp
//  test1
//
//  Created by Guillot Pierre on 31/05/2015.
//  Copyright (c) 2015 PierreGuillot. All rights reserved.
//

#define OSP_USE_SSE

#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "../../../Sources/Osp.hpp"
#include <limits>

#ifdef __APPLE__
#include <Accelerate/Accelerate.h>
#elif _WINDOWS
#include <mmintrin.h>
#endif

static std::clock_t c_start;
static std::clock_t c_end;
static auto t_start = std::chrono::high_resolution_clock::now();
static auto t_end = std::chrono::high_resolution_clock::now();

using namespace osp;

inline void start_clock()
{
    c_start = std::clock();
    t_start = std::chrono::high_resolution_clock::now();
}

inline void stop_clock()
{
    c_end = std::clock();
    t_end = std::chrono::high_resolution_clock::now();
    std::cout << std::fixed << "CPU time used: "
    << 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC << " ms\n"
    << "Wall clock time passed: "
    << std::chrono::duration<double, std::milli>(t_end-t_start).count()
    << " ms\n";
}

inline void post(int size , const float *in)
{
    std::cout << "\n";
    for(int i = 0; i < size; i++)
    {
        std::cout << in[i] << " ";
    }
    std::cout << "\n";
}

int main(int argc, const char * argv[])
{
    //size_t size = 1024;
    //size_t size = 64 +7;
    size_t size =16*1024*1024-1;
    size_t nloop = size>>3;
    size_t remain = size&7;
    std::cout << "Size : "<< size << " Nloops : " << (size>>2)  << " Remain : " << (size&3) << " " << 2097151 *2 <<"\n";
    std::cout << "Size : "<< size << " Nloops : " << nloop  << " Remain : " << remain << "\n";
    
    float* in1 = new (std::nothrow) float[size];
    float* in2 = new (std::nothrow) float[size];
    float* out = new (std::nothrow) float[size];
    if(!in1 || !in2)
    {
        std::cout << "alloc error" << "\n";
        return 0;
    }
    Osp<float>::fill(size, 1.f, in1);
    std::cout << "\nClear : \n";
    start_clock();
    Osp<float>::clear(size, in1);
    stop_clock();
    
    std::cout << "\nFill : \n";
    start_clock();
    Osp<float>::fill(size, 1.f, in1);
    stop_clock();
    Osp<float>::fill(size, 2.f, in2);
    
    std::cout << "\nDot : \n";
    start_clock();
    Osp<float>::dot(size, in1, in2);
    stop_clock();
    
    std::cout << "\nSwap : \n";
    start_clock();
    Osp<float>::swap(size, in1, in2);
    stop_clock();
    
    std::cout << "\nCopy : \n";
    start_clock();
    Osp<float>::copy(size, in1, in2);
    stop_clock();
    
    std::cout << "\nAdd vector : \n";
    start_clock();
    Osp<float>::add(size, in1, in2);
    stop_clock();
    
    std::cout << "\nAdd scalar : \n";
    start_clock();
    Osp<float>::add(size, 1.4f, in1);
    stop_clock();
    
    std::cout << "\nAdd vector2 : \n";
    start_clock();
    Osp<float>::add(size, in1, in2, out);
    stop_clock();
    
    std::cout << "\nAdd scalar2 : \n";
    start_clock();
    Osp<float>::add(size, 2.6, in1, out);
    stop_clock();
    
    post(10, out);
    
    delete [] in1;
    delete [] in2;
    std::cout << "end\n";
    return 0;
}
