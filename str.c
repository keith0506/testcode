char *substr(char *string, int begin, int end)
{
	char *result = NULL;
	int resultCount = 0;

	if (NULL == string || begin < 0 || end  > (strlen(string) - 1) || (end - begin) < 0)
	{
		return NULL;
	}

	resultCount = end - begin + 1;
	result = (char *)malloc(sizeof(char) * resultCount + 1);

	if(NULL == result)
	{
		return NULL;
	}

	strncpy(result, string + begin, resultCount);
	result[resultCount] = '\0';

	return result;
}