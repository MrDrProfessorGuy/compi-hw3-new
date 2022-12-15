#ifndef _236360_3_
#define _236360_3_

#include <vector>
#include <string>
#include <memory>
#include <map>
//#include <stack>

//using namespace std;
extern int yylineno;

#define Shared(Class) std::shared_ptr<Class>

namespace output{
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

}

enum class Type {INVALID=0, INT, BYTE, BOOL, STRING, VOID, TOKEN};
enum class DeclType {INVALID=0, VAR, FUNC};
enum class FrameType {FUNC, LOOP, BLOCK};

class AppaException : public std::exception{
public:
    long lineno;
    AppaException(long line_number) : std::exception(){
        lineno = line_number;
    }
    /*
    const char* what() const noexcept override{
            
            return "A game related error has occurred: IllegalArgument";
    }*/
};

class Lexception : public AppaException{
public:
    Lexception(long lineno) : AppaException(lineno){};
};
class SynExc : public AppaException{
public:
    SynExc(long lineno) : AppaException(lineno){};
};
class UndefExc : public AppaException{
public:
    UndefExc(long lineno) : AppaException(lineno){};
};
class DefExc : public AppaException{
public:
    DefExc(long lineno) : AppaException(lineno){};
};
class UndDefFuncExc : public AppaException{
public:
    UndDefFuncExc(long lineno, std::string id) : AppaException(lineno){};
};
class MismatchExc : public AppaException{
public:
    MismatchExc(long lineno) : AppaException(lineno){};
};
class PrototypeMismatchExc : public AppaException{
public:
    PrototypeMismatchExc(long lineno, std::string id, std::vector<Type> param_types) : AppaException(lineno){};
};
class UnexpectedBreakExc : public AppaException{
public:
    UnexpectedBreakExc(long lineno) : AppaException(lineno){};
};
class UnexpectedContinueExc : public AppaException{
public:
    UnexpectedContinueExc(long lineno) : AppaException(lineno){};
};
class MainMissingExc : public AppaException{
public:
    MainMissingExc(long lineno) : AppaException(lineno){};
};
class ByteTooLargeExc : public AppaException{
public:
    ByteTooLargeExc(long lineno) : AppaException(lineno){};
};

class Generic_Node;
class Data;
class symTableEntry;
class StackEntry;
class Frame_class;
class Node_FormalDecl;
class Node_Exp_Type;

typedef std::shared_ptr<Generic_Node> Node;
typedef std::vector<Node> NodeVector;
typedef std::shared_ptr<symTableEntry> SymEntry;
typedef std::map<std::string, SymEntry> dict;
typedef std::vector<StackEntry> frame;

class Symbol {
public:
    Type type;
    std::string name;
    Symbol(Type sym_type, std::string sym_name): type(sym_type), name(sym_name){
    }
    Symbol(Symbol&)=default;
    Symbol(Symbol const&)=default;
    Symbol& operator=(Symbol const& sym)=default;
    
    static Symbol invalidSymbol(){
        return Symbol(Type::INVALID, "");
    }
};


class symTableEntry{
public:
    //std::string name;
    Symbol symbol;
    DeclType entry_type;
    long offset;
    bool valid;

    symTableEntry(Symbol sym, DeclType entry_type, long entry_offset, bool entry_valid=true): symbol(sym){
        this->entry_type = entry_type;
        offset = entry_offset;
        valid = entry_valid;
    }
    ~symTableEntry() = default;
    symTableEntry(symTableEntry& entry) = delete;
    virtual void stam(){};
};
class symTableEntryID : public symTableEntry{
public:
    
    symTableEntryID(Symbol sym, DeclType entry_type, long entry_offset) : symTableEntry(sym, entry_type, entry_offset, true){
    
    }
    ~symTableEntryID() = default;
    symTableEntryID(symTableEntryID& entry) = delete;
};
class symTableEntryFunc : public symTableEntry{
public:
    std::vector<Symbol> parameter_list;

    symTableEntryFunc(Symbol sym, DeclType entry_type, long entry_offset, std::vector<Symbol> func_params) : symTableEntry(sym, entry_type, entry_offset, true){
        parameter_list = func_params;
    }
    ~symTableEntryFunc() = default;
    symTableEntryFunc(symTableEntryFunc& entry) = delete;
};

class StackEntry{
    const SymEntry invalid_entry;
public:
    long next_offset;
    FrameType frame_type;
    dict entries;
    
    StackEntry(FrameType frame_type){
        this->frame_type = frame_type;
    };
    ~StackEntry()=default;
    StackEntry(StackEntry&) = delete;

    void newIdEntry(Symbol sym){
        auto entry = std::make_shared<symTableEntryID>(sym, DeclType::VAR, next_offset);
        next_offset++;

        entries.insert({entry->symbol.name, entry});
    }
    void newFuncEntry(Symbol sym, std::vector<Symbol> func_params){
        auto entry = std::make_shared<symTableEntryFunc>(sym, DeclType::FUNC, next_offset, func_params);
        next_offset++;

        entries.insert({entry->symbol.name, entry});
    }
    SymEntry find(std::string name){
        auto search = entries.find(name);
        if (search == entries.end()){
            return nullptr;
        }
        return search->second;
    }
};

class Frame_class{
public:
    frame frames;
    
    Frame_class()=default;
    ~Frame_class()=default;
    Frame_class(Frame_class&)=delete;
    
    void newEntry(DeclType entry_type, std::string name, Type id_type){
        SymEntry entry = find(name);
        if (entry->valid){
            throw UndefExc(yylineno);
        }
        frames.back().newIdEntry(Symbol(id_type, name));
    }
    void newEntry(DeclType entry_type, std::string name, Type ret_type, std::vector<Symbol> func_params){
        SymEntry entry = find(name);
        if (entry->valid){
            output::errorUndefFunc(yylineno, name);
            exit(0);
        }
        frames.back().newFuncEntry(Symbol(ret_type,name), func_params);
    }
    SymEntry find(std::string name){
        for(auto iter = frames.rbegin(); iter != frames.rend(); ++iter){
            SymEntry entry = iter->find(name);
            if (entry->valid){
                return entry;
            }
        }
        return nullptr;
    }
    
};

bool valid_cast(Type to, Type from);

Frame_class frame_manager;
std::vector<Node> TreeNodes;

class Generic_Node{
    long node_tree_index;
public:
    Node parent;
    NodeVector children;

/////////// Methods ///////////

    Generic_Node(NodeVector children){
        //initNodes();
        setChildren(children);
    }
    ~Generic_Node() = default;
    Generic_Node(Generic_Node&) = delete;

    void setChildren(NodeVector vector){
        for (int index = 0; index < vector.size(); index++){
            children.push_back(vector[index]);
            children[index]->setParent(get());
        }
    }
    void setParent(Node parent){
        this->parent = parent;
    }
    Node get(){
        return TreeNodes[node_tree_index];
    }
    virtual void stam(){};

};

class Node_Token : public Generic_Node{
public:
    std::string value;

/////////// Methods ///////////
    
    Node_Token(std::string token_value): Generic_Node({}){
        value = token_value;
    }
    ~Node_Token()=default;
    Node_Token(Node_Token&) = delete;
};

class Node_RetType : public Generic_Node{
public:
    Type type;

/////////// Methods ///////////

    Node_RetType(NodeVector children, Type ret_type): Generic_Node(children){
        type = ret_type;
    }
    ~Node_RetType() = default;
    Node_RetType(Node_RetType&) = delete;

    void set_type(Type new_type){
        type = new_type;
    };
};

class Node_FormalDecl : public Generic_Node{
public:
    //Type param_type;
    Symbol id_symbol;
/////////// Methods ///////////

    Node_FormalDecl(Shared(Node_Exp_Type) node_type, Shared(Node_Token) node_token_id);
    ~Node_FormalDecl()=default;
    Node_FormalDecl(Node_FormalDecl&) = delete;
};

class Node_FormalsList : public Generic_Node{
public:
    std::vector<Symbol> parameter_list;
    /// std::vector<std::pair<Type, std::string>> parameter_list;
/////////// Methods ///////////
    Node_FormalsList(Shared(Node_FormalDecl) node_formalDecl);
    Node_FormalsList(Shared(Node_FormalDecl) node_formalDecl, Shared(Node_Token) node_comma, Shared(Node_FormalsList) node_formalsList);
    ~Node_FormalsList()=default;
    Node_FormalsList(Node_FormalsList&) = delete;
};

class Node_FuncDecl : public Generic_Node{
public:
/////////// Methods ///////////

    Node_FuncDecl(NodeVector children);
    ~Node_FuncDecl()=default;
    Node_FuncDecl(Node_FuncDecl&) = delete;

};

class Node_FuncsList : public Generic_Node{
public:
    std::vector<Node_FuncDecl> funcs_list;
/////////// Methods ///////////

    Node_FuncsList(NodeVector children): Generic_Node(children){
        //TODO: check validity in sym table
    }
    ~Node_FuncsList()=default;
    Node_FuncsList(Node_FuncsList&) = delete;

};

class Node_Statement : public Generic_Node{
public:

/////////// Methods ///////////
    Node_Statement(NodeVector children);
    ~Node_Statement()=default;
    Node_Statement(Node_Statement&) = delete;


};

class Node_StatementList : public Generic_Node{
public:
    std::vector<Node_Statement> statement_list;
/////////// Methods ///////////
    Node_StatementList(NodeVector children);
    ~Node_StatementList()=default;
    Node_StatementList(Node_StatementList&) = delete;
};

class Node_Exp : public Generic_Node{
public:
    Type type;
/////////// Methods ///////////
    Node_Exp(NodeVector children, Type exp_type): Generic_Node(children){
        type = exp_type;
    }
    ~Node_Exp()=default;
    Node_Exp(Node_Exp&) = delete;

    void set_type(Type exp_type);
    bool typeCheck(std::vector<Type> type_list);
};

class Node_ExpList : public Generic_Node{
public:
    std::vector<Type> exp_list;
/////////// Methods ///////////

    Node_ExpList(Shared(Node_Exp) exp);
    Node_ExpList(Shared(Node_Exp) node_exp, Shared(Node_Token) node_token, Shared(Node_ExpList) node_expList);
    ~Node_ExpList()=default;
    Node_ExpList(Node_ExpList&) = delete;
    
    
};

class Node_Call : public Generic_Node{
public:
    Symbol func_id;
    std::vector<Type> func_parameters;
/////////// Methods ///////////

    Node_Call(Shared(Node_Token) node_id, Shared(Node_Token) node_lparen, Shared(Node_ExpList) node_expList, Shared(Node_Token) node_rparen);
    ~Node_Call()=default;
    Node_Call(Node_Call&) = delete;
};

class Node_Exp_Type : public Node_Exp{
public:
    Node_Exp_Type(NodeVector children, Type exp_type): Node_Exp(children, exp_type){
    
    }
    ~Node_Exp_Type()=default;
    Node_Exp_Type(Node_Exp_Type&) = delete;;
    
    
};

class Node_Exp_NUM : public Node_Exp{
public:
/////////// Methods ///////////
    
    Node_Exp_NUM(NodeVector children, Type exp_type): Node_Exp(children, exp_type){
        if (type == Type::BYTE){
            long token_val = std::atoi(std::static_pointer_cast<Node_Token>(children[0])->value.c_str());
            
            if (token_val > 255){
                throw ByteTooLargeExc(yylineno);
            }
        }
        
    }
    ~Node_Exp_NUM()=default;
    Node_Exp_NUM(Node_Exp_NUM&) = delete;
};

class Node_Exp_Binop : public Node_Exp{
public:
/////////// Methods ///////////
    
    Node_Exp_Binop(NodeVector children): Node_Exp(children, Type::INT){
        //Todo: if bool, update type
        auto exp1 = std::static_pointer_cast<Node_Exp>(children[0]);
        auto binop = std::static_pointer_cast<Node_Token>(children[1]);
        auto exp2 = std::static_pointer_cast<Node_Exp>(children[2]);
        
        if (!exp1->typeCheck({Type::INT, Type::BYTE}) || !exp2->typeCheck({Type::INT, Type::BYTE})){
            throw MismatchExc(yylineno);
        }
        if (exp1->type == Type::BYTE && exp2->type == Type::BYTE){
            set_type(Type::BYTE);
        }
        
    }
    ~Node_Exp_Binop()=default;
    Node_Exp_Binop(Node_Exp_NUM&) = delete;
};

class Node_Exp_Relop : public Node_Exp{
public:
/////////// Methods ///////////
    
    Node_Exp_Relop(NodeVector children): Node_Exp(children, Type::BOOL){
        auto exp1 = std::static_pointer_cast<Node_Exp>(children[0]);
        auto binop = std::static_pointer_cast<Node_Token>(children[1]);
        auto exp2 = std::static_pointer_cast<Node_Exp>(children[2]);
        
        if (!exp1->typeCheck({Type::INT, Type::BYTE}) || !exp2->typeCheck({Type::INT, Type::BYTE})){
            throw MismatchExc(yylineno);
        }
        
    }
    ~Node_Exp_Relop()=default;
    Node_Exp_Relop(Node_Exp_Relop&) = delete;
};

class Node_Exp_Cast : public Node_Exp{
public:
/////////// Methods ///////////
    
    Node_Exp_Cast(NodeVector children): Node_Exp(children, Type::INT){
        //Todo: if bool, update type
        auto type_node = std::static_pointer_cast<Node_Exp_Type>(children[1]);
        auto exp = std::static_pointer_cast<Node_Exp>(children[3]);
        
        if (!type_node->typeCheck({Type::INT, Type::BYTE}) || !exp->typeCheck({Type::INT, Type::BYTE})){
            throw MismatchExc(yylineno);
        }
        
        set_type(type_node->type);
    }
    ~Node_Exp_Cast()=default;
    Node_Exp_Cast(Node_Exp_Relop&) = delete;
};

class Node_Exp_Str : public Node_Exp{
public:
/////////// Methods ///////////
    
    Node_Exp_Str(NodeVector children): Node_Exp(children, Type::STRING){
    
    }
    ~Node_Exp_Str()=default;
    Node_Exp_Str(Node_Exp_Str&) = delete;
};

class Node_Exp_Bool : public Node_Exp{
public:
/////////// Methods ///////////
    
    Node_Exp_Bool(NodeVector children): Node_Exp(children, Type::BOOL){
    
    }
    ~Node_Exp_Bool()=default;
    Node_Exp_Bool(Node_Exp_Bool&) = delete;
};

class Node_Exp_ID : public Node_Exp{
public:
    Symbol id;
    Node_Exp_ID(Node_Token node_token): Node_Exp(children, Type::INVALID), id(Symbol::invalidSymbol()){
        //TODO: check validity and update frame stack
        auto node_token_id = std::dynamic_pointer_cast<Node_Token>(children[0]);
        auto entry = std::dynamic_pointer_cast<symTableEntryID>(frame_manager.find(node_token_id->value));
        if (!entry->valid){
            throw UndefExc(yylineno);
            //printf();
        }
        set_type(entry->symbol.type);
        id = entry->symbol;
    }
    ~Node_Exp_ID()=default;
    Node_Exp_ID(Node_Exp_ID&) = delete;
    
};

class Node_Exp_Call : public Node_Exp{
public:
    
    Node_Exp_Call(NodeVector children): Node_Exp(children, Type::INVALID){
        ///TODO: check validity and update frame stack
        auto node_call = std::dynamic_pointer_cast<Node_Call>(children[0]);
        //auto func_entry = (frame_manager.find(node_call->func_id.name));
        //assert(func_entry->valid);
        
        set_type(node_call->func_id.type);
    }
    ~Node_Exp_Call()=default;
    Node_Exp_Call(Node_Exp_Call&) = delete;;
    
};

class Node_Exp_IfElse : public Node_Exp{
public:
    
    Node_Exp_IfElse(NodeVector children): Node_Exp(children, Type::INVALID){
        ///TODO: check validity and update frame stack
        auto exp1 = std::dynamic_pointer_cast<Node_Exp>(children[0]);
        auto exp2 = std::dynamic_pointer_cast<Node_Exp>(children[3]);
        auto exp3 = std::dynamic_pointer_cast<Node_Exp>(children[6]);
        
        if (!exp2->typeCheck({Type::BOOL})){
            throw MismatchExc(yylineno);
        }
        
        if (exp1->type != exp3->type){
            if (exp1->typeCheck({Type::INT}) && exp3->typeCheck({Type::BYTE})){
                set_type(Type::INT);
            }
            else if(exp1->typeCheck({Type::BYTE}) && exp3->typeCheck({Type::INT})){
                set_type(Type::INT);
            }
            else{
                throw MismatchExc(yylineno);
            }
        }
        else{
            set_type(exp1->type);
        }
        
        
    }
    ~Node_Exp_IfElse()=default;
    Node_Exp_IfElse(Node_Exp_IfElse&) = delete;;
    
};


//#define YYSTYPE Node
/*
 * union YYSTYPE {
    Shared(Generic_Node) ProgramNode;
    Shared(Node_Token) NodeToken;
    Shared(Node_RetType) NodeRetType;
    Shared(Node_FormalDecl) NodeFormalDecl;
    Shared(Node_FormalsList) NodeFormalsList;
    Shared(Node_FuncDecl) NodeFuncDecl;
    Shared(Node_FuncsList) NodeFuncsList;
    Shared(Node_Statement) NodeStatement;
    Shared(Node_StatementList) NodeStatementList;
    Shared(Node_Exp) NodeExp;
    Shared(Node_ExpList) NodeExpList;
    Shared(Node_Call) NodeCall;

    
};

 */


#endif

