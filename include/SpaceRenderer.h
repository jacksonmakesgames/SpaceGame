#pragma once
#include <Watty/graphics/renderer2d.h>
#include <Watty/graphics/buffers/indexbuffer.h>
#include <Watty/graphics/renderable2d.h>

#define RENDERER_MAX_SPRITES		60000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE		RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_TID_INDEX		2
#define SHADER_COLOR_INDEX		3


using namespace letc;
using namespace graphics;

class SpaceRenderer : public Renderer2D
{
public:
	SpaceRenderer(std::vector<bool>& starsRef, glm::vec2 windowSize);
	~SpaceRenderer();

private:
	std::vector<bool>& m_starsRef;

	float screenX, screenY;

	GLuint m_vertexArray;
	GLuint m_vertexBuffer;
	IndexBuffer* m_indexBuffer;
	GLsizei m_indexCount;
	VertexData* m_currentBuffer;
	std::vector<float> m_glTIDsThisFlush;
	unsigned int m_textureArrayID;
	std::vector<const Texture*> m_textures;

	void begin() override;
	void submit(const Renderable2D* renderable) override;
	void submit(glm::vec3* vertices, int vertexCount, unsigned int color);
	void end() override;
	void flush() override;
	void flush(unsigned int mode, int indexCount);
	//void drawString(const std::string& text, const glm::vec3& position, const Font& font, unsigned int color) override;

private:
	void init();

private:
	
};
