#pragma once

#include "olcPixelGameEngine.h"
#include "Mesh.h"
#include "Matrix4x4.h"
#include "RotationMatrix4x4.h"
#include "Vector3D.h"

class SandboxEngine : public olc::PixelGameEngine
{
public:
	SandboxEngine();

	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

private:
	Mesh m_meshCube;
	Vector3D m_camera;
	Matrix4x4 m_projectionMatrix;
	RotationMatrix4x4 m_rotateX;
	RotationMatrix4x4 m_rotateZ;

	double m_theta;
};