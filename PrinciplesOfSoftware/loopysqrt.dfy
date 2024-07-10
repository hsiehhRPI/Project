function fib(n: int) : int
	decreases n
{
	if(n < 2) then n else fib(n-2) + fib(n-1)
}

method computeFib(n: int) returns (f: int)
	requires 0 <= n
	ensures f == fib(n)
{
	print "computeFib(", n, ")'s trace:", "\n";
	var i:= 0;
	var k := 1;
	f := 0;
	var t := 0;
	while (i < n)
		invariant 0 <= i <= n
		invariant k == fib(i+1)
		invariant f == fib(i)
	{
		print "Before iteration starts \t\tf = \t", f, "; \tk = \t", k, "; \ti = \t", i, "\n";
		t, f, k := f, k, f + k;
		i := i + 1;
		print "After iteration ends \t\t\tf = \t", f, "; \tk = \t", k, "; \ti = \t", i, "\n";
	}
	print "**********************************\n";
	return f;
}

method Main() {
	var tests := [[0, 0], [1, 1], [2, 1], [5, 5], [8, 21]];
	var c:int;
	var i := 0;
	while i < |tests|
	invariant i <= |tests|
	{
		c := computeFib(tests[i][0]);
		print "computeFib(", tests[i][0], ") = ", c, ", expected ", tests[i][1], "\n\n";
		assert c == tests[i][1];
		i := i + 1;
	}
}
