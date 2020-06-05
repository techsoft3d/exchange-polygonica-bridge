#ifndef EXCHANGE_POLYGONICA_BRIDGE
#define	 EXCHANGE_POLYGONICA_BRIDGE

#include "pgapi.h"

#include "PgVisitTesselation.h"

class ExchangePolygonicaBridge
{
protected:

private:

	PTEnvironment pg_environment;

	int LoadFile(char* file_name, PgVisitTesselation* psPgVisitTesselation);
	bool TesselationToSolid(PgVisitTesselation* psPgVisitTesselation, PTSolid* pSolid);

public:
	ExchangePolygonicaBridge(PTEnvironment pg_environment);
	~ExchangePolygonicaBridge();

	int Process(char* file_name, PTSolid* pSolid);
};

#endif