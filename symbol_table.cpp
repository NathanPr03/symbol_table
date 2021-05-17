/**
 * The purpose of this program is to take a .c file and return information about each of the variables and funcitons in the file
 * Author: Nathan Pringle 
 * Last modified: 02/05/2021
 */
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/**
 * Counts the number of variables in a given .c file
 * 
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 * @return Returns the amount of variables in a given .c file
 */
int var_counter(vector <string> token_vec){
    int var_count = 0; //Counts amount of variables
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i] == "int" || token_vec[i] == "short" || token_vec[i] == "char" || token_vec[i] ==  "long"  || token_vec[i] == "float" || token_vec[i] == "double" || token_vec[i] == "struct" || token_vec[i] == "int*" || token_vec[i] == "char*" || token_vec[i] == "long*"  || token_vec[i] == "float" || token_vec[i] == "double*" || token_vec[i] == "long long*"){
            if(token_vec[i+1] == "long"){
                var_count--;
            }
            if(token_vec[i+2] == "("){
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
int func_counter(vector<string> token_vec){
    int func_count=0;
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i] == "void" ||token_vec[i] == "int" || token_vec[i] == "short" || token_vec[i] == "char" || token_vec[i] ==  "long"  || token_vec[i] == "float" || token_vec[i] == "double" || token_vec[i] == "struct" || token_vec[i] == "int*" || token_vec[i] == "char*" || token_vec[i] == "long*"  || token_vec[i] == "float" || token_vec[i] == "double*" || token_vec[i] == "long long*"){
            if(token_vec[i+2] == "("){
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
int if_counter(vector<string> token_vec){
    int if_count =0;
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i] == "if"){
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
int for_counter(vector<string> token_vec){
    int for_count =0;
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i] == "for"){
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
int while_counter(vector<string> token_vec){
    int while_count =0;
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i] == "while"){
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
    int referenced =0;

    int start_token =0;
    int end_token =0;
    string get_variable_name(){
        return variable_name;
    }
};

/**
 * Loops over all the tokens, adds the neccesary information into a struct, then adds that struct into a vector.
 * 
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 * @param argc Number of command line arguments (used for input file)
 * @param argv Command line arguments (used for input file) 
 */
vector<information> file_output(vector<string> token_vec, int argc, char **argv){
    ifstream input(argv[1]);
    ofstream output("outputFile.txt"); 

    string line;
    string last_token;
    string function_name;

    int line_number= 0;
    bool function_flag = 0;
    int token_count =0;

    information f;
    vector<information> info_vec;
    
    //Loops over every token 
    for(int i =0; i < token_vec.size(); ++i){
        if(token_vec[i] == "void" ||token_vec[i] == "int" || token_vec[i] == "short" || token_vec[i] == "char" || token_vec[i] ==  "long"  || token_vec[i] == "float" || token_vec[i] == "double" || token_vec[i] == "struct" || token_vec[i] == "int*" || token_vec[i] == "char*" || token_vec[i] == "long*"  || token_vec[i] == "float" || token_vec[i] == "double*" || token_vec[i] == "long long*"){
            //Doesnt store the variable if it = "long"
            if(token_vec[i+1] != "long"){
                f.variable_name = token_vec[i+1];
                f.start_token = i+1;
            
                //Checks for brackets which indicates its a function, if not its a variable
                if(token_vec[i+2] == "("){
                    f.func_var = "function";  
                }else {
                    f.func_var = "variable";
                }
                f.type = token_vec[i];
                if(token_vec[i+2] == "[]"){
                        f.type += " ";
                        f.type += token_vec[i+2];
                }else if(token_vec[i-1] == "long"){
                    f.type += " ";
                    f.type += token_vec[i-1];
                }
                info_vec.push_back(information(f));
            }
        } 
    }
    
    //Loops over the two vectors lookign for the start of a function which means the previous function has ended
    for(int n=0; n < info_vec.size(); ++n){ 
        for(int i =0; i < token_vec.size(); ++i){        
            if(token_vec[i] == "void" ||token_vec[i] == "int" || token_vec[i] == "short" || token_vec[i] == "char" || token_vec[i] ==  "long"  || token_vec[i] == "float" || token_vec[i] == "double" || token_vec[i] == "struct" || token_vec[i] == "int*" || token_vec[i] == "char*" || token_vec[i] == "long*"  || token_vec[i] == "float" || token_vec[i] == "double*" || token_vec[i] == "long long*"){
                if(token_vec[i+2] == "(" && i > info_vec[n].start_token){
                    info_vec[n].end_token = i +1;
                    break;
                }else{
                    info_vec[n].end_token = token_vec.size();
                }
            }
        }
    }
    
    //Gives functions the max end token as functions scope doesnt end
    for(int i=0; i<info_vec.size(); ++i){ 
        if(info_vec[i].func_var == "function"){
            info_vec[i].end_token = token_vec.size();
        }
    }
    //Loops over the info vec and the token vector (between start and end vec) and counts occurences
    for(int n=0; n < info_vec.size(); ++n){
        for(int i =info_vec[n].start_token; i < info_vec[n].end_token; ++i){
            if(token_vec[i] == info_vec[n].variable_name){
                info_vec[n].referenced ++;
            }
        }
    }

    for(int i=0; i <info_vec.size(); ++i){
        info_vec[i].referenced --;
    }


    //Loops over each line in the file again to get the line numbers of each token thats declared
    if(input.is_open()){
        while(getline(input, line)){
            line_number ++;

            //Turns the string into a char*, this allows me to use delimiters to tokenise
            char* lineC = new char [line.length()+1];
            strcpy(lineC, line.c_str());
            char *delimiters = " \n\t";
            char *tokenC = strtok(lineC, delimiters);

            //Loops while token is not null
            while(tokenC!=NULL){
                //Converts the char* to a C++ string (alligns with coursework spec)
                string token(tokenC);
                //Loops over the variable names looking for the line number it is declared on
                for(int i=0; i < info_vec.size(); ++i){
                    if(info_vec[i].variable_name == token){
                            if(last_token == "void" ||last_token == "int" || last_token == "short" || last_token == "char" || last_token ==  "long"  || last_token == "float" || last_token == "double" ||last_token == "struct" || last_token == "int*" || last_token == "char*" || last_token == "long*"  || last_token == "float" || last_token == "double*" || last_token == "long long*"){
                                if(token_count == info_vec[i].start_token){
                                    info_vec[i].line_no = line_number;
                                }
                            }
                    }
                }
                token_count ++;
                last_token = token;
                tokenC = strtok(NULL, delimiters);
            }
        }
    }
    

    //Loops over the info vec and looks for functions, sets the flag to true then adds the function name to each variable inside said function
    for(int i=0; i<info_vec.size(); ++i){
        if(info_vec[i].func_var == "function"){
            function_name = info_vec[i].variable_name;
            function_flag =1;
        }
        if(info_vec[i].variable_name == "main"){
           function_flag =0;
        }
        if(function_flag && info_vec[i].func_var != "function"){
            info_vec[i].variable_name += " (";
            info_vec[i].variable_name += function_name;
            info_vec[i].variable_name += ")";
        } 
    }

    //Prints vector to a file
    for(auto i : info_vec){
        output << i.variable_name << ", line " << i.line_no << ", " << i.func_var << ", " << i.type << ", referenced " << i.referenced << endl;
    }

    //Closes input and output file
    input.close();
    output.close();
    return info_vec;
}

int main(int argc, char **argv){
	ifstream input(argv[1]); //Loads the file in

	string line; //Stores each line of the .c file
    string last_token; //Stores the current token at the end of the token loop, this lets it act as the last token when we come back around
	
    vector <string> token_vec; //Creates a vector to store the tokens in
    
    int line_number =0; //Stores the current line number
    int test_count =0;
    information a;
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
                //Converts the char* to a C++ string (alligns with coursework spec)
                string token(tokenC);

                //Adds the tokens to a vector
                token_vec.push_back(token);
                
                tokenC = strtok(NULL, delimiters);
                //End of token loop
            }
            delete[] line_c; //Frees memory allocated on line 215

            //End of line loop   
		}
        //Calls and prints the var_counter function
        cout << "The number of variables are: " << var_counter(token_vec) << endl;

        //Calls and prints the funct_counter function
        cout << "The number of functions are: " << func_counter(token_vec) << endl;

        //Calls and prints the if_counter function
        cout << "The number of if statements are: " << if_counter(token_vec) << endl;

        //Calls and prints the for_counter function
        cout << "The number of for loops are: " << for_counter(token_vec) << endl;

        //Calls and prints the while_counter function
        cout << "The number of while loops are: " << while_counter(token_vec) << endl;

        file_output(token_vec, argc, argv);

        input.close();
	}	
	return 0;
}