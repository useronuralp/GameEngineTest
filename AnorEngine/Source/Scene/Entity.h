#pragma once
#include "Scene.h"
#include "entt.h"
#include <glm.hpp>
#include "Components.h"
namespace AnorEngine
{
	class ANOR_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
	public:
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>()){	CRITICAL_ASSERT("Components you tried to add does already exist!");}
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}
		template<typename T>
		T& GetComponent()
		{
			if (!HasComponent<T>()){CRITICAL_ASSERT("Components you tried to get does not exist!");}
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}
		template<typename T> 
		bool HasComponent()
		{
			if (m_Scene->m_Registry.try_get<T>(m_EntityHandle) == nullptr)
				return false;
			else
				return true;
		}
		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>()) { CRITICAL_ASSERT("Component you tried to remove does not exist!"); }
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}
		operator bool() { return m_EntityHandle != entt::null; }
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}