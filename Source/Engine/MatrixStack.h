#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <stack>
#include <Gamma/Engine/IMatrixStack.h>

namespace Gamma
{
	namespace Engine
	{
		class MatrixStack : public IMatrixStack
		{
		public:
			MatrixStack();
			~MatrixStack();

			void setActiveMatrix(MatrixType_t matrix);
			MatrixType_t getActiveMatrix() const;

			void pushMatrix();
			void popMatrix();
			bool isMatrixIdentity() const;

			void makeIdentityMatrix();
			void makePerspectiveMatrix(float fov, float width, float height, float zNear, float zFar);
			void makeOrthogonalMatrix(float left, float right, float bottom, float top, float zNear, float zFar);
			void makeLookAtMatrix(const Math::Vector3 &eye, const Math::Vector3 &center, const Math::Vector3 &up);

			void translateMatrix(const Math::Vector3 &vector);
			void rotateMatrix(float angle, const Math::Vector3 &vector);
			void scaleMatrix(const Math::Vector3 &vector);

			const Math::Matrix4 &getModelMatrix();
			const Math::Matrix4 &getViewMatrix();
			const Math::Matrix4 &getProjectionMatrix();
			const Math::Matrix3 &getNormalMatrix();
		private:
			MatrixType_t m_matrix;
			std::stack<Math::Matrix4> m_matrices[MatrixType_Projection + 1];

			Math::Matrix4 m_modelMatrix;
			Math::Matrix4 m_viewMatrix;
			Math::Matrix4 m_projectionMatrix;
			Math::Matrix3 m_normalMatrix;
		};
	}
}

#endif