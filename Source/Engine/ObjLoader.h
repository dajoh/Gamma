//-----------------------------------------------------------------------------
// Copyright (c) 2007 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <cstdio>
#include <map>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------
// Alias|Wavefront OBJ file loader.
//
// This OBJ file loader contains the following restrictions:
// 1. Group information is ignored. Faces are grouped based on the material
//    that each face uses.
// 2. Object information is ignored. This loader will merge everything into a
//    single object.
// 3. The MTL file must be located in the same directory as the OBJ file. If
//    it isn't then the MTL file will fail to load and a default material is
//    used instead.
// 4. This loader triangulates all polygonal faces during importing.
//-----------------------------------------------------------------------------

class ObjLoader
{
public:
    struct Material
    {
        float ambient[4];
        float diffuse[4];
        float specular[4];
        float shininess;        // [0 = min shininess, 1 = max shininess]
        float alpha;            // [0 = fully transparent, 1 = fully opaque]

        std::string name;
        std::string colorMapFilename;
        std::string bumpMapFilename;
    };

    struct Vertex
    {
        float position[3];
        float texCoord[2];
        float normal[3];
        float tangent[4];
        float bitangent[3];
    };

    struct Mesh
    {
        int startIndex;
        int triangleCount;
        const Material *pMaterial;
    };

    ObjLoader();
    ~ObjLoader();

    void destroy();
    bool import(const char *pszFilename, bool rebuildNormals = false);
    void normalize(float scaleTo = 1.0f, bool center = true);
    void reverseWinding();

    // Getter methods.

    void getCenter(float &x, float &y, float &z) const;
    float getWidth() const;
    float getHeight() const;
    float getLength() const;
    float getRadius() const;

    const int *getIndexBuffer() const;
    int getIndexSize() const;

    const Material &getMaterial(int i) const;
    const Mesh &getMesh(int i) const;

    int getNumberOfIndices() const;
    int getNumberOfMaterials() const;
    int getNumberOfMeshes() const;
    int getNumberOfTriangles() const;
    int getNumberOfVertices() const;

    const std::string &getPath() const;

    const Vertex &getVertex(int i) const;
    const Vertex *getVertexBuffer() const;
    int getVertexSize() const;

    bool hasNormals() const;
    bool hasPositions() const;
    bool hasTangents() const;
    bool hasTextureCoords() const;

private:
    void addTrianglePos(int index, int material,
        int v0, int v1, int v2);
    void addTrianglePosNormal(int index, int material,
        int v0, int v1, int v2,
        int vn0, int vn1, int vn2);
    void addTrianglePosTexCoord(int index, int material,
        int v0, int v1, int v2,
        int vt0, int vt1, int vt2);
    void addTrianglePosTexCoordNormal(int index, int material,
        int v0, int v1, int v2,
        int vt0, int vt1, int vt2,
        int vn0, int vn1, int vn2);
    int addVertex(int hash, const Vertex *pVertex);
    void bounds(float center[3], float &width, float &height,
        float &length, float &radius) const;
    void buildMeshes();
    void generateNormals();
    void generateTangents();
    void importGeometryFirstPass(FILE *pFile);
    void importGeometrySecondPass(FILE *pFile);
    bool importMaterials(const char *pszFilename);
    void scale(float scaleFactor, float offset[3]);

    bool m_hasPositions;
    bool m_hasTextureCoords;
    bool m_hasNormals;
    bool m_hasTangents;

    int m_numberOfVertexCoords;
    int m_numberOfTextureCoords;
    int m_numberOfNormals;
    int m_numberOfTriangles;
    int m_numberOfMaterials;
    int m_numberOfMeshes;

    float m_center[3];
    float m_width;
    float m_height;
    float m_length;
    float m_radius;

    std::string m_directoryPath;

    std::vector<Mesh> m_meshes;
    std::vector<Material> m_materials;
    std::vector<Vertex> m_vertexBuffer;
    std::vector<int> m_indexBuffer;
    std::vector<int> m_attributeBuffer;
    std::vector<float> m_vertexCoords;
    std::vector<float> m_textureCoords;
    std::vector<float> m_normals;

    std::map<std::string, int> m_materialCache;
    std::map<int, std::vector<int> > m_vertexCache;
};

//-----------------------------------------------------------------------------

inline void ObjLoader::getCenter(float &x, float &y, float &z) const
{ x = m_center[0]; y = m_center[1]; z = m_center[2]; }

inline float ObjLoader::getWidth() const
{ return m_width; }

inline float ObjLoader::getHeight() const
{ return m_height; }

inline float ObjLoader::getLength() const
{ return m_length; }

inline float ObjLoader::getRadius() const
{ return m_radius; }

inline const int *ObjLoader::getIndexBuffer() const
{ return &m_indexBuffer[0]; }

inline int ObjLoader::getIndexSize() const
{ return static_cast<int>(sizeof(int)); }

inline const ObjLoader::Material &ObjLoader::getMaterial(int i) const
{ return m_materials[i]; }

inline const ObjLoader::Mesh &ObjLoader::getMesh(int i) const
{ return m_meshes[i]; }

inline int ObjLoader::getNumberOfIndices() const
{ return m_numberOfTriangles * 3; }

inline int ObjLoader::getNumberOfMaterials() const
{ return m_numberOfMaterials; }

inline int ObjLoader::getNumberOfMeshes() const
{ return m_numberOfMeshes; }

inline int ObjLoader::getNumberOfTriangles() const
{ return m_numberOfTriangles; }

inline int ObjLoader::getNumberOfVertices() const
{ return static_cast<int>(m_vertexBuffer.size()); }

inline const std::string &ObjLoader::getPath() const
{ return m_directoryPath; }

inline const ObjLoader::Vertex &ObjLoader::getVertex(int i) const
{ return m_vertexBuffer[i]; }

inline const ObjLoader::Vertex *ObjLoader::getVertexBuffer() const
{ return &m_vertexBuffer[0]; }

inline int ObjLoader::getVertexSize() const
{ return static_cast<int>(sizeof(Vertex)); }

inline bool ObjLoader::hasNormals() const
{ return m_hasNormals; }

inline bool ObjLoader::hasPositions() const
{ return m_hasPositions; }

inline bool ObjLoader::hasTangents() const
{ return m_hasTangents; }

inline bool ObjLoader::hasTextureCoords() const
{ return m_hasTextureCoords; }

#endif
