#include "pch.h"
#include "OrthographicCameraController.h"
namespace AnorEngine {
	namespace Graphics
	{
		OrthographicCameraController::OrthographicCameraController(Ref<OrthographicCamera> camera, float aspectRatio)
			:m_Camera(camera), m_AspectRatio(aspectRatio)
		{
		}
		void OrthographicCameraController::OnUpdate(float deltaTime)
		{
			m_CameraTranslationSpeed = m_ZoomLevel; //liner curve to smooth out the translation a little bit
			if (Input::EventHandler::IsKeyDown(ANOR_KEY_W))
			{
				m_CameraPos.y += m_CameraTranslationSpeed * deltaTime;
			}
			else if (Input::EventHandler::IsKeyDown(ANOR_KEY_S))
			{
				m_CameraPos.y -= m_CameraTranslationSpeed * deltaTime;
			}
			if (Input::EventHandler::IsKeyDown(ANOR_KEY_A))
			{
				m_CameraPos.x -= m_CameraTranslationSpeed * deltaTime;
			}
			else if (Input::EventHandler::IsKeyDown(ANOR_KEY_D))
			{
				m_CameraPos.x += m_CameraTranslationSpeed * deltaTime;
			}

			m_Camera->SetPosition(m_CameraPos);
		}
		void OrthographicCameraController::OnEvent(Ref<Input::Event> e)
		{
			if (e->GetEventType() == Input::EventType::WindowResizeEvent)
			{
				OnResizeEvent(std::static_pointer_cast<Input::WindowResizeEvent>(e));
			}
			else if (e->GetEventType() == Input::EventType::MouseScrollEvent)
			{
				OnMouseScrollEvent(std::static_pointer_cast<Input::MouseScrollEvent>(e));
			}
		}
		bool OrthographicCameraController::OnResizeEvent(Ref<Input::WindowResizeEvent> e)
		{	
			m_AspectRatio = (float)e->GetWidth() / (float)e->GetHeight();
			m_Camera->SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			return false;
		}
		bool OrthographicCameraController::OnMouseScrollEvent(Ref<Input::MouseScrollEvent> e)
		{
			m_ZoomLevel -= e->GetYOffset() * 0.15f;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
			m_Camera->SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			return false;
		}
	}
}