#include "Renderer.h"

#include <iostream>

void GLClearErrors()
{
	while (glGetError() != GL_NO_ERROR)
		;
}

bool GLCheckError(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":"
			  << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	GLCallV(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	GLCallV(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
