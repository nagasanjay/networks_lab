#include <stdio.h>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "typo.h"

using namespace std;

int main(){
	FILE *fp;
	FILE *fp1;
	vector<string> files;
	
	char buffer[4096];
	bzero(buffer,sizeof(buffer));
	
	fp1 = popen("ls programs", "r");
	while(fscanf(fp1, "%s", buffer) != EOF){
		//cout << buffer << " ";
		files.push_back(buffer);
	}
	
	fclose(fp1);
	
	cout << "No. of programs compiled : " << files.size() << endl;
	vector<string> tokens;

for(int j = 0; j < files.size(); j++){
	files[j].insert(0,"gcc programs/");
	files[j].append(" 2>&1");
	
	//cout << files[j];
	
	fp = popen(files[j].c_str(), "r");
	
	while(fscanf(fp, "%s", buffer)!=EOF)
		//fprintf(fp2, "%s\n",buffer);
		tokens.push_back(buffer);
		
	//while(fgets(buffer, sizeof(buffer), fp))
	//	fprintf(fp2, "%s", buffer);
	//for(string i : tokens)
	//	cout << i << endl;
	
	fclose(fp);	
}
	for(int i = 0; i < tokens.size(); i++){
		if(tokens[i] == "implicit" && tokens[i+1] == "declaration" && tokens[i+2] == "of" && tokens[i+3] == "function")
			typo[UNDECLARED_FUNCTION]++;
		else if(tokens[i] == "expected" && (tokens[i+1] == "‘;’"||tokens[i+3] == "‘;’,") )
			typo[MISSED_SEMICOLON]++;
		else if(tokens[i] == "expected" && tokens[i+1] == "‘(’" )
			typo[MISSED_OPENING_PARANTHESIS]++;
		else if(tokens[i] == "expected" && tokens[i+1] == "‘)’" )
			typo[MISSED_CLOSING_PRANATHESIS]++;
		else if(tokens[i] == "expected" && (tokens[i+1] == "‘{’"  ||  tokens[i+3] == "‘(’"))
			typo[MISSED_OPEN_CURLY_BRACKET]++;
		else if((tokens[i] == "expected" && tokens[i+1] == "‘}’" ) || (tokens[i] == "end" && tokens[i+1] == "of" && tokens[i+2] == "input"))
			typo[MISSED_CLOSE_CURLY_BRACKET]++;
		else if(tokens[i] == "undeclared" && tokens[i+1] == "(first")
			typo[UNDECLARED_VARIABLE]++;
	}
	
	FILE *fp2;
	fp2 = fopen("errors.csv","w");
	
	for(int i = 0; i < 7; i++){
		if(typo[i])
			cout << typo_name[i] << " : " << typo[i] << endl;
		fprintf(fp2, "%s", typo_name[i]);
		fprintf(fp2, "%c", ',');
		fprintf(fp2, "%d", typo[i]);
		fprintf(fp2, "\n");
	}
	fclose(fp2);
				
	return 0;
}
