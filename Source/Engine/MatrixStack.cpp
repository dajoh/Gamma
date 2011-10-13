#include "MatrixStack.h"

namespace Gamma
{
	namespace Engine
	{
		MatrixStack::MatrixStack() : m_matrix(MatrixType_Model)
		{
			m_matrices[MatrixType_Model].push(Math::Matrix4(1.0f));
			m_matrices[MatrixType_View].push(Math::Matrix4(1.0f));
			m_matrices[MatrixType_Projection].push(Math::Matrix4(1.0f));
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
			Math::Matrix4 top = m_matrices[m_matrix].top();
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
			return m_matrices[m_matrix].top() == Math::Matrix4(1.0f);
		}

		void MatrixStack::makeIdentityMatrix()
		{
			m_matrices[m_matrix].top() = Math::Matrix4(1.0f);
		}

		void MatrixStack::makePerspectiveMatrix(float fov, float width, float height, float zNear, float zFar)
		{
			m_matrices[m_matrix].top() = Math::makePerspectiveMatrix(fov, width, height, zNear, zFar);
		}

		void MatrixStack::makeOrthogonalMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
		{
			m_matrices[m_matrix].top() = Math::makeOrthogonalMatrix(left, right, bottom, top, zNear, zFar);
		}

		void MatrixStack::makeLookAtMatrix(const Math::Vector3 &eye, const Math::Vector3 &center, const Math::Vector3 &up)
		{
			m_matrices[m_matrix].top() = Math::makeLookAtMatrix(eye, center, up);
		}

		void MatrixStack::translateMatrix(const Math::Vector3 &vector)
		{
			m_matrices[m_matrix].top() = Math::translateMatrix(m_matrices[m_matrix].top(), vector);
		}

		void MatrixStack::rotateMatrix(float angle, const Math::Vector3 &vector)
		{
			m_matrices[m_matrix].top() = Math::rotateMatrix(m_matrices[m_matrix].top(), angle, vector);
		}

		void MatrixStack::scaleMatrix(const Math::Vector3 &vector)
		{
			m_matrices[m_matrix].top() = Math::scaleMatrix(m_matrices[m_matrix].top(), vector);
		}

		const Math::Matrix4 &MatrixStack::getModelMatrix()
		{
			m_modelMatrix = m_matrices[MatrixType_Model].top();
			return m_modelMatrix;
		}

		const Math::Matrix4 &MatrixStack::getViewMatrix()
		{
			m_viewMatrix = m_matrices[MatrixType_View].top();
			return m_viewMatrix;
		}

		const Math::Matrix4 &MatrixStack::getProjectionMatrix()
		{
			m_projectionMatrix = m_matrices[MatrixType_Projection].top();
			return m_projectionMatrix;
		}

		const Math::Matrix3 &MatrixStack::getNormalMatrix()
		{
			m_normalMatrix = Math::transposeMatrix(Math::invertMatrix(Math::Matrix3(m_matrices[MatrixType_Model].top())));
			return m_normalMatrix;
		}
	}
}