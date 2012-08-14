#!/bin/bash

if which apt-get
then
  sudo apt-get install build-essential libncurses5-dev subversion
else
  echo "not debian-based, support won't be auto installed."
fi

mkdir bochs
cd bochs
svn co --non-interactive --trust-server-cert https://bochs.svn.sourceforge.net/svnroot/bochs/trunk/bochs bochs
cd bochs
./configure --with-term --enable-gdb-stub --enable-e1000 --enable-pci
make
sudo make install

