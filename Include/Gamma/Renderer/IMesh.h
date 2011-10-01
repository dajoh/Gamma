#ifndef GAMMA_RENDERER_IMESH_H
#define GAMMA_RENDERER_IMESH_H

namespace Gamma
{
	namespace Renderer
	{
		typedef enum
		{
			MeshDataUsage_Static,
			MeshDataUsage_Stream,
			MeshDataUsage_Dynamic,
		} MeshDataUsage_t;

		typedef enum
		{
			MeshPrimitive_Points,
			MeshPrimitive_Lines,
			MeshPrimitive_LineStrip,
			MeshPrimitive_Triangles,
			MeshPrimitive_TriangleStrip,
			MeshPrimitive_Quads,
		} MeshPrimitive_t;

		typedef struct
		{
			float position[3];
			float texCoord[2];
			float normal[3];
			float color[3];
		} MeshVertex_t;

		typedef unsigned int MeshIndex_t;

		class IMesh
		{
		public:
			virtual void fillVertices(const MeshVertex_t *vertices, unsigned int vertexCount, MeshDataUsage_t dataUsage) = 0;
			virtual void fillIndices(const MeshIndex_t *indices, unsigned int indexCount, MeshDataUsage_t dataUsage) = 0;

			virtual bool hasVertices() const = 0;
			virtual bool hasIndices() const = 0;

			virtual void drawVertices(MeshPrimitive_t primitive, unsigned int vertexCount) = 0;
			virtual void drawIndices(MeshPrimitive_t primitive, unsigned int indexCount) = 0;

			virtual void drawVerticesInstanced(MeshPrimitive_t primitive, unsigned int vertexCount, unsigned int instances) = 0;
			virtual void drawIndicesInstanced(MeshPrimitive_t primitive, unsigned int indexCount, unsigned int instances) = 0;
		};
	}
}

#endif