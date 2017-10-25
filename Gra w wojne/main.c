#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

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

int main()
{
	srand(time(0));
	struct Karta talia[52];
	Resetuj(talia);
	Tasuj(talia);


	for (int i = 0; i<52; i++)
		printf("%d\n", talia[i].wartosc);
	return 0;
}

int Losowa(int mini, int maxi)
{
	return mini + rand() % (maxi - mini);
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
	const int rozmiar = 52;
	for (int i = rozmiar - 1; i>0; i--)
	{
		int j = Losowa(0, i + 1);
		struct Karta tmp = talia[i];
		talia[i] = talia[j];
		talia[j] = tmp;
	}
}