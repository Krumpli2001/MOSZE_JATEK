#include "global.hpp"

bool Global::mentes(Global* g)
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
                f << g->getgCP() << std::endl;
                f << g->getgElet() << std::endl;
                f << g->getgErmemutatas() << std::endl;
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
    }

}
