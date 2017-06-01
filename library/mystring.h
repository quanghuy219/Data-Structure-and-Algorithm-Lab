char* convertName(char *s) {
	if(s == NULL) return NULL;

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
	if (str == NULL) return;
	
	if (strlen(str) == 0) return;
	
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


char *toLower(char *s){
	if(s == NULL) return NULL;

	char *result = (char*)malloc( MAX * sizeof(char));
	strcpy(result,s);
	Validate(result);
	for (int i = 0; i < strlen(result); i++)
	{
		result[i] = tolower(result[i]);
	}
	return result;
}


char* stdinRead(){
	char *result = (char*)malloc(sizeof(char) * MAX);
	fgets(result,MAX,stdin);
	Validate(result);
	return result;
}


void swapStr(char* str1, char *str2){
	char tmp[MAX];

	if(str1 == NULL || str2 == NULL) {
		printf("NULL value\n");
		return;
	}
		
	strcpy(tmp,str1);
	strcpy(str1, str2);
	strcpy(str2,tmp);
}


void sortStr(char list[][MAX], int num){
	if(list == NULL) return;

	for (int i = 0; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			if (strcmp(list[i], list[j] ) > 0)
			{
				swapStr(list[i],list[j]);
			}
		}
	}
} 
