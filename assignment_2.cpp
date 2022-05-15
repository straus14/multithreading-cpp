//
//  main.cpp
//  mt_ex2
//
//  Created by Sud . on 15.05.22.
//

#include <iostream>
#include <thread>

uint32_t cntr{0};

void incr()
{
    for(size_t i=0; i<100000; i++)
        cntr++;
}

int main(int argc, const char * argv[]) {
    
    std::cout << "initial value of cntr " << cntr << std::endl;
    
    std::thread t1{incr};
    std::thread t2{incr};
    
    t1.join();
    t2.join();
    
    std::cout << "final value of cntr " << cntr << std::endl;
    
    return 0;
}
