# ifndef PHILO_H
# define PHILO_H 

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/time.h>



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
    pthread_mutex_t meal_lock;
    pthread_mutex_t simulation_lock;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philosopher   *philos;
} t_data;

/* INIT */
int     valid_agruments(int argc,char **argv,t_data *data);
int init_all(t_data *data, int argc, char **argv);


/* get time */
long long get_time_in_ms(void);

/* MONITOR */
void *monitor_threads(void *arg);
void smart_sleep(long long duration, t_data *data);
void stop_simulation(t_data *data);

/* ACTIONS */
void eat(t_philosopher *philo);
void    take_forks(t_philosopher *philo);
void put_down_forks(t_philosopher *philo);
void *philosopher_routine(void *arg);
void think(t_philosopher *philo);
// void better_sleep(long long time);
void ft_sleep(t_philosopher *philo);

/*  utils  */
int    philos_threads(t_data *data);
void print_action(t_philosopher *philo, char *action);
int is_simulation_running(t_data *data);

/* ROUTINE */
void *philo_routine(void *arg);

/*  utils  libft */
int	ft_atoi(const char *src);
void	ft_putstr_fd(char *s, int fd);
int	is_numeric(const char *str);

/* CLEANUP */
void cleanup(t_data *data);

#endif