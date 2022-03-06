//============================================================================
// Name        : PaserBool.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
#include<fstream>  
#include<string> 

using namespace std;

//Gets the operation result of two expressions
char operation(stack<char> *ops, stack<char> *exps)
{
	char tempC = exps->top();
	if(!(ops->empty()))
	{
		bool t = false;
		bool f = false;
		
		while(!(exps->empty()))
		{
			char exp = exps->top();
			exps->pop();
			if(exp == 'T')
			{
				t = true;
	    	}
			else
			{
				f = true;
			}
		}
		
		char op = ops->top();
		ops->pop();
		
		if(op == '&')
		{
			tempC = f ? 'F' : 'T';
		}else if( op == '|' )
		{
			tempC = t ? 'T' : 'F';
		}
	}
	else
	{
		exps->pop();
	}
	return tempC;
}

bool parseExpr(string expression)
{
	stack<char> ops, exps;
	bool flg = false;

	for(char tempChar : expression)
	{
		if( ('&' == tempChar) || ('|' == tempChar) )
		{
			ops.push(tempChar);
		}
		else if (('T' == tempChar) || ('F' == tempChar) || ('(' == tempChar))
		{
			exps.push(tempChar);
			if( ('(' == tempChar) || (flg == true) )
			{
				flg = true;
				continue;
			}
			exps.push(operation(&ops, &exps));
		}
		else if(')' == tempChar)
		{
			bool t = false;
			bool f = false;
			
			while( exps.top() != '(' )
			{
				char exp = exps.top();
				exps.pop();
				if(exp == 'T')
				{
					t = true;
            	}
				else
				{
					f = true;
				}
			}
			exps.pop();//pop the '('
			flg = false;

			// Operation expression in "()"
 			char op = ops.top();
			ops.pop();
			
			if(op == '&')
			{
				exps.push(f ? 'F' : 'T');
			}else if( op == '|' )
			{
				exps.push(t ? 'T' : 'F');
			}
		}
	}
	exps.push(operation(&ops, &exps));

	return exps.top() == 'T';
}

void printExpression(string line)
{
	cout << "Test input: " <<line << endl;
	cout << "The S-expression : ";
	for(char tempChar : line)
	{
		if('T' == tempChar)
		{
			cout << " true";
		}
		else if('F' == tempChar)
		{
			cout << " false";
		}
		else if('&' == tempChar)
		{
			cout << " and";
		}
		else if('|' == tempChar)
		{
			cout << " or";
		}
		else if('(' == tempChar)
		{
			cout << " (";
		}
		else if(')' == tempChar)
		{
			cout << " )";
		}
	}
	cout << "" << endl;
}

int main(int argc, char* argv[]) {
	
	string strPath = argv[1];
	ifstream inFile(strPath);
    string filename;  
    string line;
    
	if (NULL == argv[1])
	{
		printf("Please drag a test file into the exe file.\r\n");
		system("pause");
		return 1;
	}
    
    if(inFile)
    {
    	while(getline(inFile, line))
    	{
    		printExpression(line);
    		
			bool ret = parseExpr(line);
			if(ret)
			{
				cout << "The result of expression is : T" << endl;
				cout << "" << endl;
			}
			else
			{
				cout << "The result of expression is : F" << endl;
				cout << "" << endl;
			}
    	}
    }
    system("pause");
	return 0;
}