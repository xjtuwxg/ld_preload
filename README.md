# ld_preload
The LD_PRELOAD tricks.

### SIGTRAP (int3) signal handler
```
├── src
│   └── sig.c
└── test
    └── int3.c
```

Printing the RIP address on intercepting `int3` instructions:
```
❯ make run_int3
LD_PRELOAD=./sig.so ./int3 && echo "=> Exit(0)" || echo "=> Exit(!0)"
INFO  Signal handler loaded ...   at _init (sig.c:37)
pid: 50444
Before int3 ...
INFO  signal #5. rip: 0x5555555551aa (1)   at handler (sig.c:16)
INFO  signal #5. rip: 0x5555555551ab (2)   at handler (sig.c:16)
INFO  signal #5. rip: 0x5555555551ac (3)   at handler (sig.c:16)
After int3 ...
```

