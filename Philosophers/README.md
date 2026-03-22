# Philosophers

*This project has been created as part of the 42 curriculum by viceda-s.*

## Description

**Philosophers** is a classic concurrent programming project that implements the Dining Philosophers problem. The project consists of two parts:

- **Mandatory Part**: A multi-threaded solution using POSIX threads (pthreads) and mutexes to solve the dining philosophers synchronization problem.
- **Bonus Part**: A multi-process solution using semaphores, demonstrating an alternative approach to concurrency.

### Goal

The project teaches fundamental concepts of concurrent programming, including:
- Thread/process creation and management
- Synchronization primitives (mutexes and semaphores)
- Deadlock prevention and avoidance strategies
- Race condition prevention
- Real-time monitoring and resource management

### Overview

Philosophers sit around a table with a bowl of spaghetti in the middle. Each philosopher alternates between three states: thinking, eating, and sleeping. To eat, a philosopher needs two forks—one on each side. The challenge is to design a system where:
- No philosopher starves
- All philosophers can eat and think
- There are no deadlocks or race conditions

## Instructions

### Compilation

#### Mandatory Part
```bash
cd philo
make
```

#### Bonus Part
```bash
cd philo_bonus
make
```

### Execution

#### Mandatory Part (Threads + Mutexes)
```bash
./philo/philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

#### Bonus Part (Processes + Semaphores)
```bash
./philo_bonus/philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Arguments

- **number_of_philosophers**: The number of philosophers and forks at the table (1-200)
- **time_to_die**: Time in milliseconds before a philosopher dies if they haven't eaten
- **time_to_eat**: Time in milliseconds it takes a philosopher to eat
- **time_to_sleep**: Time in milliseconds a philosopher sleeps
- **number_of_times_each_philosopher_must_eat** (optional): If specified, the simulation ends when all philosophers have eaten this many times

### Output Format

Each philosopher's state change is printed with the following format:
```
<timestamp_in_ms> <philosopher_id> <state>
```

States are:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

### Example Usage

```bash
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep, eat 7 times each
./philo 5 800 200 200 7

# Single philosopher test (interesting edge case)
./philo 1 800 200 200

# Stress test with many philosophers
./philo 100 400 100 100
```

## Mandatory Part Features

- **Program Name**: `philo`
- **Implementation**: Multi-threaded using POSIX pthreads
- **Synchronization**: Mutex-based fork management
- **Resource Management**: One fork (mutex) per adjacent pair of philosophers
- **Monitoring**: Background monitor thread detects philosopher deaths

### Key Implementation Details

- Each philosopher is a separate thread
- Forks are protected by mutexes to prevent race conditions
- A dedicated monitor thread checks for starvation
- Proper synchronization ensures no data races
- All heap allocations are properly freed

## Bonus Part Features

- **Program Name**: `philo_bonus`
- **Implementation**: Multi-process using fork() and semaphores
- **Synchronization**: Semaphore-based fork management
- **Process Model**: Each philosopher runs as a separate process
- **Main Process**: Does not participate in dining; only manages child processes

### Key Implementation Differences from Mandatory Part

- Philosophers are **processes** instead of threads
- Forks are represented by a single **semaphore** counting available forks
- Each philosopher decrements the semaphore twice (pick two forks) and increments twice (drop forks)
- No separate monitor thread; monitoring integrated into main process

## Resources

### Documentation
- [POSIX Threads (pthreads)](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html) - Official pthread reference
- [POSIX Semaphores](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/semaphore.h.html) - Official semaphore reference
- [The Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) - Classic explanation on Wikipedia

### Classic References
- Dijkstra, E. W. (1971). "Hierarchical Ordering of Sequential Processes"
- Stallings, W. (2018). "Operating Systems: Internals and Design Principles" - Chapter on Process Synchronization

### AI Usage

AI tools were used to assist with:
- Generating initial code scaffolding and structure templates
- Validating semaphore and mutex usage patterns
- Debugging timing and synchronization edge cases
- Reviewing error handling and resource cleanup logic

All code was thoroughly reviewed, tested, and verified for correctness before integration.

## Project Structure

```
Philosophers/
├── philo/                          # Mandatory part (threads + mutexes)
│   ├── Makefile
│   ├── inc/
│   │   └── philo.h
│   ├── src/
│   │   ├── main.c
│   │   ├── args_parser.c
│   │   ├── mutex_manager.c
│   │   ├── philosophers_actions.c
│   │   ├── philosophers_threads.c
│   │   ├── simulation_init.c
│   │   ├── simulation_monitor.c
│   │   ├── simulation_utils.c
│   │   └── time_utils.c
│   └── philo                       # Compiled executable
│
├── philo_bonus/                    # Bonus part (processes + semaphores)
│   ├── Makefile
│   ├── inc/
│   │   └── philo_bonus.h
│   ├── src/
│   │   ├── main.c
│   │   ├── args_parser.c
│   │   ├── semaphore_manager.c
│   │   ├── philosopher_process.c
│   │   ├── philosopher_actions.c
│   │   ├── simulation_init.c
│   │   ├── monitor.c
│   │   ├── simulation_utils.c
│   │   └── time_utils.c
│   └── philo_bonus                 # Compiled executable
│
├── en.subject.pdf                  # Official project specification
└── README.md                        # This file
```

## Testing & Validation

### Recommended Test Cases

1. **Basic functionality** (5 philosophers, normal timing)
   ```bash
   ./philo/philo 5 800 200 200
   ```

2. **Edge case: Single philosopher** (will die as expected)
   ```bash
   ./philo 1 800 200 200
   ```

3. **Meal limit test** (should exit when all have eaten enough)
   ```bash
   ./philo 3 410 200 200 5
   ```

4. **Stress test** (many philosophers, tight timings)
   ```bash
   ./philo 50 800 200 200
   ```

5. **Comparison test** (run same arguments on both versions)
   ```bash
   ./philo 4 600 200 200
   ./philo_bonus 4 600 200 200
   ```

### Important Checks

- ✓ No segmentation faults or memory leaks
- ✓ No deadlocks or infinite waits
- ✓ All philosophers get a fair chance to eat
- ✓ Death detection within 10ms of actual death time
- ✓ No data races (verified with tools like Helgrind if available)
- ✓ Clean output with no overlapping messages

## Compilation & Cleanup

```bash
# Build mandatory part
cd philo && make && cd ..

# Build bonus part
cd philo_bonus && make && cd ..

# Clean everything
cd philo && make clean && cd ..
cd philo_bonus && make clean && cd ..

# Full rebuild
cd philo && make re && cd ..
cd philo_bonus && make re && cd ..
```

## Notes

- The project forbids global variables
- All required functions from the specification must be used correctly
- Makefiles follow the 42 standard (must have all, clean, fclean, re, and NAME rules)
- The implementation avoids unnecessary complexity while remaining robust
- Both versions handle edge cases gracefully (single philosopher, immediate death, etc.)

## Author

**viceda-s** - 42 Luxembourg

---

*"I never thought philosophy would be so deadly."*
