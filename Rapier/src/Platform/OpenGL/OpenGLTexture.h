#pragma once

#include "Assets/Texture/Texture.h"

namespace Rapier {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual uint32_t GetRendererId() const override { return m_RendererId; };

		virtual uint32_t GetAssetManagerId() const override { return m_AssetManagerId; }
		virtual void SetAssetManagerId(uint32_t id) override { m_AssetManagerId = id; }

		virtual void Bind(uint32_t slot = 0) const override;
		
	private:
		uint32_t m_Width, m_Height;
		uint32_t m_RendererId;
		
		uint32_t m_AssetManagerId;
		uint32_t m_Slot;
	};
}
