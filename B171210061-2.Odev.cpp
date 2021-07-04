/****************************************************************************
**					        SAKARYA ÜNİVERSİTESİ						   **
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ			   **
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ						   **
**				          PROGRAMLAMAYA GİRİŞİ DERSİ					   **
**																		   ** 
**				ÖDEV NUMARASI.............:          2					   **
**				ÖĞRENCİ ADI...............:          ECE NUR ARSLAN        **
**				ÖĞRENCİ NUMARASI..........:          B171210061			   **
**				DERS GRUBU................:          1B                    **
****************************************************************************/

#include <iostream>
#include <Windows.h>
#include <stdlib.h> //rand fonksiyonu için
#include <time.h> //srand fonksiyonu için

using namespace std;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


class Cati {

public:
	int yukseklik;
	int genislik;
	int xKonum;
	int yKonum;
	char catiKarakter;


	Cati(int genislik, int yukseklik, char catiKarakter, int xKonum, int yKonum) {

		this->catiKarakter = catiKarakter;
		this->genislik = genislik;
		this->yukseklik = yukseklik;
		this->xKonum = xKonum;
		this->yKonum = yKonum;
		int maxDeger = (genislik / 2)  ;

		//yuksekligin taban genisligine uygun olmasi icin bir max deger ile sinirlandirilmasini saglar
		if (!(this->yukseklik < maxDeger)) {
			this->yukseklik = maxDeger;
		}

	}

	void CatiCiz() {
		int c = 0;
		//cati yuksekligi kez donen for
		for (int i = yukseklik; i > 0; i--)
		{
			gotoxy(xKonum, yKonum + c);
			//cati olusturulurken ucgen seklini vermek icin bosluk basilmasi gereken yerlerde basar
			for (int j = 0; j < (((i * 2) + 2) / 2) - 2; j++)
			{
				cout << " ";

			}
			//catinin kendisini uygun yerlerde basmak icin
			for (int j = 0; j < (genislik + 2) - (i * 2); j++)
			{
				cout << catiKarakter;
			}
			c++;
		}
	}
};

class Kat {
public:
	int katSayisi;
	int genislik;
	char katKarakter;
	int x;
	int yYeni;

	Kat(int katSayisi, int genislik, int katKarakter, int x, int yYeni) {

		//kat sayisi sifirdan buyukse kullanilmak üzere alınır
		if (katSayisi > 0) {
			this->katSayisi = katSayisi;
		}
		//sifirdan buyuk degilse default olarak 1 alinir
		else {
			this->katSayisi = 1;
			//cout << "Ev en az 1 katli olmali. Kat sayisi 1 olarak ayarlandi.";
		}
		this->genislik = genislik;
		this->katKarakter = katKarakter;
		this->x = x;
		this->yYeni = yYeni;
	}
	void KatCiz() {

		//kat sayisi kadar donen for dongusu
		for (int j = 0; j < katSayisi; j++) {

			gotoxy(x, yYeni);

			//cerceve seklindeki kat yapısının karakterlerden olusan kismi icin
			if (j == 0 || j == katSayisi - 1) {
				for (int i = 0; i < genislik; i++) {
					cout << katKarakter;
				}
			}
			//cerceve seklindeki kat yapısının boslukları icin
			else {
				for (int i = 0; i < genislik; i++) {
					if (i == 0 || i == genislik - 1) cout << katKarakter;
					else cout << " ";
				}
			}

			yYeni++;
		}
	}
};

class Kapi {

public:

	int kapiGenislik;
	int kapiYukseklik;
	int x, y;
	char kapiKarakter;

	Kapi(int katX, int katY, int evGenislik, int evYukseklik, char kapiKarakter) {


		this->kapiKarakter = kapiKarakter;
		this->kapiGenislik = (rand() % evGenislik) / 2 + 3;
		this->kapiYukseklik = (rand() % evYukseklik) / 2 + 3;
		this->y = katY + evYukseklik - kapiYukseklik;
		this->x = rand() % (evGenislik - kapiGenislik - 2) + katX + 1;

	}

	void KapiCiz() {

		//kapının yuksekligi boyunca satır satır olusturulması icin
		for (int j = 0; j < kapiYukseklik; j++) {

			gotoxy(x, y + j);
			//her satirda kapi genislik kadar kapı karakter basilir
			for (int i = 0; i < kapiGenislik; i++) {
				cout << kapiKarakter;
			}

		}

	}

};


class Ev {

public:

	Cati* cati;
	Kapi* kapi;
	Kat* kat;

	// Evin konumu
	int x;
	int y;

	Ev(int x, int y, char catiKarakter, char katKarakter, char kapiKarakter, int katSayisi, int catiYukseklik, int evGenislik) {

		this->x = x;
		this->y = y;
		cati = new Cati(evGenislik, catiYukseklik, catiKarakter, x, y);
		kat = new Kat(katSayisi, evGenislik, katKarakter, x, y + cati->yukseklik);
		kapi = new Kapi(x, kat->yYeni, evGenislik, katSayisi, kapiKarakter);


		cati->CatiCiz();
		kat->KatCiz();
		kapi->KapiCiz();

		gotoxy(0, y + katSayisi + cati->yukseklik + 1);
	}
};



int main()
{
	int evGenislik, katSayisi, catiYukseklik, x, y;
	char catiKarakter, katKarakter, kapiKarakter;
	srand(time(0));

	cout << "Genislik: ";
	cin >> evGenislik;
	cout << "Yukseklik: ";
	cin >> katSayisi;
	cout << "Cati Yukseklik: ";
	cin >> catiYukseklik;
	cout << "x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	cout << "Cati Karakter: ";
	cin >> catiKarakter;
	cout << "Kat Karakter: ";
	cin >> katKarakter;
	cout << "Kapi Karakter: ";
	cin >> kapiKarakter;

	system("CLS");
	Ev* ev = new Ev(x, y, catiKarakter, katKarakter, kapiKarakter, katSayisi, catiYukseklik, evGenislik);

}