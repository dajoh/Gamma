#ifndef MODEL_H
#define MODEL_H

#include <Gamma/Renderer/IMesh.h>
#include <Gamma/Engine/IModel.h>

namespace Gamma
{
	namespace Engine
	{
		class Model : public IModel
		{
		public:
			Model();
			~Model();

			bool load(const char *fileName);
			void unload();
			bool isLoaded() const;

			void draw();
			void drawInstanced(unsigned int instances);
		private:
			bool m_loaded;
			unsigned int m_indexCount;
			Renderer::IMesh *m_mesh;
		};
	}
}

#endif