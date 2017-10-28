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
char Graj(int delay);
void WyczyscWejscie(void);


int main()
{
	puts("Krzysztof Dabrowski gr. 1I1\nProjekt Gra w wojne\n-----------------------------------------------------\n");
    
    int opoznienieRozgrywki = 1000;
    char decyzja;
    bool ponow;
    
	srand((unsigned int)time(0));
    
    puts("Komputerowa wersja znanej gry karcianej - gry w wojne\nSterowanie: Aby wylozyc karte podaj dowolny klawisz  (najwygodniej ENTER)\nW dowolnej chwili mozesz wlaczyc tryb automatyczny podajac \"a\" lub \"f\"\n");
    do
    {
        ponow = false;
        puts("Aby zagrac jedna gre wybierz: 1\n"
             "Aby zagrac kilka partii wybierz: 2\n"
             "Aby zmienic szybkosc trybu automatycznego wybierz: 3\n");
        decyzja = getchar();
		if (decyzja != '\n')
			WyczyscWejscie();
        
        if (decyzja == '1')
        {
            Graj(opoznienieRozgrywki);
        }
        else if(decyzja == '2')
        {
			bool nieWczytano;
			int liczbaGier = 0;
			do
			{
				nieWczytano = false;
				printf("Podaj liczbe gier: ");
				scanf("%d", &liczbaGier);
				if (liczbaGier <= 0)
				{
					nieWczytano = true;
					WyczyscWejscie();
					puts("Nieprawidlowa liczba gier. Sproboj ponownie");
				}
				else
					WyczyscWejscie();
			} while (nieWczytano);
			
			for (int i = 1, wygrane = 0, przegrane = 0; i <= liczbaGier; i++)
			{
				printf("Gra %d z %d\tWynik: %dW %dP\n", i, liczbaGier, wygrane, przegrane);
				puts("Wcisnij dowolny klawisz by zaczac aktualna gre");
				if (getchar() != '\n')
					WyczyscWejscie();
				switch (Graj(opoznienieRozgrywki))
				{
				case 'G' :
					wygrane++;
					break;
				case 'K':
					przegrane++;
					break;
				case 'R':
				default:
					break;
				}
			}
        }
        else if (decyzja == '3')
        {
            ponow = true;
            bool nieWczytano;
            do
            {
                nieWczytano = false;
                puts("0 - Bardzo szybko\n1 - Szybko\n2 - Normalnie\n3 - wolno");
                char szybkosc = getchar();
				if (szybkosc != '\n')
					WyczyscWejscie();
                switch (szybkosc)
                {
                    case '0':
                        opoznienieRozgrywki = 1;
                        break;
                    case '1':
                        opoznienieRozgrywki = 500;
                        break;
                    case '2':
                        opoznienieRozgrywki = 1000;
                        break;
                    case '3':
                        opoznienieRozgrywki = 2000;
                        break;
                    default:
                        puts("Nierozpoznany znak. Sproboj ponownie");
                        nieWczytano = true;
                        break;
                }
            } while (nieWczytano);
        }
        else if (decyzja == 'q')
            return 0;
        else
        {
            puts("Nierozpoznany znak. Sproboj ponownie");
            ponow = true;
        }
    } while (ponow);

	return 0;
}

int Losowa(int mini, int maxi)
{
	return mini + rand() % (maxi - mini);
}

void WyczyscWejscie()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


char Graj(int delay)
{
	struct Karta gracz[ROZMIAR_TALII];
	struct Karta komputer[ROZMIAR_TALII];
	int liczbaKartGracza = ROZMIAR_TALII / 2, liczbaKartKomputera = ROZMIAR_TALII / 2;
    struct Karta stol[52];
    int liczbaKartNaStole = 0;
    char kartaS1[20], kartaS2[20];
    bool autoplay = false;
    
    puts("Dowolny klawisz wyklada karte");

	Rozdaj(gracz, komputer);
    
    while (true)
    {
		if (autoplay)
        #ifdef _WIN32
            Sleep(delay);
        #else
            usleep(delay*1000);
        #endif
		else
		{
			char input = getchar();
			if (input != '\n')
				WyczyscWejscie();
			if (input == 'q')
				exit(0);
			if (input == 'f' || input == 'a')
				autoplay = true;
		}
		
		if (liczbaKartGracza == 0 && liczbaKartKomputera == 0)
		{
			puts("Remis\n");
			return 'R';
		}
		if (liczbaKartGracza == 0)
		{
			puts("Przegrales gre\n");
			return 'K';
		}
		if (liczbaKartKomputera == 0)
		{
			puts("Wygrales gre\n");
			return 'G';
		}

        struct Karta wystawionaG = gracz[0];
        struct Karta wystawionaK = komputer[0];
        liczbaKartGracza--;
        liczbaKartKomputera--;
        memmove(gracz, gracz+1, sizeof(struct Karta)*liczbaKartGracza);
        memmove(komputer, komputer+1, sizeof(struct Karta)*liczbaKartKomputera);
        
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
				puts("Remis\n");
				return 'R';
			}
            if (liczbaKartGracza == 0)
            {
                puts("Przegrales gre\n");
                return 'K';
            }
            if (liczbaKartKomputera == 0)
            {
                puts("Wygrales gre\n");
				return 'G';
            }
            stol[liczbaKartNaStole++] = gracz[0];
            stol[liczbaKartNaStole++] = komputer[0];
            liczbaKartGracza--;
            liczbaKartKomputera--;
            memmove(gracz, gracz+1, sizeof(struct Karta)*liczbaKartGracza);
            memmove(komputer, komputer+1, sizeof(struct Karta)*liczbaKartKomputera);
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