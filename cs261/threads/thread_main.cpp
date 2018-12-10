/* # Program: thread_main.cpp
   # Class: CS261
   # Date: 7-Dec-2018
   # Author: Gage Boehm
*/

/* Description: This program generates 150 random numbers ranging from 1 to 10,000.
*  Then calculates the average number, standard deviation, minimum number, median, and maximum number.
*  It will display a list of the 150 random numbers.
*  Then an sorted list of the 150 random numbers.
*  Then will display all the calculated stats.
*  Thread 0 is calculating average number.
*  Thread 1 is calculating the standard deviation.
*  Thread 2 is sorting the list of random numbers.
*  Thread 3 is finding the min, median, and max numbers.
*/


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

using namespace std;

const int NUM_OF_RAN = 149;

// List of all the variables that the threads are using.
list <int> ran_nums;
float mean = 0;
float sigma = 0;
int arr[NUM_OF_RAN];
int maximum = 0;
float median = 0;
int minimum = 0;

// Initialize the funcaction that the threads will run.
void *average(void *arg);
void *standard_deviation(void *arg);
void *bubble_sort(void *arg);
void *min_max_mid(void *arg);

// Initialize the funcation that are not being runned in a thread.
void *showlist();
void *refill();
void *description();

int main()
{
  // Initialize the thread que, the thread counter, and loop counter.
  pthread_t threadID[50];
  long tnum;
  int i;
  
  // Desplay the description of the program.
  description();

  // Fill the list with random number ranging from 1 - 10,000
  // Then display this unsorted list of numbers
  cout << "Unsorted list :" << endl;
  for (i=0; i <= NUM_OF_RAN;i++)
    {
        ran_nums.push_front(rand() % 100000 + 1);
    }
  showlist();

  // Create and run all four threads.
  // Thread one calculates the average number in the list of random numbers.
  // Thread two calculates the standard deviation of the list of random numbers.
  // Thread three sorts the list with a bubble sort.
  // Thread four finds the minimum, median, and maximum numbers in the list.

  // Thread one
  tnum = 0;
  if(pthread_create(&threadID[tnum], NULL, &average, (void *) tnum)) {
    cout << "Error in creating thread" << endl;
    exit(0);
  }  

  // Thread two
  sleep (1);
  tnum ++;
  if(pthread_create(&threadID[tnum], NULL, &standard_deviation, (void *) tnum)) {
    cout << "Error in creating thread" << endl;
    exit(0);
  }

  // Thread three
  sleep(1);
  tnum ++;
  if(pthread_create(&threadID[tnum], NULL, &bubble_sort, (void *) tnum)) {
    cout << "Error in creating thread" << endl;
    exit(0);
  }

  // Thread four
  sleep(1);
  tnum ++;
  if(pthread_create(&threadID[tnum], NULL, &min_max_mid, (void *) tnum)) {
    cout << "Error in creating thread" << endl;
    exit(0);
  }
  for(tnum=0; tnum < 4; tnum++) 
    pthread_join(threadID[tnum],NULL);
  
  cout << endl << endl;

  // Display the sorted list and all the states that the threads calculated.
  cout << "Sorted list:" << endl;
  showlist();

  cout << "Summary of the stats calculated:" << endl << endl;
  cout << "Average number in the list = " << mean << endl;
  cout << "Standard deviation of the list = " << sigma << endl;
  cout << "minimum value = " << minimum << endl;
  cout << "median value = " <<  median << endl;
  cout << "maximum value = " <<  maximum << endl;

  return(0);
}

/*
* Display a description of what the program is proforming.
*/
void *description()
{
    cout << "<Random numbers sorted and stats realated calculated>" << endl << endl;
    cout << "This program generates 150 random numbers ranging from 1 to 10,000." << endl;
    cout << "Then calculates the average number, standard deviation, minimum number, median, and maximum number." << endl << endl;
    cout << "It will display a list of the 150 numbers." << endl;
    cout << "Then an sorted list of the 150 numbers." << endl;
    cout << "Then will display all the calculated stats." << endl;
    cout << "Thread 0 is calculating average number." << endl;
    cout << "Thread 1 is calculating the standard deviation." << endl;
    cout << "Thread 2 is sorting the list of random numbers." << endl;
    cout << "Thread 3 is finding the min, median, and max numbers." << endl << endl << endl << endl;
}


/* 
* Calculate the average number in the list by adding up all the values in the list.
* Then dividing that number by the length of the list. 
*/
void *average(void *arg)
{
    cout << "Thread " << (long) arg << " started." << endl;

    // Create a pointer for the list called it.
    list <int> :: iterator it;
    float sum_of_list = 0;
    for(it = ran_nums.begin(); it != ran_nums.end(); ++it)
    {
        sum_of_list = sum_of_list + *it;
    }
    sum_of_list = sum_of_list / (NUM_OF_RAN + 1);
    mean = mean + sum_of_list;

    cout << "Thread " << (long) arg << " exiting." << endl;
    pthread_exit(0);
}

/*
* Calculate the standard deviation of the list by using the formula
* sigma = square-root(sum(xi-mean)^2/total number intems in list) 
*/
void *standard_deviation(void *arg)
{
    cout << "Thread " << (long) arg << " started." << endl;

    // Create a pointer for the list called it.
    list <int> :: iterator it;
    float i;
    float t;

    // sum(xi-mean)^2
    for(it = ran_nums.begin(); it != ran_nums.end(); ++it)
    {
        t = *it - mean;
        i = i + pow(t, 2);
    }
    // sum(xi-mean)^2/total number intems in list
    i = i / (NUM_OF_RAN + 1);
    // square-root(sum(xi-mean)^2/total number intems in list)
    i = sqrt(i);

    sigma = sigma + i;

    cout << "Thread " << (long) arg << " exiting." << endl;
    pthread_exit(0);
}

/*
 * Using a standard bubble sort.
 * Convert the list into an array.
 * Run the bubble sort on the array.
 * Refill the list with the sorted numbers.
 */
void *bubble_sort(void *arg)
{
    cout << "Thread " << (long) arg << " started." << endl;

    list <int> :: iterator it;
    bool swapped; 
    int i = 0;
    int t, j; 

    // Convert the list of random numbers to an array for the bubble sort
	for(it = ran_nums.begin(); it != ran_nums.end(); ++it)
    {
        arr[i] = *it;
        i ++;
    }

    // Run the bubble sort algorithm on the array of random numbers
    for (t = 0; t < NUM_OF_RAN; t++) 
    { 
      swapped = false; 
      for (j = 0; j < NUM_OF_RAN-t; j++) 
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
    // re-fill the list.
    refill();

    cout << "Thread " << (long) arg << " exiting." << endl;
    pthread_exit(0);

}

/*
* After the list of random numbers has been sorted find min, max and median of the list of numbers.
* Find minimum number just take the first number from the sorted list.
* To find the median go to the middle of the list, if the list is odd median found.
* Else take one number from one side of the middle and take a number for the other side.
* Add those two numbers together and divided by two and that is the median.
* Find maximum traverse to the end of the list and that is the maximum number.
*/
void *min_max_mid(void *arg)
{
    cout << "Thread " << (long) arg << " started." << endl;

    // Create a pointer for the list called it.
    list <int> :: iterator it;
    int median1;
    int median2;
    int i = 0;

    // Get the first number of the list, thus minimum number
    it = ran_nums.begin();
    minimum = *it;

    // Test if the list has an even or odd length then finding the median appropatly 
    if ((NUM_OF_RAN + 1 )%2 == 0)
    {
        for(it = ran_nums.begin(); it != ran_nums.end(); ++it)
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
        median = (median1 + median2)/2;
    }
    else
    {
        for(it = ran_nums.begin(); it != ran_nums.end(); ++it)
        {
            i ++;
            if (i == (((NUM_OF_RAN + 1 )/2)+1))
            {
                median = *it;
            }
         
            if (i == (NUM_OF_RAN + 1))
            {
                maximum = *it;
            }
        }
    }

    cout << "Thread " << (long) arg << " exiting." << endl;
    pthread_exit(0);
}

/* Display the containts of the list with up to ten items a line. */
void *showlist()
{
    // Create a pointer for the list called it.
    list <int> :: iterator it;
    int i = 0;
    for(it = ran_nums.begin(); it != ran_nums.end(); ++it)
    {
        cout << ' ' << *it;
        i ++;
        if (i%10 == 0)
        {
            cout << '\n';
        }
    }
    cout << endl << endl;
}

/*
* Replace the unsorted list with the sorted array
*/
void *refill()
{
    // Create a pointer for the list called it.
    list <int> :: iterator it;
    int i = 0;
    for(it = ran_nums.begin(); it != ran_nums.end(); ++it)
    {
        *it = arr[i];
        i ++; 
    }
}