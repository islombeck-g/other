#include <iostream>
#include <utility>
#include <vector>
#include <bits/stdc++.h>
#include <queue>

class RSA{
protected:
    int p,  q, mod, pi, e, d;

    static bool nod_evklid(int a, int b); //проверка, является ли число простым
    bool isPrime(int n);                 //алгоритм Миллера-Рабина
    bool miller_test(int w, int n);    //алгоритм Миллера-Рабина
    static int power(int x, unsigned int y, int p);//алгоритм Миллера-Рабина
    void create_prime_numbers();//cin>>p>>q
    void create_keys();//p, q, mod, pi, e, d
    static long powerFast(long num, long deg);//алгоритм быстрого возведения в степень
    static long int decrypt(long int me, long int d, long int mod);//d*e % mod
    int gcd (int a, int b, int &x, int& y);//Расширенный алгоритм Евклида
};
class Crypt:RSA{
private:
    std::vector<char> arr_en = {' ','b','a','j','x','w','f','g','c','t','h','k','l','z','n','o','s','q','r','p','i','u','v','e','d','y','m'};
    std::string line;//for save not encrypted line
    std::string s;//line for return result
    std::queue<int>elems_queue;//line for save encrypted line
public:
    explicit Crypt(std::string str) : RSA(){
        line=std::move(str);
        rsa_algorithm();
    }
    void encryption();
    void decryption();
    void print_encrypted_line();
    void print_decrypted_line();
    ~Crypt()= default;
private:
    void rsa_algorithm();
    static void print(std::queue<int> a);
};
int main() {
    srand(time(nullptr));
    std::string str="text me something";
    Crypt me(str);
        me.encryption();
        me.print_encrypted_line();
        me.decryption();
        me.print_decrypted_line();

    return 0;
}
void Crypt::rsa_algorithm(){
    std::cout<<"do you want to enter two prime numbers? [y, n]\n";
    char yes_no;
    std::cin>>yes_no;
    //yes_no='n';
    switch (yes_no) {
        case 'y':
            std::cout<<"p= ";std::cin>>p;
            std::cout<<"q= ";std::cin>>q;
            break;
        case 'n':
            create_prime_numbers();
            break;
        default:
            std::cerr<<"error of entering prime numbers\n";
            return;
    }
    create_keys();

}
void Crypt::print_decrypted_line(){
    std::cout<<"\ndecrypted line: "<<s<<"\n";
}
void Crypt::print_encrypted_line(){
    std::cout<<"\nencrypted line:\n";
    print(elems_queue);
}
void Crypt::print(std::queue<int> a){
    while(!a.empty()){
        std::cout<<a.front()<<" ";
        a.pop();
    }
    std::cout<<"\n";
}
void Crypt::encryption() {
    std::vector<char>::iterator it;
    for(char & i : line)
    {
        it = find(arr_en.begin(), arr_en.end(), i);
        int elem= it-arr_en.begin();
        int result=powerFast(elem, e) % mod;
        elems_queue.push(result);
    }
}
void Crypt::decryption(){
    std::queue<int> que;
    while(!elems_queue.empty()){
        int me=elems_queue.front();
        elems_queue.pop();
        int t=decrypt(me, d, mod);
        que.push(t);
    }
    //закидываю расшифрованные элементы из очереди в строку
    while(!que.empty()){
        int me=que.front();
        que.pop();
        s.push_back(arr_en[me]);
    }
}
int  RSA::power(int x, unsigned int y, int p){
    int res = 1;      // Initialize result
    x = x % p;  // Update x if it is more than or
    // equal to p
    while (y > 0){
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}
int  RSA::gcd(int a, int b, int &x, int& y) {
    if (b < a){
        int t = a;
        a = b;
        b = t;
    }
    if (a == 0){
        x = 0;
        y = 1;
        return b;
    }
    int u = gcd(b % a, a, x, y);
    int newY = x;
    int newX = y - (b / a) * x;
    x = newX;
    y = newY;
    return u;
}
long RSA::powerFast(long num, long deg) {
    long result = 1;
    while(deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            num *= num;
        }
        else {
            deg--;
            result *= num;
        }
    }
    return result;
}
bool RSA::nod_evklid(int a, int b){
    auto cur=1;
    for(int i=2; i<=a && i<=b; i++)
        if(a%i==0 && b%i==0)
            cur++;

    if(cur==1)//если cur==1 то оно взаимопростое
        return true;
    return false;
}
void RSA::create_keys(){
    mod=p*q;
    pi=(p-1)*(q-1);
    std::vector<int> prime_numbers ={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499};
    for(auto cur: prime_numbers){
        e=cur;
        if(e<pi && nod_evklid(e, pi))
            break;
    }
    int a1;
    gcd(e, pi, d, a1);
    if(d<0){
        d+=pi;
    }
    std::cout<<"p= "<<p<<"  q= "<<q<<"  pi= "<<pi<<std::endl;
    std::cout<<"public key\n{e, mod}  {"<<e<<", "<<mod<<"}";
    std::cout<<"\nprivate key\n{d, mod}  {"<<d<<", "<<mod<<"}";
}
void RSA::create_prime_numbers() {
    do{
        int A=1, B=99;
        p=rand()%(B-A+1) + A;//[A, B]
        q=rand()%(B-A+1) + A;

    } while (p==q);
    while(true){
        if(isPrime(p)){
            if(isPrime(q)){
                break;
            }
            else{
                while(!isPrime(q)){
                    q+=1;
                }
                std::cout<<"q=true\n";
                break;
            }
        }else{
            while(!isPrime(p)){
                p+=1;
            }
            if(isPrime(q)){
                break;
            }
            else{
                while(!isPrime(q)){
                    q+=1;
                }
                break;
            }
        }
    }
}
bool RSA::miller_test(int w, int n){
    // Pick a random number in [2..n-2]
    // Corner cases make sure that n > 4
    int a = 2 + rand() % (n - 4);
    // Compute a^d % n
    int x = power(a, w, n);
    if (x == 1  || x == n-1)
        return true;
    while (w != n-1){
        x = (x * x) % n;
        w *= 2;
        if (x == 1)      return false;
        if (x == n-1)    return true;
    }
    return false;
}
bool RSA::isPrime(int n){
    int k=4;
    // Corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
    // Find r such that n = 2^d * r + 1 for some r >= 1
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    // Iterate given number of 'k' times
    for (int i = 0; i < k; i++)
        if (!miller_test(d, n))
            return false;
    return true;
}
long int RSA::decrypt(long int me, long int d, long int mod){
    long int current, result;
    current = me;
    result = 1;
    for ( long int j = 0; j < d; j++ ){
        result = result * current;
        result = result % mod;
    }
    return result;
}
