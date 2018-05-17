void removeComments()
{
    char code [1024] = {0};
    char output[1024] = {0};
    bool inblock = false;
    bool instr = false;
    while(readline(code))
    {
        j = 0;
        int len = strlen(code);
        while(code[i] != '\0')
        {
            if(!inblock && instr && code[i] == '\"')
                instr = true;
            else if(instr && code[i] == '\"')
                instr = false;
            if(!instr)
            {
                if(!inblock && i+1 < len && code[i] == '/' && code[i+1] == '*')
                {
                    inblock = true;
                    i++;
                }
                else if(inblock && i+1 < len && code[i] == '*' && code[i+1] == '/')
                {
                    inblock = false;
                    i++;
                }
                else if(!inblock && i+1 < len && code[i] == '/' && code[i+1] == '/')
                {
                    break;
                }
            }
            else if(!inblock)
                output[j++] = code[i];
            i++;
        }
        if(!inblock)
            printf("%s", output);
    }
    
}