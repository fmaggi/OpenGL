#include "OBJLoader.h"

Model* OBJLoader::LoadObj(std::string filename)
{
    std::string line;
    std::ifstream object("res/" + filename + ".obj");
    std::ifstream mtl("res/" + filename + ".mtl");
    
    if (!object.is_open())
    {
        return NULL;
    }

    Model* mod = new Model;

    // ------------------Parse .obj----------------

    std::vector<Vertex> objV;
    std::vector<Vertex> objN;
    std::vector<float*> objT;
    std::vector<unsigned int> indices;
    

    int faceCount = 0;

    std::string delim = "/";
    std::string curr_material;

    std::string word;

    while(getline(object, line))
    {
        
        std::istringstream ss(line);

        ss >> word;
        if (strcmp(word.c_str(), "v") == 0)
        {
            Vertex vex;
            int i = 0;
            while (ss >> word)
            {
                vex.data[i] = std::stof(word);
                i++;
            }

            objV.push_back(vex);
        }
        else if (strcmp(word.c_str(), "vn") == 0)
        {
            Vertex vex;
            int i = 0;
            while (ss >> word)
            {
                vex.data[i] = std::stof(word);
                i++;
            }

            objN.push_back(vex);
        }
        else if (strcmp(word.c_str(), "vt") == 0)
        {
            float data[2];
            int i = 0;
            while (ss >> word)
            {
                data[i] = std::stof(word);
                i++;
            }

            objT.push_back(data);
        }
    }
    
    object.clear();
    object.seekg(object.beg);
    std::vector<float*> finalTextures(objV.size());
    std::vector<Vertex> finalNormals(objV.size());
   
    while (!object.eof())
    {
        getline(object, line);

        std::istringstream ss(line);
        ss >> word;
        if (strcmp(word.c_str(), "o") == 0)
        {
            if (!indices.empty())
            {
                mod->storeObj(indices, curr_material);
                indices.clear();
            }
        }
        else if (strcmp(word.c_str(), "f") == 0)
        {
            while (ss >> word)
            {
                size_t pos_v = word.find(delim);
                unsigned int index = (unsigned int)std::stoi(word.substr(0, pos_v)) - 1;
                indices.push_back(index);
                word.erase(0, pos_v + 1);
                if (word[0] == '/')
                {
                    word.erase(0, 1);
                }
                else
                {
                    size_t pos_t = word.find(delim);
                    unsigned int t_index = (unsigned int) std::stoi(word.substr(0, pos_t)) -1;
                    finalTextures[index] = objT.at(t_index);
                    word.erase(0, pos_t +1);
                }
                unsigned int n_index = (unsigned int) std::stoi(word) - 1;
                finalNormals[index] = objN.at(n_index);
            }
        }
        else if (strcmp(word.c_str(), "usemtl") == 0)
        {
            ss >> word;
            curr_material = word;
        }
    }
    mod->storeObj(indices, curr_material);
    indices.clear();

    object.close();
    mod->storeData(objV);
    mod->storeData(finalNormals);
    if (objT.size() > 0)
    {
        mod->storeData(&finalTextures[0], 2, objV.size());
    }
    //-----------------------Parse .mtl------------------

    if (!mtl.is_open())
    {
        return mod;
    }

    std::string materialName = "";
    Material material;

    while (getline(mtl, line))
    {
        std::istringstream ss(line);
        ss >> word;
        if (strcmp(word.c_str(), "newmtl") == 0)
        {
            ss >> word;
            if (strcmp(materialName.c_str(), "") != 0)
            {
                mod->storeMaterial(material, materialName);
            }
            materialName = word;
        }
        else if (strcmp(word.c_str(), "Ka") == 0)
        {
            int i = 0;
            while (ss >> word)
            {
                material.ka[i] = std::stof(word);
                i++;
            }
        }
        else if (strcmp(word.c_str(), "Kd") == 0)
        {
            int i = 0;
            while (ss >> word)
            {
                material.kd[i] = std::stof(word);
                i++;
            }
        }
        else if (strcmp(word.c_str(), "Ks") == 0)
        {
            int i = 0;
            while (ss >> word)
            {
                material.ks[i] = std::stof(word);
                i++;
            }
        }
        else if (strcmp(word.c_str(), "Ke") == 0)
        {
            int i = 0;
            while (ss >> word)
            {
                material.ke[i] = std::stof(word);
                i++;
            }
        }
        else if (strcmp(word.c_str(), "Ns") == 0)
        {
            ss >> word;
            material.ns = std::stof(word);
        }
        else if (strcmp(word.c_str(), "Ni") == 0)
        {
            ss >> word;
            material.ni = std::stof(word);
        }
        else if (strcmp(word.c_str(), "d") == 0)
        {
            ss >> word;
            material.d = std::stof(word);
        }
        else if (strcmp(word.c_str(), "illum") == 0)
        {
            ss >> word;
            material.illum = std::stof(word);
        }
    }

    mod->storeMaterial(material, materialName);

    return mod;
}
