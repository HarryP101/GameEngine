#include "SandboxEngine.h"

int main()
{
	SandboxEngine demo;

	if (demo.Construct(400, 400, 4, 4))
	{
		demo.Start();
	}
}
