void getnext(char *src, int *next)
{
	next[0] = -1;
	int i = 0;
	int j = -1;
	while(i < strlen(src))
	{
		if(j == -1 || src[i] == src[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}
int kmp(char *src, char * dst, int *next)
{
	int i = 0, j = 0;
	while(i < strlen(src) && j < strlen(dst))
	{
		if( j == -1 || src[i] == dst[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if(j == strlen(dst))
		return i - j;
	else
		return -1;
}