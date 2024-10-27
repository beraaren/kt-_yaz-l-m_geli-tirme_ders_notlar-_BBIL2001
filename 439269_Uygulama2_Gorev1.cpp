#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

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

class Yigin {
public:
    void ekle(int eleman) {
        _dizi.elemanEkle(eleman);
    }

    int cikar() {
        return _dizi.sonElemaniCikar();
    }

    int bak() {
        return _dizi.elemanGetir(_dizi.elemanSayisi() - 1);
    }

    int elemanSayisi() {
        return _dizi.elemanSayisi();
    }

    bool bosMu() {
        return _dizi.elemanSayisi() == 0;
    }

private:
    DinamikDizi _dizi;
};

/**
 * @class PostfixCalculator
 * @brief Postfix notasyonu çalıştıran sınıf.
 */
class PostfixCalculator {
public:
    /**
     * @brief Verilen postfix ifadesini çalıştırır ve sonucunu döndürür.
     *
     * @param postfix Verilen postfix ifadesi
     * @return Postfix ifadesinin sonucu
     */
    int calistir(const std::string& postfix) {
        Yigin degerler;

        for (size_t i = 0; i < postfix.size(); i++) {
            char kr = postfix[i];

            if (kr >= '0' && kr <= '9') {
                degerler.ekle(kr - '0');  // karakteri tam sayıya çevir
            } else {
                int sag = degerler.cikar();
                int sol = degerler.cikar();
                switch (kr) {
                    case '+':
                        degerler.ekle(sol + sag);
                        break;
                    case '-':
                        degerler.ekle(sol - sag);
                        break;
                    case '*':
                        degerler.ekle(sol * sag);
                        break;
                    case '/':
                        if (sag == 0) {
                            throw std::runtime_error("Sıfıra bölme hatası.");
                        }
                        degerler.ekle(sol / sag);
                        break;
                    case '%':
                        degerler.ekle(sol % sag);
                        break;
                    case '^':
                        degerler.ekle(static_cast<int>(pow(sol, sag)));
                        break;
                    default:
                        throw std::invalid_argument("Geçersiz işlem operatörü.");
                }
            }
        }

        if (degerler.elemanSayisi() != 1) {
            throw std::runtime_error("Geçersiz postfix ifade.");
        }

        return degerler.cikar();
    }
};

int main() {
    PostfixCalculator hesaplayici;
    std::string postfix = "23^5+2/"; 
    try {
        int sonuc = hesaplayici.calistir(postfix);
        std::cout << "Sonuç: " << sonuc << std::endl;  // Çıktı: Sonuç: 48
    } catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
    }
    return 0;
}
