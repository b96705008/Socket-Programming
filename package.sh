#!/bin/sh
rm dist/*
cd SocketProgramming
make clean
tar cvf ee450_taiyikuo_30502R.tar --exclude='*.csv' --exclude='.gitignore' *
gzip ee450_taiyikuo_30502R.tar
mv ee450_taiyikuo_30502R.tar.gz ../dist
