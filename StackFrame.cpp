#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"

using namespace std;

//forward declaration



enum mode_code {
    nothing = -1,
    iadd,
    fadd,
    isub,
    fsub,
    imul,
    fmul,
    idiv,
    fdiv,
    irem,
    ineg,
    fneg,
    iand,
    ior,
    ieq,
    feq,
    ineq,
    fneq,
    ilt,
    flt,
    igt,
    fgt,
    ibnot,
    iconst,
    fconst,
    iload,
    fload,
    istore,
    fstore,
    i2f,
    f2i,
    top,
    val,
    par
};

/*
convert mode into enum type
@param inString mode
*/
mode_code hashit(string const& inString) {
    if (inString == "iadd")
        return iadd;
    if (inString == "fadd")
        return fadd;
    if (inString == "isub")
        return isub;
    if (inString == "fsub")
        return fsub;
    if (inString == "imul")
        return imul;
    if (inString == "fmul")
        return fmul;
    if (inString == "idiv")
        return idiv;
    if (inString == "fdiv")
        return fdiv;
    if (inString == "irem")
        return irem;
    if (inString == "ineg")
        return ineg;
    if (inString == "fneg")
        return fneg;
    if (inString == "iand")
        return iand;
    if (inString == "ior")
        return ior;
    if (inString == "ieq")
        return ieq;
    if (inString == "feq")
        return feq;
    if (inString == "ineq")
        return ineq;
    if (inString == "fneq")
        return fneq;
    if (inString == "ilt")
        return ilt;
    if (inString == "flt")
        return flt;
    if (inString == "igt")
        return igt;
    if (inString == "fgt")
        return fgt;
    if (inString == "ibnot")
        return ibnot;
    if (inString == "iconst")
        return iconst;
    if (inString == "fconst")
        return fconst;
    if (inString == "iload")
        return iload;
    if (inString == "fload")
        return fload;
    if (inString == "istore")
        return istore;
    if (inString == "fstore")
        return fstore;
    if (inString == "i2f")
        return i2f;
    if (inString == "f2i")
        return f2i;
    if (inString == "top")
        return top;
    if (inString == "val")
        return val;
    if (inString == "par")
        return par;
    return nothing;
}

/*
error enum
*/
enum error_type {
    tmm = 1, // type mismatch
    dbz,     // divide by zero
    sfl,     // stack full
    smt,     // stack empty
    lsf,    // local space full
    udv      // undefined variable
};


StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarSpaceSize(LOCAL_VARIABLE_SPACE_SIZE) {}

void StackFrame::error(int& err, int line) {
    switch (err) {
    case tmm: {
        TypeMisMatch* tymima = new TypeMisMatch(line);
        throw(*tymima);
        delete tymima;
        break;
    }

    case dbz: {
        DivideByZero* dibyze = new DivideByZero(line);
        throw(*dibyze);
        delete dibyze;
        break;
    }

    case sfl: {
        StackFull* stfu = new StackFull(line);
        throw(*stfu);
        delete stfu;
        break;
    }

    case smt: {
        StackEmpty* stem = new StackEmpty(line);
        throw(*stem);
        delete stem;
        break;
    }

    case lsf: {
        LocalSpaceFull* lospfu = new LocalSpaceFull(line);
        throw(*lospfu);
        delete lospfu;
        break;
    }

    case udv: {
        UndefinedVariable* unva = new UndefinedVariable(line);
        throw(*unva);
        delete unva;
        break;
    }
            return;
    }
}

void StackFrame::iAdd(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(valu1 + valu2, type1);
    return;
}

void StackFrame::fAdd(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    float valu1, valu2;
    valu1 = opStack.Top()->Value();
    opStack.pop();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    opStack.push(valu1 + valu2, 1);
    return;
}

void StackFrame::iSub(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(valu2 - valu1, type1);
    return;
}

void StackFrame::fSub(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    float valu1, valu2;
    valu1 = opStack.Top()->Value();
    opStack.pop();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    opStack.push(valu2 - valu1, 1);
    return;
}

void StackFrame::iMul(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(valu1 * valu2, type1);
    return;
}

void StackFrame::fMul(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    float valu1, valu2;
    valu1 = opStack.Top()->Value();
    opStack.pop();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    opStack.push(valu1 * valu2, 1);
    return;
}

void StackFrame::iDiv(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }
    if (valu1 == 0) {
        err = dbz;
        return;
    }
    opStack.push(valu2 / valu1, type1);
    return;
}

void StackFrame::fDiv(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    float valu1, valu2;
    valu1 = opStack.Top()->Value();
    opStack.pop();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (valu1 == 0) {
        err = dbz;
        return;
    }
    opStack.push(valu2 / valu1, 1);
    return;
}

void StackFrame::iRem(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }
    if (valu1 == 0) {
        err = dbz;
        return;
    }
    opStack.push(int(valu2) % int(valu1), type1);
    return;
}

void StackFrame::iNeg(int& err) {
    if (opStack.size() == 0) {
        err = smt;
        return;
    }
    float value = opStack.Top()->Value();
    int type = opStack.Top()->Type();
    opStack.pop();
    if (type == 1) {
        err = tmm;
        return;
    }
    opStack.push(-value, type);
    return;
}

void StackFrame::fNeg(int& err) {
    if (opStack.size() == 0) {
        err = smt;
        return;
    }
    float value = opStack.Top()->Value();
    opStack.pop();
    if (value != 0) value = -value;
    opStack.push(value, 1);
    return;
}

void StackFrame::iAnd(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(int(int(valu1) & int(valu2)), type1);
    return;
}

void StackFrame::iOr(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(int(int(valu1) | int(valu2)), type1);
    return;
}

void StackFrame::iEq(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(int(int(valu1) == int(valu2)), type1);
    return;
}

void StackFrame::fEq(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    float valu1, valu2;
    valu1 = opStack.Top()->Value();
    opStack.pop();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    

    opStack.push(int(int(valu1) == int(valu2)), 1);
    return;
}

void StackFrame::inEq(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(int(int(valu1) != int(valu2)), type1);
    return;
}

void StackFrame::fnEq(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    float valu1, valu2;
    valu1 = opStack.Top()->Value();
    opStack.pop();
    valu2 = opStack.Top()->Value();
    opStack.pop();


    opStack.push(int(int(valu1) != int(valu2)), 1);
    return;
}

void StackFrame::iLt(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(int(int(valu2) < int(valu1)), type1);
    return;
}

void StackFrame::fLt(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    float valu1, valu2;
    valu1 = opStack.Top()->Value();
    opStack.pop();
    valu2 = opStack.Top()->Value();
    opStack.pop();


    opStack.push(int(int(valu2) < int(valu1)), 1);
    return;
}

void StackFrame::iGt(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    int type1, type2;
    float valu1, valu2;
    type1 = opStack.Top()->Type();
    valu1 = opStack.Top()->Value();
    opStack.pop();
    type2 = opStack.Top()->Type();
    valu2 = opStack.Top()->Value();
    opStack.pop();
    if (type1 == 1 || type2 == 1) {
        err = tmm;
        return;
    }

    opStack.push(int(int(valu2) > int(valu1)), type1);
    return;
}

void StackFrame::fGt(int& err) {
    if (opStack.size() < 2) {
        err = smt;
        return;
    }
    float valu1, valu2;
    valu1 = opStack.Top()->Value();
    opStack.pop();
    valu2 = opStack.Top()->Value();
    opStack.pop();


    opStack.push(int(int(valu2) > int(valu1)), 1);
    return;
}

void StackFrame::iBnot(int& err) {
    if (opStack.size() == 0) {
        err = smt;
        return;
    }
    float value = opStack.Top()->Value();
    int type = opStack.Top()->Type();
    opStack.pop();
    if (type == 1) {
        err = tmm;
        return;
    }
    opStack.push(int(value==0), type);
    return;
}

void StackFrame::iConst(int val, int& err) {
    if (opStack.size() == opStackMaxSize/2) {
        err = sfl;
        return;
    }
    opStack.push(val, 0);
    return;
}

void StackFrame::fConst(float val, int& err) {
    if (opStack.size() == opStackMaxSize / 2) {
        err = sfl;
        return;
    }
    opStack.push(val, 1);
    return;
}

void StackFrame::iLoad(string key, int& err) {
    AVLTree::Node* localVar = localVarSpace.takeNode(key);
    if (localVar == NULL) {
        err = udv;
        return;
    }
    if (localVar->Type() == 1) {
        err = tmm;
        return;
    }
    if (opStack.size() == opStackMaxSize / 2) {
        err = sfl;
        return;
    }
    opStack.push(localVar->Value(), localVar->Type());
    return;
}

void StackFrame::fLoad(string key, int& err) {
    AVLTree::Node* localVar = localVarSpace.takeNode(key);
    if (localVar == NULL) {
        err = udv;
        return;
    }
    if (localVar->Type() == 0) {
        err = tmm;
        return;
    }
    if (opStack.size() == opStackMaxSize / 2) {
        err = sfl;
        return;
    }
    opStack.push(localVar->Value(), localVar->Type());
    return;
}

void StackFrame::iStore(string key, int& err) {
    if (opStack.size() == 0) {
        err = smt;
        return;
    }
    if (opStack.Top()->Type() == 1) {
        err = tmm;
        return;
    }
    if (localVarSpace.size() == localVarSpaceSize) {
        err = lsf;
        return;
    }
    localVarSpace.insertNode(key, opStack.Top()->Value(), opStack.Top()->Type());
    opStack.pop();
    return;
}

void StackFrame::fStore(string key, int& err) {
    if (opStack.size() == 0) {
        err = smt;
        return;
    }
    if (opStack.Top()->Type() == 0) {
        err = tmm;
        return;
    }
    if (localVarSpace.size() == localVarSpaceSize) {
        err = lsf;
        return;
    }
    localVarSpace.insertNode(key, opStack.Top()->Value(), opStack.Top()->Type());
    opStack.pop();
    return;
}

void StackFrame::ItoF(int& err) {
    if (opStack.size() == 0) {
        err = smt;
        return;
    }
    if (opStack.Top()->Type() == 1) {
        err = tmm;
        return;
    }
    float value = opStack.Top()->Value();
    opStack.pop();
    opStack.push(value, 1);
    return;
}

void StackFrame::FtoI(int& err) {
    if (opStack.size() == 0) {
        err = smt;
        return;
    }
    if (opStack.Top()->Type() == 0) {
        err = tmm;
        return;
    }
    float value = opStack.Top()->Value();
    opStack.pop();
    opStack.push(value, 0);
    return;
}

void StackFrame::toP(int& err) {
    if (opStack.size() == 0) {
        err = smt;
        return;
    }
    opStack.printTop();
    return;
}

void StackFrame::Val(string key, int& err) {
    AVLTree::Node* localVar = localVarSpace.findNode(key);
    if (localVar == NULL) {
        err = udv;
        return;
    }
    localVar->printNode();
    return;
}

void StackFrame::Par(string key, int& err) {
    AVLTree::Node* check = localVarSpace.findNode(key);
    if (check == NULL) {
        err = udv;
        return;
    }
    localVarSpace.parent(key);
    return;
}

void StackFrame::run(string filename) {
    string mode;  // name of syntax
    string data;  // temporary string type before convert into suitable type
    string key; //var to search
    int idata = 0;    // integer variable
    float fdata = 0;  // float variable
    int line = 1; // current line (start at 1)
    int err = 0;  // type of error
    
    fstream readfile; // interact with input file

    readfile.open(filename, ios::in); // open file in read mode

    if (!readfile.is_open()) {
        cout << "wrong file name";
        return;
    }

    /*
    Scan through all line of file
    */
    while (!readfile.eof()) {
        readfile >> mode; // get the instruction
        switch (hashit(mode)) {
        case iadd: {
            iAdd(err);
            break;
        }
        case fadd: {
            fAdd(err);
            break;
        }
        case isub: {
            iSub(err);
            break;
        }
        case fsub: {
            fSub(err);
            break;
        }
        case imul: {
            iMul(err);
            break;
        }
        case fmul: {
            fMul(err);
            break;
        }
        case idiv: {
            iDiv(err);
            break;
        }
        case fdiv: {
            fDiv(err);
            break;
        }
        case irem: {
            iRem(err);
            break;
        }
        case ineg: {
            iNeg(err);
            break;
        }
        case fneg: {
            fNeg(err);
            break;
        }
        case iand: {
            iAnd(err);
            break;
        }
        case ior: {
            iOr(err);
            break;
        }
        case ieq: {
            iEq(err);
            break;
        }
        case feq: {
            fEq(err);
            break;
        }
        case ineq: {
            inEq(err);
            break;
        }
        case fneq: {
            fnEq(err);
            break;
        }
        case ilt: {
            iLt(err);
            break;
        }
        case flt: {
            fLt(err);
            break;
        }
        case igt: {
            iGt(err);
            break;
        }
        case fgt: {
            fGt(err);
            break;
        }
        case ibnot: {
            iBnot(err);
            break;
        }
        case iconst: {
            readfile >> data;

            /*
            Check if data is same as int type
            When data have dot '.' throw type mismatch
            */
            for (unsigned int i = 0; i < data.size(); i++) {
                if (data[i] == '.') {
                    err = tmm;
                    error(err, line);
                    return;
                }
            }

            idata = stoi(data);
            iConst(idata, err);
            break;

        }
        case fconst: {
            readfile >> data;
            fdata = stof(data);
            fConst(fdata, err);
            break;
        }
        case iload: {
            readfile >> key;
            iLoad(key, err);
            break;
        }
        case fload: {
            readfile >> key;
            fLoad(key, err);
            break;
        }
        case istore: {
            readfile >> key;
            iStore(key, err);
            break;
        }
        case fstore: {
            readfile >> key;
            fStore(key, err);
            break;
        }
        case i2f: {
            ItoF(err);
            break;
        }
        case f2i: {
            FtoI(err);
            break;
        }
        case top: {
            toP(err);
            break;
        }
        case val: {
            readfile >> key;
            Val(key, err);
            break;
        }
        case par: {
            readfile >> key;
            Par(key, err);
            break;
        }
        default:
            break;
        }


        if (err != 0) {
            error(err, line);
            return;
        }
        line++;
    }

    readfile.close();
    return;
    
}