*This project has been created as part of the 42 curriculum by jobraga-.*

# philosophers

## Description

philosophers is a simulation of the classic **Dining Philosophers Problem**, developed as part of the 42 school curriculum. A number of philosophers sit at a round table, each needing two forks to eat — one on their left and one on their right. They cycle through three states: eating, sleeping, and thinking. The challenge is to coordinate access to shared forks without any philosopher starving, and without causing data races or deadlocks.

The project introduces **POSIX threads** (`pthread`) and **mutex synchronization**, requiring a precise understanding of concurrent programming, shared state, and timing.

## Instructions

### Requirements

- Linux or macOS
- A C compiler (`cc`) with the flags `-Wall -Werror -Wextra -pthread`
- `make` utility

### Compilation

```bash
git clone https://github.com/jobraga/philosophers.git
cd philosophers/philo
make
```

### Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All time values are in **milliseconds**. The optional fifth argument stops the simulation once every philosopher has eaten that many times.

**Examples:**

```bash
./philo 5 800 200 200         # 5 philosophers, no one should die
./philo 5 800 200 200 7       # stops after each philosopher eats 7 times
./philo 1 800 200 200         # edge case: single philosopher, always dies
./philo 4 410 200 200         # tight timing test
```

### Output format

Each event is logged as:

```
timestamp_in_ms philosopher_id action
```

Where action is one of: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, or `died`.

### Constraints

- No philosopher should die if the timing allows survival
- Log messages must not be interleaved or delayed by more than 10ms
- No data races are permitted (verified with tools like `valgrind --tool=helgrind`)

### Cleanup

```bash
make clean    # removes object files
make fclean   # removes object files and the executable
make re       # full recompile
```

## Concurrency Design

**One thread per philosopher.** Each philosopher runs as an independent `pthread`, executing the eat → sleep → think cycle in a loop. A dedicated **monitor thread** (`waiter`) runs concurrently, checking every 500µs whether any philosopher has exceeded `time_to_die` or whether the optional meal limit has been reached.

**Four mutexes** protect shared state:

- `forks[]` — one mutex per fork; a philosopher must lock both adjacent forks to eat
- `write_flag` — ensures log messages are printed atomically, preventing interleaved output
- `dead_flag` — protects the `dead_flag` boolean and `id_dead` fields, which signal simulation end
- `meal_flag` — protects `last_eat_time` and `count_eat` per philosopher, read by the monitor and written during eating

**Deadlock prevention** is handled by fork acquisition order: even-numbered philosophers lock their right fork first, odd-numbered lock their left fork first. This breaks the circular wait condition that would otherwise cause all philosophers to hold one fork and wait indefinitely for the other.

**Starvation prevention for odd counts.** When the number of philosophers is odd, `philo_think` introduces an adaptive delay: if `time_to_eat >= time_to_sleep`, a philosopher waits `(time_to_eat * 2) - time_to_sleep` milliseconds before attempting to eat again. This prevents the faster philosophers from monopolizing forks at the expense of their slower neighbors.

**Precise sleeping** is implemented via `ft_usleep`: instead of calling `usleep` for the full duration (which can overshoot), it loops with 1ms sleeps and checks the dead flag on each iteration, allowing threads to exit promptly when the simulation ends.

**The single philosopher edge case** is handled before any threads are created: with one philosopher and one fork, eating is impossible, so the program simply waits `time_to_die` milliseconds and prints the death message directly.

## Resources

- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads programming guide — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [Deadlock — Wikipedia](https://en.wikipedia.org/wiki/Deadlock)
- [42 Docs — philosophers subject](https://harm-smits.github.io/42docs/projects/philosophers)

**AI usage:** Claude (claude.ai) was used to help write and structure this README based on the project's source files and the 42 subject requirements. No code was generated or modified with AI assistance.