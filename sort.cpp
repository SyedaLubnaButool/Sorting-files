#include "splashkit.h"
#include "splashkit-arrays.h"
#include "utilities.h"

const int SCREEN_HEIGHT = 800;
const int DATA_SIZE = 100;
const int SCREEN_WIDTH = 1400; //1080
const double MAX_VALUE = 100;
const int MARGIN = 1;

void fill_array_random(fixed_array<int,DATA_SIZE> &data,int min, int max)
{
    for(int i =0;i<DATA_SIZE;i++)
    {
        data[i]=rnd(min,max);
    }
}

void visualize_array(const fixed_array<int,DATA_SIZE> &data, int highlight_index,int index)
{
   
    bool test = false;
    int bar_distance = SCREEN_WIDTH/MAX_VALUE ;
    int bar_width = bar_distance - MARGIN *2;
    clear_screen(COLOR_WHITE);
    for(int i =0; i< DATA_SIZE;i++)
    {
        
        int bar_x = (i*bar_distance) +MARGIN;
        int bar_height = (data[i]* SCREEN_HEIGHT)/MAX_VALUE ;
        int bar_y = SCREEN_HEIGHT - bar_height;
        test = (i == highlight_index) or (i == index) ;
        fill_rectangle(test? COLOR_RED :COLOR_PINK,bar_x,bar_y,bar_width,bar_height);
        draw_rectangle(COLOR_BLACK,bar_x,bar_y,bar_width,bar_height);
        
    }
    refresh_screen();
    delay(10);
}   

void bubble_sort_pass(fixed_array<int,DATA_SIZE> &data, int range)
{
    for (int i=0;i<range-1;i++)
    {
        if(data[i]>data[i+1])
        {
            swap(data[i],data[i+1]);
        }
        visualize_array(data,i,i+1);
    }
}

void bubble_sort(fixed_array<int,DATA_SIZE> &data)
{
    for(int i =length(data);i>1;i--)
    {
        bubble_sort_pass(data,i);
    }
}

void selection_sort(fixed_array<int,DATA_SIZE> &data)
{
    for(int i =0;i<DATA_SIZE-1;i++)
    {
        int min_index =i;
        for(int j= i+1;j<DATA_SIZE;j++)
        {
            if( data[j]< data[min_index])
            {
                min_index =j;
            } 
        }
        swap(data[i],data[min_index]);
        visualize_array(data,min_index,i);
    }
}

int main()
{
    fixed_array<int,DATA_SIZE> data;
    fill_array_random(data,1,100);
    open_window("Bubble Sort Visualizer by Lubna",SCREEN_WIDTH,SCREEN_HEIGHT);
    bubble_sort(data);
    //selection_sort(data);
    while (!(quit_requested()))
    {
        process_events();       
         
    }
    
    
}