#include <iostream>
#include <string>
#include <fstream>

double fun(std::string s, double kol_elem){
    std::fstream file;
    file.open(s);
    double time;
    if (file.is_open())
        file >> time;
    else
    {
        std::cerr << "error of open file\n";
        return 0;
    }

    file.close();

    return  time/static_cast<double>(kol_elem) ;
}
int main() {
    std::string s="time_1000.0.9.txt";
    std::string s1="time_1000.100.1000.txt";
    std::string s2="time_1000.1000.10000.txt";

    std::string s3="time_10000.0.9.txt";
    std::string s4="time_10000.100.1000.txt";
    std::string s5="time_10000.1000.10000.txt";

    std::string s6="time_100000.0.9.txt";
    std::string s7="time_100000.100.1000.txt";
    std::string s8="time_100000.1000.10000.txt";
const int k1=1000, k2=10000, k3=100000;
    std::cout<<"0..10: "<<fun(s, k1)<<std::endl;
    std::cout<<"100..1'000: "<<fun(s1, k1)<<std::endl;
    std::cout<<"1'000..10'000: "<<fun(s2, k1)<<std::endl;
std::cout<<std::endl;std::cout<<std::endl;
    std::cout<<"0..10: "<<fun(s3, k2)<<std::endl;
    std::cout<<"100..1'000: "<<fun(s4, k2)<<std::endl;
    std::cout<<"1'000..10'000: "<<fun(s5, k2)<<std::endl;
std::cout<<std::endl;std::cout<<std::endl;
    std::cout<<"0..10: "<<fun(s6, k3)<<std::endl;
    std::cout<<"100..1'000: "<<fun(s7, k3)<<std::endl;
    std::cout<<"1'000..10'000: "<<fun(s8, k3)<<std::endl;


    return 0;
}
