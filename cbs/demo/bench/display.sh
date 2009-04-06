#!/bin/sh
##

dot -Tpng benchmark_1.dot -o benchmark_1.png
dot -Tpng benchmark_10.dot -o benchmark_10.png
dot -Tpng benchmark_100.dot -o benchmark_100.png
dot -Tpng benchmark_1000.dot -o benchmark_1000.png
dot -Tpng benchmark_10000.dot -o benchmark_10000.png
display benchmark_1.png &
display benchmark_10.png &
display benchmark_100.png &
display benchmark_1000.png &
display benchmark_10000.png &

