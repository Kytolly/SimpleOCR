#!/bin/bash
source ./internal/ocr*/.venv/bin/activate
./internal/frontend/build/Desk*/frontend & 
sudo -S python3 ./internal/ocr*/main.py &
wait