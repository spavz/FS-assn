#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>
#include <unordered_map>
using namespace std;


// Pass the array by reference &
void heapify(vector<int>& a, int i, int n)
{
    int j, temp;
    temp = a[i];
    j = 2*i;
    while (j <= n)
    {
        if (j < n && a[j+1] > a[j])
            j = j+1;
        if (temp > a[j])
            break;
        else if (temp <= a[j])
        {
            a[j/2] = a[j];
            j = 2*j;
        }
    }
    a[j/2] = temp;
}
void heapsort(vector<int>& a, int n)
{
    int i, temp;
    for (i = n; i >= 2; i--)
    {
        swap(a[i],a[1]);
        heapify(a, 1, i - 1);
    }
}
void build_heap(vector<int>& a, int n)
{
    for(int i = n/2; i >= 1; i--)
        heapify(a, i, n);
}


int main()
{
    /* Define n dynamically until EOF */
    int n = 18, address, x;


    /* hashing is a hashmap data structure used to map addresses with their index list keys */
    unordered_map<int,int> hashing;

    /* Vector "a" has keys of the records. "index.txt" is unsorted index list */
    vector<int> a;
    ifstream index("index.txt");

    /* 0th element is inconvenient to iterate in heapsort algorithm. 
    Hence push ununsed value */
    a.push_back(-1);

    for (int i = 0; i < n; i++)
    {
        // Read first column
        index >> x;
        // a has its entry (key)
        a.push_back(x); 
        // Read second column
        index >> address;

        //Map key with its address (hash)
        hashing[x] = address;
    }

    /* Heapify first to place the largest element in first position and corresponding removal */
    build_heap(a,n);

    /*Remove first element which is the largest value, place it in the last position. 
    Perform heapification for the rest of the elements*/
    heapsort(a, n);
    cout<<"Success"<<endl;



    // "sorted" has both keys and values after sorting
    ofstream sorted("sorted.txt"); 
    a.erase(a.begin());
    for (auto& x: a)
        sorted << x << "\t" << hashing[x] <<endl;
}
