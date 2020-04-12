set -e

rm -rf build

make -j8 -f black.mk
make -j8 -f blue-207.mk
make -j8 -f blue-atomic.mk
make -j8 -f blue.mk
make -j8 -f discovery.mk
make -j8 -f nucleo-32.mk
make -j8 -f nucleo-64.mk
make -j8 -f w1209.mk
