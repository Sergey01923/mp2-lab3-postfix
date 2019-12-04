#include "postfix.h"
#include "stack.h"

string TPostfix::ToPostfix()
{
	isCorrectInfix();
	postfix.clear();
	TStack <string> stack;
	string word;
	string str = Infix2Space();
	for (istringstream is(str); is >> word;)
	{
		if (priority[word] != 0)
		{
			if (stack.isEmpty())
				stack.push(word);
			else
			{
				if (word == "(")
					stack.push(word);
				else
				{
					if (word == ")")
					{
						while (stack.gettop() != "(")
							postfix += (stack.pop() + ' ');
						stack.pop();
					}
					else
					{
						while (!stack.isEmpty())
						{
							if ((priority[word] >= priority[stack.gettop()]) && (stack.gettop() != "("))
							{
								postfix += (stack.pop() + ' ');
							}
							else break;
						}
						stack.push(word);
					}
				}
			}
		}
		else
		{
			postfix += (word + ' ');
		}
	}
	while (!stack.isEmpty())
	{
		postfix += (stack.pop() + ' ');

	}
	return postfix;
}
string TPostfix::Infix2Space()
{
	string word;
	string d;
	string TInfix;
	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] == ' ')
		{
			if (word.length() != 0)
				TInfix += (word += ' ');
			else
				TInfix += (word);
			word.clear();
		}
		else
		{
			d = infix[i];
			if (((infix[i] >= 40) && (infix[i] <= 47) && (infix[i] != 46) && (infix[i] != 44)))
			{
				if (infix[i] == 45)
				{
					if (i == 0)
					{
						d = "0";
						infix.insert(0, "0");
					}
					else {
						int j = i-1;
						while (infix[j] == ' ')
							j--;
						if (infix[j] == 40)
						{
							d = "0";
							infix.insert(i, "0");
						}
					}
				}
				if (word.length() == 0)
				{
					
					if (i == (infix.length() - 1))
						TInfix += (d);
					else
						TInfix += (d + ' ');
				}
				else
				{
					TInfix += (word + ' ');
					word.clear();
					if (i == (infix.length() - 1))
						TInfix += (d);
					else
						TInfix += (d + ' ');
				}
			}
			else
			{
				word += infix[i];
			}
			if (i == infix.size() - 1)
			{
				TInfix += word;
				word.clear();
			}
		}
	}
	return TInfix;
}

double TPostfix::Calculate()
{
	TStack <double> Calculus;
	vector <string> Alt;
	map <string, double> Values;
	string word;
	for (stringstream is(postfix); is >> word;)
	{
		if (!(isNumber(word) || priority[word] != 0))
		{
			vector <string>::iterator it = Alt.begin();
			while (it != Alt.end())
			{
				
				if (*it == word)
					break;
				it++;
			}
			if (it == Alt.end() || Alt.empty())
				Alt.push_back(word);
		}
	}
	if (Alt.size()!=0)
	cout << "В выражении имеется " << Alt.size() << " переменных (вот они справа налево) : " << endl;
	for (int i = 0; i < Alt.size(); i++)
	{
		if (i != Alt.size() - 1)
			cout << Alt[i] << ",";
		else
			cout << Alt[i] << endl;
	}
	if (Alt.size() != 0)
	cout << "Введите переменные:" << endl;
	for (int i = 0; i < Alt.size(); i++)
	{
		double Input;
		cout << Alt[i] << " = ";
		cin >> Input;
		Values.insert(pair<string, double>(Alt[i], Input));
	}
	for (stringstream is(postfix); is >> word;)
	{
		if (priority[word] == 0)
		{
			if (isNumber(word))
			{
				stringstream tmp(word);
				double set;
				tmp >> set;
				Calculus.push(set);

			}
			else
				Calculus.push(Values[word]);
		}
		else
		{
			switch (operations[word])
			{
			case 1:
			{
				Calculus.push(Calculus.pop() + Calculus.pop());
				break;
			}
			case 2:
			{
				double b = Calculus.pop();
				double a = Calculus.pop();
				Calculus.push(a - b);
				break;
			}
			case 3:
			{
				Calculus.push(Calculus.pop() * Calculus.pop());
				break;
			}
			case 4:
			{
				double b = Calculus.pop();
				double a = Calculus.pop();
				Calculus.push(a / b);
				break;
			}
			case 5:
			{
				Calculus.push(sin(Calculus.pop()));
				break;
			}
			case 6:
			{
				Calculus.push(cos(Calculus.pop()));
				break;
			}
			case 7:
			{
				Calculus.push(log(Calculus.pop()));
				break;
			}
			}
		}
	}
	return Calculus.pop();

}
bool TPostfix::isNumber(const string &a)
{
	int check = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (i == 0)
			if (!((a[i] >= 48) && (a[i] <= 57)))
				return 0;
			else {}
		else {
			if (!((a[i] >= 48) && (a[i] <= 57) || (a[i] == 46)))
				return 0;
			else
			{
				if (a[i] == 46)
					check += 1;
			}
		}
	}
	if (check > 1)
		return 0;
	return 1;
}
bool TPostfix::isAlt(const string &a)
{
	for (int i = 0; i < a.length(); i++)
	{
		if (i == 0)
			if (!((a[i] >= 65 && a[i] <= 90) || (a[i] >= 97 && a[i] <= 122)))
				return 0;
			else {}
		else
		{
			if (!((a[i] >= 65 && a[i] <= 90) || (a[i] >= 97 && a[i] <= 122) || (a[i] >= 48) && a[i] <= 57))
				return 0;
		}
	}
	return 1;
}
void TPostfix::isCorrectInfix()
{
	string str = Infix2Space();
	int skb=0;
	string LastWord, word;
	int check = 0;
	for (stringstream is(str); is >> word;)
	{
		if (check == 0)
		{
			if (priority[word] != 0) {
				if (priority[word] >= 3 || priority[word] == -1)
					throw 1;
				else
					if (priority[word] == 1)
						skb++;
			}

			else {
				if (!(isNumber(word) || isAlt(word)))
					throw 1;
			}
			check++;
		}
		else {
			if (priority[word] != 0)
			{
				if (priority[word] == 1)
					skb++;
				if (priority[word] == -1)
					skb--;
				if (skb < 0)
					throw 1;
				if (priority[LastWord] != 0)
				{
					if (priority[LastWord] == 1)
						if (!(priority[word] == 1 || priority[word] == 2))
							throw 1;
					if (priority[LastWord] == -1)
						if (!(priority[word] == 3 || priority[word] == 4 || priority[word] == -1))
							throw 1;

					if (priority[LastWord] >= 3)
						if (!(priority[word] == 1 || priority[word] == 2))
							throw 1;
					if (priority[LastWord] == 2)
						if (!(priority[word] == 1))
							throw 1;

				}
				else
				{

					if (!(priority[word] >= 3 || priority[word] == -1))
						throw 1;


				}
			}
			else
			{
				if (!(isNumber(word) || isAlt(word)))
					throw 1;
				else
				{

					if (priority[LastWord] == 0)
						throw 1;
					else
					{
						if (priority[LastWord] == -1 || priority[LastWord] == 2)
							throw 1;
					}
				}
			}
		}
		LastWord = word;
	}
	if (skb!= 0)
		throw 1;
}
