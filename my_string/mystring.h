char* convertName(char *s) {
	char *token;
	char s1[MAX];
	strcpy(s1,s);
	token = strtok(s1," ");
	char tmp[MAX][MAX];
	int count = 0;
	char *result = (char*)malloc(sizeof(char) * MAX);

	while(token != NULL) {
		strcpy(tmp[count++], token);
		token = strtok(NULL," ");
	}
	for (int i = count-1; i >= 0; i--)
	{
		strcat(result,tmp[i]);
		strcat(result," ");
	}

	while (!isalpha(result[strlen(result) - 1]))
	{
		result[strlen(result) - 1] = '\0';
	}
	return result;
}


void Validate(char *str){
	while(!isalpha(str[0])){
		strcpy(str, str+1);
	}

	while(!isalpha(str[strlen(str)-1])) {
		str[strlen(str)-1] = '\0';
	}

	for (int i = 0; i < strlen(str); i++)
	{
		while( isspace(str[i])  && isspace(str[i+1]) ){
			strcpy(str+i,str+(i+1));
		}
	}
}