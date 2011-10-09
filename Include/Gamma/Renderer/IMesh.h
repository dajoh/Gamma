#ifndef GAMMA_RENDERER_IMESH_H
#define GAMMA_RENDERER_IMESH_H

namespace Gamma
{
	namespace Renderer
	{
		typedef enum
		{
			Primitive_Points,
			Primitive_Lines,
			Primitive_LineStrip,
			Primitive_Triangles,
			Primitive_TriangleStrip,
			Primitive_Quads
		} Primitive_t;

		typedef enum
		{
			MeshDataType_None,
			MeshDataType_Int8,
			MeshDataType_Int16,
			MeshDataType_Int32,
			MeshDataType_Uint8,
			MeshDataType_Uint16,
			MeshDataType_Uint32,
			MeshDataType_Float,
			MeshDataType_Vector2,
			MeshDataType_Vector3,
			MeshDataType_Vector4
		} MeshDataType_t;

		typedef enum
		{
			MeshDataUsage_Static,
			MeshDataUsage_Stream,
			MeshDataUsage_Dynamic
		} MeshDataUsage_t;

		typedef enum
		{
			MeshDataAccess_Read = 0x01,
			MeshDataAccess_Write = 0x02
		} MeshDataAccess_t;

		typedef struct
		{
			MeshDataType_t dataType;
		} MeshAttribute_t;

		class IMesh
		{
		public:
			virtual bool fillVertexBuffer(const void *data, unsigned int size, MeshAttribute_t *attributes, MeshDataUsage_t dataUsage) = 0;
			virtual bool fillIndexBuffer(const void *data, unsigned int size, MeshDataType_t dataType, MeshDataUsage_t dataUsage) = 0;
			virtual bool fillVertexBufferArea(const void *data, unsigned int offset, unsigned int size) = 0;
			virtual bool fillIndexBufferArea(const void *data, unsigned int offset, unsigned int size) = 0;

			virtual void *mapVertexBufferArea(unsigned int offset, unsigned int size, MeshDataAccess_t dataAccess) = 0;
			virtual void *mapIndexBufferArea(unsigned int offset, unsigned int size, MeshDataAccess_t dataAccess) = 0;
			virtual void unmapVertexBuffer() = 0;
			virtual void unmapIndexBuffer() = 0;

			virtual bool hasVertices() const = 0;
			virtual bool hasIndices() const = 0;

			virtual void drawVertices(Primitive_t primitive, unsigned int vertexCount) const = 0;
			virtual void drawIndices(Primitive_t primitive, unsigned int indexCount) const = 0;
			virtual void drawVerticesInstanced(Primitive_t primitive, unsigned int vertexCount, unsigned int instances) const = 0;
			virtual void drawIndicesInstanced(Primitive_t primitive, unsigned int indexCount, unsigned int instances) const = 0;
		};
	}
}

#endif