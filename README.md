# Milestone 3 – In Progress

Welcome to my repository documenting **Milestone 3** at 42 School. This repository tracks my ongoing progress on both core projects—**Philosophers** and **Minishell**—including technical highlights, structures, and implementation insights.

> **Status:** _Work in Progress_ 🚧

## 🔎 Project Overview

| Project | Status | Focus \& Technical Highlights |
| :-- | :--: | :-- |
| Philosophers | ⏳ In Progress | Concurrent programming, thread/mutex synchronization |
| Minishell | ⏳ In Progress | Shell parsing, process management, Unix signals |

### 🍝 Philosophers

- **Objective:**
Implement and simulate the classic Dining Philosophers problem to explore concurrency, synchronization, and deadlock avoidance.
- **Key Features (planned):**
    - Efficient thread handling with **POSIX threads**.
    - Mutexes for fork management to prevent data races.
    - Deadlock detection strategies and starvation prevention.
    - Responsive logging and timing to track philosopher actions.
- **Anticipated Skills:** Concurrency, multithreading, resource locking, timing coordination, edge-case testing.


### 🐚 Minishell

- **Objective:**
Recreate a simple Unix shell capable of interpreting and executing user commands.
- **Key Features (planned):**
    - Custom parser for handling complex command lines, quoting, and variable expansion.
    - Process forking and execution with robust error management.
    - Implementation of pipelines (`|`), redirections (`>`, `<`), and built-in commands.
    - Signal handling (SIGINT/SIGQUIT) for user interaction fidelity.
- **Anticipated Skills:** Parsing, process and memory management, file descriptor manipulation, shell scripting standards.


## 📂 Repository Structure

Projects are split into dedicated subdirectories, each with their code and relevant documentation:

```
42-cursus-level-3/
│
├── philosophers/
└── minishell/
```


## 🚦 Progress Tracker

| Milestone Item | Status |
| :-- | :--: |
| Repository structure | ✅ Complete |
| Philosophers code | ⏳ WIP |
| Philosophers evaluation | ⏳ WIP |
| Minishell docs | ⏳ WIP |
| Minishell evaluation | ⏳ WIP |

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

_This README will be updated regularly with progress, implementation notes, and final results._

**For feedback, issues, or collaboration, open an issue or contact me directly!**

<div style="text-align: center">⁂</div>
