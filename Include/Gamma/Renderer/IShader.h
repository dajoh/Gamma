#ifndef GAMMA_RENDERER_ISHADER_H
#define GAMMA_RENDERER_ISHADER_H

#include <glm/glm.hpp>

namespace Gamma
{
	namespace Renderer
	{
		class IShader
		{
		public:
			virtual bool load(const char *vertexShader, const char *fragmentShader) = 0;
			virtual void unload() = 0;
			virtual bool isLoaded() const = 0;

			virtual void setUniformInt(const char *name, int value) = 0;
			virtual void setUniformFloat(const char *name, float value) = 0;
			virtual void setUniformVector2(const char *name, const glm::vec2 &value) = 0;
			virtual void setUniformVector3(const char *name, const glm::vec3 &value) = 0;
			virtual void setUniformMatrix3(const char *name, const glm::mat3 &value) = 0;
			virtual void setUniformMatrix4(const char *name, const glm::mat4 &value) = 0;
			virtual void setUniformIntArray(const char *name, unsigned int count, const int *value) = 0;
			virtual void setUniformFloatArray(const char *name, unsigned int count, const float *value) = 0;
			virtual void setFragmentLocation(const char *name, int fragmentIndex) = 0;

			virtual void bind() = 0;
			virtual void unbind() = 0;
		};
	}
}

#endif