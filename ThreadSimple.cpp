#include<thread>
#include<iostream>
#include<string>

void printFuck(std :: string msg){
    std :: cout << msg << std :: endl;
    return;
}

int main(){
    std :: thread thread1(printFuck,"fuck you");
    thread1.join();
    // thread1.detach();
    
    return 0;
}