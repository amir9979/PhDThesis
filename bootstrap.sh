#!/bin/bash
LLVM_SRC=http://llvm.org/releases/3.3/llvm-3.3.src.tar.gz
CLANG_SRC=http://llvm.org/releases/3.3/cfe-3.3.src.tar.gz
RT_SRC=http://llvm.org/releases/3.3/compiler-rt-3.3.src.tar.gz
BOOST_SRC=http://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.gz
OPENMPI_SRC=http://www.open-mpi.org/software/ompi/v1.6/downloads/openmpi-1.6.5.tar.gz
MPFR_SRC=http://www.mpfr.org/mpfr-current/mpfr-3.1.2.tar.gz

LLVM_EXTRA_OPTS=--with-python=/usr/bin/python2
BOOST_EXTRA_OPTS=--with-python=/usr/bin/python2

BUILD_JOBS=16


DEPS=("$LLVM_SRC $CLANG_SRC $RT_SRC $BOOST_SRC $SCONS_SRC $OPENMPI_SRC $MPFR_SRC")

echo "Creating .deps dir"

if [[ ! -e deps ]]; then
    mkdir deps
fi
cd deps

PREFIX=$PWD/build

echo "Downloading stuff"
for d in $DEPS; do
    BASENAME=`basename $d`
    DIRNAME=`echo $BASENAME | sed 's/\.tar\.gz//'`
    DEP_NAME=`echo $DIRNAME | sed 's/\([a-zA-Z_-]*\)[-_].*$/\1/'`
    echo $BASENAME $DIRNAME $DEP_NAME

    if [[ ! -e $BASENAME ]]; then
        wget $d -q -O $BASENAME
    else
        echo "$BASENAME already exists, not downloading..."
    fi

    if [[ ! -e $DEP_NAME ]]; then
        tar -zxf $BASENAME
        mv $DIRNAME $DEP_NAME
    fi
done

if [[ ! -e llvm/ready ]]; then
    ln -s ../../cfe llvm/tools/clang
    ln -s ../../compiler-rt llvm/projects/compiler-rt

    cd llvm

    mkdir build
    cd build

    echo "Configuring LLVM"
    ../configure \
        --prefix=$PREFIX \
        --enable-optimized=NO \
        --enable-assertions=NO \
        $LLVM_EXTRA_OPTS

    echo "Building LLVM"
    make -j $BUILD_JOBS

    echo "Installing LLVM"
    make install

    cd ..
    touch ready
    echo "Finished LLVM"
    cd ..
else
    echo "Not building LLVM"
fi

if [[ ! -e boost/ready ]]; then
    cd boost

    echo "Configuring Boost"

    ./bootstrap.sh \
        $BOOST_EXTRA_OPTS

    echo "Building Boost"
    ./b2 -j $BUILD_JOBS

    echo "Building Boost"
    ./b2 install --prefix=$PREFIX


    echo "Finished Boost"
    touch ready
    cd ..
else
    echo "Not building Boost..."
fi


if [[ ! -e openmpi/ready ]]; then
    cd openmpi

    echo "Configuring OpenMPI"
    configure \
        --prefix=$PREFIX \
        --enable-mpi-f77 \
        --enable-mpi-f90 \
        $OPENMPI_EXTRA_OPTS

    echo "Building OpenMPI"
    make -j $BUILD_JOBS

    echo "Installing OpenMPI"
    make install

    touch ready
    echo "Finished OpenMPI"
    cd ..
else
    echo "Not building OpenMPI"
fi

if [[ ! -e mpfr/ready ]]; then
    cd mpfr

    echo "Configuring MPFR"
    configure \
        --prefix=$PREFIX \
        $MPFR_EXTRA_OPTS

    echo "Building MPFR"
    make -j $BUILD_JOBS

    echo "Installing MPFR"
    make install

    touch ready
    echo "Finished MPFR"
    cd ..
else
    echo "Not building MPFR"
fi
