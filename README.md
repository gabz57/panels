This project intends to provide some kind of animated `Component` library on the top of the awesome [Matrix](https://github.com/hzeller/rpi-rgb-led-matrix) library.
I've created it for my personal use to create and draw simple or complex displays, with animation in a very customisable way, step by step.

Coming from the Java world, building in C++ is a rather complicated task for me, I would really appreciate PR to enchance the CMakeFile, and have Unit Test.
If you can help me to add Boost and cppnetlib to call external web api it would be awesome 😘

# Pre-requirements

I have bought 4 of these [led panels](https://fr.aliexpress.com/item/32816409052.html), and a Raspberry Pi3 B with the [AdaFruit bonnet](https://learn.adafruit.com/adafruit-rgb-matrix-bonnet-for-raspberry-pi?view=all), and also a [100W alimentation](https://www.reichelt.com/fr/fr/bloc-d-alimentation-d-coupage-ferm-90-w-5-v-18-a-mw-lrs-100-5-p202973.html) to supply the 4 panels.
Currently the code contains a hard-coded configuration which I edit on the fly when needed (only a global rotation using matrix library), and chains the 4 panels to build a single square of 4x64x64 leds.

I use the CLion IDE to develop and directly test my code on the raspberry connected to the panels.
It is surprisingly easy to setup it and run the code, the only things needed are some setup on the raspberry to install tools for compiling your code and accept SSH connections.
The IDE requires you to have the raspberry reachable and configured, as it will automatically check whether the code is executable (if not then every line of code appears in red, which is not ideal).

You may also setup your own C++ compiler on your machine, but you won't be able to run the code, and there's currently no unit test to run.

A small python script was necessary (found on the matrix library Issues section) for the panels to display anything, after connecting to a power source, this must be run before running any C++ code otherwise nothing will happen.

# How to 

# Historic

As some people might wonder what is needed in software part, here are some commands I used to create this project (it is also a way for me to remember them 😉).
## Add *rpi-rgb-led-matrix* as a Git module
```shell
git submodule add https://github.com/hzeller/rpi-rgb-led-matrix.git libs/matrix
```

### Add *rapidjson* as a Git module
```shell
git submodule add https://github.com/Tencent/rapidjson.git libs/rapidjson
```

I failed to link correctly cpp-netlib, thus you won't find it in the commited code, below is just to add the source code dependency and compile it (this also require BOOST library)

### Add *cpp-netlib* as a Git module
```shell
git submodule add https://github.com/cpp-netlib/cpp-netlib.git libs/cppnetlib
cd cppnetlib
git submodule init
git submodule update
```

### INSTALL BOOST on RPi
sudo apt-get install libboost1.67-all-dev 

# Next coding intentions

- Chained animations (or a bit more of control) : Imagine a rotating cube which would switch from one component to another by combining streching animations
- Try to have shorter code for component's event handling

Feel free to help !