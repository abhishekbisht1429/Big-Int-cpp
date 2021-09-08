#include "big_int.cpp"
#include<tuple>
#include<fstream>
#include<chrono>

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