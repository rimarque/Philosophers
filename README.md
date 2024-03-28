# **Philosophers**

## :speech_balloon: **About**
This project is about solving the dining philosophers problem, using threads. 
The philosopher's problem is a synchronization problem where multiple philosophers sit at a table with limited resources. 
They alternate between thinking, sleeping and eating, but must avoid deadlock and starvation by coordinating their actions to prevent conflicts over shared resources.
Coded in C.

## 🙋‍♀️ **Authorship**
- [Rita Marques](https://github.com/rimarque)

## :inbox_tray: **Cloning the repository**

```shell
git clone git@github.com:rimarque/Philosophers.git 
```

## 💎 **Features**
```
- Each philosopher is a thread
- There are as many forks as philosophers, one between each pair of philosophers
- Every forks state is protected with a mutex
- A philosopher takes their right and left forks to eat
- Every philosopher needs to eat and should never starve
- Philosophers don´t communicate with each other
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again.
- Number of philosophers, time it takes for a philosopher to die of starvation,
time it takes a philosopher to eat and time a philosopher spends sleeping are taken as an argument
- There is an optional argument: number of times a philosopher should eat
- The simulation stops when all philosopher have eaten the number of times specified.
If not specified, the simulation stops when a philosopher dies.
```

## :link: **Compilation**
To compile the program you should run `make`.

This rule will generate an executable file named `philo`. To launch the executable you should follow this syntax:

```sh
$ ./philo <n_philo> <time_to_die> <time_to_eat> <time_to_sleep> <OPCIONAL(n_eat)>
```
## 🥇 **Testing**
In order for the simulation to run smoothly, with no philosophers dying of starvation, the parameters need to be set properly. Because there is only one fork per philosopher, and the philosophers need two forks to eat, they must take turns eating. 
### Lets test for an even number of philosofers!
If there is an even number of philosofers, half the philosophers can it at a time, taking two shifts so that every philosofer as time to eat.
- Time_to_die must be equal or greater than double the time_to_eat plus 10 (for tolerance): this ensures that philosophers have enough time to take turns eating before facing starvation.
- Time_to_die must be equal or greater than the sum of time_to_eat plus time_to_sleep plus 10 (for tolerance): this ensures that a philosopher has enough time to eat and sleep before potentially starving.

With **time_to_die** >= **time_to_eat** * 2 + 10: the philosophers will never starv and the simulation will never stop
```sh
$ ./philo 12 410 200 200
```
With **time_to_die** < **time_to_eat** + **time_to_sleep** + 10:. The philosopher will starv:
```sh
$ ./philo 12 410 200 210
```
### Lets test for an odd number of philosofers! 
