# HashDog.exe

With our program you can "break" hash of supported hash functions with supported attacks.
## Requirements
OpenSSL library
* tested with version 1.1.1a for Windows
* program needs to be built with correctly linked OpenSSL **include** and **lib** folder

CUDA Toolkit
* tested with version 10.1
## Overview
Supported hash functions: *MD5*
Supported attacks: *Bruteforce attack*


Hashdog.exe <input_hash> <length_of_password>
Hashdog.exe E701E45B0D65A6B43A09F1C4408F9070625356D1 8 -b
