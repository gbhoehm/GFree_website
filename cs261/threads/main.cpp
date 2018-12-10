# include <iostream>
# include <cerrno>
# include <limits>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <list>
# include <string>
# include <iterator>
# include <cmath>

# include <pthread.h>
/* # include <synch.h> */

using namespace std;

const int NUM_OF_RAN = 149;

int arr[NUM_OF_RAN+1];


/* display the containts of the list with up to ten items a line. */
void showlist(list <int> g)
{
    // Create a pointer for the list called it.
    list <int> :: iterator it;
    int i = 0;
    for(it = g.begin(); it != g.end(); ++it)
    {
        cout << ' ' << *it;
        i ++;
        if (i%10 == 0)
        {
            cout << '\n';
        }
    }
    cout << endl << endl << endl;
}

/* 
* Calculate the average number in the list by adding up all the values in the list.
* Then dividing that number by the length of the list. 
*/
float average(list <int> g)
{
    // Create a pointer for the list called it.
    list <int> :: iterator it;
    float sum_of_list = 0;
    for(it = g.begin(); it != g.end(); ++it)
    {
        sum_of_list = sum_of_list + *it;
    }
    sum_of_list = sum_of_list / (NUM_OF_RAN + 1);
    return sum_of_list;
}

/*
* Calculate the standard deviation of the list by using the formula
* sigma = square-root(sum(xi-mean)^2/total number intems in list) 
*/
float standard_deviation(list <int> g, int mean)
{
    // Create a pointer for the list called it.
    list <int> :: iterator it;
    float i;
    float t;
    // sum(xi-mean)^2
    for(it = g.begin(); it != g.end(); ++it)
    {
        t = *it - mean;
        i = i + pow(t, 2);
    }
    // sum(xi-mean)^2/total number intems in list
    i = i / (NUM_OF_RAN + 1);
    // square-root(sum(xi-mean)^2/total number intems in list)
    i = sqrt(i);

    return i;
}

/*
* After the list of random numbers has been sorted find min, max and median of the list of numbers.
* Find minimum number just take the first number from the sorted list.
* To find the median go to the middle of the list, if the list is odd median found.
* Else take one number from one side of the middle and take a number for the other side.
* Add those two numbers together and divided by two and that is the median.
* Find maximum traverse to the end of the list and that is the maximum number.
*/
void min_max_mid(list <int> g)
{
    // Create a pointer for the list called it.
    list <int> :: iterator it;
    int minimum;
    int median1;
    int median2;
    int maximum;
    int i = 0;

    // Get the first number of the list, thus minimum number
    it = g.begin();
    minimum = *it;

    // Test if the list has an even or odd length then finding the median appropatly 
    if ((NUM_OF_RAN + 1 )%2 == 0)
    {
        for(it = g.begin(); it != g.end(); ++it)
        {
            i ++;
            if (i == ((NUM_OF_RAN + 1 )/2))
            {
                median1 = *it;
            }
            if (i == (((NUM_OF_RAN + 1 )/2)+1))
            {
                median2 = *it;
            }
            if (i == (NUM_OF_RAN + 1))
            {
                maximum = *it;
            }
        }
        median1 = (median1 + median2)/2;
    }
    else
    {
        for(it = g.begin(); it != g.end(); ++it)
        {
            i ++;
            if (i == (((NUM_OF_RAN + 1 )/2)+1))
            {
                median1 = *it;
            }
         
            if (i == (NUM_OF_RAN + 1))
            {
                maximum = *it;
            }
        }
    }
    cout << "minimum value = " << minimum << endl;
    cout << "median value = " <<  median1 << endl;
    cout << "maximum value = " <<  maximum << endl;
}

void refill(list <int> g)
{
    // Create a pointer for the list called it.
    list <int> :: iterator it;
    int i = 0;
    for(it = g.begin(); it != g.end(); ++it)
    {
        cout << *it << ' ';
        *it = arr[i];
        cout << *it << endl;
        i ++; 
    }
}

void bubble_sort(list <int> g)
{
    list <int> :: iterator it;
    list <int> :: iterator in;
    int t, j; 
    bool swapped; 
    int i = 1;

    // Convert the list of random numbers to an array for the bubble sort
	for(it = g.begin(); it != g.end(); ++it)
    {
        arr[i] = *it;
        i ++;
    }

    // Run the bubble sort algorithm on the array of random numbers
    for (t = 0; t < NUM_OF_RAN-1; t++) 
    { 
      swapped = false; 
      for (j = 0; j < NUM_OF_RAN-t-1; j++) 
      { 
         if (arr[j] > arr[j+1]) 
         { 
            swap(arr[j], arr[j+1]); 
            swapped = true; 
         } 
      } 
  
      // IF no two elements were swapped by inner loop, then break 
      if (swapped == false) 
         break; 
    }

    cout << i << endl << endl;



}

int main()
{
    list <int> ran_nums;
    int i;
    float mean;
    float sigma;
    int minimum;
    int median;
    int maximum;
    for (i=0; i <= NUM_OF_RAN;i++)
    {
        ran_nums.push_front(rand() % 100000 + 1);
        //cout << rand() % 100000 + 1 << endl;
    }
    showlist(ran_nums);

    cout << "average of the list of random numbers" << endl;
    mean = average(ran_nums);
    cout << mean << endl;
    cout << "standard deviation of the list of random numbers" << endl;
    sigma = standard_deviation(ran_nums, mean);
    cout << sigma << endl;
    cout << "sorted list" << endl;
    bubble_sort(ran_nums);
    refill(ran_nums);
    showlist(ran_nums);
    min_max_mid(ran_nums);
    
    return (0);

}
