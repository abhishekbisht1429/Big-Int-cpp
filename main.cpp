#include "big_int.cpp"
#include "stack.cpp"
#include<tuple>
#include<fstream>
#include<chrono>
#include<string>

#define DEBUG

pair<int, int> convert(string &s, char **mag) {
    int signum;
    int len;
    if(s[0] == '-') {
        signum = -1;
        len = s.size()-1;
        for(int i=1; i<s.size(); ++i)
            (*mag)[len-i] = s[i] - '0';
    } else if(s.size()==1 && s[0] == '0') {
        signum = 0;
        len = 0;
    } else {
        signum = 1;
        len = s.size();
        for(int i=0; i<s.size(); ++i)
            (*mag)[s.size()-i-1] = s[i] - '0';
    }

    return {signum, len};
}

inline bool isOp(string str) {
    return str == "+" || str == "-" || str == "x" || str == "/";
}

inline int preced(string str) {
    if(str == "x")
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

big_int eval(big_int &bi1, big_int &bi2, string op) {
    // cout<<"op "<<op<<"\n";
    if(op == "+")
        return bi1+bi2;
    else if(op == "-")
        return bi1-bi2;
    else if(op == "x")
        return bi1*bi2;
    else if(op == "/")
        return bi1/bi2;
    else
        return big_int(0, nullptr, -1);
}

big_int evalExpr(string *postfix, int len) {
    stack<big_int> st;
    for(int i=0; i<len; ++i) {
        if(isOperand(postfix[i])) {
            cout<<"push "<<postfix[i]<<"\n";
            st.push(big_int(postfix[i]));
        } else {
            big_int a = st.top();
            st.pop();
            big_int b = st.top();
            st.pop();
            cout<<"a "<<a<<"\n";
            cout<<"b "<<b<<"\n";
            big_int res = eval(b, a, postfix[i]);
            cout<<"res "<<postfix[i]<<" "<<res<<"\n";
            cout<<"\n";
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
            cout<<factorial(bi)<<"\n";
            break;
        }
        case 4: {
            string expr;
            cin>>expr;
            string *infix = nullptr;
            int lenIfx = tokenize(expr, &infix);
            cout<<"infix : ";
            for(int i=0; i<lenIfx; ++i)
                cout<<"{"<<infix[i]<<"}";
            cout<<"\n";
        
            cout<<"postfix : ";
            string *postfix = nullptr;
            int lenPfx = infixToPostfix(infix, lenIfx, &postfix);
            cout<<"len pfx "<<lenPfx<<"\n";
            for(int i=0; i<lenPfx; ++i)
                cout<<"{"<<postfix[i]<<"}";
            cout<<"\n";
            cout<<evalExpr(postfix, lenPfx)<<"\n";
            break;
        }

        default: {
            cout<<"Invalid choice\n";
            break;
        }
    }

    // int signum1, signum2;
    // int len1, len2;
    // string s1, s2;
    // getline(cin, s1);
    // getline(cin, s2);
    // char *mag1 = new char[s1.size()];
    // char *mag2 = new char[s2.size()];

    // tie(signum1, len1) = convert(s1, &mag1);
    // tie(signum2, len2) = convert(s2, &mag2);



    
    // big_int bi1(signum1, mag1, len1);
    // big_int bi2(signum2, mag2, len2);

    // big_int bi3 = bi1 + bi2;
    // big_int bi4 = bi1 - bi2;
    // cout<<"sum "<<bi3<<"\n";
    // cout<<"subtraction "<<bi4<<"\n";

    // big_int bi5 = bi1 * bi2;
    // cout<<"product "<<bi5<<"\n";

    // big_int bi6 = exp(bi1, 2);
    // cout<<bi6<<"\n";

    // big_int bi7 = factorial(bi1);
    // cout<<bi7<<"\n";

    // big_int bi8 = bi1 / bi2;
    // cout<<"quotient "<<bi8<<"\n";

    // big_int bi9 = bi1%bi2;
    // cout<<"remainder "<<bi9<<"\n";

    // big_int bi10 = gcd(bi1, bi2);
    // cout<<"gcd "<<bi10<<"\n";

    // stack<string> s;
    // s.push("hello");
    // s.push("world");
    // s.push("hi");

    // s.print();
    // s.pop();
    // s.print();
    // s.push("safda");
    // s.print();

    // string expr;
    // cin>>expr;
    // string *infix = nullptr;
    // int lenIfx = tokenize(expr, &infix);
    // cout<<"infix : ";
    // for(int i=0; i<lenIfx; ++i)
    //     cout<<infix[i]<<" ";
    // cout<<"\n";

    // cout<<"postfix : ";
    // string *postfix = nullptr;
    // int lenPfx = infixToPostfix(infix, lenIfx, &postfix);
    // for(int i=0; i<lenPfx; ++i)
    //     cout<<postfix[i]<<" ";
    // cout<<"\n";
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