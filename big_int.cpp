#include<iostream>
#include<cstring>

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
    public:int comp(char *mag2, int len2) {
        char *mag1 = this->mag;
        int len1 = this->len;
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
    public:int sum(char *mag2, int len2, char **res) {
        char *mag1 = this->mag;
        int len1 = this->len;
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
    public:int diff(char *mag2, int len2, char **res) {
        char *mag1 = this->mag;
        int len1 = this->len;
        /* Ensure that mag1 is higher */
        if(comp(mag2, len2) < 0) {
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
        * Operator overloading for addition
    */
    public:big_int operator+(big_int &num) {
        /* handle the cases when either is zero */
        if(num.get_signum() == 0)
            return *this;
        else if(this->signum == 0)
            return num;
        
        char *mag;
        int len;
        int signum;
        if(this->signum * num.get_signum() > 0) {
            len = this->sum(num.get_mag(), num.get_len(), &mag);
        } else {
            len = this->diff(num.get_mag(), num.get_len(), &mag);
            signum = comp(num.get_mag(), num.get_len());
        }

        big_int res(signum, mag, len);
        delete[] mag;

        return res;
    }

    public:void print() {
        if(signum < 0)
            cout<<"-";
        for(int i=len-1; i>=0; --i) {
            cout<<(int)mag[i];
        }
        cout<<"\n";
    }


};

int main() {
    char mag1[] = {1, 2, 3, 4, 5, 3, 4};
    char mag2[] = {0, 2, 4, 4, 5, 3, 4, 4, 4, 4};

    big_int bi1(1, mag1, 7);
    big_int bi2(1, mag2, 10);

    bi1.print();
    bi2.print();
    big_int bi3 = bi1 + bi2;
    bi3.print();
}