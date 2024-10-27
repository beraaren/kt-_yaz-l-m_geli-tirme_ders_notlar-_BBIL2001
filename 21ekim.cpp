#include<iostream>

using namespace std;

class DinamikDizi {
public:
    DinamikDizi() {
        _a = new int[2];
        _kapasite = 2;
        _elemanSayisi = 0;
    }

    ~DinamikDizi() {
        delete[] _a;
    }
    DinamikDizi(const DinamikDizi &diger) = delete;

    void elemanEkle(int yeniEleman) {
        _a[_elemanSayisi++] = yeniEleman;
        if (_elemanSayisi == _kapasite) {
            diziyiKontrolluBuyut();
        }
    }

    int elemanCikar(int index) {
        if (index < 0 || index >= _elemanSayisi) {
            throw std::out_of_range("Geçersiz indeks: Dizi sınırlarının dışında.");
        }
        auto sonuc = _a[index];
        for (int i = index; i < _elemanSayisi - 1; i++) {
            _a[i] = _a[i + 1];
        }
        _elemanSayisi--;
        return sonuc;
    }

    int ilkElemaniCikar() {
        return elemanCikar(0);
    }

    int sonElemaniCikar() {
        return elemanCikar(_elemanSayisi - 1);
    }

    int elemanGetir(int index) {
        if (index >= 0 && index < _elemanSayisi) {
            return _a[index];
        } else {
            throw std::out_of_range("Geçersiz indeks: Dizi sınırlarının dışında.");
        }
    }

/// operetörleri atayabiliryorsun  
    int& operator[](int index) {
        if (index >= 0 && index < _elemanSayisi) {
            return _a[index];
        } else {
            throw std::out_of_range("Geçersiz indeks: Dizi sınırlarının dışında.");
        }
    }

/// operetörleri atayabiliryorsun 

    int elemanSayisi() {
        return _elemanSayisi;
    }

    int kapasite() {
        return _kapasite;
    }

    void elemanDegistir(int index, int yeniDeger) {
        if (index >= 0 && index < _elemanSayisi) {
            _a[index] = yeniDeger;
        } else {
            throw std::out_of_range("Geçersiz indeks: Dizi sınırlarının dışında.");
        }
    }

private:
    void diziyiKontrolluBuyut() {
        auto eskiKap = _a;
        auto eskiKapasite = _kapasite;
        _kapasite *= 2;
        _a = new int[_kapasite];
        for (auto i = 0; i < eskiKapasite; i++) {
            _a[i] = eskiKap[i];
        }
        delete[] eskiKap;
    }

    int *_a;
    int _kapasite;
    int _elemanSayisi;
};

int main() {
    DinamikDizi dd;
    dd.elemanEkle(10);
    dd.elemanEkle(20);
    dd.elemanEkle(30);

    cout << "Eleman sayısı: " << dd.elemanSayisi() << endl;
    cout << "Kapasite: " << dd.kapasite() << endl;

    cout << "Elemanlar: ";
    for (int i = 0; i < dd.elemanSayisi(); i++) {
        cout << dd.elemanGetir(i) << " ";
    }
    cout << endl;

    dd.elemanDegistir(1, 40);
    cout << "Değiştirilen eleman: " << dd.elemanGetir(1) << endl;

    dd[2] = 50;

    cout << "Değiştirilen eleman: " << dd[2] << endl;

    dd.elemanCikar(0);
    cout << "Silinen eleman: " << dd.elemanGetir(0) << endl;

    return 0;
}