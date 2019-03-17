# HashDog

Bruteforce attack:
```
Hashdog.exe <input> <hash> -b
Hashdog.exe <hash> <length> -b
```

Dictionary attack:
```
Hashdog.exe <input> <hash> -d <dic_filename>
Hashdog.exe <hash> <length> -d <dic_filename>
```

Mask attack:
```
Hashdog.exe <input> <hash> -m <mask>
Hashdog.exe <hash> <length> -m <mask>
```

## Hash

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

For '%' use %%.
