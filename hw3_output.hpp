
#ifndef _236360_3_
#define _236360_3_

#include <string>

#include <vector>
#include <memory>
#include <map>
#include <ostream>
#include "iostream"

static std::ostream& Log(){
    return std::cout;
}

//using namespace std;
extern int yylineno;

namespace output{
    extern const std::string rules[];
    void endScope();
    void printID(const std::string& id, int offset, const std::string& type);

    /* Do not save the string returned from this function in a data structure
        as it is not dynamically allocated and will be destroyed(!) at the end of the calling scope.
    */
    std::string makeFunctionType(const std::string& retType, std::vector<std::string>& argTypes);

    void errorLex(int lineno);
    void errorSyn(int lineno);
    void errorUndef(int lineno, const std::string& id);
    void errorDef(int lineno, const std::string& id);
    void errorUndefFunc(int lineno, const std::string& id);
    void errorMismatch(int lineno);
    void errorPrototypeMismatch(int lineno, const std::string& id, std::vector<std::string>& argTypes);
    void errorUnexpectedBreak(int lineno);
    void errorUnexpectedContinue(int lineno);
    void errorMainMissing();
    void errorByteTooLarge(int lineno, const std::string& value);
    void printProductionRule(const int ruleno);
}


enum class Type {
    INVALID = 0, INT, BYTE, BOOL, STRING, VOID, TOKEN
};
enum class DeclType {
    INVALID = 0, VAR, FUNC
};
enum class FrameType {
    FUNC, LOOP, BLOCK, IF_ELSE
};
static std::vector<std::string> TypeToSTRVec = {"INVALID", "INT", "BYTE", "BOOL", "STRING", "VOID", "TOKEN"};
static std::string TypeToSTR(Type type){
    return TypeToSTRVec.at(static_cast<unsigned long>(type));
}
static std::vector<std::string> typeToStrVector(std::vector<Type> vec){
    std::vector<std::string> str_vec;
    for (auto iter = vec.begin(); iter != vec.end(); iter++){
        str_vec.push_back(TypeToSTR(*iter));
    }
    return str_vec;
}

class AppaException : public std::exception {
public:
    long lineno;
    
    AppaException(long line_number) : std::exception() {
        lineno = line_number;
    }
    /*
    const char* what() const noexcept override{
            
            return "A game related error has occurred: IllegalArgument";
    }*/
};

class Lexception : public AppaException {
public:
    Lexception(long lineno) : AppaException(lineno) {};
};

class SynExc : public AppaException {
public:
    SynExc(long lineno) : AppaException(lineno) {};
};

class UndefExc : public AppaException {
public:
    UndefExc(long lineno, std::string &id) : AppaException(lineno) {};
};

class DefExc : public AppaException {
public:
    DefExc(long lineno, std::string &id) : AppaException(lineno) {};
};

class UndDefFuncExc : public AppaException {
public:
    UndDefFuncExc(long lineno, std::string &id) : AppaException(lineno) {};
};

class MismatchExc : public AppaException {
public:
    MismatchExc(long lineno) : AppaException(lineno) {};
};

class PrototypeMismatchExc : public AppaException {
public:
    PrototypeMismatchExc(long lineno, std::string id, std::vector<Type> param_types) : AppaException(lineno) {};
};

class UnexpectedBreakExc : public AppaException {
public:
    UnexpectedBreakExc(long lineno) : AppaException(lineno) {};
};

class UnexpectedContinueExc : public AppaException {
public:
    UnexpectedContinueExc(long lineno) : AppaException(lineno) {};
};

class MainMissingExc : public AppaException {
public:
    MainMissingExc(long lineno) : AppaException(lineno) {};
};

class ByteTooLargeExc : public AppaException {
public:
    ByteTooLargeExc(long lineno) : AppaException(lineno) {};
};

class Generic_Node;
class symTableEntry;
class StackEntry;
class Frame_class;
class Node_FormalDecl;
class Node_Exp_Type;
class Node_Statement;

typedef Generic_Node* Node;
typedef std::vector<Node> NodeVector;
typedef std::shared_ptr<symTableEntry> SymEntry;
typedef std::map<std::string, SymEntry> dict;
typedef std::vector<StackEntry> frame;

class Symbol {
public:
    Type type;
    std::string name;
    
    Symbol(Type sym_type, std::string sym_name) : type(sym_type), name(sym_name) {
    }
    
    Symbol(Symbol &) = default;
    
    Symbol(Symbol const &) = default;
    
    Symbol &operator=(Symbol const &sym) = default;
    
    static Symbol invalidSymbol() {
        return Symbol(Type::INVALID, "");
    }
};


class symTableEntry {
public:
    //std::string name;
    Symbol symbol;
    DeclType entry_type;
    long offset;
    bool valid;
    
    symTableEntry(Symbol sym, DeclType entry_type, long entry_offset, bool entry_valid = true) : symbol(sym) {
        this->entry_type = entry_type;
        offset = entry_offset;
        valid = entry_valid;
    }
    
    ~symTableEntry() = default;
    
    symTableEntry(symTableEntry &entry) = default;
    
    virtual void print() const=0;
    
    friend std::ostream &operator<<(std::ostream &os, const symTableEntry &entry) {
        entry.print();
        return os;
    };
};

class symTableEntryID : public symTableEntry {
public:
    
    symTableEntryID(Symbol sym, DeclType entry_type, long entry_offset) : symTableEntry(sym, entry_type,
                                                                                        entry_offset, true) {
        
    }
    ~symTableEntryID() = default;
    symTableEntryID(symTableEntryID &entry) = default;
    
    void print() const override;
    
};

class symTableEntryFunc : public symTableEntry {
public:
    std::vector<Symbol> parameter_list;
    
    symTableEntryFunc(Symbol sym, DeclType entry_type, long entry_offset, std::vector<Symbol> func_params)
            : symTableEntry(sym, entry_type, entry_offset, true) {
        parameter_list = func_params;
    }
    ~symTableEntryFunc() = default;
    symTableEntryFunc(symTableEntryFunc &entry) = default;
    
    std::vector<Type> paramsToTypeVec() const{
        std::vector<Type> type_vec;
        for (auto iter = parameter_list.begin(); iter != parameter_list.end(); iter++){
            type_vec.push_back(iter->type);
        }
        return type_vec;
    }
    
    void print() const override;
};

class StackEntry {
public:
    long next_offset;
    FrameType frame_type;
    SymEntry scope_func_entry;
    bool inside_loop;
    dict entries;
    std::vector<SymEntry> entries_vector;
    
    
    StackEntry(FrameType frame_type, bool in_loop, SymEntry &scope_func) {
        this->frame_type = frame_type;
        inside_loop = in_loop;
        scope_func_entry = scope_func;
    };
    
    ~StackEntry() = default;
    StackEntry(StackEntry &) = default;
    StackEntry(StackEntry const&) = default;
    
    void newIdEntry(Symbol sym) {
        auto entry = std::make_shared<symTableEntryID>(sym, DeclType::VAR, next_offset);
        next_offset++;
        
        entries.insert({entry->symbol.name, entry});
        entries_vector.push_back(entry);
        entry->print();
    }
    void newFuncEntry(Symbol sym, std::vector<Symbol> func_params) {
        auto entry = std::make_shared<symTableEntryFunc>(sym, DeclType::FUNC, next_offset, func_params);
        next_offset++;
        
        entries.insert({entry->symbol.name, entry});
        entries_vector.push_back(entry);
        entry->print();
    }
    
    SymEntry find(std::string name) {
        auto search = entries.find(name);
        if (search == entries.end()) {
            return nullptr;
        }
        return search->second;
    }
    void removeEntry(std::string name) {
        auto search = entries.find(name);
        if (search == entries.end()) {
            return;
        }
        entries.extract(search);
    }
    
    friend std::ostream &operator<<(std::ostream &os, const StackEntry &frame) {
        output::endScope();
        for (auto iter = frame.entries_vector.begin(); iter != frame.entries_vector.end(); iter++) {
            os << iter->get();
        }
        return os;
    }
    
    
};

class Frame_class {
public:
    frame frames;
    
    Frame_class() {
        Symbol sym(Type::INVALID, "Global");
        SymEntry a = std::make_shared<symTableEntryID>(sym, DeclType::INVALID, 0);
        frames.emplace_back(FrameType::BLOCK, false, a);
        Log() << "Frame_class::Constructor Done" << std::endl;
    };
    ~Frame_class() = default;
    Frame_class(Frame_class &) = delete;
    
    static Frame_class &getInstance();
    
    
    void newEntry(DeclType entry_type, std::string name, Type id_type) {
        SymEntry entry = find(name);
        if (entry->valid) {
            output::errorDef(yylineno, name);
            exit(0);
        }
        frames.back().newIdEntry(Symbol(id_type, name));
    }
    void newEntry(DeclType entry_type, std::string name, Type ret_type, std::vector<Symbol> func_params) {
        SymEntry entry = find(name);
        if (entry->valid) {
            output::errorDef(yylineno, name);
            exit(0);
        }
        frames.back().newFuncEntry(Symbol(ret_type, name), func_params);
    }
    void newFrame(FrameType frame_type) {
        auto &curr_frame = frames.back();
        bool in_loop = (frame_type == FrameType::LOOP) || curr_frame.inside_loop;
        frames.emplace_back(frame_type, in_loop, curr_frame.scope_func_entry);
    }
    void newFrame(FrameType frame_type, std::string scope_func) {
        assert(frame_type == FrameType::FUNC);
        SymEntry func_entry = find(scope_func);
        assert(func_entry != nullptr);
        frames.emplace_back(frame_type, false, func_entry);
    }
    SymEntry find(std::string name) {
        for (auto iter = frames.rbegin(); iter != frames.rend(); ++iter) {
            SymEntry entry = iter->find(name);
            if (entry->valid) {
                return entry;
            }
        }
        return nullptr;
    }
    
    void closeFrame(){
        std::cout << frames.back();
        frames.pop_back();
    }
    
    void removeEntryFromCurrentScope(std::string name) {
        auto &scope = frames.back();
        scope.removeEntry(name);
    }
    bool inLoop() {
        return frames.back().inside_loop;
    }
    Type scopeRetType() {
        return frames.back().scope_func_entry->symbol.type;
    }
};


class Generic_Node {
    long node_tree_index;
public:
    Node parent;
    NodeVector children;

/////////// Methods ///////////
    
    Generic_Node(NodeVector children) {
        //initNodes();
        setChildren(children);
    }
    
    ~Generic_Node() = default;
    Generic_Node(Generic_Node &) = delete;
    
    void setChildren(NodeVector vector) {
        for (int index = 0; index < vector.size(); index++) {
            children.push_back(vector[index]);
            children[index]->setParent(this);
        }
    }
    void setParent(Node parent) {
        this->parent = parent;
    }
    
    virtual void stam() {};
    
};

class Node_Token : public Generic_Node {
public:
    std::string value;

/////////// Methods ///////////
    
    Node_Token(std::string token_value) : Generic_Node({}) {
        value = token_value;
        Log() << "Node_Token:: " << token_value << std::endl;
    }
    
    ~Node_Token() = default;
    
    Node_Token(Node_Token &) = delete;
};

class Node_RetType : public Generic_Node {
public:
    Type type;

/////////// Methods ///////////
    
    Node_RetType(NodeVector children, Type ret_type) : Generic_Node(children) {
        type = ret_type;
    }
    
    ~Node_RetType() = default;
    
    Node_RetType(Node_RetType &) = delete;
    
    void set_type(Type new_type) {
        type = new_type;
    };
};

class Node_FormalDecl : public Generic_Node {
public:
    //Type param_type;
    Symbol id_symbol;
/////////// Methods ///////////
    
    Node_FormalDecl(Node_Exp_Type * node_type, Node_Token * node_token_id);
    
    ~Node_FormalDecl() = default;
    
    Node_FormalDecl(Node_FormalDecl &) = delete;
};

class Node_FormalsList : public Generic_Node {
public:
    std::vector<Symbol> parameter_list;
    
    /// std::vector<std::pair<Type, std::string>> parameter_list;
/////////// Methods ///////////
    Node_FormalsList(Node_FormalDecl * node_formalDecl);
    
    Node_FormalsList(Node_FormalDecl * node_formalDecl, Node_Token * node_comma,
                     Node_FormalsList * node_formalsList);
    
    ~Node_FormalsList() = default;
    
    Node_FormalsList(Node_FormalsList &) = delete;
};

class Node_FuncDecl : public Generic_Node {
public:
/////////// Methods ///////////
    
    Node_FuncDecl(Node_Exp_Type * node_retType, Node_Token * node_id, Node_Token * node_lparen,
                  Node_FormalsList * node_formals, Node_Token * node_rparen,
                  Node_Token * node_lbrace,
                  Node_Statement * node_statement, Node_Token * node_rbrace);
    
    ~Node_FuncDecl() = default;
    
    Node_FuncDecl(Node_FuncDecl &) = delete;
    
};

class Node_FuncsList : public Generic_Node {
public:
    //std::vector<Node_FuncDecl> funcs_list;
/////////// Methods ///////////
    
    Node_FuncsList(NodeVector children);
    
    ~Node_FuncsList() = default;
    
    Node_FuncsList(Node_FuncsList &) = delete;
    
};

class Node_Statement : public Generic_Node {
public:

/////////// Methods ///////////
    Node_Statement(NodeVector children);
    
    ~Node_Statement() = default;
    
    Node_Statement(Node_Statement &) = delete;
    
    
};

class Node_StatementList : public Generic_Node {
public:
    //std::vector<Node_Statement> statement_list;
/////////// Methods ///////////
    Node_StatementList(NodeVector children);
    
    ~Node_StatementList() = default;
    
    Node_StatementList(Node_StatementList &) = delete;
};

class Node_Exp : public Generic_Node {
public:
    Type type;

/////////// Methods ///////////
    Node_Exp(NodeVector children, Type exp_type) : Generic_Node(children) {
        type = exp_type;
    }
    
    ~Node_Exp() = default;
    
    Node_Exp(Node_Exp &) = delete;
    
    void set_type(Type exp_type){
        type = exp_type;
    }
    
    bool typeCheck(std::vector<Type> type_list){
        for (auto iter = type_list.begin(); iter != type_list.end(); iter++){
            if (type == *iter){
                return true;
            }
        }
        return false;
    }
};

class Node_ExpList : public Generic_Node {
public:
    std::vector<Type> exp_list;
/////////// Methods ///////////
    
    Node_ExpList(Node_Exp * exp);
    
    Node_ExpList(Node_Exp * node_exp, Node_Token * node_token, Node_ExpList * node_expList);
    
    ~Node_ExpList() = default;
    
    Node_ExpList(Node_ExpList &) = delete;
    
    
};

class Node_Call : public Generic_Node {
public:
    Symbol func_id;
    std::vector<Type> func_parameters;
/////////// Methods ///////////
    
    Node_Call(Node_Token * node_id, Node_Token * node_lparen, Node_ExpList * node_expList,
              Node_Token * node_rparen);
    
    ~Node_Call() = default;
    
    Node_Call(Node_Call &) = delete;
};

class Node_Exp_Type : public Node_Exp {
public:
    Node_Exp_Type(NodeVector children, Type exp_type) : Node_Exp(children, exp_type) {
    
    }
    
    ~Node_Exp_Type() = default;
    
    Node_Exp_Type(Node_Exp_Type &) = delete;;
    
    
};

class Node_Exp_NUM : public Node_Exp {
public:
/////////// Methods ///////////
    
    Node_Exp_NUM(NodeVector children, Type exp_type) : Node_Exp(children, exp_type) {
        if (type == Type::BYTE) {
            long token_val = std::atoi(((Node_Token*)(children[0]))->value.c_str());
            
            if (token_val > 255) {
                throw ByteTooLargeExc(yylineno);
            }
        }
        
    }
    
    ~Node_Exp_NUM() = default;
    
    Node_Exp_NUM(Node_Exp_NUM &) = delete;
};

class Node_Exp_Binop : public Node_Exp {
public:
/////////// Methods ///////////
    
    Node_Exp_Binop(NodeVector children) : Node_Exp(children, Type::INT) {
        //Todo: if bool, update type
        auto exp1 = (Node_Exp*)(children[0]);
        auto binop = (Node_Token*)(children[1]);
        auto exp2 = (Node_Exp*)(children[2]);
        
        if (!exp1->typeCheck({Type::INT, Type::BYTE}) || !exp2->typeCheck({Type::INT, Type::BYTE})) {
            throw MismatchExc(yylineno);
        }
        if (exp1->type == Type::BYTE && exp2->type == Type::BYTE) {
            set_type(Type::BYTE);
        }
        
    }
    
    ~Node_Exp_Binop() = default;
    
    Node_Exp_Binop(Node_Exp_NUM &) = delete;
};

class Node_Exp_Relop : public Node_Exp {
public:
/////////// Methods ///////////
    
    Node_Exp_Relop(NodeVector children) : Node_Exp(children, Type::BOOL) {
        auto exp1 = (Node_Exp*)(children[0]);
        auto binop = (Node_Token*)(children[1]);
        auto exp2 = (Node_Exp*)(children[2]);
        
        if (!exp1->typeCheck({Type::INT, Type::BYTE}) || !exp2->typeCheck({Type::INT, Type::BYTE})) {
            throw MismatchExc(yylineno);
        }
        
    }
    
    ~Node_Exp_Relop() = default;
    
    Node_Exp_Relop(Node_Exp_Relop &) = delete;
};

class Node_Exp_Cast : public Node_Exp {
public:
/////////// Methods ///////////
    
    Node_Exp_Cast(NodeVector children) : Node_Exp(children, Type::INT) {
        //Todo: if bool, update type
        auto type_node = (Node_Exp_Type*)(children[1]);
        auto exp = (Node_Exp*)(children[3]);
        
        if (!type_node->typeCheck({Type::INT, Type::BYTE}) || !exp->typeCheck({Type::INT, Type::BYTE})) {
            throw MismatchExc(yylineno);
        }
        
        set_type(type_node->type);
    }
    
    ~Node_Exp_Cast() = default;
    
    Node_Exp_Cast(Node_Exp_Relop &) = delete;
};

class Node_Exp_Str : public Node_Exp {
public:
/////////// Methods ///////////
    
    Node_Exp_Str(NodeVector children) : Node_Exp(children, Type::STRING) {
    
    }
    
    ~Node_Exp_Str() = default;
    
    Node_Exp_Str(Node_Exp_Str &) = delete;
};

class Node_Exp_Bool : public Node_Exp {
public:
/////////// Methods ///////////
    
    Node_Exp_Bool(NodeVector children) : Node_Exp(children, Type::BOOL) {
    
    }
    
    ~Node_Exp_Bool() = default;
    
    Node_Exp_Bool(Node_Exp_Bool &) = delete;
};

class Node_Exp_ID : public Node_Exp {
public:
    Symbol id;
    
    Node_Exp_ID(Node_Token* node_token);
    ~Node_Exp_ID() = default;
    Node_Exp_ID(Node_Exp_ID &) = delete;
    
};

class Node_Exp_Call : public Node_Exp {
public:
    
    Node_Exp_Call(NodeVector children) : Node_Exp(children, Type::INVALID) {
        ///TODO: check validity and update frame stack
        auto node_call = (Node_Call*)(children[0]);
        //auto func_entry = (frame_manager.find(node_call->func_id.name));
        //assert(func_entry->valid);
        
        set_type(node_call->func_id.type);
    }
    
    ~Node_Exp_Call() = default;
    
    Node_Exp_Call(Node_Exp_Call &) = delete;;
    
};

class Node_Exp_IfElse : public Node_Exp {
public:
    
    Node_Exp_IfElse(NodeVector children) : Node_Exp(children, Type::INVALID) {
        ///TODO: check validity and update frame stack
        auto exp1 = (Node_Exp*)(children[0]);
        auto exp2 = (Node_Exp*)(children[3]);
        auto exp3 = (Node_Exp*)(children[6]);
        
        if (!exp2->typeCheck({Type::BOOL})) {
            throw MismatchExc(yylineno);
        }
        
        if (exp1->type != exp3->type) {
            if (exp1->typeCheck({Type::INT}) && exp3->typeCheck({Type::BYTE})) {
                set_type(Type::INT);
            }
            else if (exp1->typeCheck({Type::BYTE}) && exp3->typeCheck({Type::INT})) {
                set_type(Type::INT);
            }
            else {
                throw MismatchExc(yylineno);
            }
        }
        else {
            set_type(exp1->type);
        }
        
        
    }
    
    ~Node_Exp_IfElse() = default;
    
    Node_Exp_IfElse(Node_Exp_IfElse &) = delete;;
    
};

class Node_Statement_Block : public Node_Statement {
public:
/////////// Methods ///////////
    Node_Statement_Block(NodeVector children);
    
    ~Node_Statement_Block() = default;
    
    Node_Statement_Block(Node_Statement_Block &) = delete;
    
};

class Node_Statement_ID_Decl : public Node_Statement {
public:

/////////// Methods ///////////
    Node_Statement_ID_Decl(Node_Exp *node_type, Node_Token * node_token,
                           Node_Token * node_sc);
    
    Node_Statement_ID_Decl(Node_Exp * node_type, Node_Token * node_token,
                           Node_Token * node_assign,
                           Node_Exp * node_exp, Node_Token * node_sc);
    
    ~Node_Statement_ID_Decl() = default;
    
    Node_Statement_ID_Decl(Node_Statement_ID_Decl &) = delete;
    
};

class Node_Statement_ID_Assign : public Node_Statement {
public:

/////////// Methods ///////////
    Node_Statement_ID_Assign(Node_Token * node_id, Node_Token * node_assign, Node_Exp * node_exp,
                             Node_Token * node_sc);
    
    ~Node_Statement_ID_Assign() = default;
    
    Node_Statement_ID_Assign(Node_Statement_ID_Assign &) = delete;
    
};

class Node_Statement_Call : public Node_Statement {
public:

/////////// Methods ///////////
    Node_Statement_Call(Node_Call * node_call, Node_Token * node_sc);
    
    ~Node_Statement_Call() = default;
    
    Node_Statement_Call(Node_Statement_Call &) = delete;
    
};

class Node_Statement_Ret : public Node_Statement {
public:
/////////// Methods ///////////
    Node_Statement_Ret(Node_Token * node_ret, Node_Token * node_sc);
    
    Node_Statement_Ret(Node_Token * node_ret, Node_Exp * node_exp, Node_Token * node_sc);
    
    ~Node_Statement_Ret() = default;
    
    Node_Statement_Ret(Node_Statement_Ret &) = delete;
    
};

class Node_Statement_IF : public Node_Statement {
public:
/////////// Methods ///////////
    Node_Statement_IF(Node_Token * node_if, Node_Token * node_lparen, Node_Exp * node_exp,
                      Node_Token * node_rparen,
                      Node_Statement * node_statement);
    
    Node_Statement_IF(Node_Token * node_if, Node_Token * node_lparen, Node_Exp * node_exp,
                      Node_Token * node_rparen,
                      Node_Statement * node_statement1, Node_Token * node_else,
                      Node_Statement * node_statement2);
    
    ~Node_Statement_IF() = default;
    
    Node_Statement_IF(Node_Statement_IF &) = delete;
    
};

class Node_Statement_While : public Node_Statement {
public:
/////////// Methods ///////////
    Node_Statement_While(Node_Token * node_while, Node_Token * node_lparen, Node_Exp * node_exp,
                         Node_Token * node_rparen, Node_Statement * node_statement);
    
    ~Node_Statement_While() = default;
    
    Node_Statement_While(Node_Statement_While &) = delete;
    
};

class Node_Statement_LoopMod : public Node_Statement {
public:
/////////// Methods ///////////
    Node_Statement_LoopMod(Node_Token * node_loop_mod, Node_Token * node_sc);
    
    ~Node_Statement_LoopMod() = default;
    
    Node_Statement_LoopMod(Node_Statement_LoopMod &) = delete;
    
};

//#define YYSTYPE Node
    

struct YYSTYPE {
    Generic_Node * ProgramNode;
    Node_Token * NodeToken;
    Node_RetType * NodeRetType;
    Node_FormalDecl * NodeFormalDecl;
    Node_FormalsList * NodeFormalsList;
    Node_FuncDecl * NodeFuncDecl;
    Node_FuncsList * NodeFuncsList;
    Node_Statement * NodeStatement;
    Node_StatementList * NodeStatementList;
    Node_Exp * NodeExp;
    Node_ExpList * NodeExpList;
    Node_Call * NodeCall;
};


    



#endif

