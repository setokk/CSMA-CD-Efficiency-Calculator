/* 
|  Author: setokk
|  LinkedIn: https://www.linkedin.com/in/kostandin-kote-255382223/
|
|  This is a simple program for calculating the efficiency of a simulation 
|  of a specific CSMA/CD communication system.
|  
*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>


#define V 200000000 // Velocity (2 * 10^8)
#define EXIT 113 // q


double toBits(double L);
double toBytes(double L);
double toMeters(double d);
double toBps(double R);


int main(int argc, char* argv[])
{
    double efficiency;
    double R; // Rate (Gbps), R == Capacity in this case
    double L; // Length of bytes per package/frame
    double Lmin; // The minimum length of packages/frames (Lmin) in order for the protocol to work
    double d; // Distance between the two terminals (km)

    // Initial Values
    double d_prop = 0; 
    double d_trans = 0;

    double b = 0;

    char ans = 'y';

    while (ans != EXIT && ans != EXIT - 32)
    {
        // Read User Input (R, L, d)
        do
        {
            printf("Please insert the rate R (Gbps): ");
            scanf("%lf", &R);

            if (R <= 0)
            {
                printf("The rate can't be negative or zero\n");
            }
        } 
        while (R <= 0);

        do
        {
            printf("Please insert the length of the packages/frames L (bytes): ");
            scanf("%lf", &L);

            if (L <= 0)
            {
                printf("The package/frame length can't be negative or zero\n");
            }
        } 
        while (L <= 0);

        do
        {
            printf("Please insert the distance between the two terminals (km): ");
            scanf("%lf", &d);

            if (d <= 0)
            {
                printf("The distance between the two terminals can't be negative or zero\n");
            }
        }
        while (d <= 0);


        // Calculate transmission and propagation delays
        d_trans = toBits(L) / toBps(R);
        d_prop = toMeters(d) / V;

        // Calculate b
        b = (d_prop / d_trans);

        // Calculate the efficiency
        efficiency = (1 / (1 + 5 * b));

        // Calculate the minimum length of packages/frames (Lmin)
        // in order for the protocol to work d_trans >= 2 * d_prop
        Lmin = 2 * ((toMeters(d) * toBps(R)) / V);

        // Print results
        printf("Efficiency = %.7lf%%\n", efficiency * 100);
        printf("Transmission Delay = %.7lfs\n", d_trans);
        printf("Propagation Delay = %.7lfs\n", d_prop);
        printf("Minimum length of packages/frames = %d bytes\n", (int) toBytes(Lmin));

        // Clear Buffer
        fflush(stdin);

        printf("\nPress any key to continue or q to exit...");
        ans = getch();
        printf("\n");
        printf("\n");
    }

    return 0;
}


double toBits(double L)
{
    return (L * 8); 
}

double toBytes(double L)
{
    return (L / 8); 
}

double toMeters(double d)
{
    return (d * 1000); 
}

double toBps(double R)
{
    return (R * pow(10, 9));
}