#include "SandboxEngine.h"

int main()
{
	SandboxEngine demo;

	if (demo.Construct(200, 200, 4, 4))
	{
		demo.Start();
	}
}
