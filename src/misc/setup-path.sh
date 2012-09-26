#!/bin/bash

HERE=`dirname $0`
cd $HERE/../utils
UTILS=`pwd`
make
echo "PATH=$UTILS:~/pintos/build/bin:\$PATH" >> ~/.bashrc
