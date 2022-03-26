#include "EventLoop.h"


//前置条件:线程构造EventLoop对象时线程的所创建的EventLoop对象指针。
//线程局部变量，每个线程都有该变量的备份。该变量的构造会在该变量使用前被构造。只要链接了这个目标文件，即使不是使用，线程也会构造这个变量。
thread_local EventLoop* t_loopInThisThread=nullptr;

EventLoop::EventLoop():looping_(false),threadId_(std::this_thread::get_id()){
    std::cout<< "[LOG_TRACE]:EvenLoop  "<<this<<"  created in thread: "<<threadId_<<std::endl;
    if(t_loopInThisThread){
        std::cout<<"[LOG_FATAL]:Another EventLoop  "<<
        t_loopInThisThread<<"  exsited in this thread:"<<threadId_<<std::endl;
        assert(!t_loopInThisThread);//异常终止进程
    }
    else{
        t_loopInThisThread=this;
    }
}

EventLoop::~EventLoop(){
    assert(!looping_.load());
    t_loopInThisThread=nullptr;
}

void EventLoop::assertInLoopThread(char* funName){
    if(!isInLoopThread()){
        abortNotInLoopThread(funName);

    }

}

bool EventLoop::isInLoopThread() const  {
    return std::this_thread::get_id()==threadId_;
}

EventLoop* EventLoop::getEventLoopOfThread(){
    return t_loopInThisThread;
}

void EventLoop::abortNotInLoopThread(char* funName){
    
    std::cout<<"[LOG_FATAL]:"<<funName<< "is not safe member function."
    <<"created in thread "<<threadId_<<"  but used in thread "<<std::this_thread::get_id()<<std::endl;
    assert(false);
	

}
void EventLoop::loop(){
    assert(!looping_.load());
    assertInLoopThread("EventLoop::loop()");
    looping_.store(true);
    poll(nullptr,0,5*1000);
    std::cout<<"[LOG_TRACE]:thread "<<this<<" stop looping"<<std::endl;
    looping_.store(false);

}

