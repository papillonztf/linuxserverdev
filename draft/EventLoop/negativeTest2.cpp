#include"EventLoop.h"
#include<iostream>
#include<unistd.h>///getpid()

void threadFunc(){
    std::cout<<"threadFunc(): pid= "<<getpid()<<" thread id= "<<std::this_thread::get_id()<<std::endl;
    EventLoop loop;
    loop.loop();

}

//负面测试2：同一线程创建两个EventLoop对象--应该报错终止
int main(){
    std::cout<<"main(): pid= "<<getpid()<<" thread id= "<<std::this_thread::get_id()<<std::endl;
    EventLoop mainLoop;

    EventLoop loop;
    
    mainLoop.loop();
    
    return 0;
}