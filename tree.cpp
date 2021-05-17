/** 
 * Implementation for BST library
 * Author: Nathan Pringle
 * Last modified: 02/05/2021
 */ 
#include "tree.h"
#include <iostream>
#include <string>
using namespace std;

/** 
 * Node struct
 * Function implementations
 */

//Default constructor for node struct
node::node(){
    this->variable_name = variable_name;
    this->line_no = line_no;
    this->func_var = func_var;
    this->type = type;
    this->referenced =referenced;
    this->start_token=start_token;
    this->end_token=end_token;
}

//Default destructor for node struct
node::~node(){

}

/**
 * Returns the variable name for a specified node struct
 * @returns variable_name the variable name
 */
string node::get_variable_name(){
    return variable_name;
}

/**
 * Returns the line number for a specified node struct
 * @returns line_no the line number
 */
int node::get_line_no(){
    return line_no;
}

/**
 * Returns whether the identifier is a variable or a function for a specified node struct
 * @returns func_var the category of the identifer variable
 */
string node::get_func_var(){
    return func_var;
}

/**
 * Returns the type of variable, or the return type of a functon for a specified node struct
 * @return type the type or return type
 */
string node::get_type(){
    return type;
}

/**
 * Retuns the amount of times a variable, or function was referenced for a specified node struct 
 * @return referenced the amount of references
 */
int node::get_referenced(){
    return referenced;
}

/** 
 * Returns the token index where a variable or function enters scope for a specified node struct
 * @return start_token the start of scope
 */ 
int node::get_start_token(){
    return start_token;
}

/**
 * Returns the token index where a variable or function exits scope for a specified node struct
 * @return end_token the end of scope
 */
int node::get_end_token(){
    return end_token;
}

/**
 * Sets the variable name for a specified node struct
 * @param variable_name_set The variable name passed in from the struct in the call to insert() in main
 */
void node::set_variable_name(string variable_name_set){
    variable_name = variable_name_set;
}

/**
 * Sets the line number for a specified node struct
 * @param line_no_set The line number passed in from the struct in the call to insert() in main
 */
void node::set_line_no(int line_no_set){
    line_no = line_no_set;
}

/**
 * Sets the identifier category for a specified node struct
 * @param func_var_set The identifier category passed in from the struct in the call to insert() in main
 */
void node::set_func_var(string func_var_set){
    func_var = func_var_set;
}

/**
 * Sets the type of variable or return type of function for a specified node struct
 * @param type_set The type passed in from the struct in the call to insert() in main
 */
void node::set_type(string type_set){
    type = type_set;
}

/**
 * Sets the number of references for a specified node struct
 * @param referenced_set The number of references passed in from the struct in the call to insert() in main
 */
void node::set_referenced(int referenced_set){
    referenced = referenced_set;
}

/**
 * Sets the token index where a variable or function enters scope for a specified node struct
 * @param start_token_set The token index where a variale or function enters scope passed in from the struct in the call to insert() in main
 */
void node::set_start_token(int start_token_set){
    start_token = start_token_set;
}

/**
 * Sets the token index where a variable or function enters scope for a specified node struct
 * @param end_token_set The token index where a variale or function exits scope passed in from the struct in the call to insert() in main
 */
void node::set_end_token(int end_token_set){
    end_token = end_token_set;
}

/** 
 * BST class
 * Function implementations
 */

/**
 * Default constructor for BST class
 * Sets the root node
 */
BST::BST(){
    root = nullptr;
}

/**
 * Default destructor for BST class
 * Calls the delete_tree() method to free up allocated memory 
 */
BST::~BST(){
    delete_tree();
}

/**
 * Calls a helper function to insert a node into the tree
 * @param variable_name_main
 * @param line_no_main
 * @param func_var_main
 * @param type_main
 * @param referenced_main
 * @param start_token_main
 * @param end_token_main
 */
void BST::insert(string variable_name_main, int line_no_main, string func_var_main, string type_main, int referenced_main, int start_token_main, int end_token_main){
    insert_helper(&root, variable_name_main, line_no_main, func_var_main, type_main, referenced_main, start_token_main, end_token_main);
}
/**
 * Inserts a node into the tree
 * @param root The root of the tree
 * @param variable_name_main The variable name passed in from main
 * @param line_no_main The line number passed in from main
 * @param func_var_main The identifier category passed in from main
 * @param type_main The type passed in from main
 * @param referenced_main The amount of references passed in from main
 * @param start_token_main The index of the start of scope passed in from main
 * @param end_token_main The index of the end of scope passd in from main
 */
void BST::insert_helper(node **root, string variable_name_main, int line_no_main, string func_var_main, string type_main, int referenced_main, int start_token_main, int end_token_main){
    if(*root == nullptr){
        //Create new node
        *root = new node();
        //Set new values
        (*root)->set_variable_name(variable_name_main);
        (*root)->set_line_no(line_no_main);
        (*root)->set_func_var(func_var_main);
        (*root)->set_type(type_main);
        (*root)->set_referenced(referenced_main);
        (*root)->set_start_token(start_token_main);
        (*root)->set_end_token(end_token_main);
        //Set branches to nullptr
        (*root)->left = nullptr;
        (*root)->right = nullptr;
    }else{
        if(variable_name_main.compare((*root)->get_variable_name()) == -1){
            insert_helper(&(*root)->left, variable_name_main, line_no_main, func_var_main, type_main, referenced_main, start_token_main, end_token_main);
        }else if(variable_name_main.compare((*root)->get_variable_name())==1){
            insert_helper(&(*root)->right, variable_name_main, line_no_main, func_var_main, type_main, referenced_main, start_token_main, end_token_main);
        }else
            return;
    }
}

/***
 * Calls a helper function to print the tree in order
 * @param output The designated ouput file
 */
void BST::print_tree(ostream& output){
    print_tree_helper(root, output);
}

/**
 * Prints the tree in order
 * @param root The root node of the tree
 * @param output The designated output file
 */
void BST::print_tree_helper(node* root, ostream& output){
    if(root == nullptr){
        return;
    }
        print_tree_helper(root->left, output);
        output << root->get_variable_name() << ", line " << root->get_line_no() << ", " << root->get_func_var() << ", " << root->get_type() << ", referenced " << root->get_referenced() << endl;
        print_tree_helper(root->right, output);  
}

/**
 * Calls a helper method to delete the tree
 */
void BST::delete_tree(){
    delete_tree_helper(root);
}

/**
 * Deletes the tree
 * @param root The root of the tree
 */
void BST::delete_tree_helper(node *root){
    if (root == nullptr){
        return;
    }
    //Delete the left then right branches
    delete_tree_helper(root->left);
    delete_tree_helper(root->right);
    delete root;
}

/**
 * Calls a helper function to update the tree with the amount of times a variable has been referenced
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 */
void BST::update(vector <token_and_line> token_vec){
    update_helper(root, token_vec);
}

/**
 * Updates the tree with the amount of times a variable has been referenced
 * @param root The root node of the tree
 * @param token_vec Contains all the tokens (each line split by space, newline or tab)
 */
void BST::update_helper(node *root, vector <token_and_line> token_vec){
    string erase_this = "(";
    if(root != nullptr){
        update_helper(root->left, token_vec);

        //Removes the brackets and whats in-between them, to check for references
        string lets_erase = root->get_variable_name();
        size_t found = 0;
        found = lets_erase.find(erase_this);
        if(found >0 && found < lets_erase.length()){
            lets_erase.erase(found, lets_erase.length());
        }
        for(int i=root->get_start_token(); i<root->get_end_token(); i++){
            if(token_vec[i].token == lets_erase){
                int referenced = root->get_referenced();
                referenced++;
                root->set_referenced(referenced);
            }
        }
        update_helper(root->right, token_vec);
    }
}