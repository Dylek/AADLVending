#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

//2 tablice do produktów
int[10] productPrice = {250,250,365,100,99,215,300,100,100,50};
int[10] productQuanity = {2,2,3,4,5,6,7,8,9,10};


//nie ma p³atnoœci banknotami
//0-1gr, 1-2gr, 3-5gr, 4-10gr, 5-20gr, 6-50gr, 7-100gr, 8-200gr, 9-500gr,
int[9] coin = {50,50,50,50,50,25,25,25,10};
int[9] coinValue = {1,2,5,10,20,50,100,200,500};
int paid;// zmienna przechowuj¹ca pieni¹dze, które wp³aci³ klient
bool productFallen;//zmienna oznaczaj¹ca, ¿e produkt pomyœlnie wypad³

void give_change(int toPay);
void give_product(int number);
void pay_deal(int product);
void pressed_button(int pressed);
void view_message(string message);
void has_fallen();
void insert_money(int inserted);

void pay_deal(int product) {
	assert(productQuanity[product] >= 0);//automat nie mo¿e mieæ -1 batoników
	if (productQuanity[product] == 0) {
		view_message("Brak produkty!");
		give_change(0);
	}
	else {
		assert(productPrice[product] >= 0);//nie ma ujemnych cen
		int toPay = productPrice[product];
		char str[80];
		//póki nie ma doœæ pieniêdzy, wyœiwtlamy ile pozosta³o do wp³aty
		while (toPay > paid) {			
			sprintf(str, "Do zap³aty:%f!", (toPay-paid));
			view_message(str);
		}
		//próbujemy wydaæ produkt
		give_product(product);
		//czekam 4 sekundy na to ¿e spadnie produkt
		sleep(4000);
		//jeœli wypad³ wydajemy reszte
		if (has_fallen == true) {
			sprintf(str, "Zap³acono! Reszta: %F", (paid - toPay));
			view_message(str);
			give_change(toPay);
		}
		//jeœli nie wypad³, wydajemy wp³acone pieni¹dze
		else {			
			view_message("Coœ posz³o nie tak!");
			give_change(0);
		}		
	}
}

void insert_money(int inserted) {
	assert(inserted > 0);//nie ma ujemnych pieniêdzy
	assert(paid >= 0);// nie mo¿na wzi¹c na kredyt
	paid += inserted;
}

void pressed_button(int pressed) {
	//wciœniêty przycisk, zapisujemy
	chosenProduct = pressed;
	switch (pressed) {
	case 0:
		give_change(0);// w razie anulowania wydajemy, wszystko co klient wp³aci³
		break; 
	default: 
		pay_deal(pressed);//domyœlnie dokonujemy tranzakcji zwi¹zanej z danym produktem
	}
}

void view_message(string message) {
	//wyœlij tekst "message" na wyœwietlaczu
}

void has_fallen() {
	//otrzymano sygna³ z fotokomórki
	//po otrzymaniu, sygna³u ustawiamy zmienn¹, która informuje nas ¿e produkt spad³
	productFallen = true;
}

void give_product(int number) {
	//poruszam spiralê podajnika "number",¿eby spad³ odpowiedni produkt
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
		//sygna³ do liczyd³a, ¿eby wyda³o monete o wartoœæi "coinValue"
	}
}
