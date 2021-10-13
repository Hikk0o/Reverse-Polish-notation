#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/*	.top() верхний элемент
	.empty() пуст ли
	.push() вставить в стек
	.pop() удалить верхний	*/

			/*-----------------*
			*		Пр 1	   *
			*------------------*/

const string priority_1 = {'(', ')'};
const string priority_2 = {'-', '+'};
const string priority_3 = {'*', '/'};
stack <int> steck;

int getPriority(char sym)
{
	int priority = 0;
	for (int a = 0; a < 2; a++)
	{
		if (sym == priority_1[a])
		{
			priority = 1;
		} else if (sym == priority_2[a])
		{
			priority = 2;
		} else if (sym == priority_3[a])
		{
			priority = 3;
		}
	}
	return priority;
}

void operation(char sym)
{
	int x = steck.top();
	steck.pop();
	int y = steck.top();
	steck.pop();
	int z;
	if (sym == '*') {
		z = y * x;
	}
	else if (sym == '/') {
		z = y / x;
	}
	else if (sym == '+') {
		z = y + x;
	}
	else if (sym == '-') {
		z = y - x;
		
	}
	steck.push(z);
};

int main()
{
	setlocale(LC_ALL, "");
	//const string str = "(4+6)*2-10/2";
	const string str = "5*2+4*(12-10)";
	//const string str = "2+(4-3)*5";
	vector <string> outStr;
	const int counter = str.length();

	cout << "\t" << str << endl << endl;
	for (int a = 0; a < counter; a++)
	{
		/*cout << "Обработка " << str[a] << endl;*/
		if (isdigit(str[a]))
		{
			string number;
			number += str[a];
			while (isdigit(str[a + 1])) {
				a++;
				number += str[a];
			}			
			outStr.push_back(number);
		}
		else if (str[a] == '(')
		{
			steck.push(str[a]);
		}
		else if (str[a] == ')')
		{
			while (steck.top() != '(')
			{
				string symbol;
				symbol += steck.top();
				outStr.push_back(symbol);
				steck.pop();
			}
			steck.pop();
		}
		else if (getPriority(str[a]))
		{
			if (!steck.empty())
			{
				if (getPriority(str[a]) > getPriority(steck.top()))
				{
					steck.push(str[a]);
				}
				else
				{
					while (getPriority(str[a]) <= getPriority(steck.top()))
					{
						string symbol;
						symbol += steck.top();
						outStr.push_back(symbol);
						steck.pop();
						if (steck.size() == 0) break;
					}
					steck.push(str[a]);
				}
			}
			else
			{
				steck.push(str[a]);
			}
		}
		
	}
	if (!steck.empty())
	{
		for (int a = 0; a < steck.size()+1; a++)
		{
			string symbol;
			symbol += steck.top();
			outStr.push_back(symbol);
			steck.pop();
		}
	}
	cout << "\t";
	for (int a = 0; a < outStr.size(); a++)
	{
		cout << outStr[a] << " ";
	}
	cout << endl;



			/*-----------------*
			*		Пр 2	   *
			*------------------*/

	//const string OPZ = "4 6 + 2 * 10 2 / -";
	const string OPZ = "5 2 * 4 12 10 - * +";
	//const string OPZ = "2 4 3 - 5 * +";


	for (int a = 0; a < OPZ.size(); a++)
	{
		if (isdigit(OPZ[a])) {
			string number;
			number += OPZ[a];
			while (isdigit(OPZ[a + 1])) {
				a++;
				number += OPZ[a];
			}
			int num = atoi(number.c_str());
			steck.push(num);
		}
		else if (OPZ[a] == '*' || OPZ[a] == '/' || OPZ[a] == '+' || OPZ[a] == '-') {
			operation(OPZ[a]);
		}
	}
	cout << endl << "Result: " << steck.top();
}
