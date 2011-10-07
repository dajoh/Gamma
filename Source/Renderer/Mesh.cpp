#include <cstddef>
#include "Mesh.h"

namespace Gamma
{
	namespace Renderer
	{
		static inline GLenum getGlUsage(MeshDataUsage_t dataUsage)
		{
			switch(dataUsage)
			{
			case MeshDataUsage_Static:
				return GL_STATIC_DRAW;
			case MeshDataUsage_Stream:
				return GL_STREAM_DRAW;
			case MeshDataUsage_Dynamic:
				return GL_DYNAMIC_DRAW;
			default:
				return 0;
			}
		}

		static inline GLenum getGlMode(Primitive_t primitive)
		{
			switch(primitive)
			{
			case Primitive_Points:
				return GL_POINTS;
			case Primitive_Lines:
				return GL_LINES;
			case Primitive_LineStrip:
				return GL_LINE_STRIP;
			case Primitive_Triangles:
				return GL_TRIANGLES;
			case Primitive_TriangleStrip:
				return GL_TRIANGLE_STRIP;
			case Primitive_Quads:
				return GL_QUADS;
			default:
				return 0;
			}
		}

		Mesh::Mesh() : m_hasVertices(false), m_hasIndices(false)
		{
			glGenVertexArrays(1, &m_vertexArray);
			glGenBuffers(1, &m_vertexBuffer);
			glGenBuffers(1, &m_indexBuffer);
		}

		Mesh::~Mesh()
		{
			glDeleteBuffers(1, &m_indexBuffer);
			glDeleteBuffers(1, &m_vertexBuffer);
			glDeleteVertexArrays(1, &m_vertexArray);
		}

		void Mesh::fillVertices(const MeshVertex_t *vertices, unsigned int vertexCount, MeshDataUsage_t dataUsage)
		{
			GLenum usage = getGlUsage(dataUsage);
			if(!usage)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex_t) * vertexCount, vertices, usage);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex_t), (const GLvoid *)(0));
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex_t), (const GLvoid *)(0 + 12));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex_t), (const GLvoid *)(0 + 12 + 8));
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex_t), (const GLvoid *)(0 + 12 + 8 + 12));

			m_hasVertices = true;
		}

		void Mesh::fillIndices(const MeshIndex_t *indices, unsigned int indexCount, MeshDataUsage_t dataUsage)
		{
			GLenum usage = getGlUsage(dataUsage);
			if(!usage)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(MeshIndex_t) * indexCount, indices, usage);

			m_hasIndices = true;
		}

		bool Mesh::hasVertices() const
		{
			return m_hasVertices;
		}

		bool Mesh::hasIndices() const
		{
			return m_hasIndices;
		}

		void Mesh::drawVertices(Primitive_t primitive, unsigned int vertexCount)
		{
			if(!m_hasVertices)
			{
				return;
			}

			GLenum mode = getGlMode(primitive);
			if(!mode)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glDrawArrays(mode, 0, vertexCount);
		}

		void Mesh::drawIndices(Primitive_t primitive, unsigned int indexCount)
		{
			if(!m_hasVertices || !m_hasIndices)
			{
				return;
			}

			GLenum mode = getGlMode(primitive);
			if(!mode)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glDrawElements(mode, indexCount, GL_UNSIGNED_INT, NULL);
		}

		void Mesh::drawVerticesInstanced(Primitive_t primitive, unsigned int vertexCount, unsigned int instances)
		{
			if(!m_hasVertices)
			{
				return;
			}

			GLenum mode = getGlMode(primitive);
			if(!mode)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glDrawArraysInstanced(mode, 0, vertexCount, instances);
		}

		void Mesh::drawIndicesInstanced(Primitive_t primitive, unsigned int indexCount, unsigned int instances)
		{
			if(!m_hasVertices || !m_hasIndices)
			{
				return;
			}

			GLenum mode = getGlMode(primitive);
			if(!mode)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glDrawElementsInstanced(mode, indexCount, GL_UNSIGNED_INT, NULL, instances);
		}
	}
}