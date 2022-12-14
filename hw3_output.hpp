#ifndef _236360_3_
#define _236360_3_

#include <vector>
#include <string>
#include <memory>
#include <map>
//#include <stack>

//using namespace std;
extern int yylineno; 


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
    UndDefFuncExc(long lineno) : AppaException(lineno){};
};
class MismatchExc : public AppaException{
public:
    MismatchExc(long lineno) : AppaException(lineno){};
};
class PrototypeMismatchExc : public AppaException{
public:
    PrototypeMismatchExc(long lineno) : AppaException(lineno){};
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

class Node_class;
class Generic_Node;
class Data;
class symTableEntry;
class StackEntry;
class Frame_class;
class Node_FormalDecl;
class Node_Exp_Type;

typedef std::shared_ptr<Generic_Node> Node;
typedef std::vector<Node>   NodeVector;
typedef std::shared_ptr<Data> DataP;
typedef std::shared_ptr<symTableEntry> SymEntry;
typedef std::map<std::string, SymEntry> dict;
typedef std::vector<StackEntry> frame;


enum class Type {INVALID=0, INT, BYTE, BOOL, STRING, FUNC, TOKEN, RET_TYPE};
enum class DeclType {INVALID=0, VAR, FUNC};
enum class FrameType {FUNC, LOOP, BLOCK};

class symTableEntry{
public:
    std::string name;
    DeclType entry_type;
    long offset;
    bool valid;

    symTableEntry(std::string entry_name, DeclType entry_type, long entry_offset, bool entry_valid=true){
        name = entry_name;
        this->entry_type = entry_type;
        offset = entry_offset;
        valid = entry_valid;
    }
    ~symTableEntry() = default;
    symTableEntry(symTableEntry& entry) = default;
};
class symTableEntryFunc : public symTableEntry{
public:
    Type ret_type;
    std::vector<Type> parameter_list;

    symTableEntryFunc(std::string entry_name, DeclType entry_type, long entry_offset, Type return_type, std::vector<Type> func_params) : symTableEntry(entry_name, entry_type, entry_offset, true){
        ret_type = return_type;
        parameter_list = func_params;
    }
    ~symTableEntryFunc() = default;
    symTableEntryFunc(symTableEntryFunc& entry) = default;
};
class symTableEntryID : public symTableEntry{
public:
    Type type;

    symTableEntryID(std::string entry_name, DeclType entry_type, long entry_offset, Type id_type) : symTableEntry(entry_name, entry_type, entry_offset, true){
        type = id_type;
    }
    ~symTableEntryID() = default;
    symTableEntryID(symTableEntryID& entry) = default;
};

class StackEntry{
    const SymEntry invalid_entry;
public:
    long next_offset;
    FrameType frame_type;
    dict entries;
    
    StackEntry():invalid_entry(std::make_shared<symTableEntry>("", DeclType::INVALID, 0, false)){
        
    };
    ~StackEntry()=default;
    StackEntry(StackEntry&) = delete;

    void newIdEntry(std::string name, Type id_type){
        auto entry = std::make_shared<symTableEntryID>(name, DeclType::VAR, next_offset, id_type);
        next_offset++;

        entries.insert({name, entry});
    }
    void newFuncEntry(std::string name, Type ret_type, std::vector<Type> func_params){
        auto entry = std::make_shared<symTableEntryFunc>(name, DeclType::FUNC, next_offset, ret_type, func_params);
        next_offset++;

        entries.insert({name, entry});
    }
    SymEntry find(std::string name){
        auto search = entries.find(name);
        if (search == entries.end()){
            return invalid_entry;
        }
        return search->second;
    }
    SymEntry invalidEntry(){
        return invalid_entry;
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
        frames.back().newIdEntry(name, id_type);
    }
    void newEntry(DeclType entry_type, std::string name, Type ret_type, std::vector<Type> func_params){
        SymEntry entry = find(name);
        if (entry->valid){
            throw UndDefFuncExc(yylineno);
        }
        frames.back().newFuncEntry(name, ret_type, func_params);
    }
    SymEntry find(std::string name){
        for(auto iter = frames.rbegin(); iter != frames.rend(); ++iter){
            SymEntry entry = iter->find(name);
            if (entry->valid){
                return entry;
            }
        }
        return StackEntry().invalidEntry();
    }

};
Frame_class frame_manager;

class Data{
public:
    const Type type;
    bool lVAL;

    Data(Type data_type) : type(data_type){
        lVAL = false;
    }
    ~Data();
    Data(Data&) = delete;

    
};

class DataID : public Data{
public:
    std::string name;
    symTableEntry* id_entry;
    
    DataID(Type data_type, std::string name): Data(data_type){
        this->name = name;
        /// TODO: fill id_entry
    }
    ~DataID();
    DataID(DataID&) = delete;
};

class DataType : public Data{
public:
    DataType(Type d_type): Data(d_type){}
    ~DataType();
    DataType(DataType&)=delete;
};
class DataToken : public Data{
public:
    std::string value;
    
    DataToken(std::string token_value): Data(Type::TOKEN){
        value = token_value;
    }
    ~DataToken();
    DataToken(DataToken&)=delete;

};
class DataNum : public Data{
public:
    int value;
    DataNum(Type num_type) : Data(num_type){
        value = 0;
    }   
    DataNum(Type num_type, int num_value): Data(num_type){
        value = num_value;
    }
    ~DataNum();
    DataNum(DataNum&)=delete;

};
class DataBool : public Data{
public:
    bool value;

    DataBool(bool val): Data(Type::BOOL){
        value = val;
    }
    ~DataBool();
    DataBool(DataBool&)=delete;
};
class DataStr : public Data{
public:
    std::string value;

    DataStr(std::string str_value): Data(Type::STRING){
        value = str_value;
    }
    ~DataStr();
    DataStr(DataStr&)=delete;
};


class DataFunc : public Data{
public:
    std::string name;
    Type retType;

    DataFunc(Type ret_type): Data(ret_type){
        name = "";
    }
    ~DataFunc();
    DataFunc(DataFunc&)=delete;


};


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
    Type param_type;
/////////// Methods ///////////

    Node_FormalDecl(NodeVector children, Type parameter_type): Generic_Node(children){
        param_type = parameter_type;
        //TODO: check validity in symtable.
    }
    ~Node_FormalDecl()=default;
    Node_FormalDecl(Node_FormalDecl&) = delete;
};

class Node_FormalsList : public Generic_Node{
public:
    std::vector<Node_FormalDecl> parameter_list;
/////////// Methods ///////////

    Node_FormalsList(NodeVector children): Generic_Node(children){
        //TODO: check validity in symtable, unite lists.
    }
    ~Node_FormalsList()=default;
    Node_FormalsList(Node_FormalsList&) = delete;
};

class Node_FuncDecl : public Generic_Node{
public:
/////////// Methods ///////////

    Node_FuncDecl(NodeVector children): Generic_Node(children){
        //TODO: check validity in sym table
    }
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

class Node_Statement : public Generic_Node{
public:

/////////// Methods ///////////
    Node_Statement(NodeVector children): Generic_Node(children){
        
    }
    ~Node_Statement()=default;
    Node_Statement(Node_Statement&) = delete;


};

class Node_StatementList : public Generic_Node{
public:
    std::vector<Node_Statement> statement_list;
/////////// Methods ///////////
    Node_StatementList(NodeVector children): Generic_Node(children){
        //TODO: unite lists
    }
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
    std::vector<Node_Exp> exp_list;
/////////// Methods ///////////

    Node_ExpList(NodeVector children): Generic_Node(children){
        //TODO: unite the lists
    }
    ~Node_ExpList()=default;
    Node_ExpList(Node_ExpList&) = delete;

};

class Node_Call : public Generic_Node{
public:

/////////// Methods ///////////

    Node_Call(NodeVector children): Generic_Node(children){
        //TODO: check validity in sym table
    }
    ~Node_Call()=default;
    Node_Call(Node_Call&) = delete;
    std::string ID(){
    
    };
};


//#define YYSTYPE Node
union YYSTYPE {
  
};


#endif

