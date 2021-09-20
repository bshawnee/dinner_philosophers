# dinner_philosophers
Solving the [Hungry Philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem) Problem

- # Philo Description:
This program (located in the Philo folder) uses mutexes and threads to synchronize philosophers
- # Philo_bonus Description:
This program (located in the Philo folder) uses semaphores and forks to synchronize philosophers
# How to use:
the program takes 5 arguments (the 5th argument is optional):
1. Number of philosophers.
2. The time(ms) of the death of the philosopher.
3. The time(ms) for which the philosopher eats.
4. Philosopher's thinking time(ms).
5. (optional) How many times should all philosophers eat.

- run "make"
- run ./philo(or ./philo_bonus) 4 410 200 200
