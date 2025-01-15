#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>
#include "zmq.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

#ifndef TIRP
#define TIRP
namespace TirP {
    class Worker: public QObject
    {
        Q_OBJECT

    public:
        Worker();
        ~Worker();

        void start();
        void stop();
        void wait();
        void sendMessage(const QString& message);

    signals:
        void resultReady(const QString& result);
        void error(const QString& err);

    private:
        void run();
        zmq::context_t context;
        zmq::socket_t socket;
        std::thread thread;
        std::queue<QString> messageQueue;
        std::mutex queueMutex;
        std::condition_variable queueCondVar;
        std::atomic<bool> running;
    };
};
#endif

#endif // WORKER_H
