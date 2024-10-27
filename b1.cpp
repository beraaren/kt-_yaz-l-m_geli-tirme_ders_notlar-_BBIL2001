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


class dinamikDizi
{
    dinamikDizi () {
        kabiplus(5);
        _kapBoyut = 5;
        _elemansayısı = 0;
    }

    ~dinamikDizi () {
        delete _kap;
    }


    void kabiplus(int yenibout) {
        _kap = new int[yenibout];
        _kapBoyut = yenibout;
    }

    void ElemanEklae(int elaman) {
        _elemansayısı++;
        if (_kapBoyut < _elemansayısı) {
            kabiplus(_kapBoyut+5);
            _kap[_elemansayısı] = elaman;
        } else
        {
            _kap[_elemansayısı] = elaman;
        }
        
    }

private:
    int *_kap;
    int _kapBoyut;
    int _elemansayısı;

};


 
int main() {
    dinamikDizi a;

    a.ElemanEklae(1)
    a.ElemanEklae(2)
    a.ElemanEklae(3)
    a.ElemanEklae(4)
    a.ElemanEklae(5)
    a.ElemanEklae(6)
    a.ElemanEklae(7)
    a.ElemanEklae(8)

    return 0;
}