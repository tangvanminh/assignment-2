#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

enum balance_factor { LH, EH, RH };



/*
error enum
*/
enum error_type {
    tmm = 1, // type mismatch
    dbz,     // divide by zero
    sfl,     // stack full
    smt,     // stack empty
    aoor,    // array out of range
    udv      // undefined variable
};


//class localVariableSpace {
//public:
//    class Node;
//protected:
//    Node* root;
//    int count;
//public:
//    localVariableSpace() {
//        this->root = NULL;
//        count = 0;
//    }
//    //more func
//
//
//
//
//public:
//    //class Node
//    class Node {
//    private:
//        string key;
//        float value;
//        int type;
//        Node* left, * right;
//        balance_factor balance;
//        friend class localVariableSpace;
//    public:
//        Node() {
//            this->left = this->right = NULL;
//        }
//        Node(string key, float value, int type, Node* left, Node* right) {
//            this->key = key;
//            this->value = value;
//            this->type = type;
//            this->left = left;
//            this->right = right;
//            this->balance = EH;
//        }
//        Node(string key, float value, int type) {
//            this->key = key;
//            this->value = value;
//            this->type = type;
//            this->left = this->right = NULL;
//            this->balance = EH;
//        }
//        ~Node() {
//            this->key = "";
//            this->value = 0;
//            this->type = 0;
//            this->left = this->right = NULL;
//        }
//    };
//};

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarSpaceSize(LOCAL_VARIABLE_SPACE_SIZE) {}

void StackFrame::run(string filename) {
    string mode;  // name of syntax
    string data;  // temporary string type before convert into suitable type
    int idata;    // integer variable
    float fdata;  // float variable
    int line = 1; // current line (start at 1)
    int err = 0;  // type of error

    fstream readfile; // interact with input file

    readfile.open(filename, ios::in); // open file in read mode

    readfile.close();
}