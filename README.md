Dead Code Elimination & Common Subexpression Elimination
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
$ make CSE-test-noeffect1
$ make CSE-test-noeffect2
$ make CSE-test-noeffect3
$ make CSE-test-eli-loads1
$ make CSE-test-eli-loads2
$ make CSE-test-eli-loads3
$ make CSE-test-eli-adds1
$ make CSE-test-eli-adds2
$ make CSE-test-eli-adds3
$ make CSE-test-eli-ptr1
$ make CSE-test-eli-ptr2
$ make CSE-test-eli-ptr3
$ make CSE-test-eli-ptr4
```
