#include <glm/gtc/matrix_transform.hpp>
#include "MatrixStack.h"

namespace Gamma
{
	namespace Engine
	{
		MatrixStack::MatrixStack() : m_matrix(MatrixStackMatrix_Model)
		{
			m_matrices[0].push(glm::mat4(1.0f));
			m_matrices[1].push(glm::mat4(1.0f));
			m_matrices[2].push(glm::mat4(1.0f));
		}

		MatrixStack::~MatrixStack()
		{

		}

		void MatrixStack::setMatrix(MatrixStackMatrix_t matrix)
		{
			if(matrix >= MatrixStackMatrix_Model && matrix <= MatrixStackMatrix_Projection)
			{
				m_matrix = matrix;
			}
		}

		MatrixStackMatrix_t MatrixStack::getMatrix() const
		{
			return m_matrix;
		}

		void MatrixStack::pushMatrix()
		{
			glm::mat4 top = m_matrices[m_matrix].top();
			m_matrices[m_matrix].push(top);
		}

		void MatrixStack::popMatrix()
		{
			if(m_matrices[m_matrix].size() > 1)
			{
				m_matrices[m_matrix].pop();
			}
		}

		void MatrixStack::makeMatrixIdentity()
		{
			m_matrices[m_matrix].top() = glm::mat4(1.0f);
		}

		bool MatrixStack::isMatrixIdentity() const
		{
			return m_matrices[m_matrix].top() == glm::mat4(1.0f);
		}

		void MatrixStack::makePerspectiveMatrix(float fov, float width, float height, float near, float far)
		{
			m_matrices[m_matrix].top() = glm::perspectiveFov(fov, width, height, near, far);
		}

		void MatrixStack::makeOrthogonalMatrix(float left, float right, float bottom, float top, float near, float far)
		{
			m_matrices[m_matrix].top() = glm::ortho(left, right, bottom, top, near, far);
		}

		void MatrixStack::translateMatrix(float x, float y, float z)
		{
			m_matrices[m_matrix].top() = glm::translate(m_matrices[m_matrix].top(), glm::vec3(x, y, z));
		}

		void MatrixStack::rotateMatrix(float angle, float x, float y, float z)
		{
			m_matrices[m_matrix].top() = glm::rotate(m_matrices[m_matrix].top(), angle, glm::vec3(x, y, z));
		}

		void MatrixStack::scaleMatrix(float x, float y, float z)
		{
			m_matrices[m_matrix].top() = glm::scale(m_matrices[m_matrix].top(), glm::vec3(x, y, z));
		}

		const glm::mat4 &MatrixStack::makeFinalMatrix()
		{
			m_mvpMatrix = m_matrices[2].top() * m_matrices[1].top() * m_matrices[0].top();
			return m_mvpMatrix;
		}
	}
}