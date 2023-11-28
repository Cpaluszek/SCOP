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
#define SMOOTH_SHADING_KEYWORD "s"
#define OBJ_NAME_KEYWORD "o"
#define GROUP_NAME_KEYWORD "g"
#define LINE_KEYWORD "l"
#define TEXT_COORDS_KEYWORD "vt"
#define VERTEX_NORMALS_KEYWORD "vn"
#define PARAM_SPACE_VERTICES_KEYWORD "vn"
#define MAT_FILE_KEYWORD "mtllib"
#define MAT_NAME_KEYWORD "usemtl"

enum Face_Format {
    VERTEX,
    VERTEX_TEXTURE,
    VERTEX_TEXTURE_NORMAL,
    VERTEX_NORMAL
};

class ObjParser {
 public:
     ObjParser();
     ~ObjParser();
     void parseObjFile(const std::string& inputFile);
     bool useSmoothShading = false;
     VertexVector finalVertices;
     Material material;

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

    Face_Format faceFormat = VERTEX;

    void parseLine(VecString& tokens, const std::string& line);

    void parseVertex(VecString& tokens);
    void parseVertexNormal(VecString& tokens);
    void parseVertexTextureCoords(VecString& tokens);

    void parseFace(const VecString& tokens);

    void computeFaces();
    void handleQuadToTriangle();

    void parseSmoothShading(const VecString& tokens);
    void determineFaceFormat(const VecString& tokens);
    void checkMaterialFileArgument(const VecString& tokens);
    inline Vec3f getRandomColor();
};

#endif  // INC_OBJPARSER_H_
