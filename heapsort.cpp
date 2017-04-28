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

    //temp is the largest in the given iteration
    temp = a[i];

    //j is the left child of i
    j = 2*i;
    while (j <= n) // For the entire array
    {
        // Keep the iterator j on the minimum of the two children
        if (j < n && a[j+1] > a[j])
            j = j+1;

        // if the parent - child maintains the heap property
        // which is parent > child, break out of the loop
        if (temp > a[j])
            break;

        // Else keep iterating and swapping the children nodes with their parents 
        // in a dept-first fashion until heap property is found somewhere down the tree.
        else if (temp <= a[j])
        {
            a[j/2] = a[j];
            j = 2*j;
        }
    }

    // Place the temp node in the last but one position (Swap complete)
    a[j/2] = temp;
}
void heapsort(vector<int>& a, int n)
{
    int i, temp;
    for (i = n; i >= 2; i--)
    {

        // Current Biggest node goes to its final (last) position. It is not touched thereafter.
        swap(a[i],a[1]);

        //Perform heapification over unfixed remaining nodes since a random node is in the heap top.
        heapify(a, 1, i - 1);
    }
}

// Except the last level, perform heapification on all other levels since last level can have unordered leaves (Heap property)
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
