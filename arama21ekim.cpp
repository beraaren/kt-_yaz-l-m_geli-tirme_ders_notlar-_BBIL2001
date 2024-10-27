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

    void ekle(Veritutucu*& kök, int verix) {
        if (kök == nullptr) {
            kök = new Veritutucu();
            kök->veri = verix;
        } else if (verix < kök->veri) {
            ekle(kök->küçük, verix);
        } else {
            ekle(kök->büyük, verix);
        }
    }

    bool arama(Veritutucu *kök, int sayı) {
        if (kök == nullptr) {
            return false; // Sayı bulunamadı
        }
        if (kök->veri == sayı) {
            return true; // Sayı bulundu
        }
        if (sayı < kök->veri) {
            return arama(kök->küçük, sayı); // Sol dala git
        } else {
            return arama(kök->büyük, sayı); // Sağ dala git
        }
    }

    void inOrderTraversal(Veritutucu *kök) {
        if (kök == nullptr)
            return;
        inOrderTraversal(kök->küçük); // Sol dal
        cout << kök->veri << " ";     // Kök
        inOrderTraversal(kök->büyük); // Sağ dal
    }

    void ağacıSil(Veritutucu* kök) {
        if (kök != nullptr) {
            ağacıSil(kök->küçük);
            ağacıSil(kök->büyük);
            delete kök;
        }
    }

public:
    ikiliArarmaAğacı() {
        başlangıç = nullptr;  // Başlangıç pointerini null'a eşitleyerek boş bir ağaç.
    };

    ~ikiliArarmaAğacı(){
        ağacıSil(başlangıç);
    };

    void ekle(int verix) {
        ekle(başlangıç, verix);
    }

    bool arama(int sayı) {
        return arama(başlangıç, sayı);
    }

    void elemangetir() {
        if (başlangıç != nullptr) {
            inOrderTraversal(başlangıç);
            cout << endl;
        } else {
            cout << "Ağaç boş" << endl;
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

    agaç.elemangetir();  // Elemanlar sıralı bir şekilde yazdırılacak (2 4 5 6 7 9)

    int arananSayı = 6;
    if (agaç.arama(arananSayı)) {
        cout << arananSayı << " ağacın içinde bulundu." << endl;
    } else {
        cout << arananSayı << " ağacın içinde bulunamadı." << endl;
    }

    return 0;
}
