/*
Daniel Meyer
CSE 330
*/

#include <vector>
#include <iostream>

using namespace std;

void print(vector<int> v);
void selection_sort(vector <int> &v);

int main()
{
    int n;

    cout << "Enter vector size: ";

    cin >> n;
    vector<int> v(n);

    srand(time(0));

    for(int i = 0; i < n; i++)
    {
        v[i] = rand() % 1000000;
    }

    cout << "---------- Pre-Sort ----------" << endl;
    print(v);
    selection_sort(v);
    cout << endl;
    cout << "---------- Post-Sort ----------" << endl;
    print(v);

    return 0;
}

void print(vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
}


void selection_sort(vector<int> &v)
{
    int n = v.size();
    for(int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(v[i] > v[j])
            {
                swap(v[i], v[j]);
            }
        }
    }
}
