# ifndef PHILO_H
# define PHILO_H 

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philosopher {
    int             id;
    int             meals_eaten;
    long long       last_meal_time;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data   *data;
} t_philosopher;

typedef struct s_data {
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             max_meals;
    int             is_simulation_running;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philosopher   *philos;
} t_data;







#endif