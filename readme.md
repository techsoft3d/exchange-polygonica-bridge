# HOOPS Exchange to Polygonica Bridge

This set of classes loads a CAD file using HOOPS Exchange and maps triangles to a Polygonica
Solid.

# Prerequisits

1. HOOPS Exchange
1. Polygonica

Please goto pages.techsoft3d.com/evalute and request an evaluation of these SKDs

# Building
## Windows
Polygonica only supports up to vc140 build tools be used with the Windows SDK 8.1. It is possible to use VS2017 and VS2019 by setting these targets in your project settings. Polygonica supports older VC versions, but who uses those anymore?

## Linux
It should be possible to build using Linux versions of HOOPS Exchange and Polygonica

# Usage

	#include "ExchangePolygonicaBridge.h"

	// Assume Polygonica is initialized

	ExchangePolygonicaBridge bridge(pg_environment);
	
	PTSolid solid = NULL;
	int ret = bridge.Process(filename, &solid);

# Navigating the Codebase
```
.
├── src/ - (Bridge code)
|
└── samples/ - (Sample projects using the bridge)
    └── simple/ - (Shows how to load a part and save to STL)
```

# Todo
1. Add support for assemblies that create multiple PTSolid objects
