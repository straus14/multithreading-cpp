//
//  main.cpp
//  mt_ex4
//
//  Created by Sud . on 8.07.22.
//

#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>

using namespace std::chrono;

std::mutex mut;
std::condition_variable cv;
bool variableUpdated{false};
std::string fdata{"empty"};

void fetchData()
{
    std::cout << "started fetching data" << std::endl;
    std::this_thread::sleep_for(2s);
    
    std::unique_lock<std::mutex> guard{mut};
    fdata = "Populated";
    variableUpdated = true;
    guard.unlock();
    
    cv.notify_all();
    std::cout << "finished fetching data" << std::endl;
}

void showProgress()
{
    std::cout << "fetching data in progres..." << std::endl;
    
    std::unique_lock<std::mutex> guard{mut};
    cv.wait(guard, [] {return variableUpdated;});
}

void processData()
{
    std::unique_lock<std::mutex> guard{mut};
    cv.wait(guard, [] {return variableUpdated;});
    
    std::cout << "started processing data..." << std::endl;
    
    std::cout << "Data is " << fdata << std::endl;
    
    std::cout << "finished processing data!" << std::endl;
}

int main(int argc, const char * argv[]) {
    
    std::thread fdata{fetchData};
    
    std::thread sProg{showProgress};
    std::thread pData{processData};
    
    fdata.join();
    sProg.join();
    pData.join();
    
    return 0;
}
