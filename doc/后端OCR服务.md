# 后端OCR服务

## 需求概述

后端根目录为`OCR-uestc/backend`

技术栈：`python,OCR,OpenCV,ZeroMQ`

* 接受什么样的输入？图片，路径，文档...？输入大小有无限制？...
* 返回的结果？字符串,字节...?
* 如何保证结果的正确性?
* 对数据库的设计？
* 配置文件？
* 日志记录？

## TCP服务器

利用`ZMQ`搭建一个TCP服务器`server`;

在`5555`端口上，等待前台数据（字符串）的输入；

过度设计接受参数`process`，方便不同形式数据的输入；

其实没什么好写的...

## OCR识别模块

目前正确率很低，进一步优化再补文档

hello wolrd!