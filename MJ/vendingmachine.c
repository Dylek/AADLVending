#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

//2 tablice do produkt�w
int[10] productPrice = {250,250,365,100,99,215,300,100,100,50};
int[10] productQuanity = {2,2,3,4,5,6,7,8,9,10};


//nie ma p�atno�ci banknotami
//0-1gr, 1-2gr, 3-5gr, 4-10gr, 5-20gr, 6-50gr, 7-100gr, 8-200gr, 9-500gr,
int[9] coin = {50,50,50,50,50,25,25,25,10};
int[9] coinValue = {1,2,5,10,20,50,100,200,500};
int paid;// zmienna przechowuj�ca pieni�dze, kt�re wp�aci� klient
bool productFallen;//zmienna oznaczaj�ca, �e produkt pomy�lnie wypad�

void give_change(int toPay);
void give_product(int number);
void pay_deal(int product);
void pressed_button(int pressed);
void view_message(string message);
void has_fallen();
void insert_money(int inserted);

void pay_deal(int product) {
	assert(productQuanity[product] >= 0);//automat nie mo�e mie� -1 batonik�w
	if (productQuanity[product] == 0) {
		view_message("Brak produkty!");
		give_change(0);
	}
	else {
		assert(productPrice[product] >= 0);//nie ma ujemnych cen
		int toPay = productPrice[product];
		char str[80];
		//p�ki nie ma do�� pieni�dzy, wy�iwtlamy ile pozosta�o do wp�aty
		while (toPay > paid) {			
			sprintf(str, "Do zap�aty:%f!", (toPay-paid));
			view_message(str);
		}
		//pr�bujemy wyda� produkt
		give_product(product);
		//czekam 4 sekundy na to �e spadnie produkt
		sleep(4000);
		//je�li wypad� wydajemy reszte
		if (has_fallen == true) {
			sprintf(str, "Zap�acono! Reszta: %F", (paid - toPay));
			view_message(str);
			give_change(toPay);
		}
		//je�li nie wypad�, wydajemy wp�acone pieni�dze
		else {			
			view_message("Co� posz�o nie tak!");
			give_change(0);
		}		
	}
}

void insert_money(int inserted) {
	assert(inserted > 0);//nie ma ujemnych pieni�dzy
	assert(paid >= 0);// nie mo�na wzi�c na kredyt
	paid += inserted;
}

void pressed_button(int pressed) {
	//wci�ni�ty przycisk, zapisujemy
	chosenProduct = pressed;
	switch (pressed) {
	case 0:
		give_change(0);// w razie anulowania wydajemy, wszystko co klient wp�aci�
		break; 
	default: 
		pay_deal(pressed);//domy�lnie dokonujemy tranzakcji zwi�zanej z danym produktem
	}
}

void view_message(string message) {
	//wy�lij tekst "message" na wy�wietlaczu
}

void has_fallen() {
	//otrzymano sygna� z fotokom�rki
	//po otrzymaniu, sygna�u ustawiamy zmienn�, kt�ra informuje nas �e produkt spad�
	productFallen = true;
}

void give_product(int number) {
	//poruszam spiral� podajnika "number",�eby spad� odpowiedni produkt
}

void give_change(int toPay) {
	//algorytm wydawania reszty
	int change = paid - toPay;
	while (change > 0) {
		int coinToFall = 0;
		for (int i = 0; i <-9; i++) {
			if (coin[i] > 0 && change - coin[i] >= 0) {
				coinToFall = i;
			}
		}
		coin[coinToFall] = coin[coinToFall] - 1;
		change -= cointValue[coinToFall];
		paid -= cointValue[coinToFall];
		//sygna� do liczyd�a, �eby wyda�o monete o warto��i "coinValue"
	}
}
