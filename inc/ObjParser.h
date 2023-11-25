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

// Todo: create a parsing header with utils
// parseFloat, parseInt, parseFloatVector

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

    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;

    Face_Format faceFormat = VERTEX;

    void parseLine(const VecString& tokens, const std::string& line);
    void parseVertex(const VecString& tokens, const std::string& line);
    void parseVertexNormal(const VecString& tokens, const std::string& line);
    void parseVertexTextureCoords(const VecString& tokens, const std::string& line);

    void parseFace(const Vec3f& color, const VecString& tokens, const std::string& line);
    void parseFaceTexture(const Vec3f& color, const VecString& tokens, const std::string& line);
    void parseFaceTextureNormal(const Vec3f& color, const VecString& tokens, const std::string& line);
    void parseFaceNormal(const Vec3f& color, const VecString& tokens, const std::string& line);

    void handleQuadToTriangle();

    void parseSmoothShading(const VecString& tokens);
    void determineFaceFormat(const VecString& tokens);
    void checkMaterialFileArgument(const VecString& tokens);
    inline Vec3f getRandomColor();
};

#endif  // INC_OBJPARSER_H_
