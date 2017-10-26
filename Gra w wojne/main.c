#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROZMIAR_TALII  52

enum Kolory
{
	trefl = 1,
	karo,
	kier,
	pik
};

enum Wartosci
{
	dwojka = 2,
	trojka,
	czworka,
	piatka,
	szustka,
	siudemka,
	osemka,
	dziewiatka,
	dziesiatka,
	walet,
	dama,
	krol,
	as
};

struct Karta
{
	enum Kolory kolor;
	enum Wartosci wartosc;
};



int Losowa(int mini, int maxi);
void Resetuj(struct Karta *talia);
void Tasuj(struct Karta *talia);
const char * KolorToString(enum Kolory kolor);
const char* WartoscToString(enum Wartosci wartosc);
const char* KartaToString(struct Karta karta);
void Rozdaj(struct Karta gracz1[ROZMIAR_TALII], struct Karta gracz2[ROZMIAR_TALII]);
void Graj(struct Karta gracz[ROZMIAR_TALII], struct Karta komputer[ROZMIAR_TALII], int liczbaKartGracza, int liczbaKartKomputera);


int main()
{
	srand((uint)time(0));
    
    
    struct Karta gracz[ROZMIAR_TALII];
    struct Karta komputer[ROZMIAR_TALII];
    
    Rozdaj(gracz, komputer);
    puts(KartaToString(komputer[0]));
    Graj(gracz, komputer, ROZMIAR_TALII/2, ROZMIAR_TALII/2);

	
	return 0;
}

int Losowa(int mini, int maxi)
{
	return mini + rand() % (maxi - mini);
}

void Graj(struct Karta gracz[ROZMIAR_TALII], struct Karta komputer[ROZMIAR_TALII], int liczbaKartGracza, int liczbaKartKomputera)
{
    struct Karta stol[52];
    int liczbaKartNaStole = 0;
    
    struct Karta wystawionaG = gracz[0];
    struct Karta wystawionaK = komputer[0];
    
    stol[liczbaKartNaStole++] = wystawionaG;
    stol[liczbaKartNaStole++] = wystawionaK;
    
    for (int i=1; i<52; i++)
    {
        gracz[i-1] = gracz[i];
        komputer[i-1] = komputer[i];
    }
    
    if (wystawionaG.wartosc > wystawionaK.wartosc)
    {
        
    }
    
}

void Rozdaj(struct Karta gracz1[ROZMIAR_TALII], struct Karta gracz2[ROZMIAR_TALII])
{
    struct Karta talia[ROZMIAR_TALII];
    Resetuj(talia);
    Tasuj(talia);
    
    for (int i=0; i<ROZMIAR_TALII/2; i++)
    {
        *gracz1++ = talia[i];
    }
    for (int i=ROZMIAR_TALII/2; i<ROZMIAR_TALII; i++)
    {
        *gracz2++ = talia[i];
    }
}

void Resetuj(struct Karta *talia)
{
	struct Karta* strzalka = talia;
	for (int i = 1; i <= 4; i++)
		for (int j = 2; j <= as; j++)
		{
			strzalka->kolor = i;
			strzalka->wartosc = j;
			strzalka++;
		}
}

void Tasuj(struct Karta *talia)
{
	for (int i = ROZMIAR_TALII - 1; i>0; i--)
	{
		int j = Losowa(0, i + 1);
		struct Karta tmp = talia[i];
		talia[i] = talia[j];
		talia[j] = tmp;
	}
}

const char* KolorToString(enum Kolory kolor)
{
    switch (kolor) {
        case trefl:
            return "Trefl";
        case karo:
            return "Karo";
        case kier:
            return "Kier";
        case pik:
            return "Pik";
            
        default:
            return "Blad";
            break;
    }
}

const char* WartoscToString(enum Wartosci wartosc)
{
    switch (wartosc) {
        case dwojka:
            return "Dwojka";
        case trojka:
            return "Trojka";
        case czworka:
            return "Czworka";
        case piatka:
            return "Piatka";
        case szustka:
            return "Szustka";
        case siudemka:
            return "Siudemka";
        case osemka:
            return "Osemka";
        case dziewiatka:
            return "Dziewiatka";
        case dziesiatka:
            return "Dziesiatka";
        case walet:
            return "Walet";
        case dama:
            return "Dama";
        case krol:
            return "Krol";
        case as:
            return "As";
            
        default:
            return "Blad";
    }
}

const char* KartaToString(struct Karta karta)
{
    static char wynik[20];
    strcpy(wynik, WartoscToString(karta.wartosc));
    strcat(wynik, " ");
    strcat(wynik, KolorToString(karta.kolor));
    
    return wynik;
}





