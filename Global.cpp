#include "global.hpp"

bool Global::mentes()
{
    system(CLEAR);
    bool kilep = false;
    bool mentes = false;
    std::cout << "Biztosan ki szeretnel lepni? [ I / N ]\n";
    char biztos_k;
    std::cin >> biztos_k;
    biztos_k = tolower(biztos_k);
    if (biztos_k == 'i' or biztos_k == 'y') {
        std::cout << "Szeretnel menteni? [ I / N ]\n";
        char biztos_m;
        std::cin >> biztos_m;
        biztos_m = tolower(biztos_m);
        if (biztos_m == 'i' or biztos_m == 'y')
        {
            std::string file_nev;
            std::cout << "\nMi legyen a mentesed neve?\n";
            std::cin >> file_nev;
            std::ofstream f(file_nev);
            if (f.is_open())
            {
                f << this->getgCP()<< std::endl;
                f << this->getgElet() << std::endl;
                f << this->getgErmemutatas() << std::endl;
                f.close();
                return true;
            }
            else
            {
                std::cerr << "\nMENTESI HIBA!\n";
                return false;
            }
        }
        else if (biztos_m == 'N' or biztos_m == 'n')
        {
            std::cout << "\nNem mentettel\n";
            spause();
            return true;
        }
    }
    else if (biztos_k == 'n' or biztos_k == 'N')
    {
        std::cout << "\nNem leptel ki\n";
        spause();
        return false;
    }
    else
    {
        std::cout << "\nHibas valasz\n";
        spause();
        return false;
    }
    return false;
}

void Global::mentes_be(std::string mentes_neve)
{

    std::string file_nev;
    std::cin >> file_nev;
    std::ifstream f(file_nev);
    if (f.is_open())
    {
        std::string data[3];
        for (int i = 0; i < 3; i++)
        {
            std::getline(f, data[i]);
        }
        this->setgCP(stoi(data[0]));
        this->setgElet(stoi(data[1]));
        this->setgErmemutatas(stoi(data[2]));
        f.close();
    }
    else
    {
        std::cerr << "\nNEM SIKERULT BETOLTENI A MENTEST\n";
    }

}
