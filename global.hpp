#pragma once
#include "jatekmenet.hpp"

class Global
{
private:
	int gElet = 3;
	int gCP = 0;
	int sebzes = 0;
	bool fin;
	bool helyesbe = false;
	bool gErmemutatas = false;
public:
	Jatekmenet* jatekter = nullptr;
	int getgElet()
	{
		return gElet;
	}
	int getgCP()
	{
		return gCP;
	}
	int getSebzes()
	{
		return sebzes;
	}
	bool getFin()
	{
		return fin;
	}
	bool getHelyesbe()
	{
		return helyesbe;
	}
	bool getgErmemutatas()
	{
		return gErmemutatas;
	}

	Global& setgElet(int e)
	{
		gElet = e;
		return *this;
	}
	Global& setgCP(int cp)
	{
		gCP = cp;
		return *this;
	}
	Global& setSebzes(int s)
	{
		sebzes = s;
		return *this;
	}
	Global& setFin(bool f)
	{
		fin = f;
		return *this;
	}
	Global& setHelyesbe(bool h)
	{
		helyesbe = h;
		return *this;
	}
	Global& setgErmemutatas(bool e)
	{
		gErmemutatas = e;
		return *this;
	}

bool mentes();
void mentes_be(std::string mentes_neve);
};