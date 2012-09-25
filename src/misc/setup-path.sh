#!/bin/bash

HERE=`dirname $0`
cd $HERE/../utils
make
echo "PATH=`pwd`:\$PATH" >> ~/.bashrc
