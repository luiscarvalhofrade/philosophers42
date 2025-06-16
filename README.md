# philosophers42

	first, i need to imagine how to make the dyanmic between philosophers, each one
	is the first when he gets the first and the second fork and so on. Second, how
	to deal with other philos, if anyother is set whatsoever.

	1. set each philosopher: unique number

	2. set forks: unique number

	here the nth philo gets the nth and the (n + 1)th fork, the (n + 1)th philo, gets
	tje (n + 1)th plus the (n + 2)th forks and so on.

	if we have t philos:

	#1 philo -> #1 and #2 forks
	#2 philo -> #2 and #3 forks
	.
	.
	.
	#n philo -> #n and #(n+1) forks
	.
	.
	.
	#(t-1) philo -> #(t-1) and #t forks
	#t philo -> #t and #1 forks

## Dynamic

the first philo gets his forks, automatically the second one is locked, and the third, if we have the a even number of forks, also is allowed to get the third 
and the fourth forks and so on and on.

so here we found a new point: if the total number of philos is even, half of philos eat and the other half dont and if we have a odd number, we have (half - 1)
philos eating and the other (half + 1)philos doing other things.

special case: 1 philo.

Imagining that a philo needs 100 miliseconds to eat, 100 miliseconds to sleep and
100 miliseconds to die, what happens when we have a even and odd number?

other point, we dont have specified the amount of time of thinking, so it is the difference among eating, sleeping and the next time eating, or if the elapsed time of sleeping + thinking is higher of the amount to die.

## the table

