#include <iostream>
#include <utility>
#include <vector>
#include <bits/stdc++.h>
#include <queue>
#include <windows.h>


class RSA{
protected:
    int p,  q, mod, pi, e, d;

    static long int calculateD( long int e, long int t);
    static bool nod_evklid(int a, int b);//проверка, является ли число простым
    static bool is_prime(int m);//алгоритм Миллера-Рабина
    void create_prime_numbers();
    void create_keys();
    static long powerFast(long num, long deg);//алгоритм быстрого возведения в степень
    static long int decrypt(long int me, long int d, long int mod);

};
class Crypt:RSA{
private:
    std::vector<char> arr_en = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::string line;
    std::string s;//line for save new
    std::queue<int>elems_queue;
public:
    explicit Crypt(std::string str) : RSA(){
        line=std::move(str);
        rsa_algorithm();
    }

    void encryption();
    void decryption();
    void print_encrypted_line();
    void print_decrypted_line();
    ~Crypt()= default;;
private:
    void rsa_algorithm(){
        std::cout<<"do you want to enter two prime numbers? [y, n]\n";
        char yes_no; std::cin>>yes_no;
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
    static void print(std::queue<int> a);
};
int main() {

    std::string str="text";
    Crypt me(str);
me.encryption();
me.print_encrypted_line();
me.decryption();
me.print_decrypted_line();

    return 0;
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
long int RSA::decrypt(long int me, long int d, long int mod){
    long int current, result;

    current = me;
    result = 1;

    for ( long int j = 0; j < d; j++ )
    {
        result = result * current;
        result = result % mod;
    }

    return result;
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
long int RSA::calculateD( long int e, long int t)
{
    long int d;
    long int k = 1;
    while (true)
    {
        k = k + t;
        if ( k % e == 0)
        {
            d = (k / e);
            return d;
        }
    }

}
bool RSA::nod_evklid(int a, int b)
{
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
    for(auto cur: prime_numbers)
    {
        e=cur;
        if(e<pi && nod_evklid(e, pi))
            break;
    }
    d=calculateD(e, pi);
    std::cout<<"p= "<<p<<"  q= "<<q<<"  pi= "<<pi<<std::endl;
    std::cout<<"public key\n{e, mod}  {"<<e<<", "<<mod<<"}";
    std::cout<<"\nprivate key\nd, mod}  {"<<d<<", "<<mod<<"}";

}
void RSA::create_prime_numbers() {
    do{
        p=rand();
        q=rand();

    } while (p==q);
    while(true){
        if(is_prime(p)){
            if(is_prime(q)){
                break;
            }
            else{
                while(!is_prime(q))
                    q++;
                break;
            }
        }else{
            while(!is_prime(p))
                p++;
            if(is_prime(q)){
                break;
            }
            else{
                while(!is_prime(q))
                    q++;
                break;
            }
        }
    }

}
bool RSA::is_prime(int m){

    int r = 1000;
    int t = m-1;
    int s = 0;
    bool b = true;
    if(m%2==0){
        return false;
    }
    if(m==1){
        return false;
    }
    if(m==2){
        return true;
    }
    while(t%2==0 || b){
        b = false;
        s++;
        t=t/2;
    }
    for(int i=1;i<r+1;i++){
        int a = 2+rand()%(m-2);
        // int x = int(float(pow(float(a),float(t))))%m;
        int x = int(float(powerFast(a, t)))%m;

        if((x==1)||(x==m-1)){
            continue;
        }
        for(int j=1;j<s;j++){
            //x=int(float(pow(float(x),2)))%m;
            x=int(float(powerFast(x, 2)))%m;

            if(x==1){
                return false;
            }
            if(x==m-1){
                continue;
            }
        }
    }
    return true;
}


