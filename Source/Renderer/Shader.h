#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <string>
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
			void setUniformVector3(const char *name, const Math::Vector3 &value);
			void setUniformVector4(const char *name, const Math::Vector4 &value);
			void setUniformMatrix3(const char *name, const Math::Matrix3 &value);
			void setUniformMatrix4(const char *name, const Math::Matrix4 &value);
			void setUniformIntArray(const char *name, unsigned int count, const int *value);
			void setUniformFloatArray(const char *name, unsigned int count, const float *value);

			void bind();
			void unbind();
		private:
			static char *readShaderSource(const char *fileName);
			static void freeShaderSource(char *shaderSource);
			static void printShaderLog(GLuint shader);
			static void printProgramLog(GLuint program);
			GLint getUniformLocation(const char *name);

			bool m_loaded;
			GLuint m_program;
			GLuint m_vertexShader;
			GLuint m_fragmentShader;
			std::map<std::string, GLint> m_locationCache;
		};
	}
}

#endif