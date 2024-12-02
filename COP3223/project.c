/* cop3223-project-murali-amrit.c - Programming Project of COP3223, calculator with a paper tape.

   This program behaves is a calculator. It can access history using "b", use pi and e, 4-function ability, trig, square, storage variabe, a paper tape, and more. No input file is needed.
   This program creates a text file, "io/calculator-tape-file-murali-amrit.txt". 
   I tested the project script given and everything worked prefectly and I have tried many test cases. The error handling is pretty good and even checks domains of functions.

   Amrit Murali, 2020. */

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <math.h>

double *history; 
int history_length;
double *result_from_history;

void add(double num){
  history_length++;
  history = (double *)realloc(history, (history_length) * sizeof(double)); 
  *(history + (history_length-1)) = num;
}

char * history_finder(double *result){
  char input[64];
  int pos = history_length - 1;

  while(pos > -1){
    printf("?%.13lf\n", *(history + pos));
    fgets(input, 63, stdin); 
    input[strcspn(input, "\r\n")] = 0;

    if(!(strcmp(input, "b") == 0)){
      break;
    }
    pos--;
  }
  if(strcmp(input, "") == 0){
    *result = *(history+pos);
    return "success";
  } 
  return "error";
}

void getNumberInput(char *input){
  double inputDouble;

  printf("Enter a number.\n");
  fgets(input, 63, stdin);  
  input[strcspn(input, "\r\n")] = 0;

  if((strcmp(input, "pi") == 0) || (strcmp(input, "e") == 0) || (strcmp(input, "c") == 0) || (strcmp(input, "ca") == 0) || (strcmp(input, "q") == 0)){
      return;
  }

  if((strcmp(input, "b") == 0)){
    input = history_finder(result_from_history);
    if(strcmp(input, "success") == 0){
      return;
    }
  }

  if(sscanf(input, "%lf", &inputDouble) == 1){
    return; 
  }  

  strcpy(input, "error"); 
}

double change_num_input(char *input) {
  double inputDouble;

  if(sscanf(input, "%lf", &inputDouble) == 1){
    return atof(input);
  } else if(strcmp(input, "pi") == 0){
    return M_PI;
  } else if(strcmp(input, "e") == 0){
    return M_E;
  } else if(strcmp(input, "b") == 0){
    return *result_from_history;
  }

  return 0;
}

char * valid_unary_operator(char *op, double num){
  if((strcmp(op, "sin") == 0) || (strcmp(op, "cos") == 0) || (strcmp(op, "tan") == 0) || (strcmp(op, "arctan") == 0) || (strcmp(op, "abs") == 0) || (strcmp(op, "inv") == 0)){ //unary operators with no restrictions to domain
    return "unary";
  }

  if(((strcmp(op, "arcsin") == 0) || (strcmp(op, "arccos") == 0)) && (num>=-1 && num<= 1)){ //domain of arcsin and arccos are [-1, 1]
    return "unary";
  }

  if((strcmp(op, "root") == 0) && num >= 0){ //domain of root function is [0, infinity)
    return "unary";
  }  

  if(((strcmp(op, "log") == 0) || (strcmp(op, "log2") == 0)) && num > 0){ 
    return "unary";
  }

  return "not unary"; 
}

double unary_op(char *op, double num){
  if(strcmp(op, "sin") == 0){ return sin(num); } 
  if(strcmp(op, "cos") == 0){ return cos(num); }
  if(strcmp(op, "tan") == 0){ return tan(num); } 
  if(strcmp(op, "arcsin") == 0){ return asin(num); } 
  if(strcmp(op, "arccos") == 0){ return acos(num); } 
  if(strcmp(op, "arctan") == 0){ return atan(num); } 
  if(strcmp(op, "root") == 0){ return sqrt(num); } 
  if(strcmp(op, "abs") == 0){ return fabs(num); } 
  if(strcmp(op, "inv") == 0){ return 1/num; } 
  if(strcmp(op, "log") == 0){ return log10(num); } 
  if(strcmp(op, "log2") == 0){ return log2(num); } 

  return 0.0;
}

double binary_op(char *op, double num, double num2){
  if(strcmp(op, "+") == 0){ return num + num2; } //addition
  if(strcmp(op, "-") == 0){ return num - num2; } //subtraction
  if(strcmp(op, "x") == 0){ return num * num2; } //multiplication
  if(strcmp(op, "/") == 0){ return num / num2; } //division 
  if(strcmp(op, "^") == 0){ return pow(num, num2); } //exponentiation

  return 0.0;
}

double memory_op(char *op, double num, double num2, double *storage, FILE *ofp){
  if(strcmp(op, "rcl") == 0){ 
    fprintf(ofp,"Recalled memory %d.\n", (int)num);
    add(num);
    printf("Recalled memory %d.\n", (int)num);
    return *(storage + (int)num); 
  } 

  if(strcmp(op, "sto") == 0){
    fprintf(ofp,"Stored in memory %d.\n", (int)num2);
    add(num);
    printf("Stored in memory %d.\n", (int)num2);
    *(storage + (int)num2) = num;
    return num2; 
  } 

  return 0.0;
}

void getOperatorInput(char *input){
  printf("Enter an operator.\n");
  fgets(input, 63, stdin);  
  input[strcspn(input, "\r\n")] = 0;
}  

char * getOperatorType(char *op, double num, double *num2, char *num2string, FILE *ofp){
  //does the operator and number satisfy a valid recall memory action?  
  if((strcmp(op, "rcl") == 0) && (floor(num) == num && num >= 0 && num <= 9)){
    fprintf(ofp,"%s\n", op);
    return "memory";
  } 

  if(strcmp(op, "sto") == 0){
    fprintf(ofp,"%s\n", op);
    getNumberInput(num2string); 
    *num2 = change_num_input(num2string);
    if(strcmp(num2string, "error") == 0 || !(floor(*num2) == *num2 && *num2 >= 0 && *num2 <= 9)){ 
      return "error"; 
    }
    fprintf(ofp,"%.13lf\n", *num2);
    add(*num2);
    printf("%.13lf\n", *num2);
    return "memory";
  } 

  if(strcmp(valid_unary_operator(op, num), "unary") == 0){
    fprintf(ofp,"%s\n", op);
    return "unary";
  }

  if((strcmp(op, "+") == 0) || (strcmp(op, "-") == 0) || (strcmp(op, "x") == 0) || (strcmp(op, "/") == 0) || (strcmp(op, "^") == 0)){ 
    fprintf(ofp,"%s\n", op);
    getNumberInput(num2string); 
    if(strcmp(num2string, "error") == 0){ 
      return "error";
    } 
    *num2 = change_num_input(num2string);
    fprintf(ofp,"%.13lf\n", *num2);
    add(*num2);
    printf("%.13lf\n", *num2);
    return "binary";
  }  

  if((strcmp(op, "c") == 0) || (strcmp(op, "ca") == 0) || (strcmp(op, "q") == 0)){ 
    return "special";
  }

  return "error";
}

double operator_directory(char *optype, char *op, double num1, double num2, double *storage, FILE *ofp){
  if(strcmp(optype, "memory") == 0){
    return memory_op(op, num1, num2, storage, ofp);
  }

  if(strcmp(optype, "unary") == 0){
    return unary_op(op, num1);
  }

  if(strcmp(optype, "binary") == 0){
    return binary_op(op, num1, num2);
  }

  return 0.0;
}

int main(void) {
  FILE *ofp; 
  ofp = fopen("io/calculator-tape-file-murali-amrit.txt", "w"); 

  char *num_string = malloc(sizeof(char) * 64); 
  char *second_num_string = malloc(sizeof(char) * 64);
  char *current_operator = malloc(sizeof(char) * 64);
  char *current_operator_type;

  double num; 
  double *secondnum = malloc(sizeof(double)); 
  double result;
  
  double storage[10]; 
  double *storage_ptr = storage;

  result_from_history = malloc(sizeof(double));

  getNumberInput(num_string); 
  while((strcmp(num_string, "error") == 0) || (strcmp(num_string, "c") == 0) || (strcmp(num_string, "ca") == 0) || (strcmp(num_string, "q") == 0)){ //wrong input, c, ca, q are situations which lead back to step1 or halt program
    if(strcmp(num_string, "error") == 0){ 
      fprintf(ofp,"error\n");
      printf("error\n");
    }  
    if(strcmp(num_string, "c") == 0){
      fprintf(ofp,"%.13lf\n", 0.0);
      add(0.0);
      printf("%.13lf\n", 0.0);
    }  
    if(strcmp(num_string, "ca") == 0){
      for(int i = 0; i < 10; i++){
        *(storage_ptr + i) = 0;
      }
    }  
    if(strcmp(num_string, "q") == 0){ 
    free(num_string); 
      free(current_operator);
      free(second_num_string);
      free(secondnum);
      free(result_from_history);

      fclose(ofp);
      return 0;
    }  
    getNumberInput(num_string);
  }
  num = change_num_input(num_string);
  fprintf(ofp,"%.13lf\n", num);
  add(num);
  printf("%.13lf\n", num);

  while(1) { // this loop stops when "q" is inputted
    getOperatorInput(current_operator); //get operator

    current_operator_type = getOperatorType(current_operator, num, secondnum, second_num_string, ofp);

    if((strcmp(current_operator_type, "error") == 0) || (strcmp(current_operator_type, "special") == 0) || (strcmp(second_num_string, "c") == 0) || (strcmp(second_num_string, "ca") == 0) || (strcmp(second_num_string, "q") == 0)){ //invalid, special operators lead back to step1 or halt program
      if(strcmp(current_operator_type, "error") == 0){ //invalid operation, output an error
        fprintf(ofp,"error\n");
        printf("error\n");
      }  
      if(strcmp(current_operator, "c") == 0 || strcmp(second_num_string, "c") == 0){ //c prints 0
        fprintf(ofp,"%.13lf\n", 0.0);
        add(0.0);
        printf("%.13lf\n", 0.0);
      }  
      if(strcmp(current_operator, "ca") == 0 || strcmp(second_num_string, "ca") == 0){ //ca clears storage variable 0-9
        for(int i = 0; i < 10; i++){
          *(storage_ptr + i) = 0;
        }
      }
      if(strcmp(current_operator, "q") == 0 || strcmp(second_num_string, "q") == 0){ //q closes output file and exits
        free(num_string); //free allocated memory
        free(current_operator);
        free(second_num_string);
        free(secondnum);
        free(result_from_history);
        free(history);

        fclose(ofp);   
        return 0;
      }     
      getNumberInput(num_string); //recieve number input from user (step 1)

      while((strcmp(num_string, "error") == 0) || (strcmp(num_string, "c") == 0) || (strcmp(num_string, "ca") == 0) || strcmp(num_string, "q") == 0){ //wrong input, c, ca, q are situations which lead back to step1 or halts program
        if(strcmp(num_string, "error") == 0){ //invalid operation, output an error
          fprintf(ofp,"error\n");
          printf("error\n");
        }  
        if(strcmp(num_string, "c") == 0){ //c prints 0
          fprintf(ofp,"%.13lf\n", 0.0);
          add(0.0);
          printf("%.13lf\n", 0.0);
        }  
        if(strcmp(num_string, "ca") == 0){ //ca clears storage variable 0-9
          for(int i = 0; i < 10; i++){
            *(storage_ptr + i) = 0;
          }
        }
        if(strcmp(num_string, "q") == 0){ //q closes output file and exits
          free(num_string); //free allocated memory
          free(current_operator);
          free(second_num_string);
          free(secondnum);
          free(result_from_history);
          free(history);

          fclose(ofp);
          return 0;
        }       
        getNumberInput(num_string);
      }
      num = change_num_input(num_string);
      fprintf(ofp,"%.13lf\n", num);
      add(num);
      printf("%.13lf\n", num);

    } else { //this is a valid operation that is not special, so execute the operation

      result = operator_directory(current_operator_type, current_operator, num, *secondnum, storage_ptr, ofp);
      if(strcmp(second_num_string, "bruh") == 0){
        fprintf(ofp,"%.13lf\n", *secondnum);
        add(*secondnum);
        printf("%.13lf\n", *secondnum);
      }
      fprintf(ofp,"=\n%.13lf\n", result);
      add(result);
      printf("=\n%.13lf\n", result);
      num = result;

    } 
    strcpy(second_num_string, "bruh"); // for the next loop, this value has to equal something irrelevant (i have chosen "bruh" for this purpose)
  }

  return 0;
}
