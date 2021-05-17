/**
 * Header file, for BST library
 * Author: Nathan Pringle
 * Last modified: 29/04/2021
 */
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/**
 * Node struct that holds the variables from the information struct
 */  
struct node{
    public:

    node(); //Default constructor
    ~node(); //Default destructor

    //The left branch of the root
    node *left;

    //The right branch of the root
    node *right;

    //Getters to get the information inside a node of the BST
    string get_variable_name(); //Returns the variable name
    int get_line_no(); //Returns the line number
    string get_func_var(); //Returns whether the identifier is a variable, or a function
    string get_type(); //Returns the type (int, char etc)
    int get_referenced(); //Returns how many times it was referenced 
    int get_start_token(); //Returns the token index where the variable enters scope
    int get_end_token(); //Returns the token index where the variable exits scope

    
    //Setters to set the information inside a node of the BST
    void set_variable_name(string variable_name_set); //Sets the variable name
    void set_line_no(int line_no_set); //Sets the line number
    void set_func_var(string func_var_set); //Sets func_var
    void set_type(string type_set); //Sets the type
    void set_referenced(int referenced_set); //Sets the amount of times its referenced
    void set_start_token(int start_token_set); //Sets the token index where the variable enters scope
    void set_end_token(int end_token_set); //Sets the token index where the variable exits scope

    private:

    string variable_name;
    int line_no=0;
    string func_var;
    string type;
    int referenced =0;
    int start_token;
    int end_token;
};

//Struct that stores a token, and the line number where the token is declared
struct token_and_line{
        string token;
        int line_number;
};

//BST class
class BST {
    private: 
    node* root;

    public:
    
    BST(); //Default construcor
    ~BST(); //Default destructor

    //Calls a helper method to insert a value into the tree
    void insert(string variable_name_main, int line_no_main, string func_var_main, string type_main, int referenced_main, int start_token_main, int end_token_main);

    //Inserts a value into the tree 
    void insert_helper(node **root, string variable_name_main, int line_no_main, string func_var_main, string type_main, int referenced_main, int start_token_main, int end_token_main);

    //Calls a helper function to print the tree in order 
    void print_tree(ostream& output);

    //Prints the tree in order 
    void print_tree_helper(node* root, ostream& output);

    //Calls a helper method to delete the tree
    void delete_tree();

    //Deletes the tree
    void delete_tree_helper(node *root);

    //Calls a helper function to update the tree with the amount of times a variable has been referenced
    void update(vector <token_and_line> token_vec);

    //Updates the tree wiht the amount of times a variable has been referenced
    void update_helper(node *root, vector <token_and_line> token_vec);
};