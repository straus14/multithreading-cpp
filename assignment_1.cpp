//
//  main.cpp
//  mt_ex1
//
//  Created by Sud . on 14.05.22.
//

#include <iostream>
#include <thread>

void func_fizzbuz(uint32_t length)
{
    for(size_t i=1; i<=length; i++)
    {
        if( !(i%3) && !(i%5) )
        {
            std::cout << "Fizzbuzz!" << "\n";
        }
        else if (!(i%3))
        {
            std::cout << "fizz!" << "\n";
        }
        else if (!(i%5))
        {
            std::cout << "buzz!" << "\n";
        }
        else
        {
            std::cout << i << "\n";
        }
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "enter number of children \n";
    uint32_t length;
    std::cin >> length;
    std::thread t{func_fizzbuz, length};
    t.join();
    return 0;
}
