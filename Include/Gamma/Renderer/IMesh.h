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
			MeshDataUsage_Dynamic
		} MeshDataUsage_t;

		typedef enum
		{
			Primitive_Points,
			Primitive_Lines,
			Primitive_LineStrip,
			Primitive_Triangles,
			Primitive_TriangleStrip,
			Primitive_Quads
		} Primitive_t;

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

			virtual void drawVertices(Primitive_t primitive, unsigned int vertexCount) = 0;
			virtual void drawIndices(Primitive_t primitive, unsigned int indexCount) = 0;

			virtual void drawVerticesInstanced(Primitive_t primitive, unsigned int vertexCount, unsigned int instances) = 0;
			virtual void drawIndicesInstanced(Primitive_t primitive, unsigned int indexCount, unsigned int instances) = 0;
		};
	}
}

#endif