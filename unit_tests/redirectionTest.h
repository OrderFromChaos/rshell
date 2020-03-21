#ifndef _REDIRECT_TESTS
#define _REDIRECT_TESTS

#include "gtest/gtest.h"
#include "../header/rshellclasses.h"
#include "../header/rshelldefinition.h"
#include <stack>
#include <queue>
#include "../header/shuntingExecute.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

TEST (redirectTest, Appending)
{
	RShell shellobj = RShell();
	string file = "text.txt";

	//Create inputs. 
	Token* command = new Subcommand({"echo cc bc"});
	Token* command2 = new Subcommand({file});
	Token* check = new AppendOutToken({">>"});

	ifstream in;
	in.open(file);
	string word;

	string line;
	while(getline(in, line))
	{
		word.append(line);
		word.append("\n");
	}
	in.close();

	word.append("cc bc\n");

	cout << word << endl;

	//Store inputs into deque
	deque<Token*> V;
	V.push_back(command);
	V.push_back(command2);
	V.push_back(check);


	//Run the shell
	shellobj.commandDeque = V;
	shellobj.shuntingExecute(V);

	ifstream in2;
	in2.open(file);
	string word2;

	string line2;
	while(getline(in2,line2))
	{
		word2.append(line2);
		word2.append("\n");	
	}
	in2.close();	

	EXPECT_EQ(word, word2);
}

TEST (redirectTest, Wipe)
{
	RShell shell = RShell();
	string file = "input.txt";


	//Create inputs. 
	Token* command = new Subcommand({"input.txt"});
	Token* response = new Subcommand({"echo a"});
	Token* check = new EmptyOutToken({">"});

	//Store inputs into deque
	deque<Token*> V;
	V.push_back(response);
	V.push_back(command);
	V.push_back(check);

	//Run the shell
	shell.commandDeque = V;
	shell.shuntingExecute(V);
	
	//Open the file 
	ifstream in;
	in.open(file);
	
	//Check the first line of the file. 
	string firstLine;
	if (in.is_open())
	{
		getline(in,firstLine);
	}
	in.close();
	
	EXPECT_EQ(firstLine,"a");

	
}

TEST(redirectTest, Pipe)
{
	RShell shell = RShell();
	string file = "newInput.txt";
		
	//Create inputs. 
	Token* echo = new Subcommand({"echo b > newInput.txt | tr a-z A-Z"});
	Token* input = new Subcommand({"newInput.txt"}); 
	Token* check = new EmptyOutToken({">"});


	//Store inputs to deque
	deque<Token*> V = {echo, input, check};

	//Run the shell
	shell.commandDeque = V;
	shell.shuntingExecute(V);

	
	//Open the file 
	ifstream in;
	in.open(file);
	
	//Check the first line of the file. 
	string firstLine;
	if (in.is_open())
	{
		getline(in,firstLine);
	}
	in.close();	

	
	EXPECT_EQ(firstLine,"b");

	
}


#endif
