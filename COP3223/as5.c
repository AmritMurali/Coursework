/* cop3223-as5-murali-amrit.c - Assignment 5 of COP3223, creating a line struct (memory allocated), getting all required information from text file input, computing y-coordinates, using slope, intercept, and x-coordinates.

   This program defines and creates a line struct, which stores a slope, intercept, the number of coordinates called count, count x-coordinates, and count y-coordinates. Everything is inputted from a text file, except the y-coordinates, which are computed using y=m*x+b.
   This program must be incorporated with an input text file, "as5input.txt", and creates a text file, "as5output-murali-amrit.txt". 

   Amrit Murali, 2020. */
#include <stdio.h>                           
#include <stdlib.h>


struct line_struct {                              
  float m;
  float b;
  int count;
  double *x;
  double *y;
};

typedef struct line_struct line;            

line *create_new_line(float m_input, float b_input, int count_input){ 
  line *nline = (line *) malloc(sizeof(line));  
  nline->m = m_input;
  nline->b = b_input;
  nline->count = count_input;
  nline->x = (double *) malloc(count_input * sizeof(double));
  nline->y = (double *) malloc(count_input * sizeof(double));

  return nline;
}

double compute_y_coordinate(double x, float m, float b){ 
  double y = (m * x) + b;
  return y;
}

void print_line_output(FILE *ofp, line *a_line){  
  ofp = fopen("io/as5output-murali-amrit.txt", "w"); 

  fprintf(ofp, "Slope: %f\n", a_line->m); 
  fprintf(ofp, "Intercept: %f\n", a_line->b);

  for(int j=0; j<a_line->count; j++){ 
    fprintf(ofp, "X%d = %lf, Y%d = %lf\n", j+1, a_line->x[j], j+1, a_line->y[j]);
  }

  fclose(ofp);                                   

}

void dispose_line(line *disposed){  
  free(disposed->x);  
  free(disposed->y);  
  free(disposed);  
}

int main(void) {
  FILE *ifp, *ofp;                              
  char buffer[256];
  float m_input, b_input;
  int count_input;
  line *as5_line;

  ifp = fopen("io/as5input.txt", "r");              

  fgets(buffer, 255, ifp);                             
  sscanf(buffer, "%f%f", &m_input, &b_input);

  fgets(buffer, 255, ifp);                               
  sscanf(buffer, "%d", &count_input);

  as5_line = create_new_line(m_input, b_input, count_input); 

  for (int i = 0; i < as5_line->count; i++) {    
      fscanf(ifp, "%lf", &as5_line->x[i]);
      as5_line->y[i] = compute_y_coordinate(as5_line->x[i], as5_line->m, as5_line->b);
  }
  fgets(buffer, 64, ifp);                         

  print_line_output(ofp, as5_line);               
  dispose_line(as5_line);                       

  fclose(ifp);                                

  return 0;
}
