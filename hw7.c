#include<stdio.h>
#include<math.h>
#include"recur.c"
#include <gsl/gsl_integration.h>
#include"gsl_integration.c"
#define NMAX 100
#include"timer.h"
#include"timer.c"
#include"adjust.c"

/*Some code recycled from midterm I project.*/

int main (void)
{
    //Initializing variables
    double vals1[NMAX + 1];
    double vals2[NMAX + 1];
    double timea;
    double timea1;
    double timeb;
    double timeb1;
    double tmin = 1.;
    double tmax = 2.;
    int nmin = 0;
    int nmax = NMAX;
    int count = 1000;


    integral_recur (nmin, nmax, vals1); // Recursion formula stores 1 to 100 in an array
    integral_gen (nmin, nmax, vals2);   // GSL integration stores 1 to 100 in an array

    printf
        ("        n           Recur             GSL Integrator       Absolute Error*10^9  \n");
    int i;

    for (i = 0; i < 101; i++)
    {
        printf ("   %6d     %15.15f     %15.15f      %15.15f \n", i, vals1[i],
            vals2[i], fabs (0.000000001 * (vals1[i] - vals2[i])));
    }
    int j;

    printf
        ("\n\nTiming for recurrence function\n\nTime per call (usec) Total Time (sec)      Count\n");
    do
    {
        timer_start ();         // Starts the timer
        for (j = 0; j < count; j++)
        {
            integral_recur (nmin, nmax, vals1); // The recursion formula stores values in array vals1
        }
        timea = timer_stop ();  // Stops the timer
        timea1 = timea / count; // Calculates the time per function
        printf (" %10.2f usec     %10.6f sec    %10d\n", timea1 * 0.000001,
            timea, count);
        count = adjust_rep_count (count, timea, tmin, tmax);    // Adjusts the count
    }
    while ((timea > tmax) || (timea < tmin));
    printf ("Time per recurance function call = %f usec \n",
        timea1 * 0.000001);
    printf
        ("\n\nTiming for GSL integration function\n\nTime per call (usec) Total Time (sec)      Count\n");

    count = 1000;
    do
    {
        timer_start ();         // Starts the timer
        for (j = 0; j < count; j++)
        {
            integral_gen (nmin, nmax, vals2);   // The GSL formula stores values in array vals2
        }
        timeb = timer_stop ();  // Stops the timer
        timeb1 = timeb / count; // Calculates the time per function calls
        printf (" %10.2f usec     %10.6f sec    %10d\n", timeb1 * 0.000001,
            timeb, count);
        count = adjust_rep_count (count, timeb1, tmin, tmax);   // Adjusts the count 
    }
    while ((timeb > tmax) || (timeb < tmin));
    printf ("Time per GSL integration call = %f usec \n", timeb1 * 0.000001);
    printf (" %10.6f      %10.6f\n\n", timeb1, timea1);
    printf ("Ratio of times of gsl integration / recursion formula = %f\n",
        timeb1 / timea1);
    return 0;
}
