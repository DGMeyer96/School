/*****************************************************************
*Daniel Meyer
*insertion_sort.cpp
*10/2/17
*Lab 2: Time Complexity
*Implement a insertion sort to test that the execution time is O(n^2)
*CSE 330
*Fall 2017
*****************************************************************/

#include <vector>
#include <iostream>

using namespace std;

void print(vector<int> v);
void insertion_sort(vector <int> &v);

int main()
{
    int n;

    cin >> n;
    vector<int> v(n);

    srand(time(0));

    for(int i = 0; i < n; i++) {
        v[i] = rand() % 1000000;
    }

    cout << "---------- Pre- Insertion Sort ----------" << endl;
    print(v);
    insertion_sort(v);
    cout << endl;
    cout << "---------- Post- Insertion Sort ----------" << endl;
    print(v);

    return 0;
}

void print(vector<int> v)
{
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
}

void insertion_sort(vector<int> &v)
{
    int i, j, elem;

    for(i = 1; i < v.size(); i++) {
        for(elem = v[i], j = i-1; j >= 0 && elem < v[j]; j--) {
            v[j+1] = v[j];
        }

        v[j+1] = elem;
    }
}