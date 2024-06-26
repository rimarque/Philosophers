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
- The table is round, wich means philosopher number 1 sits next to philosopher number number_of_philosophers
- Number of philosophers, time it takes for a philosopher to die of starvation,
time it takes a philosopher to eat and time a philosopher spends sleeping are taken as arguments
- There is an optional argument: number of times a philosopher should eat
- The simulation stops when all philosophers have eaten the number of times specified.
If not specified, the simulation stops when a philosopher dies.
```

## :link: **Compilation**
To compile the program you should run `make`.

This rule will generate an executable file named `philo`. To launch the executable you should follow this syntax:

```sh
$ ./philo <n_philo> <time_to_die> <time_to_eat> <time_to_sleep> <OPCIONAL(n_eat)>
```
## 🥇 **Testing**
In order for the simulation to run smoothly, ensuring no philosophers die of starvation, the parameters need to be set properly. As there is only one fork per philosopher and they require two forks to eat, they must take turns eating.

If there is an **even number** of philosophers, odd numbered philosophers and even numbered phisolophers can take turns eating, taking two shifts so that every philosopher has time to eat:
- **Time_to_die** must be equal to or greater than **double the time_to_eat** plus 10 (for tolerance). This ensures that philosophers have enough time to take turns eating before facing starvation.

If there is an **odd number** of philosofers, beacause the first and last philosophers are both odd and share a fork, it takes three shifts so that every philosofer as time to eat:
- **Time_to_die** must be equal to or greater than **triple the time_to_eat** plus 10 (for tolerance). This ensures that philosophers have sufficient time to take turns eating before facing starvation.

Additionally, **Time_to_die** must be equal to or greater than the sum of **time_to_eat** plus **time_to_sleep** plus 10 (for tolerance). This ensures that a philosopher has enough time to eat and sleep before potentially starving.

### Lets test for an even number of philosophers!
With **time_to_die** >= **time_to_eat** * 2 + 10  &  **time_to_die** >= **time_to_eat** + **time_to_sleep** + 10: the philosophers will never starv and the simulation wont stop
```sh
$ ./philo 12 410 200 200
```
With **time_to_die** < **time_to_eat** * 2 + 10: a philosopher will starv
``` 
$ ./philo 12 400 200 200
```
<td><image src="img/notEnoughTimetoeatEven.png"></td>

With **time_to_die** < **time_to_eat** + **time_to_sleep** + 10: a philosopher will starv
```sh
$ ./philo 12 410 200 300
```
<td><image src="img/notEnoughTimetosleepEven.png"></td>

### Lets test for an odd number of philosophers!
With **time_to_die** >= **time_to_eat** * 3 + 10  &  **time_to_die** >= **time_to_eat** + **time_to_sleep** + 10: the philosophers will never starv and the simulation wont stop
```sh
$ ./philo 13 610 200 400
```
With **time_to_die** < **time_to_eat** * 3 + 10: a philosopher will starv
```sh
$ ./philo 13 610 400 200
```
<td><image src="img/notEnoughTimetoeatOdd.png"></td>

With **time_to_die** < **time_to_eat** + **time_to_sleep** + 10: a philosopher will starv
```sh
$ ./philo 13 610 200 500
```
<td><image src="img/notEnoughTimetosleepOdd.png"></td>

With **one philosopher**, there is only one fork: the philosopher will starv
```sh
$ ./philo 1 610 200 200
```
<td><image src="img/onePhilo.png"></td>

### The simulation stops if the number of times a philosopher shoud eat is specified!
```sh
$ ./philo 5 610 200 200 4
```
<td><image src="img/optionalParameter.png"></td>
