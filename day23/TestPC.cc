#include "Thread.h"
#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

void test()
{
    TaskQueue taskQue(10);

    function<void()> f1 = std::bind(&producer, std::ref(taskQue));//不加std::ref()会导致值传递，taskQue传入f1和f2会通过复制的方式
    function<void()> f2 = std::bind(&consumer, std::ref(taskQue));//因此导致f1和f2中的taskQue不是同一个，相当于创建了两个容器

    Thread mth1(std::move(f1));
    Thread mth2(std::move(f2));

    mth1.start();
    mth2.start();

    mth1.stop();
    mth2.stop();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
