#include <cstddef>
#include "Mesh.h"

namespace Gamma
{
	namespace Renderer
	{
		static inline GLenum getPrimitive(Primitive_t primitive)
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

		static inline GLint getDataTypeComponents(MeshDataType_t dataType)
		{
			switch(dataType)
			{
			case MeshDataType_Int8:
				return 1;
			case MeshDataType_Int16:
				return 1;
			case MeshDataType_Int32:
				return 1;
			case MeshDataType_Uint8:
				return 1;
			case MeshDataType_Uint16:
				return 1;
			case MeshDataType_Uint32:
				return 1;
			case MeshDataType_Float:
				return 1;
			case MeshDataType_Vector2:
				return 2;
			case MeshDataType_Vector3:
				return 3;
			case MeshDataType_Vector4:
				return 4;
			default:
				return 0;
			}
		}

		static inline GLenum getDataType(MeshDataType_t dataType)
		{
			switch(dataType)
			{
			case MeshDataType_Int8:
				return GL_BYTE;
			case MeshDataType_Int16:
				return GL_SHORT;
			case MeshDataType_Int32:
				return GL_INT;
			case MeshDataType_Uint8:
				return GL_UNSIGNED_BYTE;
			case MeshDataType_Uint16:
				return GL_UNSIGNED_SHORT;
			case MeshDataType_Uint32:
				return GL_UNSIGNED_INT;
			case MeshDataType_Float:
				return GL_FLOAT;
			case MeshDataType_Vector2:
				return GL_FLOAT;
			case MeshDataType_Vector3:
				return GL_FLOAT;
			case MeshDataType_Vector4:
				return GL_FLOAT;
			default:
				return 0;
			}
		}

		static inline unsigned int getDataTypeSize(MeshDataType_t dataType)
		{
			switch(dataType)
			{
			case MeshDataType_Int8:
				return sizeof(char);
			case MeshDataType_Int16:
				return sizeof(short);
			case MeshDataType_Int32:
				return sizeof(int);
			case MeshDataType_Uint8:
				return sizeof(unsigned char);
			case MeshDataType_Uint16:
				return sizeof(unsigned short);
			case MeshDataType_Uint32:
				return sizeof(unsigned int);
			case MeshDataType_Float:
				return sizeof(float);
			case MeshDataType_Vector2:
				return sizeof(float) * 2;
			case MeshDataType_Vector3:
				return sizeof(float) * 3;
			case MeshDataType_Vector4:
				return sizeof(float) * 4;
			default:
				return 0;
			}
		}

		static inline GLenum getDataUsage(MeshDataUsage_t dataUsage)
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

		static inline GLenum getDataAccess(int dataAccess)
		{
			GLenum access = 0;

			if(dataAccess & MeshDataAccess_Read)
			{
				access |= GL_MAP_READ_BIT;
			}

			if(dataAccess & MeshDataAccess_Write)
			{
				access |= GL_MAP_WRITE_BIT;
			}

			return access;
		}

		Mesh::Mesh() : m_indexFormat(0), m_hasVertices(false), m_hasIndices(false), m_verticesMapped(false), m_indicesMapped(false), m_attributeCount(0)
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

		bool Mesh::fillVertexBuffer(const void *data, unsigned int size, MeshAttribute_t *attributes, MeshDataUsage_t dataUsage)
		{
			if(m_verticesMapped)
			{
				return false;
			}

			GLenum usage = getDataUsage(dataUsage);
			if(!usage)
			{
				return false;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);

			for(unsigned int i = 0; i < m_attributeCount; i++)
			{
				glDisableVertexAttribArray(i);
			}

			unsigned int vertexSize = 0;
			for(m_attributeCount = 0; true; m_attributeCount++)
			{
				MeshAttribute_t *attribute = &attributes[m_attributeCount];
				if(attribute->dataType == MeshDataType_None)
				{
					break;
				}

				vertexSize += getDataTypeSize(attribute->dataType);
			}

			unsigned int pointer = 0;
			for(m_attributeCount = 0; true; m_attributeCount++)
			{
				MeshAttribute_t *attribute = &attributes[m_attributeCount];
				if(attribute->dataType == MeshDataType_None)
				{
					break;
				}

				GLenum type = getDataType(attribute->dataType);
				GLint components = getDataTypeComponents(attribute->dataType);
				if(!type || !components)
				{
					break;
				}

				glEnableVertexAttribArray(m_attributeCount);
				glVertexAttribPointer(m_attributeCount, components, type, GL_FALSE, vertexSize, (const GLvoid *)pointer);
				pointer += getDataTypeSize(attribute->dataType);
			}

			m_hasVertices = true;
			return true;
		}

		bool Mesh::fillIndexBuffer(const void *data, unsigned int size, MeshDataType_t dataType, MeshDataUsage_t dataUsage)
		{
			if(m_indicesMapped)
			{
				return false;
			}

			GLenum usage = getDataUsage(dataUsage);
			if(!usage)
			{
				return false;
			}

			m_indexFormat = getDataType(dataType);
			if(!m_indexFormat)
			{
				return false;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);

			m_hasIndices = true;
			return true;
		}

		bool Mesh::fillVertexBufferArea(const void *data, unsigned int offset, unsigned int size)
		{
			if(!m_hasVertices || m_verticesMapped)
			{
				return NULL;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
			return true;
		}

		bool Mesh::fillIndexBufferArea(const void *data, unsigned int offset, unsigned int size)
		{
			if(!m_hasIndices || m_indicesMapped)
			{
				return NULL;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
			return true;
		}

		void *Mesh::mapVertexBufferArea(unsigned int offset, unsigned int size, int dataAccess)
		{
			if(!m_hasVertices || m_verticesMapped)
			{
				return NULL;
			}

			GLenum access = getDataAccess(dataAccess);
			if(!access)
			{
				return NULL;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

			GLvoid *pointer = glMapBufferRange(GL_ARRAY_BUFFER, offset, size, access);
			if(pointer)
			{
				m_verticesMapped = true;
			}

			return pointer;
		}

		void *Mesh::mapIndexBufferArea(unsigned int offset, unsigned int size, int dataAccess)
		{
			if(!m_hasIndices || m_indicesMapped)
			{
				return NULL;
			}

			GLenum access = getDataAccess(dataAccess);
			if(!access)
			{
				return NULL;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

			GLvoid *pointer = glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, offset, size, access);
			if(pointer)
			{
				m_indicesMapped = true;
			}

			return pointer;
		}

		void Mesh::unmapVertexBuffer()
		{
			if(!m_verticesMapped)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			m_verticesMapped = false;
		}

		void Mesh::unmapIndexBuffer()
		{
			if(!m_indicesMapped)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			m_indicesMapped = false;
		}

		bool Mesh::hasVertices() const
		{
			return m_hasVertices;
		}

		bool Mesh::hasIndices() const
		{
			return m_hasIndices;
		}

		void Mesh::drawVertices(Primitive_t primitive, unsigned int vertexCount) const
		{
			if(!m_hasVertices || m_verticesMapped)
			{
				return;
			}

			GLenum mode = getPrimitive(primitive);
			if(!mode)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glDrawArrays(mode, 0, vertexCount);
		}

		void Mesh::drawIndices(Primitive_t primitive, unsigned int indexCount) const
		{
			if(!m_hasVertices || !m_hasIndices || m_verticesMapped || m_indicesMapped)
			{
				return;
			}

			GLenum mode = getPrimitive(primitive);
			if(!mode)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glDrawElements(mode, indexCount, m_indexFormat, NULL);
		}

		void Mesh::drawVerticesInstanced(Primitive_t primitive, unsigned int vertexCount, unsigned int instances) const
		{
			if(!m_hasVertices || m_verticesMapped)
			{
				return;
			}

			GLenum mode = getPrimitive(primitive);
			if(!mode)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glDrawArraysInstanced(mode, 0, vertexCount, instances);
		}

		void Mesh::drawIndicesInstanced(Primitive_t primitive, unsigned int indexCount, unsigned int instances) const
		{
			if(!m_hasVertices || !m_hasIndices || m_verticesMapped || m_indicesMapped)
			{
				return;
			}

			GLenum mode = getPrimitive(primitive);
			if(!mode)
			{
				return;
			}

			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			glDrawElementsInstanced(mode, indexCount, m_indexFormat, NULL, instances);
		}
	}
}