#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
//const int ROZMIAR_TALII = 52;
#define ROZMIAR_TALII 52
#pragma warning(disable : 4996)  

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
char* KartaToString(struct Karta karta ,char nazwa[]);
void Rozdaj(struct Karta gracz1[ROZMIAR_TALII], struct Karta gracz2[ROZMIAR_TALII]);
char Graj(bool autoplay);
void PrzesunWLewo(struct Karta tab[], int rozmiar);


int main()
{
	puts("Krzysztof Dabrowski gr. 1I1\nProjekt Gra w wojne\n-----------------------------------------------------\n");

	srand((unsigned int)time(0));

	

    Graj(false);

	
	return 0;
}

int Losowa(int mini, int maxi)
{
	return mini + rand() % (maxi - mini);
}


char Graj(bool autoplay)
{
	struct Karta gracz[ROZMIAR_TALII];
	struct Karta komputer[ROZMIAR_TALII];
	int liczbaKartGracza = ROZMIAR_TALII / 2, liczbaKartKomputera = ROZMIAR_TALII / 2;
    struct Karta stol[52];
    int liczbaKartNaStole = 0;
    char kartaS1[20], kartaS2[20];

	Rozdaj(gracz, komputer);
    
    while (true)
    {
		if (autoplay)
        #ifdef _WIN32
            Sleep(1000);
        #else
            sleep(1000);
        #endif
		else
		{
			char input = getchar();
			if (input == 'q')
				exit(0);
			if (input == 'f' || input == 'a')
				autoplay = true;
		}
		
		if (liczbaKartGracza == 0 && liczbaKartKomputera == 0)
		{
			puts("Remis");
			return 'R';
		}
		if (liczbaKartGracza == 0)
		{
			puts("Przegrales gre");
			return 'K';
		}
		if (liczbaKartKomputera == 0)
		{
			puts("Wygrales gre");
			return 'G';
		}

        struct Karta wystawionaG = gracz[0];
        struct Karta wystawionaK = komputer[0];
        liczbaKartGracza--;
        liczbaKartKomputera--;
        PrzesunWLewo(gracz, ROZMIAR_TALII);
        PrzesunWLewo(komputer, ROZMIAR_TALII);
        
        printf("%s %-14d%s %d\n%-20s%s\n", "Gracz", liczbaKartGracza, "Komputer", liczbaKartKomputera, KartaToString(wystawionaG, kartaS1), KartaToString(wystawionaK, kartaS2));
        
        stol[liczbaKartNaStole++] = wystawionaG;
        stol[liczbaKartNaStole++] = wystawionaK;
        
        if (wystawionaG.wartosc > wystawionaK.wartosc)
        {
            puts("Wygrywasz\n");
            while (liczbaKartNaStole > 0)
                gracz[liczbaKartGracza++] = stol[--liczbaKartNaStole];
        }
        if (wystawionaG.wartosc < wystawionaK.wartosc)
        {
            puts("Komputer wygrywa\n");
            while (liczbaKartNaStole > 0)
                komputer[liczbaKartKomputera++] = stol[--liczbaKartNaStole];
        }
        if (wystawionaG.wartosc == wystawionaK.wartosc)
        {
            puts("Wojna!\n");

			if (liczbaKartGracza == 0 && liczbaKartKomputera == 0)
			{
				puts("Remis");
				return 'R';
			}
            if (liczbaKartGracza == 0)
            {
                puts("Przegrales gre");
                return 'K';
            }
            if (liczbaKartKomputera == 0)
            {
                puts("Wygrales gre");
				return 'G';
            }
            stol[liczbaKartNaStole++] = gracz[0];
            stol[liczbaKartNaStole++] = komputer[0];
            liczbaKartGracza--;
            liczbaKartKomputera--;
            PrzesunWLewo(gracz, ROZMIAR_TALII);
            PrzesunWLewo(komputer, ROZMIAR_TALII);
        }
    }

	return 'R';
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

void PrzesunWLewo(struct Karta tab[], int rozmiar)
{
    for (int i=1; i<rozmiar; i++)
        tab[i-1] = tab[i];
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

char * KartaToString(struct Karta karta ,char nazwa[])
{
//    static char wynik[20];
//    strcpy(wynik, WartoscToString(karta.wartosc));
//    strcat(wynik, " ");
//    strcat(wynik, KolorToString(karta.kolor));
//
//    return wynik;
    strcpy(nazwa, WartoscToString(karta.wartosc));
    strcat(nazwa, " ");
    strcat(nazwa, KolorToString(karta.kolor));
    
    return nazwa;
}





