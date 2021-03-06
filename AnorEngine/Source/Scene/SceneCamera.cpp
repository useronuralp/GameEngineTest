#include "pch.h"
#include "SceneCamera.h"
namespace AnorEngine
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjectionMatrix();
	}
	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;

		RecalculateProjectionMatrix();
	}
	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjectionMatrix();
	}
	void SceneCamera::RecalculateProjectionMatrix()
	{
		float orthoLeft = -m_OrthographicSize * 0.5f * m_AspectRatio;
		float orthoRight = m_OrthographicSize * 0.5f * m_AspectRatio;
		float orthoTop = m_OrthographicSize * 0.5f;
		float orthoBottom = -m_OrthographicSize * 0.5f;

		m_ProjectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
	}
}