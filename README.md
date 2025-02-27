# protobuf experiments

## Build

### Install libraries
```
git clone --recurse-submodules -b v28.1 https://github.com/protocolbuffers/protobuf
cd protobuf
mkdir build && cd build

MY_INSTALL_DIR=$HOME/tmp/protobuf-v28.1
cmake \
    -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DBUILD_SHARED_LIBS=ON \
    -Dprotobuf_BUILD_TESTS=OFF \
    -Dprotobuf_WITH_ZLIB=OFF \
    ..
```

### Build and run test app
```
CC=clang-19 CXX=clang++-19 cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ..
LD_LIBRARY_PATH=$MY_INSTALL_DIR/lib make
LD_LIBRARY_PATH=$MY_INSTALL_DIR/lib ./test
```



## Build with ASAN
https://maskray.me/blog/2023-01-08-all-about-sanitizer-interceptors
https://github.com/google/sanitizers/issues/1086

Clang - the sanitizer libraries are compiled in statically by default.

Link with `-shared-libsan` to get a dependency to `libclang_rt.asan-x86_64.so` (not RPATH:ed though..)
Use `LD_PRELOAD` to make sure ASAN runtime is loaded first.

Example:
clang -fsanitize=address -shared-libsan -Wl,-rpath=$(dirname $(clang --print-file-name=libclang_rt.asan.so)) a.c -o a


```
MY_INSTALL_DIR=$HOME/tmp/protobuf-v28.1-asan
MY_INSTALL_DIR=$HOME/tmp/protobuf-v29.0-asan-cpp

CPPFLAGS="-O0 -fsanitize=address -fno-omit-frame-pointer" \

CXXFLAGS="-O0 -fsanitize=address -fno-omit-frame-pointer" \
CFLAGS="-O0 -fsanitize=address -fno-omit-frame-pointer" \
LDFLAGS="-fsanitize=address" \
  CC=clang-19 CXX=clang++-19 cmake \
    -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
    -DBUILD_SHARED_LIBS=ON \
    -Dprotobuf_BUILD_TESTS=OFF \
    -Dprotobuf_WITH_ZLIB=OFF \
    ..
VERBOSE=1 make -j8 install | tee log.txt
```

### Build and run test app
```
CXXFLAGS="-O0 -fsanitize=address -fno-omit-frame-pointer" \
LDFLAGS="-fsanitize=address" \
  CC=clang-19 CXX=clang++-19 cmake \
    -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR \
    ..

VERBOSE=1 make | tee log.txt

./test
```




GRPC:     v1.68.1
Protobuf: v28.1

GRPC:     v1.69.0
Protobuf: v29.0

/usr/local/lib/libprotobuf.so.29.0.0
/usr/local/lib/libgrpc++.so.1.69

(/usr/local/lib/libgrpc++.so.1.69+0x8e30d
/usr/local/lib/clang/19/lib/x86_64-unknown-linux-gnu/libclang_rt.asan.so
/usr/local/lib/clang/19/lib/x86_64-unknown-linux-gnu/libclang_rt.asan.so+0x14f5ad)

(/usr/local/lib/libprotobuf.so.29.0.0
/usr/local/lib/libgrpc++.so.1.69
/usr/local/lib/libgpr.so.44
