#include <iostream>
#include <string>

using namespace std;

enum Cinsiyet { 
    Kadın = 1,
    Erkek
};


//string tckimlik[37000];
//string isim[37000];
//string soyisim[37000];
//string uyruk[37000];
//Cinsiyet cinsiyet[37000];
//string dogumtarihi[37000];
struct Kisi {
    string tckimlik;
    string isim;
    string soyisim;
    string uyruk;
    Cinsiyet cinsiyet;
    string dogumtarihi;
};

struct Üniversite
{
    Kisi kişiler[37000]; // amacı aynı olan verileri guruplan dırmak kapsülemek. 
    int kisisayısı;
};



void Insanekle(string tckimlik1, string isim1, string soyisim1,string uyruk1,Cinsiyet cinsiyet1,string dogumtarihi1, int &kisisayısı, Üniversite &uni) {
    // string tckimlik[kisisayısı]=tckimlik1;
    // string isim[kisisayısı]=isim1;
    // string soyisim[kisisayısı]=soyisim1;
    // string uyruk[kisisayısı]=uyruk1;
    // Cinsiyet cinsiyet[kisisayısı]=cinsiyet1;
    // string dogumtarihi[kisisayısı]=dogumtarihi1;
    // kisisayısı++

    
}


int main() {
    kisisayısı=0;
     

    // Insanekle("12345", "bera", "eren", "türk", cinsiyete)



    return 0;
}
