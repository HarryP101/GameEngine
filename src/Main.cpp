#include "SandboxEngine.h"
#include "Constants.h"

int main(int argc, const char* argv[])
{
	unsigned int simSecsPerRealSec = 0.1 * Constants::SECONDS_IN_A_WEEK * std::stod(argv[1]);

	double granularity = std::stod(argv[2]);

	SandboxEngine demo(simSecsPerRealSec, granularity);

	if (demo.Construct(200, 200, 4, 4))
	{
		demo.Start();
	}
}
