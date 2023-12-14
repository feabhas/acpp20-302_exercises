set errexit
set nounset

BUILD=./build
APP=$BUILD/Application
SRC=./src

# export CPLUS_INCLUDE_PATH=/usr/include/c++/11:/usr/include/x86_64-linux-gnu/c++/11


CXXFLAGS="-Wall -Wextra -Wconversion -Wsign-conversion -std=c++2a"

function pcm
{
  clang++ $CXXFLAGS $MAPS -c "$1" -Xclang -emit-module-interface -o "$2"
}

function build
{
# -fimplicit-modules -fimplicit-module-maps -fprebuilt-module-path=$BUILD
  clang++ $CXXFLAGS $MAPS "$@" -o ${APP}
}

MAPS=
set -x
for CXX in $SRC/*.cxx; do
  PCM="$BUILD/$(basename ${CXX%.*}).pcm"
  pcm $CXX $PCM
  MAPS="$MAPS -fmodule-file=$PCM"
done

build $SRC/*.cpp
ls $BUILD
