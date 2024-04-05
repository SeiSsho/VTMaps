#ifndef VTMAPS_SHADER_H
#define VTMAPS_SHADER_H

#include <glm/glm.hpp>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <GLES3/gl3ext.h>
#include <jni.h>

#include <string>
#include <unordered_map>
#include <vector>
#include <array>

#endif //VTMAPS_SHADER_H

class Shader {
    friend class Material;
    friend class Sphere;
private:
    static const int MAX_SIZE_PARAM_NAME = 256;
    GLint _id;
    std::unordered_map<std::string, GLint> _uniformLocation;

public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    const GLint& GetId() const { return _id; }

    static std::shared_ptr<Shader> CreateDefaultShader();
    static std::shared_ptr<Shader> CreatePhongShader();

    void Bind();
    void Unbind();

    void SetIntArray(const std::string& name, const std::vector<int>& array);
    void SetIntArray(const std::string& name, int* value, unsigned int count);
    void SetInt(const std::string& name, int value);
    void SetInt2(const std::string& name, const glm::ivec2& value);
    void SetInt2(const std::string& name, int x, int y);
    void SetInt3(const std::string& name, const glm::ivec3& value);
    void SetInt3(const std::string& name, int x, int y, int z);
    void SetInt4(const std::string& name, const glm::ivec4& value);
    void SetInt4(const std::string& name, int x, int y, int z, int w);

    void SetFloatArray(const std::string& name, const std::vector<float>& array);
    void SetFloatArray(const std::string& name, float* value, unsigned int count);
    void SetFloat(const std::string& name, float value);
    void SetFloat2(const std::string& name, const glm::vec2& value);
    void SetFloat2(const std::string& name, float x, float y);
    void SetFloat3(const std::string& name, const glm::vec3& value);
    void SetFloat3(const std::string& name, float x, float y, float z);
    void SetFloat4(const std::string& name, const glm::vec4& value);
    void SetFloat4(const std::string& name, float x, float y, float z, float w);

    void SetMat2(const std::string& name, const glm::mat2& mat);
    void SetMat3(const std::string& name, const glm::mat3& mat);
    void SetMat4(const std::string& name, const glm::mat4& mat);

    std::vector<std::string> GetActiveUniformsName();

private:
    /// \brief load all uniform locations into map
    void LoadUniformLocation();

    /// \param shaderType GL_VERTEX_SHADER, GL_FRAGMENT_SHADER or GL_GEOMETRY_SHADER
    /// \param source GLSL code
    /// \return shader Id
    static GLint CompileShader(GLenum shaderType, const std::string& source);
    static bool IsCompileError(const GLint& shaderId);
    static std::string GetCompileStatus(const GLint& shaderId);
};
