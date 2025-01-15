# SimpleOCR(UESTC-软件工程)

## Introduction
SimpleOCR is a lightweight Optical Character Recognition (OCR) application developed as a course project for Software Engineering at UESTC. It enables users to extract text from images through an intuitive graphical interface.

## Features
- User-friendly GUI built with Qt
- Real-time image processing and text recognition
- Support for multiple image formats
- Cross-platform compatibility

## Tech Stack
- **C++ & Qt**: For building the desktop application and GUI
- **Python**: Backend processing and OCR algorithms
- **OpenCV**: Image processing and computer vision operations
- **ZeroMQ**: Inter-process communication between C++ frontend and Python backend

## Architecture
The application follows a client-server architecture where:
- C++/Qt frontend handles user interactions and image display
- Python backend processes images and performs OCR
- ZeroMQ facilitates communication between frontend and backend components

## License
This project is created as a course assignment for Software Engineering at UESTC.

