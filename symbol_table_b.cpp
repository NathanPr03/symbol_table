/**
 * The purpose of this program is to take a .c file and return information about each of the variables and functions in the file
 * Author: Nathan Pringle 
 * Last modified: 02/05/2021
 */
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "tree.h"

using namespace std;

/**
 * Counts the number of variables in a given .c file
 * 
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 * @return Returns the amount of variables in a given .c file
 */
int var_counter(vector <token_and_line> token_vec){
    int var_count = 0; //Counts amount of variables
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i].token == "int" || token_vec[i].token == "short" || token_vec[i].token == "char" || token_vec[i].token ==  "long"  || token_vec[i].token == "float" || token_vec[i].token == "double" || token_vec[i].token == "struct" || token_vec[i].token == "int*" || token_vec[i].token == "char*" || token_vec[i].token == "long*"  || token_vec[i].token == "float" || token_vec[i].token == "double*" || token_vec[i].token == "long long*"){
            if(token_vec[i+1].token == "long"){
                var_count--;
            }
            if(token_vec[i+2].token == "("){
                var_count--;
            }
            var_count++;
        }
    }
    return var_count;
}

/**
 * Counts the number of functions in a given .c file
 * 
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 * @return Returns the amount of functions in a given .c file
 */
int func_counter(vector <token_and_line> token_vec){
    int func_count=0;
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i].token == "void" ||token_vec[i].token == "int" || token_vec[i].token == "short" || token_vec[i].token == "char" || token_vec[i].token ==  "long"  || token_vec[i].token == "float" || token_vec[i].token == "double" || token_vec[i].token == "struct" || token_vec[i].token == "int*" || token_vec[i].token == "char*" || token_vec[i].token == "long*"  || token_vec[i].token == "float" || token_vec[i].token == "double*" || token_vec[i].token == "long long*"){
            if(token_vec[i+2].token == "("){
                func_count++;
            }
        }
    }
    return func_count;
}

/**
 * Counts the number of if statements in a given .c file
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 * @return Returns the amount of if statements in a given .c file
 */
int if_counter(vector <token_and_line> token_vec){
    int if_count =0;
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i].token == "if"){
            if_count ++;
        }
    }
    return if_count;
}


/**
 * Counts the number of for loops in a given .c file
 * 
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 * @return Returns the amount of for loops in a given .c file
 */
int for_counter(vector <token_and_line> token_vec){
    int for_count =0;
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i].token == "for"){
            for_count ++;
        }
    }
    return for_count;
}

/**
 * Counts the number of while loops in a given .c file
 * 
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 * @return Returns the amount of while loops in a given .c file
 */
int while_counter(vector <token_and_line> token_vec){
    int while_count =0;
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i].token == "while"){
            while_count ++;
        }
    }
    return while_count;
}

/**
 * Struct containing all of the neccesarry information for the symbol table
 * start_token and end_token mark the start and end of the scope (respectivley) for a given variable
 */
struct information{
    string variable_name;
    int line_no=0;
    string func_var;
    string type;
    int referenced =-1;

    int start_token =0;
    int end_token =0;
};

/**
 * Loops over all the tokens, adds the neccesary information into a struct, then adds that struct into the BST. Also calls the print_tree() method
 * 
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 */
void struct_into_tree(vector <token_and_line> token_vec){
    ofstream output("outputFile.txt"); 

    string line;
    string function_name;

    int line_number= 0;

    information f;
    
    BST my_tree;

    //Loops over every token 
    for(int i =0; i < token_vec.size(); ++i){
        //Looking for a type, which means the next token will be a new variable or function
        if(token_vec[i].token == "void" ||token_vec[i].token == "int" || token_vec[i].token == "short" || token_vec[i].token == "char" || token_vec[i].token ==  "long"  || token_vec[i].token == "float" || token_vec[i].token == "double" || token_vec[i].token == "struct" || token_vec[i].token == "int*" || token_vec[i].token == "char*" || token_vec[i].token == "long*"  || token_vec[i].token == "float" || token_vec[i].token == "double*" || token_vec[i].token == "long long*"){
            //Doesnt store the variable if it = "long"
            if(token_vec[i+1].token != "long"){
                f.start_token=0;
                f.end_token=0;
                f.variable_name = token_vec[i+1].token;
                f.start_token = i+1;
                f.line_no = 0;
                //Checks for brackets which indicates its a function, if not its a variable
                if(token_vec[i+2].token == "("){
                    f.func_var = "function";
                    function_name = "(" + f.variable_name + ")";
                }else {
                    f.func_var = "variable";
                    if(function_name != "(main)"){
                        f.variable_name += function_name;
                    }
                }
                f.type = token_vec[i].token;
                //Adds on the square brackets to the "name" variable
                if(token_vec[i+2].token == "[]"){
                        f.type += " ";
                        f.type += token_vec[i+2].token;
                }else if(token_vec[i-1].token == "long"){
                    f.type += " ";
                    f.type += token_vec[i-1].token;
                }
                //Loops over all the tokens again, looking for the end of the scope
                for(int n =0; n < token_vec.size(); ++n){
                    if(token_vec[n].token == "void" ||token_vec[n].token == "int" || token_vec[n].token == "short" || token_vec[n].token == "char" || token_vec[n].token ==  "long"  || token_vec[n].token == "float" || token_vec[n].token == "double" || token_vec[n].token == "struct" || token_vec[n].token == "int*" || token_vec[n].token == "char*" || token_vec[n].token == "long*"  || token_vec[n].token == "float" || token_vec[n].token == "double*" || token_vec[n].token == "long long*"){
                        if(token_vec[n+2].token == "(" && n+2 > f.start_token){
                            f.end_token = n +1;
                            break;
                        }else{
                            f.end_token = token_vec.size();
                        }
                    }
                }
                //If the identifier is a function, give it max scope
                if(f.func_var == "function"){
                    f.end_token = token_vec.size();
                }
                f.line_no = token_vec[i].line_number;
                //Add the struct into the binary tree
                my_tree.insert(f.variable_name, f.line_no, f.func_var, f.type, f.referenced, f.start_token, f.end_token);
            }
        } 
    }
    
    //Call the update method
    my_tree.update(token_vec);

    //Call the print method
    my_tree.print_tree(output);
    
    //Close output file
    output.close();
    return;
}


int main(int argc, char **argv){
	ifstream input(argv[1]); //Loads the file in

	string line; //Stores each line of the .c file
	
    vector <token_and_line> token_vec; //Creates a vector to store the tokens in
    int line_number =0; //Stores the current line number
    
	if(input.is_open()){
        //Loops over all the lines in the file
		while(getline(input, line)){
            line_number ++;
            //Turns the string into a char*, this allows me to use delimiters to tokenise
		    char* line_c = new char [line.length()+1];
            strcpy(line_c, line.c_str());
            char *delimiters = " \n\t";
            char *tokenC = strtok(line_c, delimiters);
            //Loops while token is not null
            while(tokenC!=NULL){
                //Creates instance of struct
                token_and_line t;
                //Converts the char* to a C++ string (alligns with coursework spec)
                string token(tokenC);

                //Adds token to struct 
                t.token = token;
                t.line_number = line_number;
                //Pushes the struct into a vector
                token_vec.push_back(t);
                
                tokenC = strtok(NULL, delimiters);
                
                //End of token loop
            }
            delete[] line_c; //Frees memory allocated on line 215
            //End of line loop   
		}
        //Calls and prints the var_counter function
        std::cout << "The number of variables are: " << var_counter(token_vec) << endl;

        //Calls and prints the funct_counter function
        std::cout << "The number of functions are: " << func_counter(token_vec) << endl;

        //Calls and prints the if_counter function
        std::cout << "The number of if statements are: " << if_counter(token_vec) << endl;

        //Calls and prints the for_counter function
        std::cout << "The number of for loops are: " << for_counter(token_vec) << endl;

        //Calls and prints the while_counter function
        std::cout << "The number of while loops are: " << while_counter(token_vec) << endl;

        //Calls struct_into_tree_function
        struct_into_tree(token_vec);

        //Closes the input file
        input.close();
	}	
	return 0;
}