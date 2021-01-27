#pragma once
#include "PAGvalores.h"
class PAGstatus
{
private:
	PAGvalores::PAGtipoMovimiento modoMovimiento;
	int teclaMantenida;
	bool botonIzqPulsado;
	double x;
	double y;
public:
	PAGstatus();
	void setModoMovimiento(PAGvalores::PAGtipoMovimiento nuevo);
	PAGvalores::PAGtipoMovimiento getModoMovimiento();
	void setTeclaMantenida(int nueva);
	int getTeclaMantenida();
	void setBotonIzqPulsado(bool valor);
	bool getBotonIzqPulsado();
	void setPosRaton(double x, double y);
	void getPosRaton(double& x, double& y);
};

