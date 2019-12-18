/*****************************************************************
*Daniel Meyer
*bubble_sort.cpp
*10/2/17
*Lab 2: Time Complexity
*Implement a bubble sort to test that the execution time is O(n^2)
*CSE 330
*Fall 2017
*****************************************************************/

#include <vector>
#include <iostream>

using namespace std;

void print(vector<int> v);
void bubble_sort(vector <int> &v);

int main()
{
    int n;

    cin >> n;
    vector<int> v(n);

    srand(time(0));

    for(int i = 0; i < n; i++) {
        v[i] = rand() % 1000000;
    }

    cout << "---------- Pre- Bubble Sort ----------" << endl;
    print(v);
    bubble_sort(v);
    cout << endl;
    cout << "---------- Post- Bubble Sort ----------" << endl;
    print(v);

    return 0;
}

void print(vector<int> v)
{
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
}

void bubble_sort(vector<int> &v)
{
    for(int i = v.size()-1; i > 0; i--) {
        for(int j = 0; j < i; j++) {
            if(v[j] > v[j+1]) {
                swap(v[j], v[j+1]);
            }
        }
    }
}