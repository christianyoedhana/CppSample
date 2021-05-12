This is an implementation of Cormen's greedy algorithm demonstration using the optimal room scheduling problem.
Given a set of activities S, with s[start time, end time), and room availability time [open, close], we want to select as many members of S.
We can safely assume that s1 is scheduled after the room's opening time, and en is scheduled before the room's closing time. 
{It will make the algo more interesting if we add a [open, close] constrain, but the filtering is trivial. All we have to do is filter out S for
(si ei) that is not a proper subset of [open, close]}

The input to this executable is a stream containing the following string lines
s1 e1 s2 e2 s3 e3 ... sn en
this either comes from the standard input stream, or a text stream from a file.
Note that Cormen's algorithm requires a starting fictitious activity that gets ignored on the first run. To simulate this, the implementation
implicitly add a pair default-initialized ( which is nowadays 0, but it will be ignored anyway) sentinel at the beginning of the list.
So the user can launch using command line 
	GreedyScheduling.exe, or 
	GreedyScheduling.exe < input.txt