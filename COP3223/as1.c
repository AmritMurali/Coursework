#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Discriminant:
    > 0: 2 real solutions
    = 0: 1 real solution
    < 0: 2 imaginary solutions
*/
double discriminant(double a, double b, double c)
{
    return pow(b,2)-(4*a*c); 
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

void compute_roots_for_quadratic_equation(double discriminant, double a, double b, double c)
{
    if (discriminant == 0) { roots_for_qe_equal_to_zero(a, b, c); } 
    else if (discriminant < 0) { roots_for_qe_less_than_zero(discriminant, a, b, c); } 
    else { roots_for_qe_greater_than_zero(discriminant, a, b, c); }
}

int main(void)
{
    double a, b, c;

    printf("Case 1(one real root)\n");
    a = 8;
    b = 8;
    c = 2;
    compute_roots_for_quadratic_equation(discriminant(a, b, c), a, b, c);

    printf("Case 2(two imaginary roots)\n");
    a = 10;
    b = 8;
    c = 2;
    compute_roots_for_quadratic_equation(discriminant(a, b, c), a, b, c);
    
    printf("Case 3(two real roots)\n");
    a = 1;
    b = 4;
    c = 2;
    compute_roots_for_quadratic_equation(discriminant(a, b, c), a, b, c);

    return 0;
}  
