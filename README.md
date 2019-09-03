
## Add *rpi-rgb-led-matrix* as a Git module
```shell
git submodule add https://github.com/hzeller/rpi-rgb-led-matrix.git matrix
```

## Add *rapidjson* as a Git module
```shell
git submodule add https://github.com/Tencent/rapidjson.git rapidjson
```

## Add *cpp-netlib* as a Git module
```shell
git submodule add https://github.com/cpp-netlib/cpp-netlib.git cpp-netlib
cd cpp-netlib
git submodule init
git submodule update
```

## INSTALL BOOST on RPi
sudo apt-get install libboost1.67-all-dev 