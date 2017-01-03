/******
 *
 *  Contains a functio to load the data from a blender .obj using features of Assimp
 *  and then stores the data inside a struct to be used later by OpenGL.
 *
 *  Original loader source code was derived from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
 *  The loader only took into account the use of a single mesh, so I reworked it to take a struct to house the data from
 *  5 meshes, which was how I exported the data from blender. It was the way I thought I'd go in order to have multiple textures
 *  be displayed on the model.
 *
 *****/

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

#include <glm/glm.hpp>

#include "objloader.hpp"

// Include AssImp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

using namespace glm;
using namespace std;

// Struct that contains the data collected from the 5 meshes
struct objData
{
    vector<unsigned short> indices1;
    vector<vec3> vertices1;
    vector<vec2> uvs1;
    vector<vec3> normals1;
    
    vector<unsigned short> indices2;
    vector<vec3> vertices2;
    vector<vec2> uvs2;
    vector<vec3> normals2;
    
    vector<unsigned short> indices3;
    vector<vec3> vertices3;
    vector<vec2> uvs3;
    vector<vec3> normals3;
    
    vector<unsigned short> indices4;
    vector<vec3> vertices4;
    vector<vec2> uvs4;
    vector<vec3> normals4;
    
    vector<unsigned short> indices5;
    vector<vec3> vertices5;
    vector<vec2> uvs5;
    vector<vec3> normals5;
};

/***
 *  
 *  Reads an .obj and converts the file's data into an assimp scene.
 *  Meshes are created from the scene and then meshes data is loaded into 
 *  a struct that contains vectors to house the data each mesh contains.
 *
 ***/
bool loadAssimp(const char * path, struct objData *data)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0); /*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/
    printf("Loading OBJ file %s...\n", path);
	if( !scene) {
        fprintf( stderr, importer.GetErrorString());
		getchar();
		return false;
	}
    
    // Intialize meshes
	const aiMesh* mesh1 = scene->mMeshes[0]; // Mesh1
    
	const aiMesh* mesh2 = scene->mMeshes[1]; // Mesh2
    
	const aiMesh* mesh3 = scene->mMeshes[2]; // Mesh3
    
	const aiMesh* mesh4 = scene->mMeshes[3]; // Mesh4

	const aiMesh* mesh5 = scene->mMeshes[4];
    
    aiVector3D pos, UVW, n;
    
//-----------------------------------------------------------
    

	// Fill vertices, uvs, and normals from mesh1
	data->vertices1.reserve(mesh1->mNumVertices);
	data->uvs1.reserve(mesh1->mNumVertices);
	data->normals1.reserve(mesh1->mNumVertices);
	for(unsigned int i=0; i<mesh1->mNumVertices; i++){
		pos = mesh1->mVertices[i];
		data->vertices1.push_back(vec3(pos.x, pos.y, pos.z));
        UVW = mesh1->mTextureCoords[0][i];
        data->uvs1.push_back(vec2(UVW.x, UVW.y));
        n = mesh1->mNormals[i];
        data->normals1.push_back(vec3(n.x, n.y, n.z));
	}
    
    // Fill vertices, uvs, and normals from mesh2
    data->vertices2.reserve(mesh2->mNumVertices);
    data->uvs2.reserve(mesh2->mNumVertices);
    data->normals2.reserve(mesh2->mNumVertices);
    for(unsigned int i=0; i<mesh2->mNumVertices; i++){
        pos = mesh2->mVertices[i];
        data->vertices2.push_back(vec3(pos.x, pos.y, pos.z));
        UVW = mesh2->mTextureCoords[0][i];
        data->uvs2.push_back(vec2(UVW.x, UVW.y));
        n = mesh2->mNormals[i];
        data->normals2.push_back(vec3(n.x, n.y, n.z));
    }

    // Fill vertices, uvs, and normals from mesh3
    data->vertices3.reserve(mesh3->mNumVertices);
    data->uvs3.reserve(mesh3->mNumVertices);
    data->normals3.reserve(mesh3->mNumVertices);
    for(unsigned int i=0; i<mesh3->mNumVertices; i++){
        pos = mesh3->mVertices[i];
        data->vertices3.push_back(vec3(pos.x, pos.y, pos.z));
        UVW = mesh3->mTextureCoords[0][i];
        data->uvs3.push_back(vec2(UVW.x, UVW.y));
        n = mesh3->mNormals[i];
        data->normals3.push_back(vec3(n.x, n.y, n.z));
    }
    
    // Fill vertices, uvs, and normals from mesh4
    data->vertices4.reserve(mesh4->mNumVertices);
    data->uvs4.reserve(mesh4->mNumVertices);
    data->normals4.reserve(mesh4->mNumVertices);
    for(unsigned int i=0; i<mesh4->mNumVertices; i++){
        pos = mesh4->mVertices[i];
        data->vertices4.push_back(vec3(pos.x, pos.y, pos.z));
        UVW = mesh4->mTextureCoords[0][i];
        data->uvs4.push_back(vec2(UVW.x, UVW.y));
        n = mesh4->mNormals[i];
        data->normals4.push_back(vec3(n.x, n.y, n.z));
    }
    
    // Fill vertices positions from mesh5
    data->vertices5.reserve(mesh5->mNumVertices);
    data->uvs5.reserve(mesh5->mNumVertices);
    data->normals5.reserve(mesh5->mNumVertices);
    for(unsigned int i=0; i<mesh5->mNumVertices; i++){
        pos = mesh5->mVertices[i];
        data->vertices5.push_back(vec3(pos.x, pos.y, pos.z));
        UVW = mesh5->mTextureCoords[0][i];
        data->uvs5.push_back(vec2(UVW.x, UVW.y));
        n = mesh5->mNormals[i];
        data->normals5.push_back(vec3(n.x, n.y, n.z));
    }
//-----------------------------------------------------------
    
	// Fill face indices from mesh1
	data->indices1.reserve(3*mesh1->mNumFaces);
	for (unsigned int i=0; i<mesh1->mNumFaces; i++){
		// Assume the model has only triangles.
		data->indices1.push_back(mesh1->mFaces[i].mIndices[0]);
		data->indices1.push_back(mesh1->mFaces[i].mIndices[1]);
		data->indices1.push_back(mesh1->mFaces[i].mIndices[2]);
	}
    
    // Fill face indices from mesh2
    data->indices2.reserve(3*mesh2->mNumFaces);
    for (unsigned int i=0; i<mesh2->mNumFaces; i++){
        // Assume the model has only triangles.
        data->indices2.push_back(mesh2->mFaces[i].mIndices[0]);
        data->indices2.push_back(mesh2->mFaces[i].mIndices[1]);
        data->indices2.push_back(mesh2->mFaces[i].mIndices[2]);
    }

    // Fill face indices from mesh3
    data->indices3.reserve(3*mesh3->mNumFaces);
    for (unsigned int i=0; i<mesh3->mNumFaces; i++){
        // Assume the model has only triangles.
        data->indices3.push_back(mesh3->mFaces[i].mIndices[0]);
        data->indices3.push_back(mesh3->mFaces[i].mIndices[1]);
        data->indices3.push_back(mesh3->mFaces[i].mIndices[2]);
    }
    
    // Fill face indices from mesh4
    data->indices4.reserve(3*mesh4->mNumFaces);
    for (unsigned int i=0; i<mesh4->mNumFaces; i++){
        // Assume the model has only triangles.
        data->indices4.push_back(mesh4->mFaces[i].mIndices[0]);
        data->indices4.push_back(mesh4->mFaces[i].mIndices[1]);
        data->indices4.push_back(mesh4->mFaces[i].mIndices[2]);
    }
    
    // Fill face indices from mesh5
    data->indices5.reserve(3*mesh5->mNumFaces);
    for (unsigned int i=0; i<mesh5->mNumFaces; i++){
        // Assume the model has only triangles.
        data->indices5.push_back(mesh5->mFaces[i].mIndices[0]);
        data->indices5.push_back(mesh5->mFaces[i].mIndices[1]);
        data->indices5.push_back(mesh5->mFaces[i].mIndices[2]);
    }
//-----------------------------------------------------------
    return true;
};
