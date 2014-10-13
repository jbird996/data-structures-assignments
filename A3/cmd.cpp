// ============================================================================
// cmd.cpp
// ~~~~~~~
// author : Jason Hatfield - 2916-3434
// - implement the two main commands: validate and display
// - this is the only file you can modify and submit
// ============================================================================

#include <iostream>
#include <sstream>
#include <stack>
#include <map>

#include "cmd.h"
#include "Lexer.h" // you should make use of the provided Lexer
#include "term_control.h"
#include "error_handling.h"

using namespace std;

string ss, disp, v;
bool checkValid(string);
bool dim, ul, bright;
void addMod(string), removeMod(string), reset(), colorize();
stack<term_colors_t> myColor;
stack<Token> myStack;

/**
 * -----------------------------------------------------------------------------
 *  TO BE IMPLEMENTED BY YOU
 *  check whether the given expression is well-formed and print it out
 *  - if it is NOT well-formed, return one of the three error messages:
 *     "INVALID TOKEN"
 *     "EXPRESSION NOT WELL-FORMED"
 *     "UNKNOWN TAG"
 *  - if it is well-formed, return the string to be printed, with control codes
 *    inserted properly at the right places 
 * -----------------------------------------------------------------------------
 */

string display(const string& expression) 
{
 
    reset();
    v = validate(expression);
    if(v != "VALID"){
        return v;
    }

    return disp;
}

/**
 * -----------------------------------------------------------------------------
 *  TO BE IMPLEMENTED BY YOU
 *  check whether the given expression is well-formed
 *  - if it is NOT well-formed, return one of the three error messages:
 *     "INVALID TOKEN"
 *     "EXPRESSION NOT WELL-FORMED"
 *     "UNKNOWN TAG"
 *  - if it is well-formed, return "VALID"
 * -----------------------------------------------------------------------------
 */

string validate(const string& expression)
{

    reset();
    Token tok;
    Lexer lex;

    lex.set_input(expression);

    while(lex.has_more_token()){
        tok = lex.next_token();

        switch(tok.type){

            case TAG:
                if((tok.value[0] == '/') && !myStack.empty() ){
                    ss = tok.value.substr(1);
                    if(!checkValid(ss)){
                        return "UNKNOWN TAG";
                    }
                    Token temp;
                    temp = myStack.top();
                    if(ss == temp.value){
                        removeMod(ss);
                        myStack.pop();
                    }
                }else if(checkValid(tok.value)){
                    ss = tok.value;
                    myStack.push(tok);
                    addMod(ss);
                }else if(tok.value[0] == '/' && myStack.empty()){
                    return "EXPRESSION NOT WELL FORMED";
                }else{
                    return "UNKNOWN TAG";
                }
                break;

            case IDENT:
                colorize();
                disp += tok.value;
                break;

            case BLANK:
                colorize();
                disp += " ";
                break;

            case ERRTOK:
                return "INVALID TOKEN";
                break;

            default:
                cout << "default" << endl;
                break;
            }
        }
    if(!myStack.empty()){
        return "EXPRESSION NOT WELL FORMED";
    }

    return "VALID";
}

bool checkValid(string s){
    
    if(s == "red"){
        return true;       
    }else if(s == "green"){
        return true;
    }else if(s == "yellow"){
        return true;
    }else if(s == "blue"){
        return true;
    }else if(s == "magenta"){
        return true;
    }else if(s == "cyan"){
        return true;
    }else if(s == "dim"){
        return true;
    }else if(s == "underline"){
        return true;
    }else if(s == "bright"){
        return true;
    }

    return false;

}
void addMod(string s){
    
    if(s == "red"){
        myColor.push(RED);  
    }else if(s == "green"){
        myColor.push(GREEN);
    }else if(s == "yellow"){
        myColor.push(YELLOW);
    }else if(s == "blue"){
        myColor.push(BLUE);
    }else if(s == "magenta"){
        myColor.push(MAGENTA);
    }else if(s == "cyan"){
        myColor.push(CYAN);
    }else if(s == "dim"){
        dim = true;
    }else if(s == "underline"){
        ul = true;
    }else if(s == "bright"){
        bright = true;
    }

}

void removeMod(string s){

    if(s == "red"){
        myColor.pop();
    }else if(s == "green"){
        myColor.pop();
    }else if(s == "yellow"){
        myColor.pop();
    }else if(s == "blue"){
        myColor.pop();
    }else if(s == "magenta"){
        myColor.pop();
    }else if(s == "cyan"){
        myColor.pop();
    }else if(s == "dim"){
        dim = false;
    }else if(s == "underline"){
        ul = false;
    }else if(s == "bright"){
        bright = false;
    }
}

void reset(){
    ss = "";
    disp = "";
    v = "";
    dim = false;
    ul = false;
    bright = false;

    while(!myStack.empty()){
            myStack.pop();
    }
    while(!myColor.empty()){
            myColor.pop();
    }
}

void colorize(){

    if(!myColor.empty()){
        disp += term_cc(myColor.top());     
            if(dim){
                disp += "\033[2m";
            }
            if(ul){
                disp += "\033[4m";
            }
            if(bright){
                disp += "\033[1m";
            }
    }else if(myColor.empty()){
        disp += term_cc();

            if(dim){
                disp += "\033[2m";
            }
            if(ul){
                disp += "\033[4m";
            }
            if(bright){
                disp += "\033[1m";
            }
    }else if(!myColor.empty() && !(dim || ul || bright)){
        disp += term_cc(myColor.top());
    }

}
