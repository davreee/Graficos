#pragma once
class PAGvalores
{
public:
	enum PAGtipoMovimiento {
		PAG_PAN,
		PAG_TILT,
		PAG_TRUCK,
		PAG_BOOM,
		PAG_ORBIT,
		PAG_ZOOM,
		PAG_NINGUNO
	};
	enum PAGTipoLuz {
		PAG_AMBIENTE,
		PAG_PUNTUAL,
		PAG_SPOT,
		PAG_DIRECCIONAL
	};
	enum PAGpartesRevolucion : int {
		PAG_CUERPO = 0,
		PAG_TAPA_SUP = 1,
		PAG_TAPA_INF = 2
	};
};

