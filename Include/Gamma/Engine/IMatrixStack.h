#ifndef GAMMA_ENGINE_IMATRIXSTACK_H
#define GAMMA_ENGINE_IMATRIXSTACK_H

#include <glm/glm.hpp>

namespace Gamma
{
	namespace Engine
	{
		typedef enum
		{
			MatrixStackMatrix_Model,
			MatrixStackMatrix_View,
			MatrixStackMatrix_Projection
		} MatrixStackMatrix_t;

		class IMatrixStack
		{
		public:
			virtual void setMatrix(MatrixStackMatrix_t matrix) = 0;
			virtual MatrixStackMatrix_t getMatrix() const = 0;

			virtual void pushMatrix() = 0;
			virtual void popMatrix() = 0;

			virtual void makeMatrixIdentity() = 0;
			virtual bool isMatrixIdentity() const = 0;

			virtual void makePerspectiveMatrix(float fov, float width, float height, float near, float far) = 0;
			virtual void makeOrthogonalMatrix(float left, float right, float bottom, float top, float near, float far) = 0;

			virtual void translateMatrix(float x, float y, float z) = 0;
			virtual void rotateMatrix(float angle, float x, float y, float z) = 0;
			virtual void scaleMatrix(float x, float y, float z) = 0;

			virtual const glm::mat4 &getModelMatrix() = 0;
			virtual const glm::mat4 &getViewMatrix() = 0;
			virtual const glm::mat4 &getProjectionMatrix() = 0;
		};
	}
}

#endif