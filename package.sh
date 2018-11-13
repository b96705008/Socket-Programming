#!/bin/sh
cd SocketProgramming
make clean
tar cvf ee450_taiyikuo_session2.tar --exclude='*.csv' --exclude='.gitignore' *
gzip ee450_taiyikuo_session2.tar
mv ee450_taiyikuo_session2.tar.gz ../dist
