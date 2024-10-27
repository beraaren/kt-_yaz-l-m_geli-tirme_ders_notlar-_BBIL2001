#include<iostream>

using namespace std;

struct Veritutucu {
    int veri = 0;
    Veritutucu *büyük = nullptr;
    Veritutucu *küçük = nullptr; 
    
};

class ikiliArarmaAğacı {
private:
    Veritutucu *başlangıç; 

public:
    ikiliArarmaAğacı() {
        başlangıç = nullptr;  // Başlangıç pointerini null'a eşitleyerek boş bir bağlı listeye sahiptir.
        enküçük = nullptr;  // Enküçük  elemanın pointerı
    };

    ~ikiliArarmaAğacı(){
        delete başlangıç;
    };

    void ekle(int verix) {
        Veritutucu *tutucu = new Veritutucu();
        tutucu->veri = verix;
        tutucu->büyük = nullptr;
        tutucu->küçük = nullptr;

        if (başlangıç == nullptr) {
            başlangıç = tutucu;
        } else {
            Veritutucu *iter = başlangıç;
            while (true) {
                if (iter->veri > verix) {
                    if (iter->küçük != nullptr) {break;}
                    if (iter->küçük == nullptr) {
                        iter->küçük = tutucu;
                    } else {
                        iter = iter->küçük;
                    }
                } else {
                    if (iter->büyük != nullptr) {break;}
                    if (iter->büyük == nullptr) {
                        iter->büyük = tutucu;
                    } else {
                        iter = iter->büyük;
                    }
                }
            }
        }
    
    };

    void pop(int index) {
        
    }  
    
    void elemangetir() {
        if (başlangıç!= nullptr) {
            Veritutucu *iter = başlangıç;
            while (iter->büyük != nullptr) {
                cout << iter->veri << " ";
                iter = iter->büyük;
            }
        } else {
            cout << "Liste boş" << endl;
        }
    }
};


int main() {
    ikiliArarmaAğacı agaç;

    agaç.ekle(5);
    agaç.ekle(6);
    agaç.ekle(4);
    agaç.ekle(2);
    agaç.ekle(7);
    agaç.ekle(9);
    agaç.elemangetir();

}