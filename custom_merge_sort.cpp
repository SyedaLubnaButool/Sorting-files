#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/// This function simulates giving us the number of available servers.
/// Ignore its implementation, all you need to know is that when you call
/// this function it returns an integer greater than 1. And you may assume it
/// does so in O(1) time.
/// No other assumptions can be made about this function.
int available_servers() {
    return 2 + rand() % 100;
}

/// `sublists` is the arrays that need to be merged
/// `sublist_sizes` is the size of each of those arrays (i.e. sublists[i] will have sublist_sizes[i] items)
/// `number_of_sublists` is the number of sublists passed to the function in the previous 2 parameters
int* merge_sorted_lists(int** sublists, int* sublist_sizes, int number_of_sublists) {
    // Implement the merging logic, return a pointer to the merged array on the heap

    //calcuting final size of result array and creating it, a pointer having current position we r in result 
    int final_size=0;
    for(int i=0;i<number_of_sublists;i++)
    {
        final_size+=sublist_sizes[i];
    }

    int* result = new int[final_size];
    int result_index =0;
    //we need to keep track of where we are in each sublist
    int* indices = new int[number_of_sublists];
    for(int i=0;i<number_of_sublists;i++)
    {
        indices[i]=0;//initially we look at first in each sublist
    }
    
    while(result_index<final_size)
    {
        int smallest = -1;
        for(int i=0;i<number_of_sublists;i++)
        {
            //if all elements in sublists looked at, stop
            if(indices[i]<sublist_sizes[i])
            {
                if(smallest == -1)//if nothing chosen , current is my smallest 
                {
                    smallest=i;
                }
                else
                {//if another sublists has smaller , change smallest
                    if(sublists[i][indices[i]]<sublists[smallest][indices[smallest]])
                    {
                        smallest=i;
                    }
                
                }
            }
        }
        //here we have smallest from every sublist,so put in result
        result[result_index]=sublists[smallest][indices[smallest]];
        result_index++;
        indices[smallest]++;
    }
    delete[] indices;
    return result;
}

int* merge_sort(int* items, int n) {
    //base case-if 1 element already sort
    if (n ==1) 
    {
        int* result = new int[n];
        //our result array should have the given 1 element and return its pointer
        result[0]= items[0];
        
        return result;
    }
    // Ask for the next k (the number of servers currently available)
    int k = available_servers();
    if (k > n) k = n;

    // Implement the sorting logic, return a pointer to the sorted array on the heap
   
    //calcuting how big each sublist will be
    int base_size =n/k;
    int remainder =n%k;

    int** sublists =new int*[k];//pointers to sub lists
    int* sublists_sizes = new int[k];//array storing size of each sublists

    for(int i=0;i<k;i++)//creating empty sublists acc to servers
    {
        int current_size =base_size;

        if(i<remainder)
        {
            current_size=base_size+1;
        }

        sublists[i]=new int[current_size];
        sublists_sizes[i]=current_size;
    }

    int current_index =0;//copying items into our empty sublists

    for(int i=0;i<k;i++)
    {
        for(int j=0;j<sublists_sizes[i];j++)
        {
            sublists[i][j]=items[current_index];
            current_index++;
        }
    }
    //now that we've created sublists acc to k; sort them recursively
    for(int i=0;i<k;i++)
    {
        sublists[i]=merge_sort(sublists[i],sublists_sizes[i]);
    }

    //merging sorted sublists
    int* result = merge_sorted_lists(sublists,sublists_sizes,k);
    //delete old sublists
    for(int i=0;i<k;i++)
    {
        delete[] sublists[i];
    }

    delete[] sublists;
    delete[] sublists_sizes;

    return result;
}

int main(int argc, char** argv) {

    bool data_from_console = argc == 1; // run './a.out' and './a.out bottom text' to see the difference

    int* sorted;
    int n;

    if (data_from_console) {

        srand(10001);

        cout << "Enter number of data values:" << endl;
        cin >> n;
        int* data = new int[n];
        cout << "Enter data values:" << endl;
        for (int i = 0; i < n; i++) {
            cin >> data[i];
        }
        sorted = merge_sort(data, n);
        delete[] data;
    } else {
        srand(time(nullptr));
        n = 10;
        int data[] = {9, 4, 7, 2, 1, 6, 8, 3, 5, 0};

        sorted = merge_sort(data, n);
    }

    cout << "Sorted values:" << endl;
    for (int i = 0; i < n; i++) {
        cout << sorted[i] << " ";
        if ((i & 31) == 31) cout << '\n'; // Break up lines so that line by line diff is useful
    }
    cout << endl;

    return 0;
}
