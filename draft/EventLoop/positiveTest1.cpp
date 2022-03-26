#include"EventLoop.h"
#include<iostream>
#include<unistd.h>///getpid()

void threadFunc(){
    std::cout<<"threadFunc(): pid= "<<getpid()<<" thread id= "<<std::this_thread::get_id()<<std::endl;
    EventLoop loop;
    loop.loop();

}

int main(){
    std::cout<<"main(): pid= "<<getpid()<<" thread id= "<<std::this_thread::get_id()<<std::endl;
    EventLoop mainLoop;

    std::thread t1;//未执行的线程对象
    t1=std::move(std::thread(threadFunc));//移赋。执行的线程对象。线程启动
    mainLoop.loop();
    t1.join();//线程对象要么join要么detach。线程对象执行后，join要晚调用或者detach立马调用。
    return 0;
}