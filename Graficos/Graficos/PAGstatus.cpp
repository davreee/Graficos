#include "PAGstatus.h"
#include <iostream>

PAGstatus::PAGstatus() : modoMovimiento(PAGvalores::PAGtipoMovimiento::PAG_NINGUNO),
teclaMantenida (-1),
botonIzqPulsado(false),
x(0),
y(0)
{
}

void PAGstatus::setModoMovimiento(PAGvalores::PAGtipoMovimiento nuevo)
{	
	modoMovimiento = nuevo;
}

PAGvalores::PAGtipoMovimiento PAGstatus::getModoMovimiento()
{
	return modoMovimiento;
}

void PAGstatus::setTeclaMantenida(int nueva)
{
	teclaMantenida = nueva;
}

int PAGstatus::getTeclaMantenida()
{
	return teclaMantenida;
}

void PAGstatus::setBotonIzqPulsado(bool valor)
{
	botonIzqPulsado = valor;
}

bool PAGstatus::getBotonIzqPulsado()
{
	return botonIzqPulsado;
}

void PAGstatus::setPosRaton(double x, double y)
{
	this->x = x;
	this->y = y;
}

void PAGstatus::getPosRaton(double& x, double& y)
{
	x = this->x;
	y = this->y;
}
