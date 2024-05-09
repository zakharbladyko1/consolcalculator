#include <iostream>
#include <cstring>
using namespace std;

const int LEN = 80;
const int MAX = 40;

class Stack2
{
private:
	char st[MAX];
	int top;
public:
	Stack2()
	{
		top = 0;
	}
	void push(char var)
	{
		st[++top] = var;
	}
	char pop()
	{
		return st[top--];
	}
	int gettop()
	{
		return top;
	}
};

class express
{
private:
	Stack2 s;
	char* pStr;
	int len;
public:
	express(char* ptr)
	{
		pStr = ptr;
		len = strlen(pStr);
	}
	void parse();
	int solve();
};

void express::parse()
{
	char ch;
	char lastval;
	char lasttop;

	for (int j = 0; j < len; j++)
	{
		ch = pStr[j];

		if (ch >= '0' && ch <= '9')
			s.push(ch - '0');
		else
			if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
			{
				if (s.gettop() == 1)
					s.push(ch);
				else
				{
					lastval = s.pop();
					lasttop = s.pop();

					if ((ch == '*' || ch == '/') && (lasttop == '+' || lasttop == '-'))
					{
						s.push(lasttop);
						s.push(lastval);
					}
					else
					{
						switch (lasttop)
						{
						case '+': s.push(s.pop() + lastval); break;
						case '-': s.push(s.pop() - lastval); break;
						case '*': s.push(s.pop() * lastval); break;
						case '/': s.push(s.pop() / lastval); break;

						default: cout << "\nUnknown operator"; exit(1);
						}
					}
					s.push(ch);
				}
			}
			else
			{
				cout << "\nUnknown symbol";
				exit(1);
			}
	}
}

int express::solve()
{
	char lastval;

	while (s.gettop() > 1)
	{
		lastval = s.pop();
		switch (s.pop())
		{
		case '+': s.push(s.pop() + lastval); break;
		case '-': s.push(s.pop() - lastval); break;
		case '*': s.push(s.pop() * lastval); break;
		case '/': s.push(s.pop() / lastval); break;

		default: cout << "\nUnknown operator"; exit(1);
		}
	}
	return int(s.pop());
}

int main()
{
	char ans;
	char string2[LEN];

	cout << "Enter the equation";

	do
	{
		cout << "\nEnter : ";
		cin >> string2;

		express* eptr = new express(string2);
		eptr->parse();

		cout << "\nResult : " << eptr->solve();

		delete eptr;

		cout << "\nAgain? (y/n): ";
		cin >> ans;

	} while (ans == 'y');


	return 0;
}