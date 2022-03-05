#pragma once

#include <vector>
#include "olcPixelGameEngine.h"
#include "Vector3D.h"
#include "Triangle.h"
#include "ProjectionMatrix.h"
#include "Sun.h"
#include "Camera.h"
#include "Planet.h"
#include "MarsShuttle.h"

class SandboxEngine : public olc::PixelGameEngine
{
public:
	SandboxEngine(unsigned int simSecsPerRealSec, double granularity);

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

private:
	unsigned int m_simSecsPerRealSec;
	double m_granularity;

	Vector3D m_lookDirection;
	ProjectionMatrix m_projectionMatrix;

	Sun m_sun;
	Camera m_camera;
	MarsShuttle m_marsShuttle;

	// Might make this its own class for clarity
	std::vector<Planet> m_solarSystem;

	std::vector<Vector3D> m_shuttlePath;

	size_t ClipAgainstPlane(const Vector3D& planePoint, Vector3D planeNormal, const Triangle& inputTriangle, Triangle &outTri1, Triangle &outTri2) const;
	void UpdateCameraFromInput(float fElapsedTime);
};