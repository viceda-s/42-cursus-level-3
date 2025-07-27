# Philosophers - Dining Philosophers Problem

## Overview

This project is an implementation of the classic *Dining Philosophers* problem using concurrent programming in C with pthreads. It demonstrates advanced synchronization techniques, deadlock prevention, and resource management in a multi-threaded environment.

The problem consists of philosophers sitting around a table, alternating between thinking and eating. Each philosopher needs two forks (shared resources) to eat but there are fewer forks than philosophers, raising challenges around concurrency, deadlock, and starvation.

---

## Features

- Robust prevention of **deadlocks** based on resource hierarchy ordering.
- Fine-grained synchronization using multiple specialized mutexes:
  - `write_mutex` for synchronized console output.
  - `death_mutex` for safe simulation termination.
  - `meal_mutex` for protecting shared state related to meals.
- Accurate timing control with custom `ft_usleep()` for precise sleep durations.
- Handling of edge cases such as simulation with a single philosopher.
- Monitor thread implements continuous checking for philosopher deaths and simulation end conditions.
- Defensive programming with comprehensive resource cleanup to avoid leaks.

---

## Usage

### Compilation
```
make
```
### Running the Simulation
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The total number of philosophers (1 to 200).
- `time_to_die` (ms): Time in milliseconds before a philosopher dies without eating.
- `time_to_eat` (ms): Time in milliseconds that a philosopher spends eating.
- `time_to_sleep` (ms): Time in milliseconds that a philosopher sleeps.
- `[number_of_times_each_philosopher_must_eat]` (optional): Number of meals each philosopher must eat before the simulation ends. If omitted, simulation runs until a philosopher dies.

Example:
```
./philo 5 800 200 200 5
```

Runs a simulation with 5 philosophers, where each philosopher dies if they don’t eat within 800ms, spends 200ms eating and sleeping, and simulation stops after each philosopher has eaten 5 times.

---

## Implementation Details

### Deadlock Prevention

Philosophers pick up forks in a strict global order determined by comparing the forks' memory addresses. This guarantees no circular wait, preventing deadlock effectively and deterministically.

### Synchronization

- Uses three mutexes specialized for:
  - Controlled and thread-safe output operations.
  - Managing the simulation state and detecting simulation termination.
  - Protecting access to shared meal data.

### Monitoring

A dedicated monitor thread checks at regular intervals for two conditions:

- If any philosopher has not eaten within `time_to_die`.
- If all philosophers have eaten the required number of meals (if specified).

The monitor gracefully signals the end of the simulation and outputs death messages consistently.

### Timing

A custom sleep function `ft_usleep()` improves precision over standard `usleep()` by looping with short sleeps and checking elapsed time, balancing accuracy and CPU usage.

---

## Edge Cases

- **Single philosopher:** Properly handled by allowing the philosopher to pick only one fork and eventually die due to starvation.
- **Large numbers of philosophers:** The implementation scales up to 200 philosophers with proper synchronization and resource management.

---

## Project Structure

| File               | Purpose                               |
|--------------------|-------------------------------------|
| `main.c`           | Program entry point and argument parsing |
| `philo.h`          | Data structures and function prototypes |
| `simulation_init.c` | Initialization and cleanup functions |
| `mutex_manager.c`  | Initialization and destruction of mutexes |
| `philosopher_thread.c` | Philosopher thread routines and lifecycle management |
| `philosopher_actions.c` | Actions: take forks, eat, sleep, think |
| `simulation_monitor.c` | Monitor thread implementation |
| `time_utils.c`     | Time and sleep utility functions |
| `simulation_utils.c` | Helper functions such as printing and simulation state checks |

---

## Requirements

- POSIX-compliant system (Linux, macOS)
- C compiler (gcc recommended)
- pthreads library (usually included in standard C libraries)

---

## How to Contribute

Feel free to fork the repository and submit pull requests to improve functionality, add features, or fix bugs. Please follow standard coding conventions and provide clear commit messages.

---

## License

This project is open-source and available under the MIT License.

---

## References

- Dijkstra, E.W., “The Dining Philosophers Problem,” 1965.
- POSIX Threads Programming [https://man7.org/linux/man-pages/man7/pthreads.7.html](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- Various academic papers on concurrency and deadlock prevention.

---

## Contact

For any questions or suggestions, please open an issue or contact me via GitHub.

---

*Crafted with care to demonstrate the fundamentals and complexities of concurrent programming.*
