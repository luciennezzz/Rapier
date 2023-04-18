#include "ipch.h"
#include "Renderer.h"
#include "Camera/Camera.h"
#include "Assets/Shader/Shader.h"

namespace Rapier {

	std::unique_ptr<Renderer> Renderer::s_Renderer = nullptr;

	void Renderer::Create() {
		RAPIER_CORE_ASSERT(!s_Renderer, "Renderer already exists!");

		Renderer::s_Renderer.reset(new Renderer());
	}

	void Renderer::BeginScene(const OrthographicCamera& camera) {
		s_Renderer->m_SceneData.reset(new SceneData(camera));
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_Renderer->m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


	Renderer::Renderer()
		:m_StartedScene(false) {}

}