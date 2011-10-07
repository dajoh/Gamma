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
			void makePerspectiveMatrix(float fov, float width, float height, float near, float far);
			void makeOrthogonalMatrix(float left, float right, float bottom, float top, float near, float far);

			void translateMatrix(float x, float y, float z);
			void rotateMatrix(float angle, float x, float y, float z);
			void scaleMatrix(float x, float y, float z);

			const glm::mat4 &getModelMatrix();
			const glm::mat4 &getViewMatrix();
			const glm::mat4 &getProjectionMatrix();
			const glm::mat3 &getNormalMatrix();
		private:
			MatrixType_t m_matrix;
			std::stack<glm::mat4> m_matrices[MatrixType_Projection + 1];
			glm::mat4 m_modelMatrix;
			glm::mat4 m_viewMatrix;
			glm::mat4 m_projectionMatrix;
			glm::mat3 m_normalMatrix;
		};
	}
}

#endif