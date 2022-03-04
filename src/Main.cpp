#include "SandboxEngine.h"
#include "Constants.h"

int main(int argc, const char* argv[])
{
	unsigned int simSecsPerRealSec = Constants::SECONDS_IN_A_WEEK * std::stoul(argv[1]);

	unsigned int granularity = std::stoul(argv[2]);

	SandboxEngine demo(simSecsPerRealSec, granularity);

	if (demo.Construct(200, 200, 4, 4))
	{
		demo.Start();
	}
}
