#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Obiekt.h"

/**
 * @brief Klasa obsługująca animacje
 *
 */
class Animacja : public Obiekt
{
private:
	/// Pozycja x klatki
	int x = 0;
	/// Pozycja y klatki
	int y = 0;
	/// Szerokosc klatki
	int szerokosc;
	/// WYsokosc klatki
	int wysokosc;
	/// Ilosc klatek w teksturze
	int klatki;
	/// Numer aktualnej klatki
	int klatka;
	/// Maksymalna wysokosc na ktora moze dotrzec algorytm przed powrotem na poczatek
	int wysokoscMAX = 0;
	/// Maksymalna szerokosc na ktora moze dotrzec algorytm przed powrotem na poczatek
	int szerokoscMAX = 0;
	/// Czas jaki ma uplynac miedzy klatkami
	float przerwa;
	/// Licznik kontroli czasu
	float dt = 0;
	/// Orientacja
	bool pionowa;
	/// Czy animacja ma sie wykonywac w kolko czy tylko jednorazowo
	bool jednorazowa;
	/// Czy animacja jednorazowa sie skonczyla
	bool skonczona = false;

	/**
	 * @brief  Zmienia klatke na nastapna, po dotarciu na ostatnia klatke wraca do pierwszej.
	 *
	 */
	void zmienKlatke() {
		if (dt > przerwa) { // Je�eli licznik jest wi�kszy ni� podana przerwa zmienia sie klatka animacji
			if (pionowa) {
				this->y += wysokosc;
				if (this->y >= wysokoscMAX) {
					if (this->jednorazowa == true) {
						this->skonczona = true;
					}
					this->y = 0;
				}
			}
			else {
				this->x += szerokosc;
				if (this->x >= szerokoscMAX) {
					if (this->jednorazowa == true) {
						this->skonczona = true;
					}
					this->x = 0;
				}
			}
			dt = 0; // Licznik jest resetowany
		}
	}

public:
	/**
	* @brief Konstruktor klasy animacja
	*
	* @param sciezka Sciezka do pliku z tekstura
	* @param pozx Pozycja startowa
	* @param pozy Pozycja startowa
	* @param szerokosc Szerokosc klatki
	* @param wysokosc Wysokosc klatki
	* @param klatki Ilosc klatek
	* @param przerwa Czas przerwy
	* @param pionowa Orientacja
	*/
	Animacja(std::string sciezka, int pozx, int pozy, int szerokosc, int wysokosc, int klatki, float przerwa, bool jednorazowa = false, bool pionowa = true) : Obiekt(sciezka, sf::Vector2f(pozx, pozy)) {
		this->szerokosc = szerokosc;
		this->wysokosc = wysokosc;
		this->klatki = klatki;
		this->klatka = 1;
		this->jednorazowa = jednorazowa;
		this->pionowa = pionowa;
		this->przerwa = przerwa;
		if (pionowa) this->wysokoscMAX = wysokosc * klatki;
		else this->szerokoscMAX = szerokosc * klatki;

		//Sprite
		this->sprajt.setTextureRect(sf::IntRect(this->x, this->y, this->szerokosc, this->wysokosc));
	}


	/**
	 * @brief Rysuje i zmienia klatki animacji
	 *
	 * @param cel Obiekt typu RenderTarget w ktorym ma byc wyswietlany obraz
	 * @param dtime Kontrola czasu
	 */
	void animuj(sf::RenderTarget* cel, const float& dtime) {
		cel->draw(this->sprajt);
		this->dt += dtime;
		zmienKlatke();
		this->sprajt.setTextureRect(sf::IntRect(this->x, this->y, this->szerokosc, this->wysokosc));
	}

	/**
	 * @brief Zmienia pozycje sprite'a
	 *
	 * @param gdzie Vector2f na ktory ma przejsc sprite
	 */
	void rusz(sf::Vector2f gdzie) {
		this->sprajt.setPosition(gdzie);
	}

	/**
	* @brief Zwraca stan animacji
	* @return true gdy animacja juz sie skonczyla
	* @return false gdy animacja dalej trwa
	*/
	bool koniec() {
		if (this->skonczona == true) {
			return true;
		}
		else return false;
	}

	/**
	* @brief Ustawia origin na srodku sprite'a
	*/
	void setOriginOnMiddle() {
		this->sprajt.setOrigin(sf::Vector2f(this->szerokosc/2, this->wysokosc/2));
	}

	/**
	* @brief Resetuje stan animacji do początkowej wartosci
	*/
	void zresetuj() {
		if (this->skonczona == true) {
			this->x = 0;
			this->y = 0;
			this->skonczona = false;
		}
	}

};