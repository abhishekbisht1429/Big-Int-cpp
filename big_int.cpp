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

    /* Destructor */
    public:~big_int() {
        delete[] mag;
    }

    /* Getter functions */
    public:int get_signum() {
        return signum;
    }

    public:char *get_mag() {
        return mag;
    }

    public:int get_len() {
        return len;
    }

    /*
        * Compares the magnitude of mag1 and mag2
        * Returns 1 if mag1 > mag2
        * Returns -1 if mag1 < mag2
        * Returns 0 otherwise
    */
    public:int comp(char *mag1, int len1, char *mag2, int len2) {
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
    public:int add(char *mag1, int len1, char *mag2, int len2, char **res) {
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
    public:int diff(char *mag1, int len1, char *mag2, int len2, char **res) {
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


};

int main() {

    big_int bi(0, nullptr, 0);
    char mag1[] = {1, 2, 3, 4, 5, 3, 4};
    char mag2[] = {0, 2, 4, 4, 5, 3, 4, 4, 4, 4};

    char *res;
    int len = bi.diff(mag1, 7, mag2, 10, &res);
    // cout<<len<<"\n";
    for(int i=0; i<len; ++i) {
        cout<<(int)res[i]<<" ";
    }
    cout<<"\n";
}