#!/bin/bash

#Run source env.sh from Project root dir

export LD_LIBRARY_PATH=/usr/local/lib64/R/lib/:$LD_LIBRARY_PATH

export MPR_DIR=$(pwd)
export MPR_PACKAGE_DIR=$(pwd)/MPR_1.0.tar.gz