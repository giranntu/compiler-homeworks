Dead Code Elimination - Using mark & sweep algorithm
=====================

R05944012 Chih-Yung Liang (梁智湧)

## Build Instructions

### Build LLVM
```bash
$ git submodule update --depth 1
$ mkdir env llvm/build && cd llvm/build
$ cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD=X86 ..
$ taskset -c 0-17 make -j36
$ cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../../env -P cmake_install.cmake
$ cd ../..
```

### Build This Project
```bash
$ export PATH=`pwd`/env/bin:$PATH
$ mkdir build && cd build
$ cmake ..
$ make
```

## Test Results
Assume that Clang is already installed on the system.

```bash
$ make DCE-test1
```
