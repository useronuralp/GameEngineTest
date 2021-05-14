#include "pch.h"
#include "model.h"
namespace AnorEngine {
	namespace Graphics {

		void Model::Draw(const Ref<Shader> shader , const Ref<PerspectiveCamera> camera)
		{
			for (unsigned int i = 0; i < meshes.size(); i++)
				meshes[i].Draw(shader, camera);
		}
		void Model::loadModel(std::string path)
		{
			Assimp::Importer import;
			const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{	
				CRITICAL("ERROR::ASSIMP:: {0}", import.GetErrorString());
				//std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
				return;
			}
			directory = path.substr(0, path.find_last_of("\\/"));
			INFO("Directory name: {0}", directory);
			//std::cout << "Directory name: "<< directory << std::endl;
			processNode(scene->mRootNode, scene);
		}
		void Model::processNode(aiNode* node, const aiScene* scene)
		{
			// process all the node's meshes (if any)
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(processMesh(mesh, scene));
			}
			// then do the same for each of its children
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				//spdlog::info("Loaded part: {0}", node->mChildren[i]->mName.C_Str());
				//std::cout << node->mChildren[i]->mName.C_Str() << std::endl;
				processNode(node->mChildren[i], scene);
			}
		}
		Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<TextureInfo> textures;

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				// process vertex positions, normals and texture coordinates
				glm::vec3 vector;
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.Position = vector;

				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;

				if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					glm::vec2 vec;
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.TexCoords = vec;
				}
				else
					vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		
				vertices.push_back(vertex);

			}
			// process indices
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}
			// process material
			if (mesh->mMaterialIndex >= 0)
			{
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				std::vector<TextureInfo> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
				std::vector<TextureInfo> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			}

			return Mesh(vertices, indices, textures);
		}
		std::vector<TextureInfo> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
		{
			std::vector<TextureInfo> textures;
			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				bool skip = false;
				for (unsigned int j = 0; j < textures_loaded.size(); j++)
				{
					if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
					{
						textures.push_back(textures_loaded[j]);
						skip = true;
						break;
					}
				}
				if (!skip)
				{   // if texture hasn't been loaded already, load it
					TextureInfo texture;
					texture.id = TextureFromFile(str.C_Str(), directory);
					texture.type = typeName;
					texture.path = str.C_Str();
					textures.push_back(texture);
					textures_loaded.push_back(texture); // add to loaded textures
				}
			}
			return textures;
		}

		unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
		{
			std::string filename = std::string(path);
			filename = directory + '\\' + filename;
			unsigned int textureID;

			glGenTextures(1, &textureID);

			int width, height, nrComponents;

			//stbi_set_flip_vertically_on_load(1); //remove hard coding here later.

			unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
			if (data)
			{
				GLenum format = 0;
				if (nrComponents == 1)
					format = GL_RED;
				else if (nrComponents == 3)
					format = GL_RGB;
				else if (nrComponents == 4)
					format = GL_RGBA;

				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_image_free(data);
				INFO("Textures succesfuly loaded from path: {0}", path);
				//std::cout << "LOAD SUCCSESFUL FROM: " << path << std::endl;
			}
			else
			{
				CRITICAL("Textures failed to load from path: {0}", path);
				//std::cout << "Texture failed to load at path: " << path << std::endl;
				stbi_image_free(data);
			}
			return textureID;
		}
		void Model::rotate(const float& degree, const float& x, const float& y, const float& z)
		{
			for (int i = 0; i < meshes.size(); i++)
			{
				meshes[i].getModelMatrix() = glm::rotate(meshes[i].getModelMatrix(), glm::radians(degree), glm::vec3(x, y, z));
			}
		}
		void Model::translate(const float& x, const float& y, const float& z)
		{
			for (int i = 0; i < meshes.size(); i++)
			{
				meshes[i].getModelMatrix() = glm::translate(meshes[i].getModelMatrix(), glm::vec3(x, y, z));
			}
		}
		void Model::scale(const float& x, const float& y, const float& z)
		{
			for (int i = 0; i < meshes.size(); i++)
			{
				meshes[i].getModelMatrix() = glm::scale(meshes[i].getModelMatrix(), glm::vec3(x, y, z));
			}
		}
	}
}
