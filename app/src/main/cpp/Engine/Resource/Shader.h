#ifndef VTMAPS_SHADER_H
#define VTMAPS_SHADER_H

#include <GLES2/gl2.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <exception>

#include <glm/glm.hpp>
#include <magic_enum/magic_enum.hpp>


#include "../Utility/Logger.h"
#include "../Utility/JNIHelper.h"


namespace Engine::Resource {
    class Shader {
    public:
        class Parameter;
    private:
        static const int MAX_LENGTH_PARAM_NAME = 128;
        std::unordered_map<std::string, GLint> _uniformLocation;
        GLint _id;

    public:
        Shader(const std::string& path);
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

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

        /// \return All uniform's names which contribute in calculate in shader program, not only declare but no use
        std::vector<std::string> GetActiveUniformName() const;

        std::vector<Parameter> GetActiveUniform() const;
        std::vector<Parameter> GetActiveAttribute() const;
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

    class Shader::Parameter {
    public:
        typedef enum {
            Bool,
            Float, Float2, Float3, Float4,
            Int, Int2, Int3, Int4,
            Mat2, Mat3, Mat4
        } Type;

        static const unsigned MAX_LENGTH_PARAM_NAME = 128;
        static unsigned int GetTypeSize(const Type& type);
        static std::string TypeToString(const Type& type);
        static Type GLTypeToParameterType(const GLenum& type);

    private:
        std::string _name;
        int _size;
        Type _type;

    public:
        Parameter(const std::string& name, const int& size, const Type& type);
        Parameter(const std::string& name, const int& size, const GLenum& type);
        std::string GetName() const;
        int GetSize() const;
        Type GetType() const;
    };
}

#endif //VTMAPS_SHADER_H
