#pragma once
#include "jatekmenet.hpp"

class Global
{
private:
	int gElet;
	int gCP;
	int sebzes;
	bool fin;
	bool helyesbe;
	bool gErmemutatas;
public:
	Global() { gElet = 3; gCP = 0; sebzes = 0; fin = false; helyesbe = false; gErmemutatas = false; }

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
void mentes_be();
};