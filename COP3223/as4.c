/* cop3223-as4-murali-amrit.c - Assignment 4 of COP3223, writing a line struct to a file in binaray, and computing y-coordinates, using slope, 
intercept, and x-coordinates

   This program defines and creates a line struct, which stores a title, slope, intercept, 10 x-coordinates, and 10 y-coordinates. Everything 
   is inputted from a text file, except the y-coordinates, which are computed using y=m*x+b. This program must be incorporated with an input 
   text file, "as4input.txt", and creates a binary file, "as4output-murali-amrit.bin". Also there is another program called "as4reader.c" 
   which reads the binary file created outputs of all the line structs. One very important note, the reader file must have the binary file 
   renamed to "as4output-murali-amrit.bin" to work properly.

   Amrit Murali, 2020. */

#include <stdio.h>    
#include <string.h>

struct line_struct {        
  char title[64];
  float m;
  float b;
  double x[10];
  double y[10];
};

typedef struct line_struct line; 

void fill_line_and_compute_y_coordinates(line *line_input, char *title_input, float *m_input, float *b_input, double *x_input){
  strcpy(line_input->title, title_input);   
  line_input->m = *m_input;  
  line_input->b = *b_input;  
  for (int i = 0; i < 10; i++){              
      line_input->x[i]= x_input[i]; 
      line_input->y[i]= (x_input[i]* *m_input) + *b_input; 
  }     
}

void print_line(line *pline){ 
  printf("The title of the line is %s\n", pline->title);
  printf("The slope of the line is %f\n", pline->m);
  printf("The intercept of the line is %f\n", pline->b);
  for (int i = 0; i < 10; i++){ 
    printf("element %d of x array is %lf\n", i, pline->x[i]);
    printf("element %d of y array is %lf\n", i, pline->y[i]);         
  }     
  printf("\n");
}

int main(void){
  FILE *ifp, *ofp;  
  int count;
  char buffer[256];
  char title[64];
  float m, b;
  double x[10];
  line inputline;          
  
  ifp = fopen("io/as4input.txt", "r");               
  ofp = fopen("io/as4output-murali-amrit.bin", "wb"); 

  fgets(buffer, 64, ifp);                          
  sscanf(buffer, "%d", &count);

  for (int i = 0; i < count; i++){               

    fgets(buffer, 256, ifp);                    
    buffer[strcspn(buffer, "\r\n")] = 0;      
    strcpy(title, buffer);

    fgets(buffer, 64, ifp);                         
    sscanf(buffer, "%f%f", &m, &b);

    for (int i = 0; i < 10; i++){               
      fscanf(ifp, "%lf", &x[i]);
    }
    fgets(buffer, 64, ifp);                     

    fill_line_and_compute_y_coordinates(&inputline, title, &m, &b, x);   
    //print_line(&inputline);                      

    fwrite(&inputline, sizeof(inputline), 1, ofp);
  }


  fclose(ifp); //closing files
  fclose(ofp);

  return 0;
}
