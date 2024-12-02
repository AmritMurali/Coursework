/* cop3223-as3-murali-amrit.c - Assignment 3 of COP3223, computing y-coordinates, slope, and y-intercept of a linear equation using input from a file

   This program computes the slope and y-intercept using two ordered pairs from file input. It also stores and outputs a title,
   Lastly, this program computes y-coordinates for 5 distinct arrays of x-coordinates, one of them coming frome file input. 
   This program must be incorporated with an input file, "cop3223-as3input.txt", and an output file, "cop3223-as3output-murali-amrit".

   Amrit Murali, 2020. */
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>

// remove_crlf: Remove carriage return and/or line feed characters from a string.
void remove_crlf(char *s)
{
   char *t = s + strlen(s) - 1;
    while ((t >= s) && (*t == '\n' || *t == '\r'))
    {
        *t = '\0'; 
        t--; 
    }
}

double calculate_slope(double x1, double y1, double x2, double y2)
{
  return (y2 - y1) / (x2 - x1); 
}

double calculate_y_intercept(double x, double y, double slope)
{
  return y - (slope * x);
}

void print_array(FILE *ofp, double *xarray, double *yarray , int n)
{
  for(int i = 0; i < n; i++)
  {
    fprintf(ofp, "(%15.5lf, %15.5lf)\n", xarray[i], yarray[i]);   //print ordered pair(x, y)
  }
}

void compute_y_coordinates(double *xarray, double *yarray , int n, double slope, double y_intercept)
{
  for(int i = 0; i < n; i++)
  {
    yarray[i] = (slope * xarray[i]) + y_intercept;    //y = = (m * x) + b
  }
}

int main(void)
{
    FILE *ifp;  
    FILE *ofp; 
    char title[128], buffer[128];   
    double x1, y1, x2, y2, slope, y_intercept, x;
    int n;

    ifp = fopen("io/cop3223-as3input.txt", "r");   
    ofp = fopen("io/cop3223-as3output-murali-amrit", "w");

    fgets(title, 127, ifp);   
    remove_crlf(title);

    fgets(buffer, 127, ifp);    
    remove_crlf(buffer);
    sscanf(buffer, "%lf,%lf", &x1, &y1);
    fgets(buffer, 127, ifp);  
    remove_crlf(buffer);
    sscanf(buffer, "%lf,%lf", &x2, &y2);

    slope = calculate_slope(x1, y1, x2, y2);   
    y_intercept = calculate_y_intercept(x1, y1, slope);

    fgets(buffer, 127, ifp);    
    remove_crlf(buffer);
    n = atoi(buffer);

    double xarray_input[n];   
    for(int i = 0; i < n; i++)
    {
      fgets(buffer, 127, ifp);  
      remove_crlf(buffer);
      x = atof(buffer);
      xarray_input[i] = x;
    }
    
    double xarray_add[11] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0}; 
    double xarray_subtract[11] = {0.0, -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -9.0, -10.0};
    double xarray_multiply[8] = {0.0, 1.0, 10.0, 100.0, 1000.0, 10000.0, 100000.0, 1000000.0};
    double xarray_divide[6] = {1.0, 0.1, 0.01, 0.001, 0.0001, 0.00001};

    double yarray_input[n], yarray_add[11], yarray_subtract[11], yarray_multiply[8], yarray_divide[6];    
    
    compute_y_coordinates(xarray_input, yarray_input, n, slope, y_intercept);
    compute_y_coordinates(xarray_add, yarray_add, 11, slope, y_intercept);
    compute_y_coordinates(xarray_subtract, yarray_subtract, 11, slope, y_intercept);
    compute_y_coordinates(xarray_multiply, yarray_multiply, 8, slope, y_intercept);
    compute_y_coordinates(xarray_divide, yarray_divide, 6, slope, y_intercept);

    fprintf(ofp, "%s\n", title);    
    fprintf(ofp, "The original ordered pairs are (%.3lf, %.3lf) and (%.3lf, %.3lf). ", x1, y1, x2, y2);
    fprintf(ofp, "The slope of the line is %.3lf, and the y_intercept of the line is %.3lf.\n", slope, y_intercept);
    fprintf(ofp, "%d Ordered pairs, calculated from the file input.\n", n);
    print_array(ofp, xarray_input, yarray_input, n);
    fprintf(ofp, "11 Ordered pairs, with x-coordinates from 0.0, incremented by 1.0 to 10.0.\n");
    print_array(ofp, xarray_add, yarray_add, 11);
    fprintf(ofp, "11 Ordered pairs, with x-coordinates from 0.0, decremented by 1.0 to -10.0.\n");
    print_array(ofp, xarray_subtract, yarray_subtract, 11);
    fprintf(ofp, "8 Ordered pairs, with x-coordinates from 0.0, multipled by 10.0 to 1000000.0.\n");
    print_array(ofp, xarray_multiply, yarray_multiply, 8);
    fprintf(ofp, "6 Ordered pairs, with x-coordinates from 1, divided by 10.0 to 0.00001.\n");
    print_array(ofp, xarray_divide, yarray_divide, 6);
    
    fclose(ifp);   
    fclose(ofp);

    return 0;
}
