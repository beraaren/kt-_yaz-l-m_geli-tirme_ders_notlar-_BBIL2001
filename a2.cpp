#include <iostream>
#include <string>

using namespace std;

enum Cinsiyet { 
    Kadın = 1,
    Erkek
};

// Kisi sınıfı
class Kisi {
private:  // Üye değişkenler (veriler genelde private olur)
    string tckimlik;
    string isim;
    string soyisim;
    string uyruk;
    Cinsiyet cinsiyet;
    string dogumtarihi;

public:  // Public metodlar (getter ve setter fonksiyonları)
    // Yapıcı fonksiyon (constructor)
    Kisi(string tckimlik, string isim, string soyisim, string uyruk, Cinsiyet cinsiyet, string dogumtarihi) {
        this->tckimlik = tckimlik;
        this->isim = isim;
        this->soyisim = soyisim;
        this->uyruk = uyruk;
        this->cinsiyet = cinsiyet;
        this->dogumtarihi = dogumtarihi;
    }

    // Getter fonksiyonları
    string getTCKimlik() const { return tckimlik; }
    string getIsim() const { return isim; }
    string getSoyisim() const { return soyisim; }
    string getUyruk() const { return uyruk; }
    Cinsiyet getCinsiyet() const { return cinsiyet; }
    string getDogumTarihi() const { return dogumtarihi; }

    // Kişi bilgilerini yazdırma
    void yazdir() const {
        cout << "Kişi Bilgileri: " << endl;
        cout << "İsim: " << isim << " " << soyisim << endl;
        cout << "TCKimlik: " << tckimlik << endl;
        cout << "Uyruk: " << uyruk << endl;
        cout << "Cinsiyet: " << (cinsiyet == Erkek ? "Erkek" : "Kadın") << endl;
        cout << "Doğum Tarihi: " << dogumtarihi << endl;
    }
};

// Üniversite sınıfı
class Universite {
private:  // Üye değişkenler
    Kisi* kişiler[37000];  // Dinamik olarak kişiler dizisi
    int kisiSayisi;

public:  // Public metodlar
    // Yapıcı fonksiyon
    Universite() {
        kisiSayisi = 0;
    }

    // Yeni kişi ekleme fonksiyonu
    void insanEkle(string tckimlik, string isim, string soyisim, string uyruk, Cinsiyet cinsiyet, string dogumtarihi) {
        kişiler[kisiSayisi] = new Kisi(tckimlik, isim, soyisim, uyruk, cinsiyet, dogumtarihi);  // Yeni kişi ekleniyor
        kisiSayisi++;
    }

    // Tüm kişileri yazdırma
    void tumKisileriYazdir() const {
        for (int i = 0; i < kisiSayisi; i++) {
            kişiler[i]->yazdir();
            cout << endl;
        }
    }

    // Kişi sayısını döndürme
    int getKisiSayisi() const {
        return kisiSayisi;
    }
};

int main() {
    Universite uni;  // Üniversite sınıfı nesnesi
    
    // Üniversiteye kişiler ekleyelim
    uni.insanEkle("12345678901", "Bera", "Eren", "Türk", Erkek, "01.01.2000");
    uni.insanEkle("98765432101", "Elif", "Yılmaz", "Türk", Kadın, "15.05.1999");

    // Tüm kişileri yazdıralım
    uni.tumKisileriYazdir();

    return 0;
}
