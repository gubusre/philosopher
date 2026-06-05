*This project has been created as part of the 42 curriculum by gubusque.*

---

## Description

**Philosophers** is an implementation of the classic synchronization problem known as the **Dining Philosophers Problem**, originally proposed by Edsger Dijkstra in 1965.

N philosophers sit around a circular table. Between each pair of philosophers there is a fork. To eat, a philosopher must pick up the two forks beside them (left and right). The challenge is to coordinate access to the forks so that:

- No philosopher starves to death.
- There is no deadlock (a circular wait in which everyone blocks forever).
- There are no data races (unprotected concurrent access to shared memory).

The implementation uses **POSIX threads** (`pthread`) and **mutexes** to manage concurrency. Each philosopher is an independent thread, each fork is a mutex, and a dedicated monitor thread supervises the state of the simulation.

### Behavior

Each philosopher cycles through three states:

1. **Think** — waits for the forks to become available.
2. **Eat** — holds both forks for `time_to_eat` ms.
3. **Sleep** — releases the forks and sleeps for `time_to_sleep` ms.

The simulation ends when a philosopher dies (more than `time_to_die` ms without eating) or when every philosopher has eaten the required minimum number of times.

---

## Instructions

### Build

```bash
make
```

Builds the `philo` binary in the current directory.

```bash
make clean    # removes the object files (.o)
make fclean   # removes the .o files and the binary
make re       # rebuilds from scratch
```

### Run

```bash
./philo <n_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [times_must_eat]
```

| Argument | Description |
|---|---|
| `n_philosophers` | Number of philosophers (and of forks) |
| `time_to_die` | Time in ms a philosopher can go without eating before dying |
| `time_to_eat` | Time in ms it takes a philosopher to eat |
| `time_to_sleep` | Time in ms a philosopher sleeps after eating |
| `times_must_eat` | (Optional) The simulation stops once every philosopher has eaten this many times |

### Output format

```
<timestamp_ms> <philosopher_id> <action>
```

Possible actions: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`.

---

## Technical decisions

### Separate mutexes for printing and state

Printing is guarded by a dedicated `print_mutex`, while the `stop` flag is guarded by a separate `state_mutex`. Keeping them apart means that checking whether the simulation has ended — which happens very frequently inside the sleep loop — never competes for the same lock a philosopher needs in order to print. The `died` message is written while the stop flag is set and the print lock is held, in the same critical section, which makes it impossible for a philosopher to print any action after a death has been reported.

### Per-philosopher meal mutex

Each philosopher owns a `meal_mutex` that protects its `last_meal` timestamp and its `meals_eaten` counter. The monitor reads those fields under the same lock, so there is no data race between a philosopher updating its last meal and the monitor checking it.

### Synchronizing last_meal with start_time

`start_time` and every philosopher's `last_meal` are set to the same instant, before any thread is created. Setting them up front (rather than inside each thread) avoids an unprotected concurrent write and prevents the monitor from computing an inflated hunger delta caused by initialization time.

### Fork acquisition order by parity

To avoid deadlock, even-id philosophers always pick up their left fork first, and odd-id philosophers pick up their right fork first. This asymmetry breaks the circular-wait condition of a deadlock without needing `pthread_mutex_trylock`.

### Even/odd staggering

Even-id philosophers wait `time_to_eat / 2` before starting their first cycle. This desynchronizes adjacent philosophers from the very beginning and reduces contention over the forks.

### Think pause for an odd number of philosophers

When the number of philosophers is odd, a philosopher thinks for a bounded extra time after sleeping (about half of the slack `time_to_die - time_to_eat - time_to_sleep`). This spaces meals out evenly and prevents the starvation pattern that an odd count tends to produce.

### Joined monitor thread

The monitor is created with `pthread_create` and joined, not detached. It sets the stop flag and returns; the main thread joins the philosopher threads first and the monitor last, which guarantees a clean shutdown with no use-after-free.

---

## Resources

### Official documentation

- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### Articles and references

- Dijkstra, E. W. (1971). *Hierarchical ordering of sequential processes.* — The original paper describing the problem.
- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Deadlock — Wikipedia](https://en.wikipedia.org/wiki/Deadlock)

### AI usage

Two AI tools were used as a support during development: **GitHub Copilot** and **Claude (Anthropic)**. AI was used as an aid to debug non-deterministic behavior, review the synchronization design, and generate repetitive test cases.

**GitHub Copilot** was used for:

- Explaining concurrency and synchronization concepts.
- Discussing race conditions and mutex design.
- Reviewing critical functions.
- Generating automated testers to validate stability and detect inconsistent deaths.

**Claude (Anthropic)** was used for:

- Code review and analysis: identifying race conditions, data races, and synchronization weaknesses (for example, the contention caused by sharing a single mutex for both printing and the stop flag, and the fragility of a detached monitor thread).
- Reviewing the synchronization design: separating the print mutex from the state mutex, the per-philosopher meal mutex, the parity-based fork ordering, and the joined monitor.
- Reviewing argument parsing and error handling (for example, removing an unjustified upper bound on the philosopher count and adding overflow protection).
- Generating repetitive stress and regression tests.
- Drafting this README.
