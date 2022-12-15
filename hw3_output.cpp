#include <iostream>
#include "hw3_output.hpp"
#include <sstream>

using namespace std;

void output::endScope(){
    cout << "---end scope---" << endl;
}

void output::printID(const string& id, int offset, const string& type) {
    cout << id << " " << type <<  " " << offset <<  endl;
}

string typeListToString(const std::vector<string>& argTypes) {
    stringstream res;
    res << "(";
    for(int i = 0; i < argTypes.size(); ++i) {
        res << argTypes[i];
        if (i + 1 < argTypes.size())
            res << ",";
    }
    res << ")";
    return res.str();
}

string valueListsToString(const std::vector<string>& values) {
    stringstream res;
    res << "{";
    for(int i = 0; i < values.size(); ++i) {
        res << values[i];
        if (i + 1 < values.size())
            res << ",";
    }
    res << "}";
    return res.str();
}

string output::makeFunctionType(const string& retType, std::vector<string>& argTypes) {
    stringstream res;
    res << typeListToString(argTypes) << "->" << retType;
    return res.str();
}

void output::errorLex(int lineno){
    cout << "line " << lineno << ":" << " lexical error" << endl;
}

void output::errorSyn(int lineno){
    cout << "line " << lineno << ":" << " syntax error" << endl;
}

void output::errorUndef(int lineno, const string& id){
    cout << "line " << lineno << ":" << " variable " << id << " is not defined" << endl;
}

void output::errorDef(int lineno, const string& id){
    cout << "line " << lineno << ":" << " identifier " << id << " is already defined" << endl;
}

void output::errorUndefFunc(int lineno, const string& id) {
    cout << "line " << lineno << ":" << " function " << id << " is not defined" << endl;
}

void output::errorMismatch(int lineno){
    cout << "line " << lineno << ":" << " type mismatch" << endl;
}

void output::errorPrototypeMismatch(int lineno, const string& id, std::vector<string>& argTypes) {
    cout << "line " << lineno << ": prototype mismatch, function " << id << " expects arguments " << typeListToString(argTypes) << endl;
}

void output::errorUnexpectedBreak(int lineno) {
    cout << "line " << lineno << ":" << " unexpected break statement" << endl;
}

void output::errorUnexpectedContinue(int lineno) {
    cout << "line " << lineno << ":" << " unexpected continue statement" << endl;	
}

void output::errorMainMissing() {
    cout << "Program has no 'void main()' function" << endl;
}

void output::errorByteTooLarge(int lineno, const string& value) {
    cout << "line " << lineno << ": byte value " << value << " out of range" << endl;
}


/// ############################################################################## ///
/// ############################    Node_ExpList    ############################///
/// ############################################################################## ///

Node_ExpList::Node_ExpList(std::shared_ptr<Node_Exp> exp) : Generic_Node({exp}){
    exp_list.clear();
    exp_list.push_back(exp->type);
}

Node_ExpList::Node_ExpList(std::shared_ptr<Node_Exp> node_exp, std::shared_ptr<Node_Token> node_token,
                           std::shared_ptr<Node_ExpList> node_expList): Generic_Node({node_exp, node_token, node_expList}) {
    exp_list = node_expList->exp_list;
    exp_list.insert(exp_list.begin(), node_exp->type);
}


/// ############################################################################## ///
/// ############################    Node_FormalDecl    ############################///
/// ############################################################################## ///

Node_FormalDecl::Node_FormalDecl(std::shared_ptr<Node_Exp_Type> node_type, std::shared_ptr<Node_Token> node_token_id)
                : Generic_Node({node_type, node_token_id}), id_symbol(node_type->type, node_token_id->value){
    if (frame_manager.find(id_symbol.name) != nullptr){
        output::errorDef(yylineno, id_symbol.name);
        exit(0);
    }
}


/// ############################################################################## ///
/// ############################    Node_FormalsList    ############################///
/// ############################################################################## ///

Node_FormalsList::Node_FormalsList(std::shared_ptr<Node_FormalDecl> node_formalDecl): Generic_Node({node_formalDecl}) {
    parameter_list.emplace_back(node_formalDecl->id_symbol);
}

Node_FormalsList::Node_FormalsList(std::shared_ptr<Node_FormalDecl> node_formalDecl,
                                   std::shared_ptr<Node_Token> node_comma, std::shared_ptr<Node_FormalsList> node_formalsList)
                                   : Generic_Node({node_formalDecl, node_comma, node_formalsList}) {
    parameter_list = node_formalsList->parameter_list;
    parameter_list.insert(parameter_list.begin(), node_formalDecl->id_symbol);
}

/// ############################################################################## ///
/// ############################    Node_Call    ############################///
/// ############################################################################## ///

Node_Call::Node_Call(std::shared_ptr<Node_Token> node_id, std::shared_ptr<Node_Token> node_lparen,
                     std::shared_ptr<Node_ExpList> node_expList, std::shared_ptr<Node_Token> node_rparen)
                     : Generic_Node({node_id, node_lparen, node_expList, node_rparen}), func_id(Symbol::invalidSymbol()){
    // check if func declared
    auto id_entry = frame_manager.find(node_id->value);
    if (id_entry == nullptr || id_entry->entry_type != DeclType::FUNC){
        throw UndDefFuncExc(yylineno, node_id->value);
    }
    func_id = Symbol(id_entry->symbol.type, id_entry->symbol.name);
    func_parameters = node_expList->exp_list;
    // check if func prototype matches func call
    auto func_entry = std::dynamic_pointer_cast<symTableEntryFunc>(id_entry);
    if (func_entry->parameter_list.size() != func_parameters.size()){
        throw PrototypeMismatchExc(yylineno, func_id.name, func_parameters);
    }
    for (int index = 0; index < func_entry->parameter_list.size(); index++){
        if (!valid_cast(func_entry->parameter_list[index].type, func_parameters[index])){
            throw PrototypeMismatchExc(yylineno, func_id.name, func_parameters);
        }
    }
    
}




/// ############################################################################## ///
/// ############################    Node_Statement    ############################///
/// ############################################################################## ///








