#include <iostream>
using namespace std;

static int Get3nAdd1SeqLen(long long int n)
{
    int seqLen;

    seqLen = 1;
    while (n > 1)
    {
        // value is even
        if (n % 2 == 0)
        {
            n = n / 2;
        }
        // value is odd
        else
        {
            n = 3 * n + 1;
        }
        seqLen++;
    }

    return seqLen;
}

int main()
{
    int v1, v2;
    int min_value, max_value;
    int sql_len;
    int max_seq_len;

    // 讀取 console 輸入的內容 (v1, v2)
    while (cin >> v1 >> v2)
    {
        // 計算最長的 3n+1 序列
        max_seq_len = 0;

        if (v1 > v2)
        {
            min_value = v2;
            max_value = v1;
        }
        else
        {
            min_value = v1;
            max_value = v2;
        }

        for (int i = min_value; i <= max_value; i++)
        {
            sql_len = Get3nAdd1SeqLen(i);
            if (sql_len > max_seq_len)
            {
                max_seq_len = sql_len;
            }
        }
        cout << v1 << " " << v2 << " " << max_seq_len << endl;
    }

    return 0;
}
