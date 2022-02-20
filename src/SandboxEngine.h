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
	Vector3D m_lookDirection;
	Matrix4x4 m_projectionMatrix;
	RotationMatrix4x4 m_rotateX;
	RotationMatrix4x4 m_rotateZ;

	Matrix4x4 CreateLookAtMatrix(const Vector3D& pos, const Vector3D& target, const Vector3D& up) const;

	double m_theta;
};