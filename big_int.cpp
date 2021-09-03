#include<iostream>
#include<cstring>
#include<tuple>
#include<fstream>
#include<chrono>

#define DEBUG

using namespace std;

class big_int {
    /*
        1 if positive integer,
        0 if zero, and
        -1 if negetive integer
    */
    int signum;

    /* 
        * store the magnitude of the integer with least significant
          digit on the left
    */
    char *mag;

    /*
        * stores the length of the integer
        * zero is represented by len = 0 
    */
    int len;

    /* Constructor */
    public:big_int(): signum(0), mag(nullptr), len(0) {}

    /* Constructor */
    public:big_int(int signum, char *mag, int len) {
        this->signum = signum;
        this->mag = new char[len];
        for(int i=0; i<len; ++i)
            this->mag[i] = mag[i];

        /* eliminate extra zeros at fron */
        while(len > 0 && mag[len-1] == 0)
            --len;
        this->len = len;
    }
    
    /* Copy Constructor */
    public:big_int(const big_int &num) {
        this->signum = num.get_signum();
        this->len = num.get_len();
        this->mag = new char[this->len];
        for(int i=0; i<this->len; ++i)
            this->mag[i] = num.get_mag()[i];
    }

    /* Destructor */
    public:~big_int() {
        delete[] mag;
    }

    /* Getter functions */
    public:int get_signum() const {
        return signum;
    }

    public:char *get_mag() const {
        return mag;
    }

    public:int get_len() const {
        return len;
    }

    /*
        * Compares the magnitude of mag1 and mag2
        * Returns 1 if mag1 > mag2
        * Returns -1 if mag1 < mag2
        * Returns 0 otherwise
    */
    private:int comp(char *mag1, int len1, char *mag2, int len2) {
        if(len1 > len2)
            return 1;
        else if(len1 < len2)
            return -1;
        
        for(int i=len1-1; i>=0; --i) {
            if(mag1[i] > mag2[i])
                return 1;
            else if(mag1[i] < mag2[i])
                return -1;
        }
        return 0;
    }
    
    /* 
        * Addition of two magnitudes 
    */
    public:int sum(char *mag1, int len1, char *mag2, int len2, char **res) {
        /* To ensure that mag2 has greater length */
        if(len1 > len2) {
            swap(mag1, mag2);
            swap(len1, len2);
        }

        /* allocate storage to store the result */
        int len = len2 + 1;
        char *temp = new char[len]();

        /* ------------------------ Processing ---------------- */
        /* add first len1 elements */
        int c = 0;
        for(int i=0; i<len1; ++i) {
            int sum = mag1[i] + mag2[i] + c;
            temp[i] = sum%10;
            c = (sum/10)%10;
        }
        /* add the remaining len2 - len1 elements */
        for(int i=len1; i<len2; ++i) {
            int sum = mag2[i] + c;
            temp[i] = sum%10;
            c = (sum/10)%10;
        }
        /* add the carry to the result */
        temp[len2] = c;
        if(c==0) --len;
        /* ------------------------------------------------------ */

        *res = temp;
        return len;
    }

    /* 
        * Absolute difference between two magnitudes
    */
    private:int diff(char *mag1, int len1, char *mag2, int len2, char **res) {
        /* Ensure that mag1 is higher */
        if(comp(mag1, len1, mag2, len2) < 0) {
            swap(mag1, mag2);
            swap(len1, len2);
        }

        int len = len1;
        char *temp = new char[len];

        /* Subtraction of mag2 from mag1 */
        int b = 0;
        /* subtract least significant len2 digits */
        for(int i=0; i<len2; ++i) {
            if(mag1[i] - b >= mag2[i]) {
                temp[i] = mag1[i] - b - mag2[i];
                b = 0;
            } else {
                temp[i] = 10 + mag1[i] - b - mag2[i];
                b = 1;
            }
        }
        /* subtract remaining digits */
        for(int i=len2; i<len1; ++i) {
            if(mag1[i] - b >= 0) {
                temp[i] = mag1[i] - b;
                b = 0;
            } else {
                temp[i] = 10 + mag1[i] - b;
                b = 1;
            }
        }

        /* eliminate extra zeros at front */
        while(len > 0 && temp[len-1] == 0)
            --len;
        
        *res = temp;
        return len;
    }

    /* 
        * < Operator
    */
    public:bool operator<(const big_int &num) {
        return comp(this->mag, this->len, num.get_mag(), num.get_len()) < 0;
    }

    /*
        * <= operator
    */
    public:bool operator<=(const big_int &num) {
        return comp(this->mag, this->len, num.get_mag(), num.get_len()) <= 0;
    }

    /*
        * > operator
    */
    public:bool operator>(const big_int &num) {
        return comp(this->mag, this->len, num.get_mag(), num.get_len()) > 0;
    }

    /*
        * >= operator
    */
    public:bool operator>=(const big_int &num) {
        return comp(this->mag, this->len, num.get_mag(), num.get_len()) >= 0;
    }

    /*
        * - unary operator
    */
    public:big_int operator-() {
        return big_int(this->signum * -1, this->mag, this->len);
    }

    /*
        * + operator
    */
    public:big_int operator+(const big_int &num) {
        /* handle the cases when either is zero */
        if(num.get_signum() == 0)
            return *this;
        else if(this->signum == 0)
            return num;
        
        char *mag = nullptr;
        int len;
        int signum;
        if(this->signum * num.get_signum() > 0) {
            len = this->sum(this->mag, this->len, num.get_mag(), num.get_len(), &mag);
            signum = this->signum;
        } else {
            len = this->diff(this->mag, this->len, num.get_mag(), num.get_len(), &mag);
            if(comp(this->mag, this->len, num.get_mag(), num.get_len()) > 0) {
                signum = this->signum;
            } else {
                signum = num.get_signum();
            }
        }

        big_int res(signum, mag, len);
        delete[] mag;

        return res;
    }

    /* 
        * - operator
    */
    public:big_int operator-(big_int &num) {
        return *this + (-num);
    }

    public:void print() {
        if(len == 0) {
            cout<<0<<"\n";
            return;
        }
        if(signum < 0)
            cout<<"-";
        for(int i=len-1; i>=0; --i) {
            cout<<(int)mag[i];
        }
        cout<<"\n";
    }

    /*
        * multipy two magnitudes
    */
    private:int mul(char *mag1, int len1, char *mag2, int len2, char **res) {
        if(len1 == 0 || len2 == 0)
            return 0;
        /* To ensure that len1 is greater */
        if(comp(mag1, len1, mag2, len2) < 0) {
            swap(mag1, mag2);
            swap(len1, len2);
        }

        int len = len1 + len2;
        /* stores final result of multiplication */
        char *mag = new char[len]();
        /* stores intermediate values */
        char *temp = new char[len]();

        /* multiplication algorithm */
        for(int i=0; i<len2; ++i) {
            for(int j=0; j<i; ++j)
                temp[j] = 0;
            int c = 0;
            for(int j=i; j<i+len1; ++j) {
                int p = mag1[j-i] * mag2[i] + c;
                temp[j] = p%10;
                c = (p/10)%10;
            }
            temp[i+len1] = c;

            char *sum_mag;
            /* add mag and temp */
            sum(mag, len, temp, len, &sum_mag);
            /* copy result into mag */
            memcpy(mag, sum_mag, len);
            /* delete the memory allocated by sum function */
            delete[] sum_mag;
        }
        delete[] temp;

        /* remove unnecessary zeros from front */
        while(len>0 && mag[len-1] == 0)
            --len;
        
        *res = mag;
        return len;
    }

    /*
        * Operator * 
    */
   public:big_int operator*(const big_int &num) {
       int signum = this->signum * num.get_signum();
       char *mag = nullptr;
       int len = mul(this->mag, this->len, num.get_mag(), num.get_len(), &mag);

       big_int res(signum, mag, len);
       delete[] mag;

       return res;
   }


};

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
    int signum1, signum2;
    int len1, len2;
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    char *mag1 = new char[s1.size()];
    char *mag2 = new char[s2.size()];

    tie(signum1, len1) = convert(s1, &mag1);
    tie(signum2, len2) = convert(s2, &mag2);



    
    big_int bi1(signum1, mag1, len1);
    big_int bi2(signum2, mag2, len2);

    // bi1.print();
    // bi2.print();
    big_int bi3 = bi1 + bi2;
    big_int bi4 = bi1 - bi2;
    bi3.print();
    bi4.print();

    big_int bi5 = bi1 * bi2;
    bi5.print();


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