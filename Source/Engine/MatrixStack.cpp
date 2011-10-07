#include <glm/gtc/matrix_transform.hpp>
#include "MatrixStack.h"

namespace Gamma
{
	namespace Engine
	{
		MatrixStack::MatrixStack() : m_matrix(MatrixType_Model)
		{
			m_matrices[MatrixType_Model].push(glm::mat4(1.0f));
			m_matrices[MatrixType_View].push(glm::mat4(1.0f));
			m_matrices[MatrixType_Projection].push(glm::mat4(1.0f));
		}

		MatrixStack::~MatrixStack()
		{

		}

		void MatrixStack::setActiveMatrix(MatrixType_t matrix)
		{
			if(matrix >= MatrixType_Model && matrix <= MatrixType_Projection)
			{
				m_matrix = matrix;
			}
		}

		MatrixType_t MatrixStack::getActiveMatrix() const
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

		bool MatrixStack::isMatrixIdentity() const
		{
			return m_matrices[m_matrix].top() == glm::mat4(1.0f);
		}

		void MatrixStack::makeIdentityMatrix()
		{
			m_matrices[m_matrix].top() = glm::mat4(1.0f);
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

		const glm::mat4 &MatrixStack::getModelMatrix()
		{
			m_modelMatrix = m_matrices[MatrixType_Model].top();
			return m_modelMatrix;
		}

		const glm::mat4 &MatrixStack::getViewMatrix()
		{
			m_viewMatrix = m_matrices[MatrixType_View].top();
			return m_viewMatrix;
		}

		const glm::mat4 &MatrixStack::getProjectionMatrix()
		{
			m_projectionMatrix = m_matrices[MatrixType_Projection].top();
			return m_projectionMatrix;
		}

		const glm::mat3 &MatrixStack::getNormalMatrix()
		{
			m_normalMatrix = glm::transpose(glm::inverse(glm::mat3(m_matrices[MatrixType_View].top() * m_matrices[MatrixType_Model].top())));
			return m_normalMatrix;
		}
	}
}