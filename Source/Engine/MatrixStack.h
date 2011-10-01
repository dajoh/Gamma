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

			void setMatrix(MatrixStackMatrix_t matrix);
			MatrixStackMatrix_t getMatrix() const;

			void pushMatrix();
			void popMatrix();

			void makeMatrixIdentity();
			bool isMatrixIdentity() const;

			void makePerspectiveMatrix(float fov, float width, float height, float near, float far);
			void makeOrthogonalMatrix(float left, float right, float bottom, float top, float near, float far);

			void translateMatrix(float x, float y, float z);
			void rotateMatrix(float angle, float x, float y, float z);
			void scaleMatrix(float x, float y, float z);

			const glm::mat4 &makeFinalMatrix();
		private:
			MatrixStackMatrix_t m_matrix;
			std::stack<glm::mat4> m_matrices[3];
			glm::mat4 m_mvpMatrix;
		};
	}
}

#endif