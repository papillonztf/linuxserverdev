#pragma once 
#include<atomic> //atomic<>
#include<thread> //std::thread::id;std::thread;
#include<iostream>
#include<sstream>  //sstream;
#include<assert.h>//assert();
#include<poll.h>//poll()

class EventLoop{
public:
    EventLoop();
    ~EventLoop();
    EventLoop(const EventLoop& other) = delete; //1.EventLoop对象不可复制。删除复制语义:拷贝构造和拷贝赋值
    EventLoop& operator=(const EventLoop& right) = delete;

    void loop();//事件循环。EventLoop的主功能

    //2.EventLoop中线程不安全成员函数的前置条件:线程不安全成员函数只能在EventLoop对象创建的线程内被调用
    //EventLoop的一些成员函数只能在EventLoop对象所创建的线程被调用。这些函数没做线程安全，不可跨线程。
    //线程安全的成员，我会注释“thread safe”
    void assertInLoopThread(char* funName);

    //调用线程是否是创建线程
    bool isInLoopThread() const;

    //获取当前线程的EventLoop对象。为null，可能当前线程是非io线程，也可能是先于EventLoop对象创建调用
    //为什么static？因为对于非io线程是不会创建EventLoop实例的。
    static EventLoop* getEventLoopOfThread();

private:
    //异常终止
    void abortNotInLoopThread(char* funName);

    //事件循环运行标志
    std::atomic<bool> looping_;

    //创建EventLoop对象的线程id
    const std::thread::id threadId_;

};