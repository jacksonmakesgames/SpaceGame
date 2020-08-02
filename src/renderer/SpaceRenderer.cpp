#include "SpaceRenderer.h"

SpaceRenderer::SpaceRenderer(std::vector<bool>& starsRef, glm::vec2 windowSize):m_starsRef(starsRef), screenX(windowSize.x), screenY(windowSize.y)
{
	init();
}

SpaceRenderer::~SpaceRenderer()
{
	delete m_indexBuffer;
	glDeleteBuffers(1, &m_vertexBuffer);
}

void SpaceRenderer::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // bind vertex buffer
	m_currentBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY); // map the buffer and get the pointer to the first vertex
}

void SpaceRenderer::submit(const Renderable2D* renderable)
{
	//return;
	int i = 0;
	for (int x = 0; x < screenX; x++)
	{
		for (int y = 0; y < screenY; y++) {
			if (m_starsRef[x*y]) {
				//if (i > 2000) { end(); flush(); begin(); i = 0; }
				if (i > 20000) {return; }

				m_currentBuffer->vertex = *m_tranformationStackBack * glm::vec4(x,y,1,1);
				m_currentBuffer->uv = glm::vec2();
				m_currentBuffer->tid = 0;
				m_currentBuffer->color = 0xFFFFFFFF;
				m_currentBuffer++;

				i++;

			}
		}
	}

}

void SpaceRenderer::submit(glm::vec3* vertices, int vertexCount, unsigned int color)
{

	
}

void SpaceRenderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void SpaceRenderer::flush()
{
	
	unsigned int mode = GL_POINTS;

	//flush
	glBindVertexArray(m_vertexArray);
	m_indexBuffer->bind();
	glDrawElements(mode, m_indexCount/6, GL_UNSIGNED_SHORT, NULL);
	m_indexBuffer->unbind();
	glBindVertexArray(NULL);
}

void SpaceRenderer::flush(unsigned int mode, int indexCount)
{

}


void SpaceRenderer::init()
{

	// Generate
	glGenVertexArrays(1, &m_vertexArray);
	glGenBuffers(1, &m_vertexBuffer);
	//Bind
	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	//Enable attribs
	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glEnableVertexAttribArray(SHADER_TID_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	//Assign
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
	glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, NULL);


	//Indices
	int indexOffset = 0;
	GLushort indices[RENDERER_INDICES_SIZE];

	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
		indices[i + 0] = indexOffset + 0;
		indices[i + 1] = indexOffset + 1;
		indices[i + 2] = indexOffset + 2;

		indices[i + 3] = indexOffset + 2;
		indices[i + 4] = indexOffset + 3;
		indices[i + 5] = indexOffset + 0;

		indexOffset += 4;
	}

	m_indexBuffer = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

	m_indexCount = 0;

	//Unbind array
	glBindVertexArray(NULL);
}
