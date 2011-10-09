#ifndef GAMMA_ENGINE_IMATRIXSTACK_H
#define GAMMA_ENGINE_IMATRIXSTACK_H

#include "../Math/Vector3.h"
#include "../Math/Matrix3.h"
#include "../Math/Matrix4.h"

namespace Gamma
{
	namespace Engine
	{
		typedef enum
		{
			MatrixType_Model,
			MatrixType_View,
			MatrixType_Projection
		} MatrixType_t;

		class IMatrixStack
		{
		public:
			virtual void setActiveMatrix(MatrixType_t matrix) = 0;
			virtual MatrixType_t getActiveMatrix() const = 0;

			virtual void pushMatrix() = 0;
			virtual void popMatrix() = 0;
			virtual bool isMatrixIdentity() const = 0;

			virtual void makeIdentityMatrix() = 0;
			virtual void makePerspectiveMatrix(float fov, float width, float height, float zNear, float zFar) = 0;
			virtual void makeOrthogonalMatrix(float left, float right, float bottom, float top, float zNear, float zFar) = 0;

			virtual void translateMatrix(const Math::Vector3 &vector) = 0;
			virtual void rotateMatrix(float angle, const Math::Vector3 &vector) = 0;
			virtual void scaleMatrix(const Math::Vector3 &vector) = 0;

			virtual const Math::Matrix4 &getModelMatrix() = 0;
			virtual const Math::Matrix4 &getViewMatrix() = 0;
			virtual const Math::Matrix4 &getProjectionMatrix() = 0;
			virtual const Math::Matrix3 &getNormalMatrix() = 0;
		};
	}
}

#endif