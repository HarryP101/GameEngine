#pragma once

#include "olcPixelGameEngine.h"
#include "Matrix4x4.h"
#include "RotationMatrix4x4.h"
#include "Vector3D.h"
#include "ProjectionMatrix.h"
#include "Sun.h"
#include "Camera.h"
#include "Planet.h"

class SandboxEngine : public olc::PixelGameEngine
{
public:
	SandboxEngine();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

private:
	Vector3D m_lookDirection;
	ProjectionMatrix m_projectionMatrix;
	RotationMatrix4x4 m_rotateX;
	RotationMatrix4x4 m_rotateZ;
	RotationMatrix4x4 m_spinMat;

	Sun m_sun;
	Camera m_camera;

	// Might make this its own class for clarity
	std::vector<Planet> m_solarSystem;

	double m_spin;

	size_t ClipAgainstPlane(const Vector3D& planePoint, Vector3D planeNormal, const Triangle& inputTriangle, Triangle &outTri1, Triangle &outTri2) const;
	void UpdateCameraFromInput(float fElapsedTime);
};