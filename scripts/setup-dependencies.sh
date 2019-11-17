#!/bin/bash

DEP_PATH=~/Development/dependencies/
SCRIPT=`realpath $0`
SCRIPTPATH=`dirname $SCRIPT`
DISTRIBUTION=`lsb_release -ds 2>/dev/null || cat /etc/*release 2>/dev/null | head -n1 || uname -om`

build_box2d_from_source_ubuntu_manjaro() {
  mkdir -p $DEP_PATH
  cd $DEP_PATH
  git clone https://github.com/google/liquidfun.git # master is the most stable and current branch
  cd liquidfun/liquidfun/Box2D
  sed -i '/-Wall\s-Werror\s-Wno-long-long\s-Wno-variadic-macros/d' CMakeLists.txt #hotfix
  ex -s -c '32i|find_package (Threads)' -c x CMakeLists.txt #hotfix
  mkdir -p build && mkdir -p build/lib && cd build
  cmake -DBOX2D_BUILD_EXAMPLES=OFF -DBOX2D_BUILD_UNITTESTS=OFF -DBOX2D_BUILD_SHARED=ON -DBOX2D_BUILD_STATIC=OFF -DCMAKE_BUILD_TYPE=$1 ..
  make
  if [[ $1 = Release ]]; 
  then
    cp Box2D/Release/libliquidfun.so.2.3.0 lib/libliquidfun.so
    cp Box2D/Release/libliquidfun.so.2.3.0 lib/libliquidfun.so.2.3.0
  else
    cp Box2D/Debug/libliquidfun.so.2.3.0 lib/libliquidfun-d.so
    cp Box2D/Debug/libliquidfun.so.2.3.0 lib/libliquidfun-d.so.2.3.0
  fi
  cd ../../../../
}

build_sfml_from_source_ubuntu() {
  mkdir -p $DEP_PATH
  cd $DEP_PATH
  git clone https://github.com/SFML/SFML.git # we don't want the old apt version
  sudo apt-get install -y libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev
  mkdir -p SFML/build && cd SFML/build
  cmake -DCMAKE_BUILD_TYPE=$1 ..
  make
  cd ../../
}

build_sfgui_from_source_manjaro() {
  mkdir -p $DEP_PATH
  cd $DEP_PATH
  git clone https://github.com/TankOs/SFGUI.git
  cd SFGUI
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=$1 ..
  make
  cd lib
  if [[ $1 = Release ]]; 
  then
    cp libSFGUI.so libsfgui.so
  else
    cp libSFGUI-d.so libsfgui-d.so
  fi
}

setup_manjaro() {
  sudo pacman -S --noconfirm --needed cmake make sfml rapidjson catch2 boost thor
  build_box2d_from_source_ubuntu_manjaro $1
  build_sfgui_from_source_manjaro $1
}

setup_cmake_manjaro() {
  cmake -DBOX2D_INCLUDE_DIR=$DEP_PATH/liquidfun/liquidfun/Box2D -DBOX2DDIR=$DEP_PATH/liquidfun/liquidfun/Box2D/build/lib -DSFGUI_ROOT=$DEP_PATH/SFGUI/build/lib -DSFGUI_INCLUDE_DIR=$DEP_PATH/SFGUI/include -DBUILD_TESTS=OFF ..
}

setup_ubuntu() {
  sudo apt install -y cmake make build-essential rsync libboost1.65-dev libboost-filesystem-dev
  build_sfml_from_source_ubuntu $1
  build_box2d_from_source_ubuntu_manjaro $1
  git clone https://github.com/Tencent/rapidjson.git
  git clone https://github.com/catchorg/Catch2.git
  echo "WARNING! SFGUI is not yet installed automatically. You'll have to install it yourself."
}

setup_cmake_ubuntu() {
  cmake -DSFML_INCLUDE_DIR=$DEP_PATH/SFML/include -DSFML_ROOT=$DEP_PATH/SFML/build/lib -DBOX2D_INCLUDE_DIR=$DEP_PATH/liquidfun/liquidfun/Box2D -DBOX2DDIR=$DEP_PATH/liquidfun/liquidfun/Box2D/build/lib -DCATCH2_INCLUDE_DIR=$DEP_PATH/Catch2/single_include -DRAPIDJSON_INCLUDEDIR=$DEP_PATH/rapidjson/include -DBUILD_TESTS=OFF ..
}

setup_deployment() {
  rsync -r resources/textures build/data
  #rsync -r resources/fonts build/data
  rsync -r resources/schemas build/data
}

setup_cmake() {
  cd $SCRIPTPATH
  cd ..
  mkdir -p build
  mkdir -p build/data
  cd build
  if [[ "$DISTRIBUTION" =~ .*buntu|neon.* ]]; then
    setup_cmake_ubuntu $1
  elif [[ "$DISTRIBUTION" =~ .*Manjaro.* ]]; then
    setup_cmake_manjaro $1
  fi
  cd ..
}

setup() {
  if [[ "$DISTRIBUTION" =~ .*buntu|neon.* ]]; then
    setup_ubuntu $1
  elif [[ "$DISTRIBUTION" =~ .*Manjaro.* ]]; then
    setup_manjaro $1
  fi
  
  setup_cmake $1
  setup_deployment $1
}

if [[ $* == *--configure* ]]; then
  setup_cmake Debug
  setup_deployment Debug
  exit 0
fi

setup Release
if [[ $* != *--production* ]]; then
  setup Debug
fi