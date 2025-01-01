#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 用來儲存已經計算過的 3n+1 序列長度
unordered_map <long long int, long long int> seqLenMap;


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
	long long int seqLen;
	long long int seqLenPart1;
	long long int seqLenPart2;
    unordered_map <long long int, long long int> seqLenPart2Map;

   
    seqLenPart1 = 0;
	seqLenPart2 = 0;
    while (value >= 1)
    {
        if (seqLenMap[value] != 0)
        {
			// 已計算過的 value 的 seqLen 直接取用, 命名為 seqLenPart1
			seqLenPart1 = seqLenMap[value];
			break;
		}
		else
		{
			// 未計算過的 value 的 seqLen, 會分為 seqLenPart1 與 seqLenPart2 (item.second)
			// 每次的計算步驟都會把 seqLenPart2 加 1
            seqLenPart2++;
            seqLenPart2Map[value] = 0;
            for (auto& item : seqLenPart2Map)
            {
                item.second++;
            }

			// 計算下一次的 value
            if (value % 2 == 0)
            {
                value = value / 2;
            }
            else
            {
                value = 3 * value + 1;
            }
        }
    }

	//  把本次新計算的 value 的 seqLen 加到 seqLenMap 裡, 供下次使用
    for (auto& item : seqLenPart2Map)
    {
		seqLenMap[item.first] = seqLenPart1 + item.second;
    }
	seqLen = seqLenPart1 + seqLenPart2;

	return seqLen;
}

static int Get3nAdd1SeqLen_v2(long long int value)
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

static int Get3nAdd1SeqLen_v1(long long int value)
{
    int seqLen;
    
	seqLen = 1;
    while (value > 1)
    {
        // value is even
		if (value % 2 == 0)
	    {
	    	value = value / 2;
    	}
		// value is odd
		else
		{
			value = 3 * value + 1;
		}
		seqLen++; 
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

	// 設定 seqLenMap[1] = 1
	seqLenMap[1] = 1;

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
