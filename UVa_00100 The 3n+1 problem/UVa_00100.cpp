#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// �Ψ��x�s�w�g�p��L�� 3n+1 �ǦC����
unordered_map <int, int> seqLenMap;

static void ParseInput(string inputLine, int& value1, int& value2)
{
    int v1, v2;
    string strVal;
    vector<string> strValues;

    // �N readline �ഫ�� string stream
    stringstream strStream(inputLine);

    // �H�Ů欰����Ū�����
    while (getline(strStream, strVal, ' '))
    {
        strValues.push_back(strVal);
    }

    // Ū�� strValues �̪���ơA�ഫ�� int
    v1 = stoi(strValues[0]);
    v2 = stoi(strValues[1]);

    if (v1 <= v2)
    {
        value1 = v1;
        value2 = v2;
    }
    else
    {
        value1 = v2;
        value2 = v1;
    }
}

static int Get3nAdd1SeqLen(long long int value)
{
	int seqLen;

	// 1 �� seqLen �� 1
    if (value == 1)
    {
		seqLen = 1;
    }
    // �p�G�w�g�p��L�A�����^��
    else if (seqLenMap[value] != 0)
    {
		seqLen = seqLenMap[value];
    }
    else
    {
		seqLen = 1;
        if (value % 2 == 0)
        {
			value = value / 2;
        }
        else
        {
			value = 3 * value + 1;
        }
		seqLen += Get3nAdd1SeqLen(value);
    }

	return seqLen;
}

int main()
{
    int value1, value2;
    int seqLen;
    int largestSeqLen;
    string inputLine;
    vector<int> seq;

    // Ū�� console ��J�����e (cin >> readline)
    while (getline(cin, inputLine))
	{
		// �B�z inputLine, Ū�� value1, value2 ����
		ParseInput(inputLine, value1, value2);
		// �p��̪��� 3n+1 �ǦC
		largestSeqLen = 0;
		for (int i = value1; i <= value2;i++)
		{
			seqLen = Get3nAdd1SeqLen(i);
			if (seqLen > largestSeqLen)
			{
				largestSeqLen = seqLen;
			}
		}
		cout << inputLine << " " << largestSeqLen << endl;
    }

    return 0;
}
