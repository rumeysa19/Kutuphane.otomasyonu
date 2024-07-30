#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

struct Kullanici 
{

    string isimSoyisim;
    string numara;
    string eposta;

};

struct KitapBilgisi 
{
    string kitapAdi;
    string yazar;
    string İSBN;
    string oduncDurumu;

};


void kullaniciEkle()
{
    Kullanici kullaniciB;

    cout << "isim ve soyisim giriniz: ";
    cin.ignore();
    getline(cin, kullaniciB.isimSoyisim);
    cout << "telefon numarasi giriniz: ";
    getline(cin, kullaniciB.numara);
    cout << "e posta adresi giriniz: ";
    cin >> kullaniciB.eposta;

    ofstream dosya1("kullanici1.txt", ios::app);

    if (dosya1.is_open())
    {
        dosya1 << kullaniciB.isimSoyisim << "#" << kullaniciB.numara << "#" << kullaniciB.eposta << endl;
        cout << "Kullanici basariyla eklendi." << endl;
    }
    else 
    {
        cout << "Dosya acilamadi!" << endl;
    }

    dosya1.close();
}


void kullaniciAra()
{
   
    Kullanici ara;
    string aranankullanici;
    cin.ignore();
    cout << "Aradiginiz kullanicinin isim ve soyismini giriniz: ";
    getline(cin, aranankullanici);
    bool kullanicibulundu = false;


    ifstream dosya2("kullanici1.txt");

    if (!dosya2.is_open())
    {
        cout << "Dosya Acilamadi!" << endl;
        return;
    }

    string satir;

    while (getline(dosya2, satir)) 
    {
        if (!satir.empty()) {
            istringstream iss(satir);
            getline(iss, ara.isimSoyisim, '#');
            getline(iss, ara.numara, '#');
            getline(iss, ara.eposta, '#');


            if (aranankullanici==ara.isimSoyisim)
            {
                cout << "Kullanici bulundu!" << endl;
                cout << ara.isimSoyisim << "\t" << ara.numara << "\t" << ara.eposta << endl;
                kullanicibulundu = true;
                break;
            }
        }
    }

    if (!kullanicibulundu) 
    {
        cout << "Boyle bir kullanici bulunamadi!" << endl;
    }

    dosya2.close();
}


void kitapEkle()
{

    KitapBilgisi kitap;
    cout << "Eklemek istediginiz kitabin ismini giriniz: ";
    cin.ignore();
    getline(cin, kitap.kitapAdi);
    cout << "Kitabin yazar adini giriniz: ";
    getline(cin, kitap.yazar);
    cout << "ISBN kodunu giriniz: ";
    getline(cin, kitap.İSBN);
    kitap.oduncDurumu = "hayir";
  
    
    ofstream dosya3("kitaplar1.txt", ios::app);
    if (dosya3.is_open())
    {
        dosya3 << kitap.kitapAdi << "#" << kitap.yazar << "#" << kitap.İSBN << "#" << kitap.oduncDurumu << endl;
        dosya3.close();
        cout << "Kitap basariyla eklendi." << endl;
    }
    else 
    {
        cout << "Dosya acilamadi!" << endl;
    }

    dosya3.close();
    
}

void kitapAra() 
{
    
    KitapBilgisi kitap;
    string arananKitap;
    bool kitapBulundu = false;
    cout << "Aradiginiz kitabin adini giriniz: ";
    cin.ignore();
    getline(cin, arananKitap);

    ifstream dosya4("kitaplar1.txt");

    if (!dosya4.is_open()) {
        cout << "Dosya Acilamadi!" << endl;
        return;
    }

    string satir;
    
    vector<KitapBilgisi> bulunanKitaplar;

    while (getline(dosya4, satir)) 
    {
        if (!satir.empty())
        {
            istringstream iss(satir);
            getline(iss, kitap.kitapAdi, '#');
            getline(iss, kitap.yazar, '#');
            getline(iss, kitap.İSBN, '#');
            getline(iss, kitap.oduncDurumu, '#');

            if (arananKitap == kitap.kitapAdi)
            {
                bulunanKitaplar.push_back(kitap);
                kitapBulundu = true;
            }
        }
    }

    dosya4.close();

    if (kitapBulundu) 
    {
        cout << "Aranan Kitapla Eslenenler: " << endl; // her bir kitabın bilgisine referans ile erişir ve bu bilgileri değiştirilemez hale getirir.
                                                       // Bu, her kitabın bilgilerini döngü içerisinde güvenli ve etkili bir şekilde işlemeyi sağlar.
        for (const auto& k : bulunanKitaplar) {
            cout << "Kitap Adi: " << k.kitapAdi
                << ", Yazar: " << k.yazar
                << ", ISBN: " << k.İSBN
                << ", Odunc Durumu: " << (k.oduncDurumu == "hayir" ? "Kitap odunc alinabilir" : "Kitap odunc alinamaz") << endl;
        }
    }
    else 
    {
        cout << "Kitap bulunamadi!" << endl;
    }

}

void kitapOduncAl()
{
    KitapBilgisi kitap;
    string kitapA, yazarA, ISBNA, satir;
    bool kitapBulundu = false;

    cout << "Odunc almak istediginiz kitabin ISBN giriniz: ";
    cin.ignore();
    getline(cin, ISBNA);

    ifstream dosya5("kitaplar1.txt");

    if (!dosya5.is_open())
    {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    vector<KitapBilgisi> kitaplar;

    while (getline(dosya5, satir)) 
    {
        if (!satir.empty())
        {
            istringstream iss(satir);
            getline(iss, kitap.kitapAdi, '#');
            getline(iss, kitap.yazar, '#');
            getline(iss, kitap.İSBN, '#');
            getline(iss, kitap.oduncDurumu, '#');

            if (ISBNA == kitap.İSBN && kitap.oduncDurumu == "hayir")
            {
                kitapBulundu = true;
                kitap.oduncDurumu = "evet";
            }

            kitaplar.push_back(kitap);
        }
    }
    dosya5.close();

    if (kitapBulundu) 
    {
        ofstream dosya5("kitaplar1.txt");
        if (dosya5.is_open()) 
        {
            for (const auto& k : kitaplar) //& (Referans): Veriyi kopyalamadan işlemeyi sağlar, 
                                           //performansı artırır ve bellek kullanımını optimize eder.
            {
                dosya5 << k.kitapAdi << "#" << k.yazar << "#" << k.İSBN << "#" << k.oduncDurumu << endl;
            }
            dosya5.close();

            cout << "Kitap odunc alindi." << endl;
        }
        else
        {
            cout << "Dosya acilamadi!" << endl;
        }
    }
    else 
    {
        cout << "Kitap odunc alinmis durumda." << endl;
    }
}


void kitapİade()
{
    string ISBNA, satir;
    bool kitapBulundu = false;

    cout << "Iade etmek istediginiz kitabin ISBN kodunu giriniz: ";
    cin.ignore();
    getline(cin, ISBNA);

    ifstream dosya6("kitaplar1.txt");
    if (!dosya6.is_open()) 
    {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    vector<KitapBilgisi> kitaplar;
    KitapBilgisi kitap;
    while (getline(dosya6, satir)) 
    {
        if (!satir.empty()) 
        {
            istringstream iss(satir);
            getline(iss, kitap.kitapAdi, '#');
            getline(iss, kitap.yazar, '#');
            getline(iss, kitap.İSBN, '#');
            getline(iss, kitap.oduncDurumu, '#');

            if (ISBNA == kitap.İSBN && kitap.oduncDurumu == "evet") 
            {
                kitapBulundu = true;
                kitap.oduncDurumu = "hayir";
            }

            kitaplar.push_back(kitap);
        }
    }
    dosya6.close();

    if (kitapBulundu) 
    {
        ofstream dosya6yaz("kitaplar1.txt");
        if (dosya6yaz.is_open()) {
            for (const auto& k : kitaplar) 
            {
                dosya6yaz << k.kitapAdi << "#" << k.yazar << "#" << k.İSBN << "#" << k.oduncDurumu << endl;
            }
            dosya6yaz.close();
            cout << "Kitap iade edildi." << endl;
        }
        else 
        {
            cout << "Dosya acilamadi!" << endl;
        }
    }
    else 
    {
        cout << "Kitap zaten iade edilmis." << endl;
    }
}


void kullaniciGuncelle()
{
    Kullanici kullanici;
    string secim;
    string yeniTel, yeniEposta;
    string arananKullanici;
    cout << "Bilgisini degistirmek istediginiz kullanicinin isim ve soyismini giriniz: ";
    cin.ignore(); 
    getline(cin, arananKullanici);
    bool kullaniciBulundu = false;

    ifstream dosya2("kullanici1.txt");
    if (!dosya2.is_open()) 
    {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    string satir;
    vector<Kullanici> kullanicilar;

    while (getline(dosya2, satir)) 
    {
        if (!satir.empty()) 
        {
            istringstream iss(satir);
            getline(iss, kullanici.isimSoyisim, '#');
            getline(iss, kullanici.numara, '#');
            getline(iss, kullanici.eposta, '#');

            if (arananKullanici == kullanici.isimSoyisim) 
            {
                cout << "Kullanici bulundu!" << endl;
                kullaniciBulundu = true;

                cout << "Kullaniciya ait hangi bilgiyi degistirmek istiyorsunuz? (telefon/eposta) ";
                cin >> secim;

                if (secim == "telefon" || secim == "Telefon") 
                {
                    cout << "Yeni telefon numarasini giriniz: ";
                    cin >> yeniTel;
                    kullanici.numara = yeniTel;
                }
                else if (secim == "eposta" || secim == "Eposta") 
                {
                    cout << "Yeni eposta adresini giriniz: ";
                    cin >> yeniEposta;
                    kullanici.eposta = yeniEposta;
                }
            }
        }
        kullanicilar.push_back(kullanici);
    }

    dosya2.close();

    if (!kullaniciBulundu) 
    {
        cout << "Kullanici bulunamadi!" << endl;
        return;
    }

    ofstream dosya3("kullanici1.txt");
    if (!dosya3.is_open()) 
    {
        cout << "Dosya acilamadi!" << endl;
        return;
    }

    for (const auto& k : kullanicilar) 
    {
        dosya3 << k.isimSoyisim << "#" << k.numara << "#" << k.eposta << endl;
    }

    dosya3.close();

    cout << "Bilgiler basariyla guncellendi!" << endl;
}

int main()
{
    string kitap;
   

    while (true)
    {

        int secim;
        cout << "1. Kullanici Ekle" << endl;
        cout << "2. Kullanici Ara" << endl;
        cout << "3. Kitap Ekle" << endl;
        cout << "4. Kitap Ara" << endl;
        cout << "5. Kitap Odunc Al" << endl;
        cout << "6. Kitap Iade Et" << endl;
        cout << "7. Kullanici Guncelle" << endl;
        cout << "8. Cikis" << endl;
        cout << "Lutfen yapmak istediginiz islemi seciniz: ";
        cin >> secim;

        system("cls");

        switch (secim) {
        case 1:
            kullaniciEkle();
            break;
        case 2:
            kullaniciAra();
            break;
        case 3:
            kitapEkle();
            break;
        case 4:
            kitapAra();
            break;
        case 5:
            kitapOduncAl();
            break;
        case 6:
            kitapİade();
            break;
        case 7:
            kullaniciGuncelle();
            break;
        case 8:
            cout << "Cikis yapiliyor bekleyiniz.. ";
            return 0;
        default:
            cout << "Gecersiz secim! Lutfen yapmak istediginiz islemi 1 ile 8 arasinda olacak sekilde seciniz." << endl;
        }
    }

    return 0;

}