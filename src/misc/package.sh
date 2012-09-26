#!/bin/bash

cd ~/pintos
cd src && make clean
tar czf submission.tgz src
