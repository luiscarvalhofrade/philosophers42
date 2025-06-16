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

	#1 philo gets forks #1 and #2, all other philos start to count the time?
	#1 start to eats, all other wait 200 miliseconds