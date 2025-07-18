#include<iostream>
using namespace std;

class Log{
public:
    static Log& GetInstance(){
        static Log Instance;
        return Instance;
    }
private:
    Log(){};
    Log(const Log& log) = delete;
    Log& operator=(const Log& log) = delete;
};

int main(int argc, char const *argv[])
{
    
    return 0;
}

