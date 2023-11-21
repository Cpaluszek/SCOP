#ifndef INC_OBJPARSER_H_
#define INC_OBJPARSER_H_

#include <string>
#include <fstream>
#include <random>
#include <vector>
#include "./Mesh.h"
#include "./math.h"
#include "./utils.h"

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

typedef std::vector<std::string> VecString;


class ObjParser {
 public:
     ObjParser();
     void parseObjFile(std::ifstream& file);
     bool useSmoothShading = false;
     VertexVector finalVertices;

 private:
    std::vector<Vec3f> normals;
    std::vector<Vec3f> textureCoords;
    VertexVector parsedVertices;

    std::mt19937 gen;
    std::uniform_real_distribution<float> dis;

    Face_Format faceFormat = VERTEX;

    void parseVertex(
            const std::vector<std::string>& lineSplit,
            const std::string& line);
    void parseVertexNormal(
            const std::vector<std::string>& lineSplit,
            const std::string& line);
    void parseVertexTextureCoords(
            const std::vector<std::string>& lineSplit,
            const std::string& line);
    void parseFace(
            const Vec3f& faceColor,
            const std::vector<std::string>& lineSplit,
            const std::string& line);
    void parseFaceTexture(
            const Vec3f& faceColor,
            const std::vector<std::string>& lineSplit,
            const std::string& line);
    void parseFaceTextureNormal(
            const Vec3f& faceColor,
            const std::vector<std::string>& lineSplit,
            const std::string& line);
    void parseFaceNormal(
            const Vec3f& faceColor,
            const std::vector<std::string>& lineSplit,
            const std::string& line);
    void parseSmoothShading(const VecString& lineSplit);
    void determineFaceFormat(const std::vector<std::string>& lineSplit);
    inline Vec3f getRandomColor();
};

#endif  // INC_OBJPARSER_H_
