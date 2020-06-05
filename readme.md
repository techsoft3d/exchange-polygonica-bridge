# HOOPS Exchange to Polygonica Bridge

This set of classes loads a CAD file using HOOPS Exchange and maps triangles to a Polygonica
Solid.

# Prerequisits

1. HOOPS Exchange
1. Polygonica

Please goto techsoft3d.com and request an evaluation of these SKDs

# Usage

	#include "ExchangePolygonicaBridge.h"

	// Assume Polygonica is initialized

	ExchangePolygonicaBridge bridge(pg_environment);
	
	PTSolid solid = NULL;
	int ret = bridge.Process(filename, &solid);

