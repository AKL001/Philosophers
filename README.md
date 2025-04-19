```
[main.c]
    |
    --> init_all(data, argc, argv)  
            |
            --> parse_args()         (parse command line arguments)
            --> init_mutexes()        (init forks + print/simulation mutexes)
            --> init_philosophers()   (setup philosophers with forks)
    |
    --> create_threads()
            |
            --> philosopher_routine(philosopher) [each philosopher's life]
    |
    --> pthread_create(monitor_routine) [one monitor thread watches all]
    |
    --> pthread_join() [wait for monitor]
    |
    --> pthread_join() [wait for all philosophers]
    |
    --> cleanup()
            |
            --> destroy all mutexes + free memory
```

```
philosophers/
├── Makefile
├── include/
│   └── philo.h
├── src/
│   ├── main.c         ✅
│   ├── philosopher.c  (philosopher life) ✅
│   ├── monitor.c      (watch death) ✅
│   ├── utils.c        (sleep, get time, print) ✅
│   ├── init.c         (create forks and philos) ✅
│   └── cleanup.c      (free everything) ✅
└── obj/               (auto after make)
```
