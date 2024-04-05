#include <android/log.h>
#include "Shader.h"

Shader::Shader(const std::string &vertexSrc,
               const std::string &fragmentSrc) {
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

    for (auto& u : _uniformLocation) {
        __android_log_print(ANDROID_LOG_INFO, "Shader", "%s", u.first.c_str());
    }
}

void Shader::Bind() {
    glUseProgram(_id);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetIntArray(const std::string &name,
                         const std::vector<int> &array) {
    glUniform1iv(_uniformLocation[name], array.size(), &array[0]);
}

void Shader::SetIntArray(const std::string &name,
                         int *value, unsigned int count) {
    glUniform1iv(_uniformLocation[name], count, value);
}

void Shader::SetInt(const std::string &name, int value) {
    glUniform1i(_uniformLocation[name], value);
}

void Shader::SetInt2(const std::string &name, const glm::ivec2 &value) {
    glUniform2iv(_uniformLocation[name], 1, &value[0]);
}

void Shader::SetInt2(const std::string &name,
                     int x, int y) {
    glUniform2i(_uniformLocation[name], x, y);
}

void Shader::SetInt3(const std::string &name, const glm::ivec3 &value) {
    glUniform3iv(_uniformLocation[name], 1, &value[0]);
}

void Shader::SetInt3(const std::string &name,
                     int x, int y, int z) {
    glUniform3i(_uniformLocation[name], x, y, z);
}

void Shader::SetInt4(const std::string &name, const glm::ivec4 &value) {
    glUniform3iv(_uniformLocation[name], 1, &value[0]);
}

void Shader::SetInt4(const std::string &name,
                     int x, int y, int z, int w) {
    glUniform4i(_uniformLocation[name], x, y, z, w);
}

void Shader::SetFloatArray(const std::string &name,
                           const std::vector<float> &array) {
    glUniform1fv(_uniformLocation[name], array.size(), &array[0]);
}

void Shader::SetFloatArray(const std::string &name,
                           float *value,
                           unsigned int count) {
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

void Shader::SetFloat4(const std::string &name,
                       float x, float y, float z, float w) {
    glUniform4f(_uniformLocation[name], x, y, z, w);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) {
    glUniformMatrix2fv(_uniformLocation[name],
                       1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) {
    glUniformMatrix3fv(_uniformLocation[name],
                       1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(_uniformLocation[name],
                       1, GL_FALSE, &mat[0][0]);
}

void Shader::LoadUniformLocation() {
    std::vector<std::string> uniformNames = GetActiveUniformsName();
    for (auto &uniformName: uniformNames) {
        _uniformLocation[uniformName] = glGetUniformLocation(_id, uniformName.c_str());
    }
}

GLint Shader::CompileShader(GLenum shaderType, const std::string &source) {
    GLint id = glCreateShader(shaderType);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    if (IsCompileError(id)) {
        std::string status = GetCompileStatus(id);
//        std::string type = shaderType;
//        __android_log_print(ANDROID_LOG_ERROR, "SHADER", "Shader compile error", );

        __android_log_print(ANDROID_LOG_ERROR, "SHADER", "Error %s", status.c_str());
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

std::vector<std::string> Shader::GetActiveUniformsName() {
    std::vector<std::string> res;
    GLint count, uniformIndex, uniformSize /*size of variable*/;
    GLenum uniformType; // type of the variable (float, vec3 or mat4, etc)
    GLchar uniformName[MAX_SIZE_PARAM_NAME]; // name in GLSL
    GLsizei nameLength;
    glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &count);
    for (uniformIndex = 0; uniformIndex < count; ++uniformIndex) {
        glGetActiveUniform(_id,
                           (GLuint) uniformIndex,
                           MAX_SIZE_PARAM_NAME,
                           &nameLength,
                           &uniformSize, &uniformType, uniformName);
        res.emplace_back(uniformName);
    }
    return res;
}

Shader::~Shader() {
    glDeleteProgram(_id);
}

std::shared_ptr<Shader> Shader::CreateDefaultShader() {
    const std::string vertSrc =
            "uniform mat4 uMVP;             \n"     // A constant representing the combined model/view/projection matrix.
            "attribute vec3 aPosition;      \n"     // Per-vertex position information we will pass in.
//            "attribute vec3 aNormal;        \n"     // Per-vertex color information we will pass in.
//            "attribute vec4 aColor;         \n"     // Per-vertex color information we will pass in.
            "attribute vec2 aTexCoord;      \n"
//            "attribute vec2 aTangent;       \n"
            "varying vec4 vColor;           \n"     // This will be passed into the fragment shader.
            "varying vec2 vTexCoord;"
            "void main()                    \n"     // The entry point for our vertex shader.
            "{                              \n"
            "   vColor = aColor;            \n"     // Pass the color through to the fragment shader.
            "   vTexCoord = aTexCoord;      \n"
            "   gl_Position = uMVP * vec4(aPosition, 1.0); \n"     // gl_Position is a special variable used to store the final position.
            "}                              \n";    // normalized screen coordinates.;

    const std::string fragSrc =
            "precision mediump float;       \n"     // Set the default precision to medium. We don't need as high of a
            "varying vec4 vColor;           \n"     // This is the color from the vertex shader interpolated across the
            "varying vec2 vTexCoord;        \n"
            "uniform sampler2D uTexture;     \n"
            "void main()                    \n"     // The entry point for our fragment shader.
            "{                              \n"
            "   gl_FragColor = texture2D(uTexture, vTexCoord);      \n"     // Pass the color directly through the pipeline.
//            "   gl_FragColor = vec4(1.0, 0.0, 0.0, 0.0); \n"
            "}                              \n";
    return std::make_shared<Shader>(vertSrc, fragSrc);
}

std::shared_ptr<Shader> Shader::CreatePhongShader() {
    std::string vertSrc = "attribute vec3 aPosition;    \n"
                          "attribute vec3 aNormal;      \n"
                          "attribute vec4 aColor;       \n"
                          "attribute vec2 aTexCoord;    \n"
                          "attribute vec2 aTangent;     \n"
                          "\n"
                          "varying vec3 vNormal;        \n"
                          "varying vec4 vColor;         \n"
                          "varying vec2 vTexCoord;      \n"
                          "varying vec2 vTangent;       \n"
                          "\n"
                          "uniform mat4 uMVP;           \n"
                          "\n"
                          "void main() {                \n"
                          "     vNormal = aNormal;      \n"
                          "     vColor = aColor;        \n"
                          "     vTexCoord = aTexCoord;  \n"
                          "     vTangent = aTangent;    \n"
                          "     gl_Position = uMVP * aPosition; \n"
                          "}\n";
    std::string fragSrc = "precision mediump float;       \n"     // Set the default precision to medium. We don't need as high of a
                          "varying vec3 vNormal;        \n"
                          "varying vec4 vColor;         \n"
                          "varying vec2 vTexCoord;      \n"
                          "varying vec2 vTangent;       \n"
                          "\n"
                          "uniform sampler2D uAmbient;      \n"
                          "uniform sampler2D uSpecular;     \n"
                          "uniform sampler2D uDiffuse;      \n"
                          "\n"
                          "void main() {                    \n"
                          "     float ambient = texture2D(uAmbient, vTexCoord);     \n"
                          "     float diffuse = texture2D(uDiffuse, vTexCoord);     \n"
                          "     float specular = texture2D(uSpecular, vTexCoord);   \n"
                          "     gl_FragColor = v_Color;                             \n"
                          "}\n";
    return std::make_shared<Shader>(vertSrc, fragSrc);
}
