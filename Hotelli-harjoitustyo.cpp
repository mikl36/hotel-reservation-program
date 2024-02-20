#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <array>

const int HUONEHINTA1H = 100; // perushuonehinnat vakioita
const int HUONEHINTA2H = 150;

// funktioiden prototyypit
void uusirivi(int montako = 1);
void tervetuloa(const int HUONEHINTA1H, const int HUONEHINTA2H);
int satunnaislukugeneraattori(int x, int y);
void vapaathuoneet(int alaraja, int ylaraja, std::vector <int>& varatutnumerot);
float alennus(float aleprosentti);
int virhetarkastelu(int alaraja, int ylaraja);
void varatuthuoneet(std::vector<int>& huonenumerot1h, std::vector<int>& huonenumerot2h);
void vapaidenhuoneidentarkistus(int vapaathuoneet1h, int vapaathuoneet2h);
void arvotaanhuone(int& huone, const int KAIKKIHUONEET, const int ARVOTTAVA_ALALUKU, std::vector<int>& huonenumerot);
void hotellivaraustiedot(int& huone, int& huonelasku, int& yomaara);

// tehty Visual Studio 2022:lla, käännetty Default (ISO C++14 Standard) ja ISO C++20 Standard (/std:c++20)
// pääohjelmassa voi varata hotellihuoneita 1 ja 2 hengen huoneista niin kauan, kun käyttäjä haluaa / huoneita on vapaana
int main() {

    srand((unsigned int)time(0));  // alustetaan satunnaislukugeneraattori koneen kellonajalla

    // sen verran paljon muuttujia, että olisi voinut olla järkevämpää tehdä esim. struct Huone, laajentumisenki takia
    // osa muuttujista tässä tarpeettomia (yksinkertaistettavissa) nyt, mutta ajateltu selkeämmäksi
    const int HUONEMAARA = { (rand() % (300 / 2 - 40 / 2 + 1) + 40 / 2) * 2 }; // kokonaismäärä on satunnainen, parillinen
    const int HUONEMAARA1H = HUONEMAARA / 2; // Huonemaarat jaetaan 2 ja 1 hengen huoneisiin, näin helpompi nyt muuttaa
    const int HUONEMAARA2H = HUONEMAARA / 2;
    int vapaathuoneet1h, vapaathuoneet2h; // esitellään vapaiden huoneiden määrä ohjelmassa
    int huone1h = 0; // lähtötilanteessa ei varattuja huoneita
    int huone2h = 0;
    float ale{ 0 }; //alearvonnan tulos
    int komento{ 0 }; // tehdään switch-valinnat komennolla
    std::vector<int> huonenumerot1h; //varaa vektorin, johon tallennetaan käytetyt huonenumerot 1 hengen huoneissa.
    std::vector<int> huonenumerot2h; //varaa vektorin, johon tallennetaan käytetyt huonenumerot 2 hengen huoneissa.

    do { // Ollaan silmukassa niin kauan, kun käyttäjä haluaa varata ja/tai huoneita on käytettävissä
        tervetuloa(HUONEHINTA1H, HUONEHINTA2H); // toistuva teksti valintoja tehdessä, tervetuloa

        // tarkastetaan, onko vapaita huoneita, jolloin joko poistutaan ohjelmasta tai annetaan varata vapaata huonetyyppiä
        vapaathuoneet1h = static_cast<int>(HUONEMAARA1H - huonenumerot1h.size()); 
        vapaathuoneet2h = static_cast<int>(HUONEMAARA2H - huonenumerot2h.size());
        vapaidenhuoneidentarkistus(vapaathuoneet1h, vapaathuoneet2h);

        komento = virhetarkastelu(0, 2); // hyvaksytaan ainoastaan casearvot 0,1 ja 2 virhetarkastelussa
        system("cls");

        switch (komento) {  // kolme peruscasea: 0 eli lopetetaan, 1 tehdään 1H-varaus ja 2 tehdään 2H-varaus
        case 0: // lopetetaan
            std::cout << "Kiitos, palataan joskus toiste!";
            break;

        case 1:  // varataan 1h huoneet    
            if (vapaathuoneet1h == 0) // ei anneta valita, jos ei ole vapaita huoneita ja käyttäjä ei sitä huomannut
            {
                system("cls"); // tyhjennetään valikko
                std::cout << "Et tainnut huomata? Valitettavasti meilla ei ole enaa yhden hengen huoneita varattavana.";
                break;
            }
            std::cout << "Kuinka moneksi yoksi haluatte yhden hengen huoneen(MAX 100 yota)? Poistu valitsemalla 0."; 
            uusirivi();
            int yomaara1h;
            yomaara1h = virhetarkastelu(0, 100); // hyväksytään yömääräksi arvo väliltä 1-100, poistuminen 0
            if (yomaara1h == 0) {
                system("cls");
                break;
            }
            std::cout << "Voit varata itse huoneen, valitse 1. Vaihtoehtoisesti arvotaan huone, valitse 2. ";
            int valinta; // tehdään valinnat
            valinta = virhetarkastelu(0, 2); // poistuminen mahdollista 0, muuten valinnat 1 tai 2 mahdollisia
            if (valinta == 0) {
                system("cls");
                break;
            }
            else if (valinta == 1) {  // tehdään itse varaus
                bool ainuthuone = false;
                do                  // huone voidaan varata ainoastaan kerran loopissa
                {
                    std::cout << "Voit varata huoneista/huoneesta: "; uusirivi(); // tarjotaan vapaat huoneet
                    vapaathuoneet(1, HUONEMAARA1H, huonenumerot1h); uusirivi();
                    huone1h = virhetarkastelu(1, HUONEMAARA1H); // huoneita hyväksytään tältä väliltä, alapuolikas
                    ainuthuone = true; // tarkastaa huoneen ainutlaatuisuuden verrattuna jo varattuihin huonenumeroihin
                    for (int i = 0; i < huonenumerot1h.size(); i++) { 
                        if (huonenumerot1h[i] == huone1h)
                        {
                            ainuthuone = false;
                        }
                    }
                } while (!ainuthuone);  // silmukka niin kauan, kun huone ei ole ainutkertainen
                huonenumerot1h.push_back(huone1h); // varaus talletetaan huonenumeroihin / vektoriin
            }
            else if (valinta == 2) {  // tehdään varaus arpomalla huone, periaate ainutlaatuisuudessa sama kuin yllä
                arvotaanhuone(huone1h, HUONEMAARA1H, 0, huonenumerot1h);
            }
            {
                system("cls");
                int huonelasku1h = static_cast<int>(yomaara1h * HUONEHINTA1H * alennus(ale)); // laskusumma + mahd. ale
                hotellivaraustiedot(huone1h, huonelasku1h, yomaara1h); // ilmoitetaan varaustiedot, hinta, huone
                // varatuthuoneet(huonenumerot1h, huonenumerot2h); // varattujen huonenumeroiden tarkastusta varten
            }
            break;

        case 2:  // varataan 2h huoneet, runko 1h hengen huoneen varauksista, kommentit pääosin varalta
            if (vapaathuoneet2h == 0) // ei anneta valita, jos ei ole vapaita huoneita ja käyttäjä ei sitä huomannut
            {
                system("cls");
                std::cout << "Et tainnut huomata? Valitettavasti meilla ei ole enaa kahden hengen huoneita varattavana.";
                break;
            }
            std::cout << "Kuinka moneksi yoksi haluatte kahden hengen huoneen(MAX 100 yota)? Poistu valitsemalla 0."; 
            uusirivi();
            int yomaara2h;
            yomaara2h = virhetarkastelu(0, 100); // hyväksytään yömääräksi arvo väliltä 1-100, poistuminen 0
            if (yomaara2h == 0) {
                system("cls");
                break;
            }
            std::cout << "Haluatko varata itse, valitse 1, vai arvotaanko huone, valitse 2? ";
            valinta = virhetarkastelu(0, 2); // hyväksytään 0, 1 tai 2, 0 poistuminen
            if (valinta == 0) {
                system("cls");
                break;
            }
            else if (valinta == 1) {  // tehdään itse varaus
                bool ainuthuone = false;
                do
                {
                    std::cout << "Voit varata huoneista/huoneesta: "; uusirivi(); // tarjotaan tähän vapaat huoneet
                    vapaathuoneet(HUONEMAARA2H + 1, HUONEMAARA, huonenumerot2h); uusirivi(); // yläpuolikkaan huoneet
                    huone2h = virhetarkastelu(HUONEMAARA2H + 1, HUONEMAARA); 
                    ainuthuone = true;
                    for (int i = 0; i < huonenumerot2h.size(); i++) { // tarkastaa huoneen ainutlaatuisuuden
                        if (huonenumerot2h[i] == huone2h)
                        {
                            ainuthuone = false;
                        }
                    }
                } while (!ainuthuone);  // silmukka niin kauan, kun huone ei ole ainutkertainen
                huonenumerot2h.push_back(huone2h); // varaus talletetaan huonenumeroihin / vektoriin
            }
            else if (valinta == 2) {  // tehdään varaus, arvonta
                arvotaanhuone(huone2h, HUONEMAARA2H, HUONEMAARA2H, huonenumerot2h);
            }
            {
                system("cls");
                int huonelasku2h = static_cast<int>(yomaara2h * HUONEHINTA2H * alennus(ale)); // huoneen laskusumma
                hotellivaraustiedot(huone2h, huonelasku2h, yomaara2h); // ilmoitetaan varaustiedot, lasku ja huone
                //  varatuthuoneet(huonenumerot1h, huonenumerot2h); // varattujen huonenumeroiden tarkistusta varten
            }
            break;

        default:
            std::cout << "Ei hyvaksyttava arvo!"; // varalta virheille / halutusta poikkeaville
            break; // järkevintä voisi olla tänne laittaa virhetarkastelu
        }

        uusirivi();

    } while (komento == 1 || komento == 2); // tehdään niin kauan, kun on hyväksyttävä valinta
    return 0;
}

// Tulostetaan rivinvaihto. Kurssin 5G00EI63-3011 / Jere Käpyahon esimerkeistä / aineistoista
void uusirivi(int montako) {
    if (montako <= 0) {
        return;
    }
    for (int i{ 0 }; i < montako; i++) {
        std::cout << '\n';
    }
}

// Tulostetaan tervetuloa, kerrotaan käyttäjälle valinnat, huonehinnat ja mahd. alennuksista
void tervetuloa(const int HUONEHINTA1H, const int HUONEHINTA2H) {
    std::cout << "******Tervetuloa hotelli Aapiseen******"; uusirivi();
    std::cout << "Haluatteko varata yhden hengen huoneen? Valitse 1."; uusirivi();
    std::cout << "Haluatteko varata kahden hengen huoneen? Valitse 2."; uusirivi();
    std::cout << "Jos haluatte lopettaa, valitse 0."; uusirivi();
    std::cout << "------------------------------------"; uusirivi();
    std::cout << "Huonehintamme on yhden hengen huoneelle " << HUONEHINTA1H << " euroa ";
    std::cout << "ja kahden hengen huoneelle " << HUONEHINTA2H << " euroa."; uusirivi();
    std::cout << "Tanaan joillekin onnekkaille arvotaan 10 % tai 20 % alennus."; uusirivi();
}

//funktio, jolla luodaan satunnaiset luvut, x = yläarvo, y =ala-arvo, satunnaisluku välillä
int satunnaislukugeneraattori(int x, int y) {
    int satunnaisluku = { (rand() % (x - y + 1) + y) };
    return satunnaisluku;
}

// tulostetaan ulos huonenumerot, jotka eivät ole varattuja vektorissa, käytetään viittausta koon takia
void vapaathuoneet(int alaraja, int ylaraja, std::vector <int>& varatutnumerot)
{
    for (int i = alaraja; i <= ylaraja; i++) {
        bool samanumero = false;
        for (int j = 0; j < varatutnumerot.size(); j++) { // verrataan vektorin varattuihin numeroihin
            if (i == varatutnumerot[j]) {
                samanumero = true;
                break;
            }
        }
        if (!samanumero) { // tulostetaan numero, jos ei ole samanumero
            std::cout << i << " ";
            if ((i - alaraja + 1) % 20 == 0) { // tehdään uusirivi 20 numeron välein, ei liikaa numeroita
                uusirivi();
            }
        }
    }
}

// tehdään alennusfunktio, joka palauttaa satunnaisesti alennuksen 0 =1,0, 10 = 0,9 tai 20 % = 0,8
float alennus(float aleprosentti) {
    int arvonta = rand() % 3 + 1;
    aleprosentti = 1.0;
    if (arvonta == 2) {
        aleprosentti = 0.9F;
    }
    else if (arvonta == 3) {
        aleprosentti = 0.8F;
    }
    return aleprosentti;
}

// virhetarkastelu, jossa rajataan valinta tiettyihin kokonaislukuihin ja ei hyväksytä tyhjää väliä esim. 01 02
int virhetarkastelu(int alaraja, int ylaraja) {
    std::cout << "Anna valintasi: "; // lisätä esim. string, jos haluaa muokata myös tekstit
    std::string syote;
    while (true) {
        std::getline(std::cin, syote);
        std::stringstream ss(syote);
        int numero;
        if (ss >> numero && numero >= alaraja && numero <= ylaraja && ss.eof()) {
            return numero;
        }
        std::cout << "Virheellinen valinta. Syota hyvaksyttava luku." << std::endl;
    }
}

// Varattujen huoneiden tarkistus: varattujen huoneiden tarkistusta varten 
// ja mahdollista case 3 varten, että voidaan perua huonevaraus vector::erase
void varatuthuoneet(std::vector<int>& huonenumerot1h, std::vector<int>& huonenumerot2h) {
    std::cout << "Varatut huoneet: ";
    for (int i = 0; i < huonenumerot1h.size(); i++) { // ilmoitetaan 1 H huoneet
        std::cout << huonenumerot1h[i] << " ";
    }
    for (int i = 0; i < huonenumerot2h.size(); i++) { // 2 H huoneet
        std::cout << huonenumerot2h[i] << " ";
    }
}

// tarkastetaan ja ilmoitetaan vapaat huoneet eri skenaarioissa, poistutaan ohjelmasta, 
// jos ei vapaita huoneita // voitaisiin tiivistää esim. switchillä
void vapaidenhuoneidentarkistus(int vapaathuoneet1h, int vapaathuoneet2h) {
    if (vapaathuoneet1h == 0 && vapaathuoneet2h == 0) { //jos ei vapaita huoneita, poistutaan, muuten kertoo vapaat huoneet
        std::cout << "Meilla ei ole valitettavasti enaa vapaita huoneita. Pahoittelut, palataan joskus toiste!"; 
        uusirivi();
        // return 0;
        exit(0);
    }
    else if (vapaathuoneet1h == 0) {
        std::cout << "Meilla ei ole enaa vapaita yhden hengen huoneita. "; // voisi ilmoitta myös vapaat huoneet
        std::cout << "Voit valita kahden hengen huoneen tai lopettaa."; 
        uusirivi();
    }
    else if (vapaathuoneet2h == 0) {
        std::cout << "Meilla ei ole enaa vapaita kahden hengen huoneita. "; // voisi ilmoittaa vapaat huoneet
        std::cout << "Voit valita yhden hengen huoneen tai lopettaa."; 
        uusirivi();
    }
    else
    {
        std::cout << "Meilla on " << vapaathuoneet1h << " yhden hengen huone/huonetta ";
        std::cout << "ja " << vapaathuoneet2h << " kahden hengen huone / huonetta vapaana."; 
        uusirivi();
    }
}

// Arvotaan huone satunnaisesti, mutta huone voidaan varata ainoastaan kerran
void arvotaanhuone(int& huone, const int KAIKKIHUONEET, const int ARVOTTAVA_ALALUKU, std::vector<int>& huonenumerot) {
    bool ainuthuone = false;
    do                  // huoneet arvotaan satunnaisesti, mutta huone voidaan varata ainoastaan kerran loopissa
    { // Huoneiden kokonaismäärä on vakio huonemäärän perusteella ja satunnainen, kun ainuthuone on true
        huone = (rand() % KAIKKIHUONEET) + 1 + ARVOTTAVA_ALALUKU; 
        ainuthuone = true; // tarkastaa huoneen ainutlaatuisuuden verrattuna jo varattuihin huonenumeroihin
        for (int i = 0; i < huonenumerot.size(); i++) {        
            if (huonenumerot[i] == huone)
            {
                ainuthuone = false;
            }
        }
    } while (!ainuthuone);  // silmukka niin kauan, kun huone ei ole ainutkertainen
    huonenumerot.push_back(huone); // varaus talletetaan huonenumeroihin / vektoriin
}

// Kerrotaan onnistuneesta varauksesta, huonenumero, hinta, yömäärä
void hotellivaraustiedot(int& huone, int& huonelasku, int& yomaara) {
    std::cout << "Kiitos varauksestanne. Teidan huonenumeronne on " << huone << ". "; uusirivi(); 
    std::cout << "Huoneenne hinta on " << huonelasku << " euroa, kun yovytte " << yomaara << " yota."; uusirivi();
}
