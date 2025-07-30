# Philosophers: Dining Philosophers Simulation

![Score Badge](https://img.shields.io/badge/Score-100%2F100-brightgreen)

Welcome to **Philosophers**, a modern implementation of the classic Dining Philosophers concurrency problem—ideal for anyone exploring threads, synchronization, and the fun (and peril!) of shared resources in C.

## ⭐ What is This Project?

This project simulates a group of philosophers who alternate between **thinking**, **eating**, and **sleeping**—but must share a limited number of forks. It’s a playful introduction to:

- **Thread synchronization**
- **Mutex-based resource control**
- **Deadlock prevention and starvation detection**
- **Real-time concurrent monitoring**


## 🚥 Rules of the Simulation

- Philosophers alternate between eating, sleeping, and thinking.
- Each needs **two forks (mutexes)** to eat.
- If a philosopher doesn’t eat within the given `time_to_die`, they die.
- Simulation ends if any philosopher dies or all philosophers have eaten the required number of times.


## 🗂️ Project Structure

```
Philosophers/
└── philo/
    ├── inc/
    │   └── philo.h
    ├── obj/
    ├── src/
    │   ├── args_parser.c
    │   ├── main.c
    │   ├── mutex_manager.c
    │   ├── philosophers_actions.c
    │   ├── philosophers_threads.c
    │   ├── simulation_init.c
    │   ├── simulation_monitor.c
    │   ├── simulation_utils.c
    │   └── time_utils.c
    ├── Makefile
    └── philo
```


## 📚 Core Components

| File | Purpose |
| :-- | :-- |
| `args_parser.c` | Command-line argument parsing and validation |
| `main.c` | Program entry and main simulation loop |
| `mutex_manager.c` | Fork/mutex initialization and management |
| `philosophers_actions.c` | Implements eat, sleep and think behaviors |
| `philosophers_threads.c` | Thread creation, execution and cleanup |
| `simulation_init.c` | Sets up initial simulation state and resources |
| `simulation_monitor.c` | Monitors for starved philosophers and completion |
| `simulation_utils.c` | Helper functions supporting the simulation |
| `time_utils.c` | Accurate timekeeping and delays |
| `philo.h` | Structures, prototypes, global includes |

## 🚀 Getting Started

### Build

```bash
make
```

This will compile the project and produce the `philo` executable.

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: How many philosophers (and forks).
- `time_to_die`: Time in ms until a philosopher dies if they don’t eat.
- `time_to_eat`: Eating duration in ms.
- `time_to_sleep`: Sleeping duration in ms.
- `number_of_times_each_philosopher_must_eat`: (Optional) End simulation when everyone has eaten this many times.


#### Example

```bash
./philo 5 800 200 200 7
```

(5 philosophers, 800ms to die, eat for 200ms, sleep for 200ms, eat 7 times each.)

## 🧠 Key Features

- **Robust Thread Synchronization:** Each philosopher is a thread, sharing forks (mutexes) with strict race condition avoidance.
- **Deadlock \& Starvation Prevention:** Uses smart resource ordering and checks to guarantee progress and safety.
- **Modular \& Testable:** Well-structured codebase for readability and extensibility.
- **Live Monitoring:** Background thread detects and reports starved philosophers instantly.


## 🧪 Testing \& Experiments

Put your simulation through its paces with:

- **Normal runs:** Typical parameters, multiple philosophers
- **Edge cases:** Single philosopher, minimum or maximum times
- **Stress tests:** Large groups (20+ philosophers), very low timings


## 🎓 Educational Value

This project is perfect for those learning:

- Classic concurrency problems
- Practical C thread programming
- Real-time synchronization techniques


## 🤝 Contributions

Pull requests and issues are welcome! See something to improve or tweak? Open an issue or make a PR and join the conversation.

*Happy coding and may all your philosophers dine in peace!*
