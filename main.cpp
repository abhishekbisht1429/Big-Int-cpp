#include "big_int.cpp"
#include "stack.cpp"
#include<tuple>
#include<fstream>
#include<chrono>
#include<string>

#define DEBUG

inline bool isOp(string str) {
    return str == "+" || str == "-" || str == "x" || str == "/" ||
            str == "^";
}

inline int preced(string str) {
    if(str == "^")
        return 10;
    else if(str == "x")
        return 4;
    else if(str == "/")
        return 4;
    else if(str == "+")
        return 3;
    else if(str == "-")
        return 3;
    else
        return -1;
}

inline bool isOperand(string str) {
    return !isOp(str) && str!="(" && str!=")";
}

int tokenize(string inp, string **out) {
    inp += "#";
    string *arr = new string[inp.size()];
    string temp = "";
    int j=0;
    for(int i=0; i<inp.size(); ++i) {
        if(isdigit(inp[i])) {
            temp += inp[i];
        } else {
            if(temp!="")
                arr[j++] = temp;
            if(inp[i]!='#')
                arr[j++] = inp[i];
            temp = "";
        }
    }
    *out = new string[j];
    for(int i=0; i<j; ++i)
        (*out)[i] = arr[i];
    
    delete[] arr;
    return j;
}

int infixToPostfix(string *inp, int len, string **out) {
    string *infix = new string[len+1];
    for(int i=0; i<len; ++i)
        infix[i] = inp[i];
    string *postfix = new string[len];
    for(int i=0; i<len; ++i)
        postfix[i] = "";
    stack<string> st;
    st.push("(");
    infix[len] = ")";

    int j=0;
    for(int i=0; i<len+1; ++i) {
        if(isOp(infix[i])) {
            while(st.top()!="(" && preced(st.top()) >= preced(infix[i])) {
                postfix[j++] = st.top();
                st.pop();
            }
            st.push(infix[i]);
        } else if(isOperand(infix[i])) {
            postfix[j++] = infix[i];
        } else if(infix[i] == "(") {
            st.push("(");
        } else {
            while(st.top()!="(") {
                postfix[j++] = st.top();
                st.pop();
            }
            st.pop();
        }
    }

    while(len > 0 && postfix[len-1] == "")
        --len;
    *out = postfix;
    return len;
}

big_int eval(big_int &bi1, big_int &bi2, string op) {
    if(op == "+")
        return bi1+bi2;
    else if(op == "-")
        return bi1-bi2;
    else if(op == "x")
        return bi1*bi2;
    else if(op == "/")
        return bi1/bi2;
    else if(op == "^")
        return exp(bi1, bi2);
    else
        return big_int(0, nullptr, -1);
}

big_int evalExpr(string *postfix, int len) {
    stack<big_int> st;
    for(int i=0; i<len; ++i) {
        if(isOperand(postfix[i])) {
            st.push(big_int(postfix[i]));
        } else {
            big_int a = st.top();
            st.pop();
            big_int b = st.top();
            st.pop();
            big_int res = eval(b, a, postfix[i]);
            st.push(res);
        }
    }
    return st.top();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef DEBUG
    ifstream _in("input.txt");
    ofstream _out("output.txt");
    streambuf* _in_backup = cin.rdbuf();
    streambuf* _out_backup = cout.rdbuf();
    cin.rdbuf(_in.rdbuf());
    cout.rdbuf(_out.rdbuf());
    auto _start = chrono::high_resolution_clock::now();
    #endif
    /* ######################CODE_START################################ */
    int type;
    cin>>type;
    switch (type) {
        case 1: {
            string s1, s2;
            cin>>s1>>s2;
            big_int bi1(s1), bi2(s2);
            cout<<exp(bi1, bi2)<<"\n";
            break;
        }
        case 2: {
            string s1, s2;
            cin>>s1>>s2;
            big_int bi1(s1), bi2(s2);
            cout<<gcd(bi1, bi2)<<"\n";
            break;
        }
        case 3: {
            string s;
            cin>>s;
            big_int bi(s);
            if(bi < big_int(0))
                cout<<"Factorial is not defined for negetive integers\n";
            else
                cout<<factorial(bi)<<"\n";
            break;
        }
        case 4: {
            string expr;
            cin>>expr;
            string *infix = nullptr;
            string *postfix = nullptr;
            int lenIfx = tokenize(expr, &infix);
            int lenPfx = infixToPostfix(infix, lenIfx, &postfix);
            cout<<evalExpr(postfix, lenPfx)<<"\n";
            break;
        }

        default: {
            cout<<"Invalid choice\n";
            break;
        }
    }
    /* #######################CODE_END############################### */
    #ifdef DEBUG
    auto _end = chrono::high_resolution_clock::now();
    auto _duration = chrono::duration_cast<chrono::nanoseconds>(_end - _start);
    long long _ns = _duration.count();
    double _s = _ns / 1e9;
    cout<<"\nDuration: "<<_s<<" sec\n";
    cin.rdbuf(_in_backup);
    cout.rdbuf(_out_backup);
    #endif
}