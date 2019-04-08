# HashDog

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
## Input
from 4 to 20 chars
## Hash 
Valid MD5, SHA1 or SHA256 hash (32, 40 or 64 lenght hex string in uppercase!)
Please use generators: [MD5](https://passwordsgenerator.net/md5-hash-generator/), [SHA1](https://passwordsgenerator.net/sha1-hash-generator/), [SHA256](https://passwordsgenerator.net/sha256-hash-generator/)

## Hash function

| Option | Description |
| ------ | ----------- |
| -m   | using hashing function MD5 |
| -s1  | using hashing function SHA-1 |
| -s2  | using hashing function SHA-256 |


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
