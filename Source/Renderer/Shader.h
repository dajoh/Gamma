#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <Gamma/Renderer/IShader.h>

namespace Gamma
{
	namespace Renderer
	{
		class Shader : public IShader
		{
		public:
			Shader();
			~Shader();

			bool load(const char *vertexShader, const char *fragmentShader);
			void unload();
			bool isLoaded() const;

			void setUniformInt(const char *name, int value);
			void setUniformFloat(const char *name, float value);
			void setUniformVector2(const char *name, const glm::vec2 &value);
			void setUniformVector3(const char *name, const glm::vec3 &value);
			void setUniformMatrix4(const char *name, const glm::mat4 &value);
			void setUniformIntArray(const char *name, unsigned int count, const int *value);
			void setUniformFloatArray(const char *name, unsigned int count, const float *value);
			void setFragmentLocation(const char *name, int fragmentIndex);

			void bind();
			void unbind();
		private:
			static char *readShaderSource(const char *fileName);
			static void freeShaderSource(char *shaderSource);
			static void printShaderLog(GLuint shader);
			static void printProgramLog(GLuint program);

			bool m_fragmentLocationSet;
			bool m_loaded;
			GLuint m_program;
			GLuint m_vertexShader;
			GLuint m_fragmentShader;
		};
	}
}

#endif