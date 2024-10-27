#include <iostream>
#include <random>

/**
 * @class DinamikDizi
 * @brief Dinamik bir dizi veri yapısını temsil eder.
 *
 * DinamikDizi sınıfı, dinamik olarak büyüyebilen ve küçülebilen bir dizi yapısını
 * içerir. Eklemeler ve çıkarmalar için çeşitli fonksiyonlar sağlar.
 */
class DinamikDizi {
public:

    /**
     * @brief DinamikDizi sınıfının kurucu (constructor) fonksiyonudur.
     *
     * Bu kurucu fonksiyon, DinamikDizi nesnesi oluşturulduğunda çağrılır ve sınıf
     * üyelerini başlatır. Başlangıçta, dizinin kapasitesi 2 eleman kapasitesi olarak
     * ayarlanır ve eleman sayısı 0 olarak başlatılır.
     *
     * @details Bu fonksiyon, `_a` göstericisini (pointer) 2 elemanlık bir tamsayı
     * dizisi olarak dinamik olarak ayırır. `_kapasite` üyesi 2 olarak ayarlanır
     * ve `_elemanSayisi` sıfırlanır.
     */
    DinamikDizi() {
        _a = new int[2];
        _kapasite = 2;
        _elemanSayisi = 0;
    }

    /**
     * @brief DinamikDizi sınıfının yıkıcı (destructor) fonksiyonu.
     *
     * Bu yıkıcı fonksiyon, DinamikDizi nesnesi yaşam döngüsünü tamamladığında
     * çağrılır ve _a dizisine ayrılmış olan belleği serbest bırakır.
     *
     * @details Bu işlev, bellekte sızıntı (memory leak) oluşmasını önlemek için
     * dinamik olarak oluşturulmuş dizinin (_a) belleğini serbest bırakır.
     * Bu fonksiyon, default olarak belleği geri kazanır.
     */
    ~DinamikDizi() {
        delete[] _a;
    }

    /**
     * @brief DinamikDizi sınıfının kopya yapıcısını devre dışı bırakır.
     *
     * Bu kopya yapıcı, DinamikDizi nesnesinin kopyalanmasını önlemek için delete ile tanımlanmıştır.
     * Böylece, nesnenin kopyalanması derleyici seviyesinde engellenir.
     *
     * @param diger Kopyalanması istenen diğer DinamikDizi nesnesi.
     */
    DinamikDizi(const DinamikDizi &diger) = delete;

    /**
     * @brief Dinamik dizide yeni bir eleman ekler.
     *
     * Bu işlev, verilen elemanı (_a dizisine) ekler ve eleman sayısını (_elemanSayisi)
     * artırır. Eğer mevcut eleman sayısı kapasiteye ulaştıysa, dizinin kapasitesi
     * artırılır.
     *
     * @param yeniEleman Eklenecek yeni elemanın değeri.
     *
     * @note Eğer dizi kapasite doluysa, dizinin kapasitesi `diziyiKontrolluBuyut` işlevi
     * tarafından artırılır.
     */
    void elemanEkle(int yeniEleman) {
        _a[_elemanSayisi++] = yeniEleman;
        if (_elemanSayisi == _kapasite) {
            diziyiKontrolluBuyut();
        }
    }

    /**
     * @brief Belirtilen indeksteki elemanı çıkarır.
     *
     * @param index Çıkartılacak elemanın indeksi.
     *
     * Bu fonksiyon, verilen pozisyondaki elemanı liste veya diziden kaldırır.
     * Elemanlar arasında boşluk bırakılmaması için indeksleri kaydırır.
     *
     * @note İndeks sıfır tabanlıdır. Yani, ilk elemanın indeksi 0'dır.
     *
     * @return Çıkartılan elemanı geri döndürür.
     *
     * @throws std::out_of_range Eğer belirtilen indis dizinin boyutları dışında ise
     */
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

    /**
     * @brief DinamikDizi sınıfındaki ilk elemanı çıkarır.
     *
     * Bu fonksiyon, dinamik dizinin ilk elemanını çıkarmak için kullanılır.
     * İlk eleman dizinin 0. indeksinde yer alır.
     *
     * @details Bu fonksiyon, elemanCikar(int index) fonksiyonunu kullanarak dizinin
     * ilk elemanını (0. indeks) çıkartır ve çıkartılan elemanın değerini geri döner.
     * Eğer dizi boş ise veya 0. indeks dışında talep gelirse, std::out_of_range hatası fırlatılır.
     *
     * @return Çıkartılan ilk elemanın değeri.
     *
     * @throws std::out_of_range Eğer dizide hiç eleman yoksa veya indeks geçersiz ise.
     */
    int ilkElemaniCikar() {
        return elemanCikar(0);
    }

    /**
     * @brief Dizinin son elemanını çıkarır.
     *
     * Bu fonksiyon, dinamik dizinin son elemanını çıkartır ve çıkartılan elemanın değerini geri döner.
     * İşlev, dizinin geçerli eleman sayısından 1 çıkararak elde edilen indeksi (`_elemanSayisi - 1`) kullanır ve
     * `elemanCikar(int index)` fonksiyonunu çağırır.
     *
     * @note Eğer dizi boşsa ve son eleman çıkarılmak istendiğinde bir hata oluşacaksa, `elemanCikar(int index)`
     * işlevinde tanımlanmış olan bir `std::out_of_range` hatası fırlatılabilir.
     *
     * @return Çıkartılan son elemanın değeri.
     *
     * @throws std::out_of_range Eğer dizide hiç eleman yoksa veya indeks geçersiz ise.
     */
    int sonElemaniCikar() {
        return elemanCikar(_elemanSayisi - 1);
    }

    /**
     * @brief Belirtilen sıradaki elemanın değerini getirir
     *
     * Bu fonksiyon belirtilen indexteki elemanın boyutunu döndürmek için kullanılır.
     * Ancak verilen index dizinin boyutları içerisinde değilse hata üretir.
     * Bu durum kullanıcı tarafından çözülmelidir.
     *
     * @param index Erişilecek olan elemanın sıra numarası
     *
     * @return Belirtilen sıra numarasındaki elemanın değeri
     *
     * @throws std::out_of_range Eğer belirtilen indis dizinin boyutları dışında ise
     */
    int elemanGetir(int index) {
        if (index >= 0 && index < _elemanSayisi) {
            return _a[index];
        } else {
            throw std::out_of_range("Geçersiz indeks: Dizi sınırlarının dışında.");
        }
    }

    /**
     * @brief Dinamik dizideki eleman sayısını döndürür.
     *
     * Bu işlev, DinamikDizi yapısındaki mevcut eleman sayısını (_elemanSayisi)
     * döndürmek için kullanılır. Bu sayede dizide kaç eleman olduğunu öğrenebilirsiniz.
     *
     * @return Dinamik dizide bulunan eleman sayısı.
     */
    int elemanSayisi() {
        return _elemanSayisi;
    }

    /**
     * @brief Dinamik dizinin kapasitesini döndürür.
     *
     * Bu işlev, DinamikDizi sınıfında mevcut olan kapasiteyi (_kapasite)
     * döndürmek için kullanılır. Kapasite, dizide kaç eleman saklanabileceğini belirtir.
     *
     * @return Dinamik dizinin kapasitesi.
     */
    int kapasite() {
        return _kapasite;
    }

    /**
     * @brief Dizide belirtilen indeksteki elemanı yeni bir değerle değiştirir.
     *
     * Bu fonksiyon, bir dizideki verilen indeksteki elemanı, yeni girilen bir değerle değiştirir.
     *
     * @param index Değeri değiştirilecek olan elemanın dizin (indeks) numarası.
     * @param yeniDeger Elemanın değiştirileceği yeni değer.
     *
     * @return void
     *
     * @note Dizinin geçerli bir dizin aralığında olup olmadığını kontrol etmelisiniz; aksi takdirde bellek ihlâli oluşabilir.
     */
    void elemanDegistir(int index, int yeniDeger) {
        if (index >= 0 && index < _elemanSayisi) {
            _a[index] = yeniDeger;
        } else {
            throw std::out_of_range("Geçersiz indeks: Dizi sınırlarının dışında.");
        }
    }

private:

    /**
     * @brief Dinamik dizi kapasitesini iki katına çıkarır.
     *
     * diziyiKontrolluBuyut fonksiyonu mevcut dinamik dizinin kapasitesini iki katına çıkarır.
     * Yeni bir dinamik dizi oluşturur, eski dizinin elemanlarını yeni diziye kopyalar ve
     * eski diziyi serbest bırakır.
     *
     * @note Bu fonksiyonun doğru çalışması için `_a` işaretçisinin ve `_kapasite` değişkeninin
     * uygun şekilde tanımlanmış ve başlatılmış olması gerekmektedir.
     */
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


/**
 * @class Kuyruk
 * @brief Kuyruk (Queue) veri yapısını temsil eden bir sınıf.
 *
 * Bu sınıf, temel olarak bir DinamikDizi örneği içeren ve
 * kuyruk veri yapısını uygulayan bir sınıftır.
 * Kuyruğa eleman ekleme ve çıkarma işlemleri yapılabilir.
 */
class Kuyruk {
public:

    /**
     * @brief Kuyruğa eleman ekler.
     *
     * Bu fonksiyon, @a eleman parametresiyle verilen değeri kuyruk veri yapısına ekler.
     * @param eleman Kuyruğa eklenecek eleman.
     */
    void ekle(int eleman) {
        _dizi.elemanEkle(eleman);
    }

    /**
     * @brief Kuyruktan eleman çıkaran fonksiyon.
     *
     * Bu fonksiyon, Kuyruk veri yapısındaki ilk elemanı çıkarır ve döner.
     * Fonksiyon, içsel olarak DinamikDizi sınıfının ilk elemanı çıkarma yöntemini kullanır.
     *
     * @return Çıkarılan elemanın değeri.
     */
    int cikar() {
        return _dizi.ilkElemaniCikar();
    }

    /**
     * @brief Kuyruğun en önündeki elemanı döner.
     *
     * Bu fonksiyon, kuyruk veri yapısındaki en ön sıradaki elemanı döndürür.
     * İçsel olarak DinamikDizi sınıfının elemanGetir(0) metodunu kullanır.
     *
     * @return Kuyruğun en önündeki elemanın değeri.
     */
    int bak() {
        return _dizi.elemanGetir(0);
    }

    /**
     * @brief Kuyruğun içindeki eleman sayısını döner.
     *
     * Bu fonksiyon, kuyrukta bulunan eleman sayısını döndürür.
     * İçsel olarak DinamikDizi sınıfının elemanSayisi() metodunu çağırır.
     *
     * @return Kuyruktaki eleman sayısı.
     */
    int elemanSayisi() {
        return _dizi.elemanSayisi();
    }

    /**
     * @brief Kuyruğun boş olup olmadığını kontrol eden fonksiyon.
     *
     * Bu fonksiyon, Kuyruk veri yapısının içeriğinin boş olup olmadığını kontrol eder.
     * Eğer kuyrukta hiç eleman yoksa true döner, aksi takdirde false döner.
     *
     * @return Kuyruk boşsa true, doluysa false.
     */
    bool bosMu() {
        if (_dizi.elemanSayisi() == 0) {
            return true;
        }
        return false;
    }

private:
    DinamikDizi _dizi;
};

/**
 * @class Yigin
 * @brief Yığın (Stack) veri yapısını temsil eden sınıf.
 *
 * Bu sınıf, DinamikDizi kullanarak yığın (stack) veri yapısının temel operasyonlarını sağlar.
 */
class Yigin {
public:

    /**
     * @brief Yığına yeni bir eleman ekler.
     *
     * Bu fonksiyon, Yigin sınıfının içindeki DinamikDizi nesnesine yeni bir eleman eklemek için kullanılır.
     * Eklenen eleman yığının üstüne (top) eklenir.
     *
     * @param eleman Eklenecek elemanın değeri.
     */
    void ekle(int eleman) {
        _dizi.elemanEkle(eleman);
    }


    /**
     * @brief Yığın (stack) yapısının üstünden bir eleman çıkarır.
     *
     * Bu fonksiyon, Yigin sınıfının içindeki DinamikDizi nesnesinden yığının en üstündeki
     * elemanı çıkarır ve döner. Yığın boş ise davranış tanımsızdır.
     *
     * @return int Çıkarılan elemanın değeri.
     */
    int cikar() {
        return _dizi.sonElemaniCikar();
    }


    /**
     * @brief Yığının (stack) en üstündeki elemanı döner.
     *
     * Bu fonksiyon, Yigin sınıfının içindeki DinamikDizi nesnesinden
     * en son eklenen (yığının en üstündeki) elemanı döner.
     * Eleman sayısını bir azaltmaz, sadece elemanın değerini döner.
     *
     * @return int Yığının en üstündeki elemanın değeri.
     */
    int bak() {
        return _dizi.elemanGetir(_dizi.elemanSayisi() - 1);
    }


    /**
     * @brief Yığın içindeki eleman sayısını döner.
     *
     * Bu fonksiyon, Yigin sınıfının içindeki DinamikDizi nesnesinin eleman sayısını
     * döner. Yani, yığın içindeki toplam eleman sayısını öğrenmek için kullanılır.
     *
     * @return int Yığın içindeki toplam eleman sayısı.
     */
    int elemanSayisi() {
        return _dizi.elemanSayisi();
    }


    /**
     * @brief Yığının boş olup olmadığını kontrol eder.
     *
     * Bu fonksiyon, Yigin sınıfının içinde bulunan yığın yapısının (DinamikDizi)
     * boş olup olmadığını kontrol etmek için kullanılır. Eğer yığında
     * hiç eleman yoksa true, aksi takdirde false döner.
     *
     * @return bool Yığın boş ise true, değilse false döner.
     */
    bool bosMu() {
        if (_dizi.elemanSayisi() == 0) {
            return true;
        }
        return false;
    }

private:
    DinamikDizi _dizi;
};

/**
 * @class OncelikKuyrugu
 * @brief Oncelik (Öncelik) Kuyruğu implementasyonu için sınıf.
 *
 * Bu sınıf, DinamikDizi kullanarak bir öncelik kuyruğu yapısını simüle eder.
 */
class OncelikKuyrugu {
public:

    /**
     * @brief OncelikKuyrugu sınıfının kurucu fonksiyonu.
     *
     * Bu fonksiyon, OncelikKuyrugu nesnesi oluşturduğunda dinamik diziyi başlatır
     * ve dizinin ilk elemanı olarak 0 ekler. Bu sayede öncelik kuyruğu için erişim sorunu ortadan kalkar.
     *
     */
    OncelikKuyrugu() {
        _dizi.elemanEkle(0);
    }

    /**
     * @brief OncelikKuyrugu sınıfına yeni bir eleman ekler.
     *
     * Bu fonksiyon, verilen elemanı dinamik diziye ekler ve ardından kuyruğu düzenler.
     * Fonksiyon, elemanın doğru şekilde saklanmasını ve öncelik kuyruğunun
     * kurallarına uygun hale getirilmesini sağlar.
     *
     * @param eleman Eklenecek eleman
     */
    void ekle(int eleman) {
        _dizi.elemanEkle(eleman);
        asagidanYukariyaKuyrukDuzenle();
    }


    /**
     * @brief Öncelik kuyruğundan bir eleman çıkarır.
     *
     * Bu fonksiyon, öncelik kuyruğunun ilk elemanını alır, ardından son elemanı
     * çıkarır ve öncelik kuyruğunun ilk elemanını bu son eleman ile değiştirir.
     * Son olarak kuyruğu tekrar yukarıdan aşağıya doğru düzenler ve çıkarılan
     * elemanı geri döner.
     *
     * @return Çıkarılan elemanın değeri
     *
     * @note Bu fonksiyon, _dizi üyesi üzerinden işlem yapar ve yukaridanAsagiyaKuyrukDuzenle fonksiyonunu çağırır.
     */
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


    /**
     * @brief Dinamik dizideki eleman sayısını döner.
     *
     * Bu fonksiyon, `_dizi` üyesine ait `elemanSayisi` fonksiyonunu çağırarak
     * dinamik dizide bulunan toplam eleman sayısını döner.
     *
     * @return int Dinamik dizideki eleman sayısı.
     */
    int elemanSayisi() {
        return _dizi.elemanSayisi();
    }


    /**
     * @brief Kuyruğun boş olup olmadığını kontrol eder.
     *
     * Bu fonksiyon, `_dizi` isimli dinamik dizinin içinde sadece bir eleman (ilk eleman olarak sıfır)
     * bulunduğunu kontrol ederek kuyruğun boş olup olmadığını belirler.
     *
     * Eğer `_dizi` içindeki eleman sayısı 1 ise kuyruk boştur ve true döner, aksi takdirde false döner.
     *
     * @return true Eğer kuyruk boşsa
     * @return false Eğer kuyruk doluysa
     */
    bool bosMu() {
        if (_dizi.elemanSayisi() == 1) {
            return true;
        }
        return false;
    }

private:

    /**
     * @brief Öncelik kuyruğu elemanlarını aşağıdan yukarıya doğru düzenler.
     *
     * Bu fonksiyon, _dizi üyesinde yer alan öncelik kuyruğu elemanlarını,
     * ebeveyn ve çocuk düğümlerini karşılaştırarak ve gerekli olduğunda
     * yer değiştirerek düzenler. Fonksiyon küçükten büyüğe sıralama
     * sağlamak için ebeveyn düğümünün çocuk düğümünden küçük veya eşit olduğu yerlerde
     * durur. Eğer kuyrukta 2 veya daha az eleman varsa düzenleme yapılmaz.
     *
     * @note Fonksiyon, küçükten büyüğe bir öncelik kuyruğu düzeni sağlar.
     */
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


    /**
     * @brief Öncelik kuyruğu elemanlarını yukarıdan aşağıya doğru düzenler.
     *
     * Bu fonksiyon, _dizi üyesindeki öncelik kuyruğu elemanlarını yukarıdan aşağıya doğru
     * ebeveyn ve çocuk düğümlerini karşılaştırarak ve gerekli durumlarda yer değiştirerek düzenler.
     * Fonksiyon, küçükten büyüğe sıralama sağlamak için ebeveyn düğümünün çocuk düğümlerinden küçük
     * olduğu yerlerde durur. Eğer kuyrukta 2 veya daha az eleman varsa düzenleme yapılmaz.
     *
     * @note Fonksiyon, küçükten büyüğe bir öncelik kuyruğu düzeni sağlar.
     */
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

/**
 * @file main.cpp
 * @brief Rastgele sayılarla bir dinamik dizi oluşturur ve bu sayıları yığın, kuyruk ve öncelikli kuyruk yapılarında işler.
 *
 * @details Bu program öncelikle rastgele sayılar üreterek bunları bir DinamikDizi nesnesine ekler.
 * Sonrasında bu sayılar sırasıyla Yigin, Kuyruk ve OncelikKuyrugu veri yapılarında depolanır ve ekranda görüntülenir.
 */
int main() {
    std::random_device rd; //Bu nesne, rastgele bir sayı üretici cihazı açar. Donanım tabanlı rastgele sayı üreteci olarak çalışır, ancak işletim sistemi tarafından implemente edilebilir.
    std::mt19937 gen(
            rd()); // en adlı nesne, Mersenne Twister algoritmasını kullanarak rastgele sayı üretir. rd() aracılığıyla başlatılır ve bu şekilde gerçekten rastgele bir tohum alır.
    std::uniform_int_distribution<> distrib(1,
                                            25000); // distrib, [1, 25000] aralığında düzgün dağılıma uyan tamsayılar üretir.

    DinamikDizi orjinalVeri; // Burada orjinalVeri adında bir DinamikDizi nesnesi oluşturuluyor.

    for (auto i = 0; i < 10; i++) {
        orjinalVeri.elemanEkle(distrib(gen));
        /*
         * Döngü, distrib(gen) kullanarak rastgele bir sayı üretir ve bu sayıyı orjinalVeri adındaki DinamikDizi nesnesine ekler.
         *      distrib ve gen burada rastgele sayı üretimi için kullanılan nesnelerdir.
         *      distrib bir tamsayı dağılımı sağlarken, gen bir rastgele sayı üretecidir (Mersenne Twister algoritması kullanarak).
         */
    }

    std::cout << "ORJİNAL VERİ" << std::endl;
    for (int i = 0; i < orjinalVeri.elemanSayisi(); ++i) {
        std::cout << orjinalVeri.elemanGetir(i) << std::endl;
        /*
         * Bu satırda, orjinalVeri içindeki her bir eleman ekrana yazdırılır.
         *      orjinalVeri.elemanGetir(i) fonksiyonu, indeks numarasına göre bir elemanı getirir ve std::cout ile bu eleman ekrana yazdırılır.
         */
    }

    Yigin a; // Bu C++ kodunun amacı, bir yığın (stack) veri yapısını kullanarak verileri işlemesidir.
    // Bu satırda, a isimli bir Yigin nesnesi oluşturuluyor.
    for (auto i = 0; i < orjinalVeri.elemanSayisi(); ++i) {
        a.ekle(orjinalVeri.elemanGetir(i));
        /*
         * Bu döngüde, orjinalVeri isimli dinamik dizi üzerinde geziyor ve her bir elemanı a yığınına ekliyor.
         * orjinalVeri.elemanGetir(i) fonksiyonu ile i. eleman alınıyor ve a.ekle(...) fonksiyonu kullanılarak yığına ekleniyor.
         * Döngü, orjinalVeri içindeki tüm elemanlar işlenene kadar devam eder.
         */
    }

    std::cout << "YIĞIN" << std::endl;
    for (int i = 0; i < orjinalVeri.elemanSayisi(); ++i) {
        std::cout << a.cikar() << std::endl;
        /*
         * Bu döngüde ise yığından elemanları çıkararak ekrana yazdırıyor.
         * a.cikar() fonksiyonu yığından bir eleman çıkarır ve bu elemanı döner.
         * Bu döngü de orjinalVeri içindeki tüm elemanlar işletene kadar devam eder.
         * Bu kod, yığının LIFO (Son Giren İlk Çıkar) mantığına uygun olarak çalışır.
         * Yani, yığına en son eklenen eleman ilk çıkar ve ekrana yazdırılır.
         */
    }

    Kuyruk b; // Bu C++ kodunun amacı, bir kuyruk (queue) veri yapısını kullanarak verileri işlemesidir.
    // Bu satırda, b isimli bir Kuyruk nesnesi oluşturuluyor.
    for (auto i = 0; i < orjinalVeri.elemanSayisi(); ++i) {
        b.ekle(orjinalVeri.elemanGetir(i));
        /*
         * Bu döngü, orjinalVeri adındaki dinamik dizi içindeki her bir elemanı sırayla kuyruğa ekler.
         * orjinalVeri.elemanGetir(i) ifadesi, indeks numarası i olan elemanı getirir.
         * b.ekle(...) fonksiyonu bu elemanı b kuyruğuna ekler.
         */
    }
    std::cout << "KUYRUK" << std::endl;
    for (int i = 0; i < orjinalVeri.elemanSayisi(); ++i) {
        std::cout << b.cikar() << std::endl;
        /*
         * İkinci döngü, kuyruktaki elemanları sırayla çıkararak ekrana yazdırır.
         * b.cikar() fonksiyonu kuyruğun başındaki elemanı çıkarır ve bu elemanı döner; bu eleman std::cout ile ekrana yazdırılır.
         * Bu kod, yığının FIFO (İlk Giren İlk Çıkar) mantığına uygun olarak çalışır.
         * Yani, yığına en son eklenen eleman ilk çıkar ve ekrana yazdırılır.
         */
    }

    OncelikKuyrugu c; /*
                     * OncelikKuyrugu adında bir öncelik kuyruğu nesnesi (muhtemelen bir sınıfın örneği) oluşturulur.
                     * Bu, öğelerin belirli bir öncelik sırasına göre saklanmasını ve çıkarılmasını sağlar.
                     */
    for (auto i = 0; i < orjinalVeri.elemanSayisi(); ++i) {
        c.ekle(orjinalVeri.elemanGetir(i));
        /*
         * orjinalVeri adlı dinamik dizi nesnesi üzerinde gezinilir.
         * Her döngü adımında, orjinalVeri.elemanGetir(i) ifadesi orjinalVeri dizisindeki i numaralı öğeyi alır.
         * Alınan bu öğe, c.ekle(...) fonksiyonu kullanılarak öncelik kuyruğuna eklenir.
         */
    }

    std::cout << "ÖNCELİK KUYRUĞU" << std::endl;
    for (int i = 0; i < orjinalVeri.elemanSayisi(); ++i) {
        std::cout << c.cikar() << std::endl;
        /*
         * orjinalVeri dizisindeki her bir öğe için, öncelik kuyruğundan c.cikar() fonksiyonu ile öğeler çıkarılır ve ekrana yazdırılır.
         * c.cikar() fonksiyonu öncelik kuyruğundan en yüksek önceliğe sahip öğeyi (ki burada değeri en düşük olan değer) çıkarır ve döndürür.
         */
    }
}
