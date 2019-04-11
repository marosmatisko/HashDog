# HashDog.exe

With our program you can "break" hash of supported hash functions with supported attacks.

## Overview
Supported hash functions: *MD5*, *SHA-1*, *SHA-256*\
Supported attacks: *Bruteforce attack*, *Dictionary attack*, *Mask attack*

You can use our program in two ways:
* with input text make hash and use attack for that output 
    - input_message - |4 - 20| characters
```
Hashdog.exe <input_message> <hash_function> <attack>
```
* use hash and length of message as input and "break" that
    - input_hash - hex string in uppercase (length: MD5 = 32, SHA-1 = 40, SHA-256 = 64)
```
Hashdog.exe <input_hash> <length_of_hashed_message> <attack>
```

You can use hash generators: 
[*MD5*](https://passwordsgenerator.net/md5-hash-generator/) 
[*SHA-1*](https://passwordsgenerator.net/sha1-hash-generator/)
[*SHA-256*](https://passwordsgenerator.net/sha256-hash-generator/)

### Hash functions
| Option | Description |
| ------ | ----------- |
| -m   | using hash function *MD5* |
| -s1  | using hash function *SHA-1* |
| -s2  | using hash function *SHA-256* |

### Attacks
| Option | Description |
| ------ | ----------- |
| -b   | using *Bruteforce attack* |
| -d  | using *Dictionary attack* |
| -m  | using *Mask attack* |

## Make a hash

### MD5
```
Hashdog.exe <input> <hash_function> -b
```
#### Usage:
```
Hashdog.exe <input> <hash_function> -b
```

### SHA-1

### SHA-256

### Bruteforce attack:
```
Hashdog.exe <input> <hash_function> -b
Hashdog.exe <hash> <length> -b
```
#### Examples:
```
Hashdog.exe Op1caaa1 -m -b
Hashdog.exe E701E45B0D65A6B43A09F1C4408F9070625356D1 5 -b
```

### Dictionary attack:
```
Hashdog.exe <input> <hash_function> -d <dic_filename>
Hashdog.exe <hash> <length> -d <dic_filename>
```
#### Examples:
```
Hashdog.exe Op1caaa1 -m -d rockyou.txt
Hashdog.exe E701E45B0D65A6B43A09F1C4408F9070625356D1 5 -d rockyou.txt
```

### Mask attack:
```
Hashdog.exe <input> <hash_function> -m <mask>
Hashdog.exe <hash> <length> -m <mask>
```
#### Examples:
```
Hashdog.exe Op1caaa1 -m -m %u%l%d%l%l%la1
Hashdog.exe E701E45B0D65A6B43A09F1C4408F9070625356D1 5 -m %u%l%d%l%l%la1
```



## Mask symbols

 Option | Description 
 ------ | ----------- 
 %a  | lowercase & uppercase alphabet 
 %l  | lowecase alphabet only 
 %u  | uppercase alphaber only 
 %s  | special characters only 
 %d  | digits only 
 %c  | all characters   
 
Standalone character represent itself, e.g. 'a' represent 'a'.
For '%' use %%.
