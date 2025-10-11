# Milestone 3 – Completed 🟢

Welcome to my repository documenting **Milestone 3** at 42 School. This repository tracks my ongoing progress on both core projects—**Philosophers** and **Minishell**—including technical highlights, structures, and implementation insights.

## 🏅 My Scores

| Project | Status | Focus \& Technical Highlights |
| :-- | :--: | :-- |
| Philosophers | ✅ 100/100 | Concurrent programming, thread/mutex synchronization |
| Minishell | ✅ 100/100 | Shell parsing, process management, Unix signals |

## 🔎 Project Details

### 🍝 Philosophers – 100/100 ✅

- **Objective:**
Implement and simulate the classic Dining Philosophers problem to explore concurrency, synchronization, and deadlock avoidance.
- **Key Features:**
    - Efficient thread handling with **POSIX threads**.
    - Mutexes for fork management to prevent data races.
    - Deadlock detection strategies and starvation prevention.
    - Responsive logging and timing to track philosopher actions.
- **Skills gained:** Concurrency, multithreading, resource locking, timing coordination, edge-case testing.


### 🐚 Minishell – 100/100 ✅

- **Objective:** Develop a simple Unix shell replicating essential Bash functionalities.
- **Key Features:**  
    - Custom command parser with quoting and variable expansion.  
    - Execution of commands via PATH or absolute/relative paths.  
    - Support for pipes (`|`), redirections (`>`, `<`, `>>`, `<<`).  
    - Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.  
    - Signal handling for `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.  
    - Command history using the `readline` library.
- **Skills gained:** Process and memory management, I/O redirection, inter-process communication, signal handling, and advanced C programming.



## 📂 Repository Structure

Projects are split into dedicated subdirectories, each with their code and relevant documentation:

```
42-cursus-level-3/
│
├── philosophers/
└── minishell/
```

## 🏆 Personal Highlights

- Tackling real concurrent systems and Unix shell internals.
- Applying advanced C coding standards and debugging multi-process environments.
- Incrementally building resilient code with dedicated testing for corner cases.


## 🚀 How to Explore

1. Clone this repo:

```
git clone https://github.com/viceda-s/42-cursus-level-3.git
```

2. Visit each project folder for implementation and evolving documentation (build/run instructions included).

**For feedback, issues, or collaboration, open an issue or contact me directly!**
