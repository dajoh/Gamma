#ifndef GAMMA_RENDERER_ISHADER_H
#define GAMMA_RENDERER_ISHADER_H

#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix3.h"
#include "../Math/Matrix4.h"

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
			virtual void setUniformVector3(const char *name, const Math::Vector3 &value) = 0;
			virtual void setUniformVector4(const char *name, const Math::Vector4 &value) = 0;
			virtual void setUniformMatrix3(const char *name, const Math::Matrix3 &value) = 0;
			virtual void setUniformMatrix4(const char *name, const Math::Matrix4 &value) = 0;
			virtual void setUniformIntArray(const char *name, unsigned int count, const int *value) = 0;
			virtual void setUniformFloatArray(const char *name, unsigned int count, const float *value) = 0;
			virtual void setFragmentLocation(const char *name, int fragmentIndex) = 0;

			virtual void bind() = 0;
			virtual void unbind() = 0;
		};
	}
}

#endif