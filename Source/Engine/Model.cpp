#include <cstring>
#include <Gamma/Utilities/Debug.h>
#include <Gamma/Renderer/IRenderer.h>
#include "ObjLoader.h"
#include "Model.h"

namespace Gamma
{
	namespace Engine
	{
		Model::Model() : m_loaded(false)
		{

		}

		Model::~Model()
		{
			if(m_loaded)
			{
				unload();
			}
		}

		bool Model::load(const char *fileName)
		{
			if(m_loaded)
			{
				return false;
			}

			// Load up the model.
			ObjLoader objLoader;
			if(!objLoader.import(fileName, true))
			{
				Utilities::printDebugString("[Gamma::Engine::Model] Couldn't load %s.\n", fileName);
				return false;
			}

			// Convert the vertices.
			ModelVertex_t *vertices = new ModelVertex_t[objLoader.getNumberOfVertices()];
			for(int i = 0; i < objLoader.getNumberOfVertices(); i++)
			{
				memcpy(vertices[i].position, objLoader.getVertexBuffer()[i].position, sizeof(float) * 3);
				memcpy(vertices[i].texCoord, objLoader.getVertexBuffer()[i].texCoord, sizeof(float) * 2);
				memcpy(vertices[i].normal, objLoader.getVertexBuffer()[i].normal, sizeof(float) * 3);
			}

			// Set up the mesh attributes.
			Renderer::MeshAttribute_t attributes[4] =
			{
				{Renderer::MeshDataType_Vector3},
				{Renderer::MeshDataType_Vector2},
				{Renderer::MeshDataType_Vector3},
				{Renderer::MeshDataType_None}
			};

			// Create the mesh and fill in our vertices and indices.
			m_mesh = Renderer::getRenderer()->createMesh();
			m_mesh->fillVertexBuffer(vertices, sizeof(ModelVertex_t) * objLoader.getNumberOfVertices(), attributes, Renderer::MeshDataUsage_Static);
			m_mesh->fillIndexBuffer(objLoader.getIndexBuffer(), sizeof(int) * objLoader.getNumberOfIndices(), Renderer::MeshDataType_Uint32, Renderer::MeshDataUsage_Static);

			// Save the index count, we need this to draw the model.
			m_indexCount = objLoader.getNumberOfIndices();

			// Clean up.
			delete vertices;
			objLoader.destroy();

			m_loaded = true;
			return true;
		}

		void Model::unload()
		{
			if(!m_loaded)
			{
				return;
			}

			Renderer::getRenderer()->destroyMesh(m_mesh);

			m_loaded = false;
		}

		bool Model::isLoaded() const
		{
			return m_loaded;
		}

		void Model::draw()
		{
			if(!m_loaded)
			{
				return;
			}

			m_mesh->drawIndices(Renderer::Primitive_Triangles, m_indexCount);
		}

		void Model::drawInstanced(unsigned int instances)
		{
			if(!m_loaded)
			{
				return;
			}

			m_mesh->drawIndicesInstanced(Renderer::Primitive_Triangles, m_indexCount, instances);
		}
	}
}