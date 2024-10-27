#include <iostream>

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


class OncelikKuyrugu {
public:
    OncelikKuyrugu() {
        _dizi.elemanEkle(0);
    }

    void ekle(int eleman) {
        _dizi.elemanEkle(eleman);
        asagidanYukariyaKuyrukDuzenle();
    }

    int cikar() {
        auto sonuc = _dizi.elemanGetir(1);
        auto sonDeger = _dizi.sonElemaniCikar();
        if (bosMu()) {
            return sonuc;
        }
        _dizi.elemanDegistir(1, sonDeger);
        yukaridanAsagiyaKuyrukDuzenle();
        return sonuc;
    }

    int elemanSayisi() {
        return _dizi.elemanSayisi();
    }

    bool bosMu() {
        if (_dizi.elemanSayisi() == 1) {
            return true;
        }
        return false;
    }

private:
    void asagidanYukariyaKuyrukDuzenle() {
        if (_dizi.elemanSayisi() <= 2)
            return;
        auto cocuk = _dizi.elemanSayisi() - 1;
        while (true) {
            auto ebeveyn = cocuk / 2;
            if (cocuk == 1 || _dizi.elemanGetir(ebeveyn) <= _dizi.elemanGetir(cocuk)) {
                break;
            }
            auto ebeveynDeger = _dizi.elemanGetir(ebeveyn);
            auto cocukDeger = _dizi.elemanGetir(cocuk);
            _dizi.elemanDegistir(ebeveyn, cocukDeger);
            _dizi.elemanDegistir(cocuk, ebeveynDeger);
            cocuk = ebeveyn;
        }
    }

    void yukaridanAsagiyaKuyrukDuzenle() {
        if (_dizi.elemanSayisi() <= 2) {
            return;
        }
        auto ebeveyn = 1;
        while (true) {
            auto sag_cocuk = ebeveyn * 2;
            auto sol_cocuk = ebeveyn * 2 + 1;
            if (sag_cocuk >= _dizi.elemanSayisi()) {
                break;
            }
            if (sol_cocuk >= _dizi.elemanSayisi()) {
                if (_dizi.elemanGetir(ebeveyn) > _dizi.elemanGetir(sag_cocuk)) {
                    auto ebeveyn_deger = _dizi.elemanGetir(ebeveyn);
                    auto min_cocuk_deger = _dizi.elemanGetir(sag_cocuk);
                    _dizi.elemanDegistir(ebeveyn, min_cocuk_deger);
                    _dizi.elemanDegistir(sag_cocuk, ebeveyn_deger);
                }
                break;
            }
            auto min_cocuk = (_dizi.elemanGetir(sag_cocuk) < _dizi.elemanGetir(sol_cocuk)) ? sag_cocuk : sol_cocuk;
            if (_dizi.elemanGetir(ebeveyn) > _dizi.elemanGetir(min_cocuk)) {
                auto ebeveyn_deger = _dizi.elemanGetir(ebeveyn);
                auto min_cocuk_deger = _dizi.elemanGetir(min_cocuk);
                _dizi.elemanDegistir(ebeveyn, min_cocuk_deger);
                _dizi.elemanDegistir(min_cocuk, ebeveyn_deger);
                ebeveyn = min_cocuk;
            } else {
                break;
            }
        }
    }

    DinamikDizi _dizi;
}; 


class HastaneKuyrugu {
public:
    HastaneKuyrugu() : _sonSiraOG1(0), _sonSiraOG2(0), _sonSiraOG3(0), _sonSiraOG4(0) {
    }

    ~HastaneKuyrugu() {
    }

    void hastaGeldi(int OG) {
        if (OG == 1) {
            _kuyruktaBekleyenHastalar.ekle(++_sonSiraOG1 + 10000);
        } else if (OG == 2) {
            _kuyruktaBekleyenHastalar.ekle(++_sonSiraOG2 + 20000);
        } else if (OG == 3) {
            _kuyruktaBekleyenHastalar.ekle(++_sonSiraOG3 + 30000);
        } else if (OG == 4) {
            _kuyruktaBekleyenHastalar.ekle(++_sonSiraOG4 + 40000);
        }
    }

    int siradakiHasta() {
        if (!_kuyruktaBekleyenHastalar.bosMu()) {
            int siradaki = _kuyruktaBekleyenHastalar.cikar();
            return siradaki;
        } else {
            throw std::out_of_range("Kuyrukta hasta yok.");
        }
    }

    int bekleyenHastaSayisi() {
        return _kuyruktaBekleyenHastalar.elemanSayisi();
    }

private:
    int _sonSiraOG1;
    int _sonSiraOG2;
    int _sonSiraOG3;
    int _sonSiraOG4;
    class OncelikKuyrugu _kuyruktaBekleyenHastalar;
};

int main() {
    HastaneKuyrugu hastane;

    // Hastalar geliyor
    hastane.hastaGeldi(1);
    hastane.hastaGeldi(3);
    hastane.hastaGeldi(3);
    hastane.hastaGeldi(3);
    hastane.hastaGeldi(1);
    hastane.hastaGeldi(1);
    hastane.hastaGeldi(2);
    hastane.hastaGeldi(1);

    std::cout << "Bekleyen hasta sayisi: " << hastane.bekleyenHastaSayisi() << std::endl;

    // Kuyruktaki sıradaki hastaları alıyoruz
    std::cout << "Siradaki hasta: " << hastane.siradakiHasta() << std::endl;
    std::cout << "Siradaki hasta: " << hastane.siradakiHasta() << std::endl;
    std::cout << "Siradaki hasta: " << hastane.siradakiHasta() << std::endl;
    std::cout << "Siradaki hasta: " << hastane.siradakiHasta() << std::endl;
    std::cout << "Siradaki hasta: " << hastane.siradakiHasta() << std::endl;
    std::cout << "Siradaki hasta: " << hastane.siradakiHasta() << std::endl;
    std::cout << "Siradaki hasta: " << hastane.siradakiHasta() << std::endl;

    // Bekleyen toplam hasta sayısını döner
    std::cout << "Bekleyen hasta sayisi: " << hastane.bekleyenHastaSayisi() << std::endl;

    return 0;
}
