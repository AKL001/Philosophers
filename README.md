<h1> Just Brain Storming </h1>

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

<h4>Main Flow (Philo life)</h4>

```
START THREAD
    |
    |__ Think
    |
    |__ Pick up forks (lock mutexes)
    |
    |__ Update last_meal_time
    |
    |__ Eat
    |
    |__ Put down forks (unlock mutexes)
    |
    |__ Sleep
    |
(Repeat)
```

<h6>Monitoring</h6>

```
5. Monitoring (Death Detection)
In each philosopher OR in a single monitor thread:

Check every few milliseconds:

current_time - last_meal_time > time_to_die

If true:

Lock death_mutex

Set someone_died = 1

Print death message

Unlock

End simulation

If a required meals count exists, check if all philosophers have eaten enough.
```

```
void smart_sleep(long time_in_ms, t_settings *settings)
{
    long start = get_current_time();
    while (!someone_died)
    {
        if (get_current_time() - start >= time_in_ms)
            break;
        usleep(100); // sleep tiny bits to avoid busy waiting
    }
}
```
