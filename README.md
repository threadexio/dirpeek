# Dirpeek

Yet another directory buster

Another directory buster written in C++

---------------------------------------

### Why though?

Because I wanted to make code something in C++ that actually did something usefull


### And why should I use it?

Honestly you shouldn't, there are much better alternatives,<br>
[here](https://github.com/OJ/gobuster) is an example

---------------------------------------

## Installation

**NOTE**: You can install evrything required by running `build.sh`, for distributions that use the `apt` package manager

**NOTE**: There is a precompiled binary for 64-bit systems, but you still need the libraries

1. Installing the required libraries

We need 2 diffirent libraries:
<ul>
	Boost Program Options:	https://www.boost.org/doc/libs/1_74_0/doc/html/program_options.html<br>
	C++ Requests library:	https://github.com/whoshuu/cpr<br>
</ul>

The boost-program-options library can either be installed through your package manager<br>
or by building it from the source from: `https://www.boost.org/`

For example, installing from apt is as simple as:
`sudo apt install 'libboost-program-options*' --no-install-recommends`

The C++ Requests library (cpr) needs to be built from the GitHub repo:<br>
`https://github.com/whoshuu/cpr`

2. Compiling the source

After you've been through all that, it's time to start compiling<br><br>
Don't worry though this will be very quick as this is a very simple program<br><br>

To compile the program run:<br>
`compile.sh`<br>
or<br>
`mkdir ./binaries; g++ -o ./binaries/dirpeek dirpeek.cpp -std=c++11 -lcpr -lboost_program_options -pthread`

And you're done...<br>

## But it sucks...

Totally agree with you,<br>
but I'm not as smart nor experienced enough to code something better
