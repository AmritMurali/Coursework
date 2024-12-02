/* cop3223-as2-murali-amrit.c - Assignment 2 of COP3223, computing roots of quadratic/linear equations

   This program computes roots of quadratic equations (and linear equations) by inputting 
   a, b, and c.  It's not meant to be incorporated in other programs and works by itself.

   Amrit Murali, 2020. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

void root_for_linear_equation (double b, double c)
{
    double x1 = (-1*c)/b; // Calculate only root

    printf("The linear equation (%lf)x + (%lf) has one real root.\n", b, c);    // Print root and equation
    printf("The real root is (%lf).\n\n", x1); 
}

double discriminant(double a, double b, double c)
{
    double discriminant;    // Declare the discriminant

    discriminant = pow(b,2);    // Calculate the discriminant
    discriminant -= (4*a*c);
    return discriminant; 
}

void roots_for_qe_equal_to_zero(double a, double b, double c)
{
    double x1 = (-1*b)/(2*a);
    printf("The quadratic equation (%lf)x^2 + (%lf)x + (%lf) has one real root.\n", a, b, c);
    printf("The real root is (%lf).\n\n", x1); 
}

void roots_for_qe_less_than_zero(double discriminant, double a, double b, double c)
{
    double xr = (-1*b)/(2*a);
    double xi = sqrt(abs(discriminant))/(2*a);
    printf("The quadratic equation (%lf)x^2 + (%lf)x + (%lf) has two imaginary roots.\n", a, b, c);
    printf("The imaginary roots are (%lf)+(%lf)i and (%lf)-(%lf)i.\n\n", xr, xi, xr, xi);   
}

void roots_for_qe_greater_than_zero(double discriminant, double a, double b, double c)
{
    double x1 = ((-1*b)+sqrt(discriminant))/(2*a);
    double x2 = ((-1*b)-sqrt(discriminant))/(2*a);    
    printf("The quadratic equation (%lf)x^2 + (%lf)x + (%lf) has two real roots.\n", a, b, c);
    printf("The real roots are (%lf) and (%lf).\n\n", x1, x2);     
}
  
void compute_roots_for_equation(double discriminant, double a, double b, double c)
{
    if(a == 0) 
    {
        root_for_linear_equation(b, c);
    }
    else if (discriminant == 0)
    {
        roots_for_qe_equal_to_zero(a, b, c);  
    } 
    else if (discriminant < 0) 
    {
        roots_for_qe_less_than_zero(discriminant, a, b, c);
    } 
    else 
    { 
        roots_for_qe_greater_than_zero(discriminant, a, b, c); 
    }
}

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

int main(void)
{
    double a, b, c;    
    char integer_buffer[128];
    char reply[128];
    bool again = true;

    while(again)
    {
        printf("Please type the a value for your equation, ax^2 + bx + c.\n");
        fgets(integer_buffer, 127, stdin);
        remove_crlf(integer_buffer);
        a = atof(integer_buffer);    
        printf("Please type the b value for your equation, ax^2 + bx + c.\n");
        fgets(integer_buffer, 127, stdin);
        remove_crlf(integer_buffer);
        b = atof(integer_buffer); 
        printf("Please type the c value for your equation, ax^2 + bx + c.\n");
        fgets(integer_buffer, 127, stdin);
        remove_crlf(integer_buffer);
        c = atof(integer_buffer); 

        compute_roots_for_equation(discriminant(a, b, c), a, b, c);

        printf("Type \"no\" if you DO NOT want to type any more values\n");
        fgets(reply, 127, stdin);
        remove_crlf(reply);

        if(strcmp(reply, "no") == 0)
        {
            again = false;
        }
    }
    
    return 0;
}  