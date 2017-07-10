# SetCover
Use DLX solve SetCover

## Basic Usage
``` shell
g++ demo.cc -o demo -std=c++14 -O3
./demo < demo_input.txt
```

## Input Format

```
6 5            # 6: size of universe, 5: numbers of sets
0 1 2          # elements in 0th set, indexed from 0
0 3 4          # elements in 1st set, indexed from 0
3 5            # ...
2 3            # ...
0 1            # ...
```
