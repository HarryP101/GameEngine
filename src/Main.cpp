#include "SandboxEngine.h"
#include "Vector3D.h"

int main()
{
	SandboxEngine demo;

	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
}
