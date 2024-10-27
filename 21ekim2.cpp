#include<iostream>

using namespace std;

struct orenci
{
    string isim;
    string soyad;
    string numara;
    int yaş;

    bool operator==(const orenci &sol) const {
        if (this->numara == sol.numara)
        {
            return true;
        }
        return false;
        
    }
};

struct Veritutucu {
    orenci *veri = nullptr;
    Veritutucu *sonraki = nullptr; 
    
};

class bağlıliste {
private:
    Veritutucu *başlangıç; 
public:
    bağlıliste() {
        başlangıç = nullptr;  // Başlangıç pointerini null'a eşitleyerek boş bir bağlı listeye sahiptir.
    };

    ~bağlıliste(){
        delete başlangıç;
    };

    void ekle(orenci *veri) {
        Veritutucu *tutucu = new Veritutucu();
        tutucu->veri = veri;
        tutucu->sonraki = nullptr;

        if (başlangıç == nullptr) {
            başlangıç = tutucu;
        } else {
            Veritutucu *iter = başlangıç;
            while (iter->sonraki!= nullptr) {
                iter = iter->sonraki;
            }
            iter->sonraki = tutucu;
        }
    };
    void pop(int index) {
        if (başlangıç != nullptr) {
            Veritutucu *temp = başlangıç;
            if (index == 0) {
                auto sonuc = başlangıç->veri;
                auto geçici = başlangıç;
                başlangıç = başlangıç->sonraki;
                delete geçici;
                delete temp;
                return;
            }

            Veritutucu *iter = başlangıç;
            while (iter->sonraki != nullptr && index > 1) {
                iter = iter->sonraki;
                index--;
            }
            if (iter->sonraki != nullptr) {
                auto silenecekyer = iter->sonraki;
                iter->sonraki = silenecekyer->sonraki;
                delete silenecekyer->veri;
                delete silenecekyer;
            }
        } else {
            cout << "Liste boş" << endl;
        }
    }  
    
    void elemangetir(int index) {
        if (başlangıç != nullptr) {
            Veritutucu *iter = başlangıç;
            int i = 0;
            while (iter != nullptr) {
                if (i == index) {
                    cout << "İsim: " << iter->veri->isim << ", Soyad: " << iter->veri->soyad << ", Numara: " << iter->veri->numara << ", Yaş: " << iter->veri->yaş << endl;
                    return;
                }
                iter = iter->sonraki;
                i++;
            }
            cout << "Index out of range" << endl;
        } else {
            cout << "Liste boş" << endl;
        }
    }
};



int main() {
    orenci a = orenci({.isim = "tol", .soyad = "asd", .numara = "123", .yaş = 17});
    orenci b = orenci({.isim = "tol", .soyad = "asd", .numara = "123", .yaş = 17});
    orenci c = orenci({.isim = "tol", .soyad = "asd", .numara = "333", .yaş = 17});

    // cout << (a == b) << endl; // true
    // cout << (a == c) << endl; // false

    bağlıliste list;

    list.ekle(&a);
    list.ekle(&b);
    list.ekle(&c);
    list.elemangetir(2);
     
    return 0;
}