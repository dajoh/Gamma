#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <Gamma/Renderer/IMesh.h>

namespace Gamma
{
	namespace Renderer
	{
		class Mesh : public IMesh
		{
		public:
			Mesh();
			~Mesh();

			bool fillVertexBuffer(const void *data, unsigned int size, MeshAttribute_t *attributes, MeshDataUsage_t dataUsage);
			bool fillIndexBuffer(const void *data, unsigned int size, MeshDataType_t dataType, MeshDataUsage_t dataUsage);
			bool fillVertexBufferArea(const void *data, unsigned int offset, unsigned int size);
			bool fillIndexBufferArea(const void *data, unsigned int offset, unsigned int size);

			void *mapVertexBufferArea(unsigned int offset, unsigned int size, MeshDataAccess_t dataAccess);
			void *mapIndexBufferArea(unsigned int offset, unsigned int size, MeshDataAccess_t dataAccess);
			void unmapVertexBuffer();
			void unmapIndexBuffer();

			bool hasVertices() const;
			bool hasIndices() const;

			void drawVertices(Primitive_t primitive, unsigned int vertexCount) const;
			void drawIndices(Primitive_t primitive, unsigned int indexCount) const;
			void drawVerticesInstanced(Primitive_t primitive, unsigned int vertexCount, unsigned int instances) const;
			void drawIndicesInstanced(Primitive_t primitive, unsigned int indexCount, unsigned int instances) const;
		private:
			GLuint m_vertexArray;
			GLuint m_vertexBuffer;
			GLuint m_indexBuffer;
			GLenum m_indexFormat;
			bool m_hasVertices;
			bool m_hasIndices;
			bool m_verticesMapped;
			bool m_indicesMapped;
			unsigned int m_attributeCount;
		};
	}
}

#endif