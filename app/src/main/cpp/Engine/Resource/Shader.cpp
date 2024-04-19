#include "Shader.h"

namespace Engine::Resource {
    void Shader::Bind() {
        glUseProgram(_id);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    void Shader::SetIntArray(const std::string &name, const std::vector<int> &array) {
        glUniform1iv(_uniformLocation[name], array.size(), &array[0]);
    }

    void Shader::SetIntArray(const std::string &name, int *value, unsigned int count) {
        glUniform1iv(_uniformLocation[name], count, value);
    }

    void Shader::SetInt(const std::string &name, int value) {
        glUniform1i(_uniformLocation[name], value);
    }

    void Shader::SetInt2(const std::string &name, const glm::ivec2 &value) {
        glUniform2iv(_uniformLocation[name], 1, &value[0]);
    }

    void Shader::SetInt2(const std::string &name, int x, int y) {
        glUniform2i(_uniformLocation[name], x, y);
    }

    void Shader::SetInt3(const std::string &name, const glm::ivec3 &value) {
        glUniform3iv(_uniformLocation[name], 1, &value[0]);
    }

    void Shader::SetInt3(const std::string &name, int x, int y, int z) {
        glUniform3i(_uniformLocation[name], x, y, z);
    }

    void Shader::SetInt4(const std::string &name, const glm::ivec4 &value) {
        glUniform3iv(_uniformLocation[name], 1, &value[0]);
    }

    void Shader::SetInt4(const std::string &name, int x, int y, int z, int w) {
        glUniform4i(_uniformLocation[name], x, y, z, w);
    }

    void Shader::SetFloatArray(const std::string &name, const std::vector<float> &array) {
        glUniform1fv(_uniformLocation[name], array.size(), &array[0]);
    }

    void Shader::SetFloatArray(const std::string &name, float *value, unsigned int count) {
        glUniform1fv(_uniformLocation[name], count, value);
    }

    void Shader::SetFloat(const std::string &name, float value) {
        glUniform1f(_uniformLocation[name], value);
    }

    void Shader::SetFloat2(const std::string &name, const glm::vec2 &value) {
        glUniform2fv(_uniformLocation[name], 1, &value[0]);
    }

    void Shader::SetFloat2(const std::string &name, float x, float y) {
        glUniform2f(_uniformLocation[name], x, y);
    }

    void Shader::SetFloat3(const std::string &name, const glm::vec3 &value) {
        glUniform3fv(_uniformLocation[name], 1, &value[0]);
    }

    void Shader::SetFloat3(const std::string &name,
                           float x, float y, float z) {
        glUniform3f(_uniformLocation[name], x, y, z);
    }

    void Shader::SetFloat4(const std::string &name, const glm::vec4 &value) {
        glUniform4fv(_uniformLocation[name], 1, &value[0]);
    }

    void Shader::SetFloat4(const std::string &name, float x, float y, float z, float w) {
        glUniform4f(_uniformLocation[name], x, y, z, w);
    }

    void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) {
        glUniformMatrix2fv(_uniformLocation[name], 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) {
        glUniformMatrix3fv(_uniformLocation[name], 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) {
        glUniformMatrix4fv(_uniformLocation[name], 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::LoadUniformLocation() {
        for (auto &uniformName: GetActiveUniformName()) {
            _uniformLocation.insert({uniformName,
                                    glGetUniformLocation(_id, uniformName.c_str())});
        }
    }

    GLint Shader::CompileShader(GLenum shaderType, const std::string &source) {
        GLint id = glCreateShader(shaderType);
        const char *src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        if (IsCompileError(id)) {
            std::string status = GetCompileStatus(id);
            LOG_ERROR("SHADER", "Compile error %s", status.c_str());
        }
        return id;
    }

    bool Shader::IsCompileError(const GLint &shaderId) {
        int result;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        return result == GL_FALSE;
    }

    std::string Shader::GetCompileStatus(const GLint &shaderId) {
        int messageLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &messageLength);
        char *message = (char *) malloc(messageLength * sizeof(char));
        glGetShaderInfoLog(shaderId, messageLength, &messageLength, message);
        std::string str_message;
        str_message.assign(message, messageLength);
        free(message);
        return str_message;
    }

    std::vector<std::string> Shader::GetActiveUniformName() const {
        std::vector<std::string> res;
        GLint count, uniformIndex, uniformSize /*size of variable*/;
        GLenum uniformType; // type of the variable (float, vec3 or mat4, etc)
        GLchar uniformName[MAX_LENGTH_PARAM_NAME]; // name in GLSL
        GLsizei nameLength;
        glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &count);
        for (uniformIndex = 0; uniformIndex < count; ++uniformIndex) {
            glGetActiveUniform(_id,
                               (GLuint) uniformIndex,
                               MAX_LENGTH_PARAM_NAME,
                               &nameLength,
                               &uniformSize, &uniformType, uniformName);
            res.emplace_back(uniformName);
        }
        return res;
    }

    std::vector<Shader::Parameter> Shader::GetActiveUniform() const {
        std::vector<Parameter> res;
        GLint count, uniformIndex, uniformSize /*size of variable*/;
        GLenum uniformType; // type of the variable (float, vec3 or mat4, etc)
        GLchar uniformName[MAX_LENGTH_PARAM_NAME]; // name in GLSL
        GLsizei nameLength;
        glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &count);
        for (uniformIndex = 0; uniformIndex < count; ++uniformIndex) {
            glGetActiveUniform(_id,
                               (GLuint) uniformIndex,
                               MAX_LENGTH_PARAM_NAME,
                               &nameLength,
                               &uniformSize, &uniformType, uniformName);
            res.emplace_back(Parameter{uniformName, uniformSize, uniformType});
        }
        return res;
    }

    std::vector<Shader::Parameter> Shader::GetActiveAttribute() const {
        std::vector<Parameter> res;
        GLint count, index, size /*size of variable*/;
        GLenum type; // type of the variable (float, vec3 or mat4, etc)
        GLchar name[MAX_LENGTH_PARAM_NAME]; // name in GLSL
        GLsizei nameLength;
        glGetProgramiv(_id, GL_ACTIVE_ATTRIBUTES, &count);
        for (index = 0; index < count; ++index) {
            glGetActiveUniform(_id,
                               (GLuint) index,
                               MAX_LENGTH_PARAM_NAME,
                               &nameLength,
                               &size, &type, name);
            res.emplace_back(Parameter{name, size, type});
        }
        return res;
    }

    Shader::Shader(const std::string &path) {
#ifndef NDEBUG
        if (exists(std::filesystem::path(path))) {
            LOG_ERROR("SHADER", "File not found");
        }
#endif
    }

    Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc) {
        _id = glCreateProgram();
        unsigned int vertexShader, fragmentShader;
        vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
        fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

        glAttachShader(_id, vertexShader);
        glAttachShader(_id, fragmentShader);

        glLinkProgram(_id);
        glValidateProgram(_id);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        LoadUniformLocation();

#ifndef NDEBUG
        for (auto& u : _uniformLocation) {
            LOG_INFO("SHADER", "Constructor: %s", u.first.c_str());
        }
#endif
    }

    unsigned int Shader::Parameter::GetTypeSize(const Shader::Parameter::Type &type) {
        switch (type) {
            case Bool:      return 4;
            case Float:     return 4;
            case Float2:    return 8;
            case Float3:    return 12;
            case Float4:    return 16;
            case Int:       return 4;
            case Int2:      return 8;
            case Int3:      return 12;
            case Int4:      return 16;
            case Mat2:      return 16;
            case Mat3:      return 36;
            case Mat4:      return 64;
        }
        LOG_ERROR("SHADER", "GetTypeSize: Invalid type");
        assert(false && "GetTypeSize: Invalid type");
    }

    Shader::Parameter::Parameter(const std::string &name, const int &size,
                                 const Shader::Parameter::Type &type)
                                 : _name(name), _size(size), _type(type) {}

    Shader::Parameter::Parameter(const std::string &name, const int &size, const GLenum &type)
        : _name(name), _size(size), _type(GLTypeToParameterType(type)) {}

    std::string Shader::Parameter::GetName() const {
        return _name;
    }

    int Shader::Parameter::GetSize() const {
        return _size;
    }

    Shader::Parameter::Type Shader::Parameter::GetType() const {
        return _type;
    }

    std::string Shader::Parameter::TypeToString(const Shader::Parameter::Type &type) {
        return std::string(magic_enum::enum_name(type));
    }

    Shader::Parameter::Type Shader::Parameter::GLTypeToParameterType(const GLenum &type) {
        switch (type) {
            case GL_BOOL:       return Bool;
            case GL_FLOAT:      return Float;
            case GL_FLOAT_VEC2: return Float2;
            case GL_FLOAT_VEC3: return Float3;
            case GL_FLOAT_VEC4: return Float4;
            case GL_INT:        return Int;
            case GL_INT_VEC2:   return Int2;
            case GL_INT_VEC3:   return Int3;
            case GL_INT_VEC4:   return Int4;
            case GL_FLOAT_MAT2: return Mat2;
            case GL_FLOAT_MAT3: return Mat3;
            case GL_FLOAT_MAT4: return Mat4;
        }
        LOG_ERROR("SHADER", "GLTypeToParameterType: Invalid type");
        assert(false && "GLTypeToParameterType: Invalid type");
    }
}