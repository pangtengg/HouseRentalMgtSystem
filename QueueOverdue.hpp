//header file for Queue
#ifndef QUEUEOVERDUE_HPP
#define QUEUEOVERDUE_HPP
#include <string>

namespace Overdue1{
struct Overdue {
    std::string UserID;
    std::string PayBeforeDate;
    double TotalOverdue;
};

typedef Overdue QueueItemType;
class Queue{
public:
    Queue();
    ~Queue();

    bool            isEmpty();//check whether queue is empty
    void            enqueue(QueueItemType newItem);//add elements to queue
    void            dequeue();//remove elements from queue
    QueueItemType   getFront();//retrieve whatever front value

private:
    static const int MAX_QUEUE = 100;

    QueueItemType items[MAX_QUEUE];
        int front;  // index of the front element
        int back;   // index of the back element
        int count;  // number of elements in the queue
};
}

#endif
