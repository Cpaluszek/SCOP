#ifndef INC_OBJPARSER_H_
#define INC_OBJPARSER_H_

#include <filesystem>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include "math.h"
#include "Material.h"
#include "MtlParser.h"
#include "settings.h"
#include "utils.h"
#include "Vertex.h"

#define COMMENT_KEYWORD "#"
#define VERTEX_KEYWORD "v"
#define FACE_KEYWORD "f"
#define TEXT_COORDS_KEYWORD "vt"
#define VERTEX_NORMALS_KEYWORD "vn"
#define PARAM_SPACE_VERTICES_KEYWORD "vn"
#define MAT_FILE_KEYWORD "mtllib"

class ObjParser {
 public:
     VertexVector finalVertices;
     Vertex_Format vertexFormat = VERTEX;
     Material material;

     ObjParser();
     ~ObjParser();

     void parseObjFile(const std::string& inputFile);

 private:
    std::ifstream objFile;
    std::string parentPath;
    std::string materialFile;

    std::vector<Vec3f> normals;
    std::vector<Vec3f> textureCoords;
    VertexVector parsedVertices;

    // Faces
    std::vector<std::vector<int>> faces;
    std::vector<std::vector<int>> textureIndices;
    std::vector<std::vector<int>> normalIndices;

    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;


    void parseLine(VecString& tokens, const std::string& line);

    void parseVertex(VecString& tokens);
    void parseVertexNormal(VecString& tokens);
    void parseVertexTextureCoords(VecString& tokens);
    void parseFace(const VecString& tokens);
    void determineFaceFormat(const VecString& tokens);
    void checkMaterialFileArgument(const VecString& tokens);

    inline Vec3f getRandomColor();
    void computeFaces();
    void handleQuadToTriangle();
    
    // void parseSmoothShading(const VecString& tokens);
};

#endif  // INC_OBJPARSER_H_
