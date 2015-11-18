# Tests of memshell

## Testing alloc
```
>init
>alloc 0x100
>alloc 0x200
>alloc 0x300
>alloc 0x400
```
Then, we should have the following
```
> used
1 0x0 0x100
2 0x100 0x200
3 0x300 0x300
4 0x600 0x400
> show
Mémoire initialement disponible : 1048576 octets
0xA00 0xFF600
```



## Testing the modulo size
```
>init
>alloc 0x99
```

The memory should look like this :
```
>used
1 0x0 0x99
>show
Mémoire initialement disponible : 1048576 octets
0xA0 0xFFF60
```
The free block start at 0xA0 which is not 0x0 + 0x99 because of the modulo size.


## Testing the free
```
init
alloc 0x100
alloc 0x100
alloc 0x100
alloc 0x100
```

```
>used
1 0x0 0x100
2 0x100 0x100
3 0x200 0x100
4 0x300 0x100
5 0x400 0x100
>show
Mémoire initialement disponible : 1048576 octets
0x500 0xFFB00
>
```

Free without any merges
```
>free 2
>used
1 0x0 0x100
3 0x200 0x100
4 0x300 0x100
5 0x400 0x100
>show
Mémoire initialement disponible : 1048576 octets
0x100 0x100
0x500 0xFFB00
```

Free without any merges
```
> free 4
>used
1 0x0 0x100
3 0x200 0x100
5 0x400 0x100
>show
Mémoire initialement disponible : 1048576 octets
0x100 0x100
0x300 0x100
0x500 0xFFB00
```

Free merging with a free block following
```
> free 1
>used
3 0x200 0x100
5 0x400 0x100
>show
Mémoire initialement disponible : 1048576 octets
0x0 0x200
0x300 0x100
0x500 0xFFB00
```

Free merging with a free block preceding
```
>free 5
>used
3 0x200 0x100
>show
Mémoire initialement disponible : 1048576 octets
0x0 0x200
0x300 0xFFD00
```

Free merging with a free block following and with a free block preceding
```
>free 3
>used
>show
Mémoire initialement disponible : 1048576 octets
0x0 0x100000
```

## First Fist allocation
```
init
alloc 0x800
alloc 0x800
alloc 0x800
alloc 0x800
free 1
free 3
```

There are now two free blocks of 0x800 bytes in the memory and a huge free block (the trailing one).
```
>used
2 0x800 0x800
4 0x1800 0x800
>show
Mémoire initialement disponible : 1048576 octets
0x0 0x800
0x1000 0x800
0x2000 0xFE000
```

3 blocks are currently big enough to hold an allocation of 0x500. We will thus make 3 allocations of this size and make sure that the free blocks are filled in in the right order.

```
>alloc 0x500
5 0x0
>used
5 0x0 0x500
2 0x800 0x800
4 0x1800 0x800
>show
Mémoire initialement disponible : 1048576 octets
0x500 0x300
0x1000 0x800
0x2000 0xFE000
```
This bloc was allocated at the beginning of the fist free block since there was enough space

```
>alloc 0x500
6 0x1000
>used
5 0x0 0x500
2 0x800 0x800
6 0x1000 0x500
4 0x1800 0x800
>show
Mémoire initialement disponible : 1048576 octets
0x500 0x300
0x1500 0x300
0x2000 0xFE000
```
The first free block wasn't big enough for this allocation. It thus used the second one.

```
>alloc 0x500
7 0x2000
>used
5 0x0 0x500
2 0x800 0x800
6 0x1000 0x500
4 0x1800 0x800
7 0x2000 0x500
>show
Mémoire initialement disponible : 1048576 octets
0x500 0x300
0x1500 0x300
0x2500 0xFDB00
```
The first two free blocks weren't big enough for this allocation. It thus used the third one.
