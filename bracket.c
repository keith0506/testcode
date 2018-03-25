void Bracket(char *str, int open, int close, int n)
{
	if(close == 0)
	{
		printf("%s ", str);
		return;
	}
	if(open == close)
	{
		str[n-close-open] = '(';
		Bracket(str, open - 1, close, n);
	}
	else
	{
		if(open > 0)
		{
			str[n-close-open] = '(';
			Bracket(str, open - 1, close, n);
		}
		if(close > 0)
		{
			str[n-close-open] = ')';
			Bracket(str, open, close - 1, n);
		}		
	}
}