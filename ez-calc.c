#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#import <math.h>


char expression[100];
char *formula;
int parenthesis_count = 0, parenthesis_location[2], counter, formula_size;

void parenthesisDetector(void){
    // search for parenthesis in the formula then forwards the expression found between the parenthesis to next priority detection
    char expression[13];
    int i = 0;

    while (counter<formula_size){
        if (formula[counter] == 40){
            parenthesis_location[0] = counter;
        }
        else if (formula[counter] == 41){
            parenthesis_location[1] = counter;
            break;
        }
        counter++;
    }

    for(counter=++parenthesis_location[0]; counter<parenthesis_location[1]; counter++){
        expression[i++] = formula[counter];
    }
    expression[i] = '\0';
    exponentDetector();
}

void exponentDetector(void){
    // search for exponent in the formula then replace with the result and forward to next priority detection
    multiplicationDetector();
}

void multiplicationDetector(void){
    // search for multiplication in the formula then replace with the result and forward to next priority detection
    divisionDetector();
}

void divisionDetector(void){
    // search for division in the formula then replace with the result and forward to next priority detection
    additionDetector();
}

void additionDetector(void){
    // search for addition in the formula then replace with the result and forward to next priority detection
    substractionDetector();
}

void substractionDetector(void){
    // search for substraction in the formula then replace with the result and forward to next priority detection
    if (parenthesis_count = 0){
        printf("The result is %s", formula);
    }
    else {
        parenthesis_count--;
        parenthesisDetector();
    }
}

void parenthesisCounter(void){
    // search for parenthesis in the formula in order to get a stop condition
    int opening_parenthesis_count=0;
    int closing_parenthesis_count=0;
    int counter;

    for(counter=0; counter<formula_size; counter++){
        if (formula[counter] == 40){
            opening_parenthesis_count++;
        }
        else if (formula[counter] == 41){
            closing_parenthesis_count++;
        }
    }
    
    if (opening_parenthesis_count != closing_parenthesis_count){
        puts("Parenthesis count incorrect it won't work");
    }
    else if (opening_parenthesis_count == 0 && closing_parenthesis_count == 0){
        exponentDetector();
    }
    else {
        parenthesis_count = opening_parenthesis_count;
        parenthesisDetector();
    }
}

int main(int argc, char **argv){

    if (argc > 3){
        puts("Too many args");
        return 1;
    }
    else if (argc == 1) {
        puts("Not yet implemented");
        return 0;
    }
    else if (argc == 2) {
        formula = argv[1];
        formula_size = strlen(formula);
        printf("The formula provided is %s\n", formula);
        parenthesisCounter();
        return 0;
    }
    else if (argc == 2){
        puts("Not yet implemented");
        return 0;
    }
}