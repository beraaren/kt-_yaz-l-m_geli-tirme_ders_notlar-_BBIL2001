#include <iostream>
#include <string>

using namespace std;

enum Cinsiyet { 
    Kadın = 1,
    Erkek
};

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
    Kisi kişiler[37000];  // Aynı amacı taşıyan verileri grupla: kişisel bilgiler
    int kisisayisi;  // Üniversitedeki kişi sayısı
};

// Kişi ekleme fonksiyonu
void Insanekle(string tckimlik1, string isim1, string soyisim1, string uyruk1, Cinsiyet cinsiyet1, string dogumtarihi1, int &kisisayisi, Üniversite &uni) {
    uni.kişiler[kisisayisi].tckimlik = tckimlik1;
    uni.kişiler[kisisayisi].isim = isim1;
    uni.kişiler[kisisayisi].soyisim = soyisim1;
    uni.kişiler[kisisayisi].uyruk = uyruk1;
    uni.kişiler[kisisayisi].cinsiyet = cinsiyet1;
    uni.kişiler[kisisayisi].dogumtarihi = dogumtarihi1;
    kisisayisi++;  // Kişi sayısını artır
}

int main() {
    Üniversite uni;  // Üniversite nesnesi
    uni.kisisayisi = 0;  // Başlangıçta kişi sayısı 0
    
    // Kişi ekleme örneği
    Insanekle("12345678901", "Bera", "Eren", "Türk", Erkek, "01.01.2000", uni.kisisayisi, uni);

    // Ekleme sonrası kişinin bilgilerini yazdır (örnek)
    cout << "Kişi: " << uni.kişiler[0].isim << " " << uni.kişiler[0].soyisim << endl;
    cout << "TCKimlik: " << uni.kişiler[0].tckimlik << endl;
    cout << "Cinsiyet: " << (uni.kişiler[0].cinsiyet == Erkek ? "Erkek" : "Kadın") << endl;
    cout << "Doğum Tarihi: " << uni.kişiler[0].dogumtarihi << endl;

    return 0;
}
