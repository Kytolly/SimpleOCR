# 前台Qt服务

## 需求概述

该服务的工程根目录为`ocr-uestc/internal/frontend`

* 用户如何输入图片？
* GUI的设计？
* 结果如何展示？
* 全局的配置文件？
* ......

## 输入模块

* 一个字符串输入框
* 一个按钮

### 文本输入框`lineEdit`

文本：输入路径

类型：`QLineEdit*`

信号：无

槽：无

功能：实时获取地址字符串的输入,数据为`QString inputText`

### 按钮`pushBotton`

文本：启动！

类型：`QPushButton*`

信号：`&QPushButton::clicked`

槽：`onButtonClick()`进行套结字的连接

功能：按下按钮，将`QString inputText`发送给后台服务

## 输出模块

### 文本输出框`textBrowser`

文本：结果

类型：`QTextBrowser*`

信号：`&QTcpSocket::readyRead`

槽：`onReadyRead()`接收到响应后立马打印数据；

功能：展示识别的结果，或者可能出现的连接错误；

## 通信模块

### `Worker`

#### 属性

* `zmq::context_t context;`：和`socket`有关的上下文，仅在创建`socket`时传入；    
* `zmq::socket_t socket;`：负责通信的核心，负责数据的发送和接受；       
* `std::thread thread;`：维护的线程，与窗口的其他工作异步，保证接受数据到展示数据的同步；
* `std::queue<QString> messageQueue;`：这里是过度设计，维护消息的队列，让用户在以多种方式输入相关的文字图片时，能以正确的顺序返回结果；
* `std::mutex queueMutex;`：确保在处理结果过程中不出现竞态条件，需要加锁；
* `std::condition_variable queueCondVar;`：某个 wait 函数被调用的时候，它使用 `std::mutex`来锁住当前线程。当前线程会一直被阻塞，直到另外一个线程在相同的 `std::condition_variable` 对象上调用了 `notification` 函数来唤醒当前线程。
* `std::atomic<bool> running;`：控制`run()`的进行，一般来说，只有在主线程被销毁，子线程随之结束，其值变为`false`

#### 方法

* `Worker();`：创建套结字，连接后台服务，做好通信相关的准备；
* `void start();`:创建线程，这一步通常跟随着窗口启动；

* `void stop();`:释放运行相关的资源，唤醒因为该线程而等待的其他线程
* `void wait();`：暂时未设计，因为目前程序仅有一个窗口主线程和通信的子线程；
* `void sendMessage(const QString& message);`：负责数据的发送和接受，获得识别结果；

