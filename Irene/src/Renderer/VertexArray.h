#pragma once
#include "ipch.h"

#include "Renderer/Buffer.h"


namespace IRENE {
	class VertexArray {

	public:
		virtual ~VertexArray() {}

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexArray* Create();
	};

}