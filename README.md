# Overview
This is a demo protocol for [CommsChampion Ecosystem](https://commschamp.github.io). 
It demonstrates a protocol that reports its version in every message
framing, and where existence of the fields depends on the reported version. 

The protocol is defined in the [schema](dsl/schema.xml)
file using [CommsDSL](https://github.com/commschamp/CommsDSL-Specification).
The **commsds2comms** code generator from [commsdsl](https://github.com/commschamp/commsdsl)
project is used to generate C++11 code of the protocol implementation.

This project also contains two [example](examples) 
applications (client + server), which demonstrate exchange of the protocol
messages over TCP/IP link.

# Protocol
The contents of the protocol messages demonstrate existence of the fields
based on the protocol version information, reported in transport framing. 

The transport framing is
```
SYNC (2 bytes) | SIZE (2 bytes) | ID (1 byte) | VERSION (1 byte) | PAYLOAD | CHECKSUM (2 bytes)
```
where
- **SYNC** is synchronization bytes, expected to be `0xab 0xcd`.
- **SIZE** is remaining length (including **CHECKSUM**)
- **ID** is numeric ID of the message.
- **VERSION** is version of the protocol (schema).
- **PAYLOAD** is message payload.
- **CHECKSUM** is 16 bit **CRC-CCITTT** checksum of `SIZE | ID | PAYLOAD` bytes.

The code generators from the [commsdsl](https://github.com/commschamp/commsdsl)
repository generate full CMake projects.
Some of these **generated** projects are hosted as separate
repositories that can be viewed and used independently.

- [cc.demo2.generated](https://github.com/commschamp/cc.demo2.generated) - Protocol 
    definition 
- [cc.demo2_protocol.cc_tools_plugin](https://github.com/commschamp/cc.demo2_protocol.cc_tools_plugin) -
    Protocol plugin for the [CommsChampion Tools](https://github.com/commschamp/cc_tools_qt).

# Examples
The [client](examples/client) reads requested version value from standard input.
Once proper version is entered, it prepares and sends `Msg1`  message to 
the server, then waits for `Msg2` in response. When the latter is received, 
prints its fields and inquires for the next version.

The [server](examples/server) prints values of received 'Msg1` message's fields and
sends back `Msg2` message with the same version.

# License
Please read [License](https://github.com/commschamp/commsdsl#license)
section from [commsdsl](https://github.com/commschamp/commsdsl) project.

# How to Build
This project uses CMake as its build system. Please open main
[CMakeLists.txt](CMakeLists.txt) file and review available options as well as
mentioned available parameters, which can be used in addition to standard 
ones provided by CMake itself, to modify the default build. 

This project also has external dependencies, it requires an access to
the [COMMS Library](https://github.com/commschamp/comms) and
code generators from [commsdsl](https://github.com/commschamp/commsdsl) projects.
These dependencies are expected to be built independenty and access to them provided
via standard **CMAKE_PREFIX_PATH** and/or **CMAKE_PROGRAM_PATH** (for the binaries of
the code generators). There are also scripts (
[script/prepare_externals.sh](script/prepare_externals.sh) for Linux and
[script/prepare_externals.bat](script/prepare_externals.bat) for Windows)
which can help in preparation of these dependencies. They are also used
in configuration of the [github actions](.github/workflows/actions_build.yml).

The project's cmake configuration [options](CMakeLists.txt) allow building
bindings to other high level programming languages using [swig](https://www.swig.org/)
and [emscripten](https://emscripten.org/), see relevant commsdsl's
[documentation](https://github.com/commschamp/commsdsl/tree/master/doc) pages for details.

The [example](#examples) applications use [Boost](https://www.boost.org)
to parse their command line parameters as well as manage their asynchronous I/O. 
In case Boost libraries are not installed in expected default location
(mostly happens on Windows systems), use variables described in 
[CMake documentation](https://cmake.org/cmake/help/v3.8/module/FindBoost.html) 
to help CMake find required libraries and headers. 
It is recommended to use `-DBoost_USE_STATIC_LIBS=ON` parameter to force
linkage with static Boost libraries.

### Linux Build
```
$> cd /source/of/this/project
$> mkdir build && cd build
$> BUILD_DIR=$PWD CC=gcc CXX=g++ COMMON_INSTALL_DIR=$PWD/install COMMON_BUILD_TYPE=Release ../script/prepare_externals.sh
$> cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PWD/install -DCMAKE_PREFIX_PATH=$PWD/install
$> make install
```

### Windows Build
```
$> cd C:\source\of\this\project
$> mkdir build && cd build
$> set BUILD_DIR=%cd%
$> set GENERATOR="NMake Makefiles"
$> set QTDIR=C:\Qt\5.15.2
$> set COMMON_INSTALL_DIR=%cd%/install
$> ..\script\prepare_externals.bat
$> cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_INSTALL_PREFIX=%cd%/install -DCMAKE_PREFIX_PATH=%cd%\install ^
    -DBOOST_ROOT="C:\Libraries\boost_1_65_1" -DBoost_USE_STATIC_LIBS=ON
$> nmake install
```

# Supported Compilers
Please read [Supported Compilers](https://github.com/commschamp/commsdsl#supported-compilers)
info from [commsdsl](https://github.com/commschamp/commsdsl) project.

# How to Build and Use Generated Code
Please read the
[Generated CMake Project Walkthrough](https://github.com/commschamp/commsdsl/blob/master/doc/GeneratedProjectWalkthrough.md)
documentation page for details on the generated project internals.

The [release](https://github.com/commschamp/cc.demo2.commsdsl/releases)
artifacts contain doxygen generated documentation of the protocol definition.

# Contact Information
For bug reports, feature requests, or any other question you may open an issue
here in **github** or e-mail me directly to: **arobenko@gmail.com**. I usually
respond within 24 hours.

