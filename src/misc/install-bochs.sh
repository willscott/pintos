#!/bin/bash

if which apt-get
then
  sudo apt-get install build-essential libncurses5-dev subversion
else
  echo "Prerequisites won't be automatically installed."
  echo "Make sure to install a working gcc, the ncurses headers, and"
  echo "subversion if the compilation fails."
fi

mkdir -p ~/pintos/build
mkdir bochs
cd bochs
svn co --non-interactive --trust-server-cert https://bochs.svn.sourceforge.net/svnroot/bochs/trunk/bochs bochs
cd bochs
./configure --with-term --with-nogui --enable-gdb-stub --enable-e1000 --enable-pci --prefix=~/pintos/build
make
make install
