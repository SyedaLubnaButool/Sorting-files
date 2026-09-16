#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Rectangle {
    int width=0;
    int height=0;

    bool operator<(const Rectangle& rect_b)
    {
        if(width*height<rect_b.width*rect_b.height)
        {
            return true;
        }
        return false;
    }

    bool operator>(const Rectangle& rect_b)
    {
        if(width*height>rect_b.width*rect_b.height)
        {
            return true;
        }
        return false;
    }

   
};

template <typename T>
void insertion_sort(T arr[],int n) {
    for(int i=0;i<n;i++)
    {
        int current_index=i;
        while(current_index-1>=0 && arr[current_index]<arr[current_index-1]){
            swap(arr[current_index-1],arr[current_index]);
            current_index--;
        }
    }
}
template <typename T>
void merge_sort(T arr[],int n) {
    if(n<=1) return;

    int left_half_size=n/2;
    int right_half_size=n-left_half_size;

    T* left_half = new T[left_half_size];
    T* right_half = new T[right_half_size];

    for(int i=0;i<n;i++)
    {
        if(i<left_half_size)
        {
            left_half[i]=arr[i];
        }
        else
        {
            right_half[i-left_half_size]=arr[i];
        }
    }

    merge_sort(left_half,left_half_size);
    merge_sort(right_half,right_half_size);

    int left_half_index=0,right_half_index=0,result_index=0;

    while(left_half_index<left_half_size && right_half_index<right_half_size)
    {
        if(left_half[left_half_index]<right_half[right_half_index])
        {
            arr[result_index]=left_half[left_half_index];
            left_half_index++;
            result_index++;
        }
        else
        {
            arr[result_index]=right_half[right_half_index];
            result_index++;
            right_half_index++;
        }
    }

    while(left_half_index<left_half_size)
    {
        arr[result_index++]=left_half[left_half_index++];
    }
    while(right_half_index<right_half_size)
    {
        arr[result_index++]=right_half[right_half_index++];
    }

    delete[] left_half;
    delete[] right_half;
}

// void test_empty(){
//     Rectangle arr[1];

//     insertion_sort(arr,0);
//     merge_sort(arr,0);//shouldnt crash
//     cout<<"No elements passed"<<endl;
// }

// void one_element()
// {
//     string strings[1];
//     strings[0]="test";

//     insertion_sort(strings,1);
//     cout<<strings[0]<<endl;//should be test
//     merge_sort(strings,1);
//     cout<<strings[0]<<endl;//should be test
// }

// void two_elements()
// {
//     string strings[2];
//     strings[0]="test";
//     strings[1]="p";
//     insertion_sort(strings,2);
//     cout<<strings[0]+ " "+strings[1] <<endl;//should be p, test
//     merge_sort(strings,2);
//     cout<<strings[0]+ " "+strings[1]<<endl;//should be p, test
// }

int main() {
    srand(time(nullptr));
    Rectangle rects_1[10], rects_2[10];
    
    for (int i = 0; i < 10; i++) {
        rects_1[i].width = rand() % 20;
        rects_1[i].height = rand() % 20;
        rects_2[i].width = rects_1[i].width;
        rects_2[i].height = rects_1[i].height;
    }
    
    insertion_sort(rects_1, 10);
    merge_sort(rects_2, 10);
    int last_area = -1;
    
    for (int i = 0; i < 10; i++) {
        int cur_area = rects_1[i].width * rects_1[i].height;
        if (cur_area < last_area) {
            cout << "The sorted arrays don't match!" << endl;
            return 1;
        }
        last_area = cur_area;
    }
    
    for (int i = 0; i < 10; i++) {
        if (rects_1[i].width != rects_2[i].width || rects_1[i].height != rects_2[i].height) {
            cout << "The sorted arrays don't match!" << endl;
            return 1;
        }
    }
    
    cout << "Everything seems fine : )" << endl;
    // test_empty();
    // one_element();
    // two_elements();
    return 0;
}