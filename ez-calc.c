#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char expression[30], formula[30], sign;
char sign_tab_parenthesis[2] = {'(', '\0'};
char sign_tab_exponant[3] = {'^', '|', '\0'};
char sign_tab_multiplication[6] = {'x', 'X', '*', '/', '%', '\0'};
char sign_tab_addition[3] = {'+', '-', '\0'};
int parenthesis_count = 0, parenthesis_location[2], negative_location[30], counter, formula_size, expression_size, sign_location = 0, number_one_length, number_two_length;
float number_one, number_two, result, remain = 0;

void parenthesisReplacer(void){
    char tmp_formula[30];
    int i = 0, f = 0, supposed_length, result_length;
    counter = 0;
    result_length = strlen(expression);
    supposed_length = formula_size - expression_size + result_length;

    while (counter < supposed_length - 2) {
            if (counter >= parenthesis_location[0] && f != result_length){
                if (expression[f] == '('){
                    ++f;
                }
                else if (expression[f] == ')'){
                    ++f;
                    i = i + (parenthesis_location[1] - parenthesis_location[0]);
                }
                else{
                    tmp_formula[counter++] = expression[f++];
                }
            }
            else {
                tmp_formula[counter++] = formula[i++];
                tmp_formula[counter+1] = '\0';
            }
        }

    for (counter = 0; counter <= 30; counter++) {
        formula[counter] = tmp_formula[counter];
    }
}

void expressionRewriter(void){
    char tmp_expression[30], str_result[30];
    int i = 0, f = 0, supposed_length, result_length;
    counter = 0;
    // Convert float result into a string
    sprintf(str_result, "%.2f", result);
    result_length = strlen(str_result);
    // Calculate the future length of the expression
    supposed_length = (strlen(expression) + strlen(str_result) + 1 ) - ( number_one_length + number_two_length);

    while (counter < supposed_length) {
        // if the character doesn't need to be changed then put it in tmp_expression
        if (counter < (sign_location - number_one_length) || f == result_length + 1){
            if (expression[i] == '='){
                ++i;
                tmp_expression[counter++] = 'n';
            }
            else {
                tmp_expression[counter++] = expression[i++];
            }
        }
        // if the character should be changed then get it from the result
        else if (counter >= (sign_location - number_one_length) && f != result_length){
            tmp_expression[counter++] = str_result[f++];
        }
        // if the result has been fully put in place continue putting from the expression
        else if (f == result_length){
            ++f;
            i = i + number_one_length + number_two_length + 1;
        }
    }
    // put tmp_expression into expression
    for (counter = 0; counter <= 30; counter++) {
        expression[counter] = tmp_expression[counter];
    }
}

void numberFinder(void){
    char number[30];
    int i = 0;

    for (counter = 0; counter <= expression_size; counter++){
        if (counter <= sign_location){
            if ((expression[counter] >= '0' && expression[counter] <= '9') || expression[counter] == '.'){
                number[i++] = expression[counter];
            }
            else if (expression[counter] == ','){
                number[i++] = '.';
            }
            else if (expression[counter] == 'n' || expression[counter] == 'N'){
                number[i++] = '-';
            }
            else if (expression[counter] == sign) {
                number[i++] = '\0';
                number_one_length = strlen(number);
                number_one = atof(number);
                i = 0;
            }
            else {
                i = 0;
            }
        }
        else if (counter > sign_location){
            if ((expression[counter] >= '0' && expression[counter] <= '9') || expression[counter] == '.'){
                number[i++] = expression[counter];
            }
            else if (expression[counter] == ','){
                number[i++] = '.';
            }
            else if (expression[counter] == 'n' || expression[counter] == 'N'){
                number[i++] = '-';
            }
            else {
                number[i++] = '\0';
                number_two_length = strlen(number);
                number_two = atof(number);
            }
        }
    }
}

void signInterpreter(void){
    // if the sign is found proceed with calculation then replace formula (or part of it if there is parenthesis) with expression
    numberFinder();
    switch (sign) {
        case '^':
            result = powf(number_one, number_two);
            remain = 0;
            break;
        case 'x':
        case 'X':
        case '*':
            result = number_one * number_two;
            remain = 0;
            break;
        case '/':
            if (number_one == 0 || number_two == 0){
                exit(1);
            }
            else{
                result = number_one / number_two;
                remain = 0;
            }
            break;
        case '%':
            if (number_one == 0 || number_two == 0){
                exit(1);
            }
            else{
                result = number_one / number_two;
                remain = fmod(number_one, number_two);
            }
            break;
        case '+':
            result = number_one + number_two;
            remain = 0;
            break;
        case '-':
            result = number_one - number_two;
            remain = 0;
            break;
        default:
            break;
    }
    expressionRewriter();
}

void signFinder(char *tab){
    int i = 0, tab_len = strlen(tab);
    counter = 0;
    // if we search for opening parenthesis search for both parenthesis
    if (tab[0] == '('){
        while (counter<formula_size){
            // if opening parenthesis found add counter to location[0] keep searching for opening parenthesis
            if (formula[counter] == '('){
                parenthesis_location[0] = counter;
            }
            // else if closing parenthesis found add counter to location[1] and stop searching
            else if (formula[counter] == ')'){
                parenthesis_location[1] = counter + 1;
                break;
            }
            counter++;
        }
    }
    // If searching an operator search only for the operator
    else {
        while (counter<expression_size){
            // if operator found send to interpretation
            for (i = 0; i < tab_len; i++){
                if (expression[counter] == tab[i]){
                    sign = tab[i];
                    sign_location = counter;
                    signInterpreter();
                    counter = 0;
                }
            }
            counter++;
        }
    }
}

void priorityCalc(void){
    // search for sign in the formula then replace with the result and forward to next priority detection
    int i = 0;
    parenthesis_location[0] = -1;

    // going thru the PEMDAS order
    signFinder(sign_tab_parenthesis);
    // if parenthesis_location[0] is not -1 there is still parenthesis
    if (parenthesis_location[0] != -1){
        for(counter=parenthesis_location[0]; counter<parenthesis_location[1]; counter++){
            expression[i++] = formula[counter];
        }
        expression[i] = '\0';
    }
    // else there is no parenthesis
    else {
        for (counter = 0; counter<formula_size; counter++){
            expression[i++] = formula[counter];
        }
        expression[i] = '\0';
    }
    expression_size = strlen(expression);
    signFinder(sign_tab_exponant);
    signFinder(sign_tab_multiplication);
    signFinder(sign_tab_addition);
    
    if (parenthesis_count == 0){
        if (remain == 0){
            printf("The result is %s\n", expression);
        }
        else{
            printf("The result is %s and remainder is %.0f\n", expression, remain);
        }
    }
    else {
        // start a recursion if there is still parenthesis
        --parenthesis_count;
        parenthesisReplacer();
        priorityCalc();
    }
}

void parenthesisCounter(void){
    // search for parenthesis in the formula in order to get a stop condition
    for(counter=0; counter<formula_size; counter++){
        if (formula[counter] == '(' || formula[counter] == ')'){
            parenthesis_count++;
        }
        
    }
    // if parenthesis_count is odd there is an issue
    if (parenthesis_count%2 != 0){
        puts("Parenthesis count incorrect it won't work");
    }
    // else we are good to go
    else{
        parenthesis_count = parenthesis_count / 2;
        priorityCalc();
    }
}

int main(int argc, char **argv){
    if (argc != 2){
        puts("You need to use the command like ./calc \"formula\"");
        return 1;
    }
    else if (argc == 2) {
        formula_size = strlen(argv[1]);
        for(counter=0; counter<formula_size; counter++){
            if (formula[counter] != ' '){
                formula[counter] = argv[1][counter];
            }
        }
        formula[formula_size+1] = '\0';
        printf("The formula provided is %s\n", formula);
        parenthesisCounter();
        return 0;
    }
}