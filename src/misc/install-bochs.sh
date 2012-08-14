#!/bin/bash

if which apt-get
then
  sudo apt-get install build-essential libncurses5-dev subversion
else
  echo "not debian-based, prerequisites won't be automatically installed."
  echo "Make sure to install a working gcc, the ncurses headers, and"
  echo "subversion if the compilation fails."
fi

mkdir bochs
cd bochs
svn co --non-interactive --trust-server-cert https://bochs.svn.sourceforge.net/svnroot/bochs/trunk/bochs bochs
cd bochs
./configure --with-term --enable-gdb-stub --enable-e1000 --enable-pci
make
sudo make install

