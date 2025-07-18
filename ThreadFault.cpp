#include<thread>
#include<iostream>
#include<string>
using namespace std;

class A{
    friend void hello();
public:
    void he(){
        cout << "he" << endl;
    }
private:
    void she(){
        cout << "she" << endl;
    }
};

void hello(){
    A hjt;
    thread thread1(&A::she,&hjt);
    thread1.join();
}
int main(){
    hello();
    return 0;
}