#include <cstdio>
#include <cstdlib>
#include <Gamma/Utilities/Debug.h>
#include "Shader.h"

namespace Gamma
{
	namespace Renderer
	{
		Shader::Shader() : m_loaded(false)
		{
			m_program = glCreateProgram();
			m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
			m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		}

		Shader::~Shader()
		{
			if(m_loaded)
			{
				unload();
			}

			glDeleteShader(m_fragmentShader);
			glDeleteShader(m_vertexShader);
			glDeleteProgram(m_program);
		}

		bool Shader::load(const char *vertexShader, const char *fragmentShader)
		{
			if(m_loaded)
			{
				return false;
			}

			// Load vertex shader source.
			char *vertexSource = readShaderSource(vertexShader);
			if(!vertexSource)
			{
				return false;
			}

			// Load fragment shader source.
			char *fragmentSource = readShaderSource(fragmentShader);
			if(!fragmentSource)
			{
				freeShaderSource(vertexSource);
				return false;
			}

			// Compile shaders.
			glShaderSource(m_vertexShader, 1, (const GLchar **)&vertexSource, NULL);
			glShaderSource(m_fragmentShader, 1, (const GLchar **)&fragmentSource, NULL);
			glCompileShader(m_vertexShader);
			glCompileShader(m_fragmentShader);
			freeShaderSource(fragmentSource);
			freeShaderSource(vertexSource);

			// Check for compile errors.
			int vertexStatus, fragmentStatus;
			glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &vertexStatus);
			glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);

			if(!vertexStatus)
			{
				Utilities::printDebugString("[Gamma::Renderer::Shader] Couldn't compile %s:\n", vertexShader);
				printShaderLog(m_vertexShader);
				return false;
			}

			if(!fragmentStatus)
			{
				Utilities::printDebugString("[Gamma::Renderer::Shader] Couldn't compile %s:\n", fragmentShader);
				printShaderLog(m_fragmentShader);
				return false;
			}

			// Attach shaders and link program.
			glAttachShader(m_program, m_vertexShader);
			glAttachShader(m_program, m_fragmentShader);

			// Check for link errors.
			int linkStatus;
			glLinkProgram(m_program);
			glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);

			if(!linkStatus)
			{
				Utilities::printDebugString("[Gamma::Renderer::Shader] Couldn't link %s and %s:\n", vertexShader, fragmentShader);
				printProgramLog(m_program);
				glDetachShader(m_program, m_fragmentShader);
				glDetachShader(m_program, m_vertexShader);
				return false;
			}

			m_loaded = true;
			return true;
		}

		void Shader::unload()
		{
			if(!m_loaded)
			{
				return;
			}

			glDetachShader(m_program, m_fragmentShader);
			glDetachShader(m_program, m_vertexShader);
			m_locationCache.clear();

			m_loaded = false;
		}

		bool Shader::isLoaded() const
		{
			return m_loaded;
		}

		void Shader::setUniformInt(const char *name, int value)
		{
			if(!m_loaded)
			{
				return;
			}

			GLint location = getUniformLocation(name);
			if(location != -1)
			{
				glUniform1i(location, value);
			}
		}

		void Shader::setUniformFloat(const char *name, float value)
		{
			if(!m_loaded)
			{
				return;
			}

			GLint location = getUniformLocation(name);
			if(location != -1)
			{
				glUniform1f(location, value);
			}
		}

		void Shader::setUniformVector3(const char *name, const Math::Vector3 &value)
		{
			if(!m_loaded)
			{
				return;
			}

			GLint location = getUniformLocation(name);
			if(location != -1)
			{
				glUniform3fv(location, 1, &value[0]);
			}
		}

		void Shader::setUniformVector4(const char *name, const Math::Vector4 &value)
		{
			if(!m_loaded)
			{
				return;
			}

			GLint location = getUniformLocation(name);
			if(location != -1)
			{
				glUniform4fv(location, 1, &value[0]);
			}
		}

		void Shader::setUniformMatrix3(const char *name, const Math::Matrix3 &value)
		{
			if(!m_loaded)
			{
				return;
			}

			GLint location = getUniformLocation(name);
			if(location != -1)
			{
				glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
			}
		}

		void Shader::setUniformMatrix4(const char *name, const Math::Matrix4 &value)
		{
			if(!m_loaded)
			{
				return;
			}

			GLint location = getUniformLocation(name);
			if(location != -1)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
			}
		}

		void Shader::setUniformIntArray(const char *name, unsigned int count, const int *value)
		{
			if(!m_loaded)
			{
				return;
			}

			GLint location = getUniformLocation(name);
			if(location != -1)
			{
				glUniform1iv(location, count, value);
			}
		}

		void Shader::setUniformFloatArray(const char *name, unsigned int count, const float *value)
		{
			if(!m_loaded)
			{
				return;
			}

			GLint location = getUniformLocation(name);
			if(location != -1)
			{
				glUniform1fv(location, count, value);
			}
		}

		void Shader::bind()
		{
			if(!m_loaded)
			{
				return;
			}

			glUseProgram(m_program);
		}

		void Shader::unbind()
		{
			if(!m_loaded)
			{
				return;
			}

			glUseProgram(0);
		}

		char *Shader::readShaderSource(const char *fileName)
		{
			FILE *file = fopen(fileName, "rb");
			if(!file)
			{
				Utilities::printDebugString("[Gamma::Renderer::Shader] Couldn't open %s.\n", fileName);
				return NULL;
			}

			fseek(file, 0, SEEK_END);
			long size = ftell(file);
			fseek(file, 0, SEEK_SET);

			char *buffer = (char *)malloc(size + 1);
			fread(buffer, 1, size, file);
			fclose(file);

			buffer[size] = '\0';
			return buffer;
		}

		void Shader::freeShaderSource(char *shaderSource)
		{
			free(shaderSource);
		}

		void Shader::printShaderLog(GLuint shader)
		{
			int logLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

			char *buffer = (char *)malloc(logLength);
			glGetShaderInfoLog(shader, logLength, NULL, buffer);

			Utilities::printDebugString("%s\n", buffer);
			free(buffer);
		}

		void Shader::printProgramLog(GLuint program)
		{
			int logLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

			char *buffer = (char *)malloc(logLength);
			glGetProgramInfoLog(program, logLength, NULL, buffer);

			Utilities::printDebugString("%s\n", buffer);
			free(buffer);
		}

		GLint Shader::getUniformLocation(const char *name)
		{
			if(m_locationCache.count(name))
			{
				return m_locationCache[name];
			}

			GLint location = glGetUniformLocation(m_program, name);
			m_locationCache[name] = location;
			return location;
		}
	}
}