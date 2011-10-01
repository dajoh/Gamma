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
			Renderer::MeshVertex_t *vertices = new Renderer::MeshVertex_t[objLoader.getNumberOfVertices()];
			for(int i = 0; i < objLoader.getNumberOfVertices(); i++)
			{
				memcpy(vertices[i].position, objLoader.getVertexBuffer()[i].position, sizeof(float) * 3);
				memcpy(vertices[i].texCoord, objLoader.getVertexBuffer()[i].texCoord, sizeof(float) * 2);
				memcpy(vertices[i].normal, objLoader.getVertexBuffer()[i].normal, sizeof(float) * 3);
				memset(vertices[i].color, 0, sizeof(float) * 3);
			}

			// Get the indices.
			const Renderer::MeshIndex_t *indices = (const Renderer::MeshIndex_t *)objLoader.getIndexBuffer();

			// Create the mesh and fill in our vertices and indices.
			m_mesh = Renderer::getRenderer()->createMesh();
			m_mesh->fillVertices(vertices, objLoader.getNumberOfVertices(), Renderer::MeshDataUsage_Static);
			m_mesh->fillIndices(indices, objLoader.getNumberOfIndices(), Renderer::MeshDataUsage_Static);

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

			m_mesh->drawIndices(Renderer::MeshPrimitive_Triangles, m_indexCount);
		}

		void Model::drawInstanced(unsigned int instances)
		{
			if(!m_loaded)
			{
				return;
			}

			m_mesh->drawIndicesInstanced(Renderer::MeshPrimitive_Triangles, m_indexCount, instances);
		}
	}
}