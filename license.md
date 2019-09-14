License
--------------------------------------------------------------------
Note that this code is for my personal use, I don't know if I must use any specific license, but I suppose I should at least give a link to the license coming from dependencies (added as git submodules)
See the last section for this project license.
 
- [matrix](./libs/matrix/COPYING) The main dependency here, to draw colored pixels on leds panels and display nice things

Other dependencies

- [influxdb-cpp](./libs/influxdb-cpp/LICENSE) I use it to retrieve data from my raspberry (which also control the led panels)

- [rapidjson](./libs/rapidjson/license.txt) For reading content from influx DB


Notes
--------------------------------------------------------------------

This project is initially made for my personal use, note that I work mainly in a Java world (but I also like other languages).
I've been coding in C/C++ in my early days, thus the code might not be as good as a serious C++ coder would do.
 
I would really appreciate any kind of suggestions to enhance code readability, add nice unit tests.
(note that I started without, I tried to do my best to split the code and avoid annoying dependencies)