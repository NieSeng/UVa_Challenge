#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 用來儲存已經計算過的 3n+1 序列長度
unordered_map <int, int> seqLenMap;

static void ParseInput(string inputLine, int& value1, int& value2)
{
    int v1, v2;
    string strVal;
    vector<string> strValues;

    // 將 readline 轉換為 string stream
    stringstream strStream(inputLine);

    // 以空格為分割讀取資料
    while (getline(strStream, strVal, ' '))
    {
        strValues.push_back(strVal);
    }

    // 讀取 strValues 裡的資料，轉換成 int
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

	// 1 的 seqLen 為 1
    if (value == 1)
    {
		seqLen = 1;
    }
    // 如果已經計算過，直接回傳
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

    // 讀取 console 輸入的內容 (cin >> readline)
    while (getline(cin, inputLine))
	{
		// 處理 inputLine, 讀取 value1, value2 的值
		ParseInput(inputLine, value1, value2);
		// 計算最長的 3n+1 序列
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
