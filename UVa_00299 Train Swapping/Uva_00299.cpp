#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    int number_of_cases;
    int number_of_trains;
    int train_id;
    int swap_times;
    vector<int> trains;

    cin >> number_of_cases;
    for (int case_no = 0; case_no < number_of_cases; case_no++)
    {
        cin >> number_of_trains;
        trains.clear();

        for (int i = 0; i < number_of_trains; i++)
        {
            cin >> train_id;
            trains.push_back(train_id);
        }

        swap_times = 0;
        for (int i = 0; i < number_of_trains; i++)
        {
            for (int j = i; j < number_of_trains; j++)
            {
                if (trains[i] > trains[j])
                {
                    swap(trains[i], trains[j]);
                    swap_times++;
                }
            }
        }

        cout << "Optimal train swapping takes " << swap_times << " swaps." << endl;
    }
}