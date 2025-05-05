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
# define SEM_DONE "/sem_done"
#define SEM_SIM_STATUS "/sem_sim_status"
// # define IS_SIMULATION "/sem_is_simulation"
# define SEM_ALL_ATE "/sem_all_ate"
# define SEM_DONE_PREFIX "/sem_done_"

typedef struct s_sem
{
	sem_t	ptr;
	char	*name;
}				t_sem;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pid_t			pid;
	// t_sem			done;
	sem_t			*done;
	char 			done_sem_name[250];
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
	int 			meal_monitor_running;
	long long		start_time;
	pthread_t 		meal_monitor_tid;
	pthread_t		is_dead_monitor_tid;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meal_check;
	sem_t			*dead;
	sem_t 			*sim_status;
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
size_t	ft_strlcpy(char *dst, const char *src, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int nbr);

/* UTILS */
long long	get_time_in_ms(void);
void	smart_sleep(long long duration, t_data *data);


/* PHILO  ROUTINE */
void	philosopher_routine(t_philo *philo);

/* ACTIONS */
void	think(t_philo *philo);
void		put_down_forks(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	eat(t_philo *philo);
void	take_forks(t_philo *philo);


/* MONITORING */
int	start_processes(t_data *data);
void	wait_for_processes(t_data *data);
void	*monitor_routine(void *arg);

/* cleanup */
void	kill_processes(t_data *data);
void	unlink_semaphores(void);
void	close_semaphores(t_data *data);
void	cleanup(t_data *data);
void stop_simulation(t_data *data);

/* LIBFT */



#endif