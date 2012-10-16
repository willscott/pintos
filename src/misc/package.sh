#!/bin/bash

cd ~/pintos
cd src && make clean
tar --exclude=src/misc/bochs -cvzf submission.tgz src/
