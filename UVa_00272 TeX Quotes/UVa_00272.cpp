#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


int main()
{
	bool isFirstQuotes;
	string input_line;
	string output_line;
	vector<char> char_out;


	isFirstQuotes = true;
	while (getline(cin, input_line))
	{
		char_out.clear();
		for (char char_in : input_line)
		{
			if (char_in == '"')
			{
				if (isFirstQuotes)
				{
					char_out.push_back('`');
					char_out.push_back('`');
				}
				else
				{
					char_out.push_back('\'');
					char_out.push_back('\'');
				}

				isFirstQuotes = !isFirstQuotes;
			}
			else
			{
				char_out.push_back(char_in);
			}
		}
		char_out.push_back('\0');
		cout << char_out.data() << endl;
	}
}