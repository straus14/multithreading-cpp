//
//  main.cpp
//  mt_ex3
//
//  Created by Sud . on 8.07.22.
//

#include <iostream>
#include <thread>

using namespace std::chrono;

std::mutex mut;
bool variableUpdated{false};
std::string sdata{"empty"};

void reader()
{
    bool updateRead{false};
    
    while(!updateRead)
    {
        std::unique_lock<std::mutex> guard{mut};
        if(variableUpdated)
        {
            std::cout << "updated data is " << sdata << std::endl;
            updateRead = true;
        }
        guard.unlock();
        std::this_thread::sleep_for(2s);
    }
}

void writer()
{
    std::cout << "writing data.... " << std::endl;
    std::unique_lock<std::mutex> guard{mut};
    std::this_thread::sleep_for(2s);
    sdata = "Populated";
    variableUpdated = true;
}

int main(int argc, const char * argv[]) {
    
    
    std::cout << "data is " << sdata << std::endl;
    
    std::thread write{writer};
    std::thread read{reader};
    
    write.join();
    read.join();
    
    return 0;
}
