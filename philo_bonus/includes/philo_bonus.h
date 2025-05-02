#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>         
#include <sys/stat.h>
#include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
 #include <signal.h>
 #include <sys/wait.h>

# define SEM_FORKS "/sem_forks"
# define SEM_PRINT "/sem_print"
# define SEM_MEAL_CHECK "/sem_meal_check"
# define SEM_DEAD "/sem_dead"
# define SEM_ALL_ATE "/sem_all_ate"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pid_t			pid;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				is_simulation_running;
	long long		start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meal_check;
	sem_t			*dead;
	sem_t			*all_ate;
	t_philo			*philos;
	pid_t			*pids;
}					t_data;

/* MAIN */
int	is_simulation_running(t_data *data);
void	print_action(t_philo *philo, char *action);
void	start_simulation(t_data *data);

/* INIT */
int	init_all(t_data *data, int argc, char **argv);
int	init_philosophers(t_data *data);

/* parsing libft */
void	ft_putstr_fd(char *s, int fd);
int	ft_atoi(const char *src);
size_t	ft_strlen(const char *s);
int	is_numeric(const char *str);
int	ft_isdigit(int c);

/* UTILS */
long long	get_time_in_ms(void);
void	smart_sleep(long long duration, t_data *data);


/* PHILO  ROUTINE */
void	philosopher_routine(t_philo *philo);


/* MONITORING */
int	start_processes(t_data *data);
void	wait_for_processes(t_data *data);
void	*monitor_routine(void *arg);

/* cleanup */
void	kill_processes(t_data *data);
void	unlink_semaphores(void);
void	close_semaphores(t_data *data);
void	cleanup(t_data *data);


#endif