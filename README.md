# guava-murmurhash3-cpp

This repository contains part of Guava implementation of Murmurhash3 algorithm  
(https://github.com/google/guava) rewritten into C++ language.  
Only String hashing functions are included.

Provided implementation doesn't provide the same results as reference code   
(https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp),
nonetheless identical to Guava ones.
Each hashing function from Guava implementation uses internal buffer. 

This library has been created for MHAP C++ implementation tests and bencharks.
https://github.com/formateu/MHAP  