#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <queue>
#include <windows.h>

//алгоритм быстрого возведения в степень
long powerFast(long num, long deg);
//вывод в конслоль очереди
void show_queue(std::queue<int> a);
//проверка, является ли число простым
bool nod_evklid(int a, int b);
//расширенный алгоритм Евклида
int gcd (int a, int b, int & x, int & y);
//вычисление числа d
long int calculateD( long int e, long int t);
//расшифровка (возведение в степень и деление по модулю)
long int decrypt(long int me, long int d, long int mod);

std::string create_rsa(std::string line)
{       std::vector<char> arr_en = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        std::vector<int> prime_numbers ={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499};
    //create open and protected keys
        int p,  q, mod, pi, e;
        std::string s{};
        do{
        p=prime_numbers[rand()%(prime_numbers.size()-1)];
        q= prime_numbers[rand()%(prime_numbers.size()-1)];
        } while (p==q);
        mod=p*q;
        pi=(p-1)*(q-1);
        for(auto cur: prime_numbers)
        {
            e=cur;
            if(e<pi && nod_evklid(e, pi)== true)
                break;
        }
    std::cout<<"e= "<<e<<"  pi= "<<pi<<"\n";
    std::cout<<"p= "<<p<<"  q= "<<q<<"mod= "<<mod<<std::endl;
    int d=calculateD(e, pi);
    std::cout<<"{d, mod}  {"<<d<<", "<<mod<<"}";
    std::cout<<"\nстрока для шифрования:"<<line<<std::endl;
    std::queue<int>elems_queue;


    //шифрование
    std::vector<char>::iterator it;
    for(char & i : line)
    {
        it = find(arr_en.begin(), arr_en.end(), i);
        int elem= it-arr_en.begin();
        int result=powerFast(elem, e) % mod;
        elems_queue.push(result);
    }
    std::cout<<"Зашифрованные элементы:\n";show_queue(elems_queue);

    //расшифровка

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

    return s;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);//для корректного отображения русских символов
    srand(time(nullptr));

    std::string s="hello it is";
    std::string new_line= create_rsa(s);
    std::cout<<"\n"<<"ready-line:"<<new_line;
    return 0;
}

long powerFast(long num, long deg) {
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
void show_queue(std::queue<int> a){
    while(!a.empty()){
        std::cout<<a.front()<<" ";
        a.pop();
    }
    std::cout<<"\n";
}
bool nod_evklid(int a, int b)
{
    auto cur=1;
    for(int i=2; i<=a && i<=b; i++)
        if(a%i==0 && b%i==0)
            cur++;

    if(cur==1)//если cur==1 то оно взаимопростое
        return true;
    return false;
}
int gcd (int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd (b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
long int calculateD( long int e, long int t)
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
long int decrypt(long int me, long int d, long int mod){
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