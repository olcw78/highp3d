#include "../pub/hpOpenglShader.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace hp {
namespace opengl {
Shader::Shader() noexcept {
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
}

void Shader::CompileShader(ShaderLayout layout) {
  if (!mHasProgramCreated) {
    bool isGeomShaderused = !layout.geomPath.empty();
    std::string vsStr, fsStr, gsStr;
    std::ifstream vsStream, fsStream, gsStream;
    vsStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fsStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gsStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
      vsStream.open(layout.vtxPath.get_c_str());
      fsStream.open(layout.frgPath.get_c_str());
      if (isGeomShaderused) {
        gsStream.open(layout.geomPath.get_c_str());
      }

      std::stringstream vsStringStream, fsStringStream, gsStringStream;
      vsStringStream << vsStream.rdbuf();
      fsStringStream << fsStream.rdbuf();
      if (isGeomShaderused) {
        gsStringStream << gsStream.rdbuf();
      }

      vsStr = vsStringStream.str();
      fsStr = fsStringStream.str();
      if (isGeomShaderused) {
        gsStr = gsStringStream.str();
      }
    }
    catch (std::ifstream::failure& e) {
      TRACE_ASSERT_MESSAGE_ALWAYS(
        hpString::concat("Shader file reading error! : ", e.what()));
    }

    char const* vsCode = vsStr.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsCode, nullptr);
    glCompileShader(vs);
    CompileResult(vs, "VERTEX SHADER");

    char const* fsCode = fsStr.c_str();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsCode, nullptr);
    glCompileShader(fs);
    CompileResult(fs, "FRAGMENT SHADER");

    GLuint gs = 0u;
    if (isGeomShaderused) {
      char const* gsCode = gsStr.c_str();
      gs = glCreateShader(GL_GEOMETRY_SHADER);
      glShaderSource(gs, 1, &gsCode, nullptr);
      glCompileShader(gs);
      CompileResult(gs, "GEOMETRY SHADER");
    }

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vs);
    glAttachShader(mProgram, fs);
    if (isGeomShaderused) {
      glAttachShader(mProgram, gs);
    }
    glLinkProgram(mProgram);
    CompileResult(mProgram, "PROGRAM");

    glDeleteShader(vs);
    glDeleteShader(fs);
    if (isGeomShaderused) {
      glDeleteShader(gs);
    }
    mHasProgramCreated = GL_TRUE;
  }
}

void Shader::DisposeBuf() {
  glDeleteVertexArrays(1, &mVAO);
  glDeleteBuffers(1, &mVBO);
  if (mHasProgramCreated) {
    DisposeProgram();
  }
}

void Shader::DisposeProgram() {
  if (mHasProgramCreated) {
    glDeleteProgram(mProgram);
    mHasProgramCreated = false;
  }
}

void Shader::CompileResult(GLuint id, const char* type) {
  GLint success = 0;
  GLchar infoLog[1024]{};

  if (type != "PROGRAM") {
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (false == success) {
      glGetShaderInfoLog(id, sizeof(infoLog), nullptr, infoLog);
      std::cout
        << "Error::Shader_Compilation_Error of type: " << type << "\n"
        << infoLog
        << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
  }
  else {
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (false == success) {
      glGetShaderInfoLog(id, sizeof(infoLog), nullptr, infoLog);
      std::cout
        << "Error::Program_Linking_Error of type: " << type << "\n"
        << infoLog
        << "\n -- --------------------------------------------------- -- "
        << std::endl;
    }
  }
}

void Shader::CreateBuf(const GLfloat* vertices, const size_t vtx_count,
                       BufferLayout*& buf_layout,
                       const size_t buf_layout_size) {
  glBindVertexArray(mVAO);

  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * vtx_count, vertices,
               GL_STATIC_DRAW);

  for (size_t i = 0; i < buf_layout_size; ++i) {
    glEnableVertexAttribArray(buf_layout[i].index);
    glVertexAttribPointer(buf_layout[i].index, buf_layout[i].size,
                          buf_layout[i].type, buf_layout[i].normalized,
                          buf_layout[i].stride, buf_layout[i].data);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Shader& Shader::Use() {
  assert(mHasProgramCreated);
  glUseProgram(mProgram);
  return *this;
}

const GLuint Shader::GetUniLoc(Uniform_Name uniform_name) const {
  assert(mHasProgramCreated);
  return glGetUniformLocation(
    mProgram, std::forward<Uniform_Name>(uniform_name).get_c_str());
}

void Shader::SetBool(Uniform_Name uniform_name, GLboolean bool_value) const {
  glUniform1i(GetUniLoc(std::move(uniform_name)),
              Cast::ToInt(bool_value));
}

void Shader::SetInt(Uniform_Name uniform_name, GLint int_value) const {
  glUniform1i(GetUniLoc(std::move(uniform_name)), int_value);
}

void Shader::SetFloat(Uniform_Name uniform_name, GLfloat float_value) const {
  glUniform1f(GetUniLoc(std::move(uniform_name)), float_value);
}

void Shader::SetTexture(Uniform_Name uniform_name,
                        GLint texture_value) const {
  SetInt(std::move(uniform_name), texture_value);
}

void Shader::SetMat2(Uniform_Name uniform_name, glm::mat2 mat2_value) const {
  glUniformMatrix2fv(GetUniLoc(std::move(uniform_name)), 1, GL_FALSE,
                     glm::value_ptr(std::move(mat2_value)));
}

void Shader::SetMat3(Uniform_Name uniform_name, glm::mat3 mat3_value) const {
  glUniformMatrix3fv(GetUniLoc(std::move(uniform_name)), 1, GL_FALSE,
                     glm::value_ptr(std::move(mat3_value)));
}

void Shader::SetMat4(Uniform_Name uniform_name, glm::mat4 mat4_value) const {
  glUniformMatrix4fv(GetUniLoc(std::move(uniform_name)), 1, GL_FALSE,
                     glm::value_ptr(std::move(mat4_value)));
}

void Shader::SetVec2(Uniform_Name uniform_name, GLfloat x, GLfloat y) const {
  glUniform2f(GetUniLoc(std::move(uniform_name)), x, y);
}

void Shader::SetVec2(Uniform_Name uniform_name, GLfloat float_value) const {
  glUniform2f(GetUniLoc(std::move(uniform_name)), float_value, float_value);
}

void Shader::SetVec2(Uniform_Name uniform_name, glm::vec2 vec2_value) const {
  glUniform2fv(GetUniLoc(std::move(uniform_name)), 1,
               glm::value_ptr(std::move(vec2_value)));
}

void Shader::SetVec3(Uniform_Name uniform_name, GLfloat x, GLfloat y,
                     GLfloat z) const {
  glUniform3f(GetUniLoc(std::move(uniform_name)), x, y, z);
}

void Shader::SetVec3(Uniform_Name uniform_name, GLfloat float_value) const {
  glUniform3f(GetUniLoc(std::move(uniform_name)), float_value, float_value,
              float_value);
}

void Shader::SetVec3(Uniform_Name uniform_name, glm::vec3 vec3_value) const {
  glUniform3fv(GetUniLoc(std::move(uniform_name)), 1,
               glm::value_ptr(std::move(vec3_value)));
}

void Shader::SetVec4(Uniform_Name uniform_name, GLfloat x, GLfloat y,
                     GLfloat z, GLfloat w) const {
  glUniform4f(GetUniLoc(std::move(uniform_name)), x, y, z, w);
}

void Shader::SetVec4(Uniform_Name uniform_name, GLfloat float_value) const {
  glUniform4f(GetUniLoc(std::move(uniform_name)), float_value, float_value,
              float_value, float_value);
}

void Shader::SetVec4(Uniform_Name uniform_name, glm::vec4 vec4_value) const {
  glUniform4fv(GetUniLoc(std::move(uniform_name)), 1,
               glm::value_ptr(std::move(vec4_value)));
}

void Shader::SetCol4(Uniform_Name uniform_name, GLfloat x, GLfloat y,
                     GLfloat z, GLfloat w) const {
  SetVec4(std::move(uniform_name), x, y, z, w);
}

void Shader::SetCol4(Uniform_Name uniform_name, GLfloat float_value) const {
  SetVec4(std::move(uniform_name), float_value);
}

void Shader::SetCol4(Uniform_Name uniform_name, glm::vec4 vec4_value) const {
  SetVec4(std::move(uniform_name), std::move(vec4_value));
}

GLuint Shader::getProgram() const noexcept { return mProgram; }

GLuint Shader::getVAO() const noexcept { return mVAO; }

GLuint Shader::getVBO() const noexcept { return mVBO; }

GLuint Shader::getEBO() const noexcept { return mEBO; }

GLboolean Shader::hasProgramCreated() const noexcept {
  return mHasProgramCreated;
}
};  // namespace opengl
};  // namespace hp
