#include "ipch.h"


#include "Application.h"
#include "Input.h"

#include "Renderer/Renderer.h"

#include "FileSystem/FileSystem.h"
#include "Assets/AssetManager.h"


namespace Rapier {

	Application* Application::s_Instance = nullptr;

	Application::Application() {

		RAPIER_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;



		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Create();
		Renderer2D::Create();
		AssetManager::Init();

		m_CameraController = std::make_shared<OrthographicCameraController>();

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

	}	



	Application::~Application() {

	}


	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		m_CameraController->OnEvent(e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::OnUpdate(DeltaTime dt) {
		RAPIER_CORE_ASSERT(false, "OnUpdate() hasn't been set!");
	}

	void Application::PostUpdate() {
		RAPIER_CORE_ASSERT(false, "PostUpdate() hasn't been set!");
	}

	void Application::Run() {

		while (m_Running) {
			DeltaTime dt = DeltaTime(m_PrevTime);
			m_PrevTime = std::chrono::high_resolution_clock::now();
			//RAPIER_CORE_INFO("time : {0} seconds, {1} fps", dt, 1 / dt);
			m_CameraController->OnUpdate(dt);

			OnUpdate(dt);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(dt);
			}

			m_ImGuiLayer->Begin();
			{

				for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();
				}
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

			PostUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}
