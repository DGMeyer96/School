/*****************************************************************
*Daniel Meyer
*selection_sort.cpp
*10/2/17
*Lab 2: Time Complexity
*Implement a selection sort to test that the execution time is O(n^2)
*CSE 330
*Fall 2017
*****************************************************************/

#include <vector>
#include <iostream>

using namespace std;

void print(vector<int> v);
void selection_sort(vector <int> &v);

int main()
{
    int n;

    cin >> n;
    vector<int> v(n);

    srand(time(0));

    for(int i = 0; i < n; i++) {
        v[i] = rand() % 1000000;
    }

    cout << "---------- Pre- Selection Sort ----------" << endl;
    print(v);
    selection_sort(v);
    cout << endl;
    cout << "---------- Post- Selection Sort ----------" << endl;
    print(v);

    return 0;
}

void print(vector<int> v)
{
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
}


void selection_sort(vector<int> &v)
{
    for(int i = 0; i < v.size()-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(v[i] > v[j]) {
                swap(v[i], v[j]);
            }
        }
    }
}
