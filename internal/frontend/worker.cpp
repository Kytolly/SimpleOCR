#include "worker.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

namespace TirP{
    Worker::Worker()
        : context(1)
        , socket(context, zmq::socket_type::req)
        , running(false)
    {
        socket.connect("tcp://localhost:5555");
        // qDebug()<<"connect successfully!";
    }

    Worker::~Worker(){
        stop();
    }

    void Worker::start(){
        running = true;
        thread = std::thread(&Worker::run, this);
        //qDebug()<<"thread build...";
    }

    void Worker::stop(){
        running = false;
        queueCondVar.notify_all();
        if(thread.joinable()){
            thread.join();
        }
    }
    void Worker::wait(){

    }
    void Worker::sendMessage(const QString &message) {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.push(message);
            //qDebug()<<"pushing message ok";
        }
        queueCondVar.notify_one();
        //应该在创建的线程中执行
        //qDebug()<<"worker start!";
        // this->start();
        // this->run();
        // this->stop();
        // qDebug()<<"worker stopped!";
    }

    void Worker::run() {
        while (running) {
            //qDebug()<<"worker running";
            QString messageToSend;
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                queueCondVar.wait(lock, [this]() { return !messageQueue.empty() || !running; });
                qDebug()<<"queue waiting!";
                if (!running && messageQueue.empty()) {
                    break;
                }

                messageToSend = messageQueue.front();
                qDebug()<<"sending message:"<<messageToSend;
                messageQueue.pop();
            }

            // 发送消息到 ZeroMQ 服务
            zmq::message_t request(messageToSend.toUtf8().constData(), messageToSend.toUtf8().size());
            socket.send(request, zmq::send_flags::none);

            // 接收服务响应
            zmq::message_t reply;
            socket.recv(reply, zmq::recv_flags::none);

            // 将响应转换为 QString，并通过信号发送
            QString result = QString::fromUtf8(static_cast<char*>(reply.data()), reply.size());
            qDebug()<<"result:"<<result;
            emit resultReady(result);
        }
    }
}
