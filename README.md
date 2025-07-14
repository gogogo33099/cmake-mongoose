# How To Build

Need to install CMake and arm-linux cross tool first.

```bash
# Cross build for gc65xx (Arm Cortex A7)
mkdir build-gc65xx
cd build-gc65xx

# Build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-gc65xx.cmake -DCMAKE_INSTALL_PREFIX=./install -DIOTNG_TARGET=gc65xx

cmake --build .

# Install
rm -rf install;cmake --build . --target install

# Pack to tar.gz
rm iotng*.tar.gz;cpack
```


