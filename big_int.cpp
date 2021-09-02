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
        store the magnitude of the integer with least significant
        digit on the left
    */
    char *mag;

    /*
        stores the length of the integer 
    */
    int len;

    /* Constructor */
    public:big_int(int signum, char *mag, int len) {
        this->signum = signum;
        this->len = len;
        this->mag = new char[len];
        for(int i=0; i<len; ++i)
            this->mag[i] = mag[i];
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

    /* Addition */
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
        /* ------------------------------------------------------ */

        *res = temp;
        return len;
    }
};

int main() {

    big_int bi(0, nullptr, 0);
    char mag1[] = {1, 2, 3, 4, 5, 3, 4};
    char mag2[] = {1, 2, 3, 4, 5, 4, 4, 4, 4, 4};

    char *res;
    int len = bi.add(mag1, 1, mag2, 1, &res);
    cout<<len<<"\n";
    for(int i=0; i<len; ++i) {
        cout<<(int)res[i]<<" ";
    }
    cout<<"\n";
}