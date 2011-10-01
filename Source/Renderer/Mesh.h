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

			void fillVertices(const MeshVertex_t *vertices, unsigned int vertexCount, MeshDataUsage_t dataUsage);
			void fillIndices(const MeshIndex_t *indices, unsigned int indexCount, MeshDataUsage_t dataUsage);

			bool hasVertices() const;
			bool hasIndices() const;

			void drawVertices(MeshPrimitive_t primitive, unsigned int vertexCount);
			void drawIndices(MeshPrimitive_t primitive, unsigned int indexCount);

			void drawVerticesInstanced(MeshPrimitive_t primitive, unsigned int vertexCount, unsigned int instances);
			void drawIndicesInstanced(MeshPrimitive_t primitive, unsigned int indexCount, unsigned int instances);
		private:
			GLuint m_vertexArray;
			GLuint m_vertexBuffer;
			GLuint m_indexBuffer;
			bool m_hasVertices;
			bool m_hasIndices;
		};
	}
}

#endif