//Full arrangement, initial a = b = src char []
void Premutation(char *a, char *b)
{
	if(*b == '\0')
	{
		printf("%s\n", a);
		return;
	}
	for(char *c = b; *c != '\0'; c++)
	{
		char temp = *b;
		*b = *c;
		*c = temp;
		Premutation(a, b+1);
		temp = *b;
		*b = *c;
		*c = temp;
	}
}