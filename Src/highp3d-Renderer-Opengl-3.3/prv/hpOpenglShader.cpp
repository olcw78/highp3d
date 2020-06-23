#include "../pub/hpOpenglShader.h"
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace hp {
namespace opengl {
Shader::Shader() noexcept {
  shader_program = VAO = VBO = EBO = 0u;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
}

void Shader::compile_shader(ShaderLayout layout) {
  const bool isGeomShaderused = !layout.geomPath.empty();
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
    hpDebug::check_always(hpString::concat("Shader file reading error! : ", e.what()));
  }

  char const* vsCode = vsStr.c_str();
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vsCode, nullptr);
  glCompileShader(vs);
  get_compile_result(vs, "VERTEX SHADER");

  char const* fsCode = fsStr.c_str();
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fsCode, nullptr);
  glCompileShader(fs);
  get_compile_result(fs, "FRAGMENT SHADER");

  GLuint gs = 0u;
  if (isGeomShaderused) {
    char const* gsCode = gsStr.c_str();
    gs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gs, 1, &gsCode, nullptr);
    glCompileShader(gs);
    get_compile_result(gs, "GEOMETRY SHADER");
  }

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vs);
  glAttachShader(shader_program, fs);
  if (isGeomShaderused) {
    glAttachShader(shader_program, gs);
  }
  glLinkProgram(shader_program);
  get_compile_result(shader_program, "PROGRAM");

  glDeleteShader(vs);
  glDeleteShader(fs);
  if (isGeomShaderused) {
    glDeleteShader(gs);
  }
}

void Shader::dispose_buffers() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  dispose_shader_program();
}

void Shader::dispose_shader_program() {
  glDeleteProgram(shader_program);
}

void Shader::get_compile_result(GLuint id, const char* type) {
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

void Shader::create_buffer(const GLfloat* vertices, const size_t vtx_count,
                           BufferLayout*& buf_layout,
                           const size_t buf_layout_size) {
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
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

Shader&
Shader::use() {  
  glUseProgram(shader_program);
  return *this;
}

GLuint
Shader::get_uniform_location(Uniform_Name uniform_name) const {  
  return glGetUniformLocation(
    shader_program, std::forward<Uniform_Name>(uniform_name).get_c_str());
}

void Shader::set_bool(Uniform_Name uniform_name, GLboolean bool_value) const {
  glUniform1i(get_uniform_location(std::move(uniform_name)),
              Cast::ToInt(bool_value));
}

void Shader::set_int(Uniform_Name uniform_name, GLint int_value) const {
  glUniform1i(get_uniform_location(std::move(uniform_name)), int_value);
}

void Shader::set_float(Uniform_Name uniform_name, GLfloat float_value) const {
  glUniform1f(get_uniform_location(std::move(uniform_name)), float_value);
}

void Shader::set_texture(Uniform_Name uniform_name,
                         GLint texture_value) const {
  set_int(std::move(uniform_name), texture_value);
}

void Shader::set_mat2(Uniform_Name uniform_name, glm::mat2 mat2_value) const {
  glUniformMatrix2fv(get_uniform_location(std::move(uniform_name)), 1, GL_FALSE,
                     glm::value_ptr(std::move(mat2_value)));
}

void Shader::set_mat3(Uniform_Name uniform_name, glm::mat3 mat3_value) const {
  glUniformMatrix3fv(get_uniform_location(std::move(uniform_name)), 1, GL_FALSE,
                     glm::value_ptr(std::move(mat3_value)));
}

void Shader::set_mat4(Uniform_Name uniform_name, glm::mat4 mat4_value) const {
  glUniformMatrix4fv(get_uniform_location(std::move(uniform_name)), 1, GL_FALSE,
                     glm::value_ptr(std::move(mat4_value)));
}

void Shader::set_vec2(Uniform_Name uniform_name, GLfloat x, GLfloat y) const {
  glUniform2f(get_uniform_location(std::move(uniform_name)), x, y);
}

void Shader::set_vec2(Uniform_Name uniform_name, GLfloat float_value) const {
  glUniform2f(get_uniform_location(std::move(uniform_name)), float_value, float_value);
}

void Shader::set_vec2(Uniform_Name uniform_name, glm::vec2 vec2_value) const {
  glUniform2fv(get_uniform_location(std::move(uniform_name)), 1,
               glm::value_ptr(std::move(vec2_value)));
}

void Shader::set_vec3(Uniform_Name uniform_name, GLfloat x, GLfloat y,
                      GLfloat z) const {
  glUniform3f(get_uniform_location(std::move(uniform_name)), x, y, z);
}

void Shader::set_vec3(Uniform_Name uniform_name, GLfloat float_value) const {
  glUniform3f(get_uniform_location(std::move(uniform_name)), float_value, float_value,
              float_value);
}

void Shader::set_vec3(Uniform_Name uniform_name, glm::vec3 vec3_value) const {
  glUniform3fv(get_uniform_location(std::move(uniform_name)), 1,
               glm::value_ptr(std::move(vec3_value)));
}

void Shader::set_vec4(Uniform_Name uniform_name, GLfloat x, GLfloat y,
                      GLfloat z, GLfloat w) const {
  glUniform4f(get_uniform_location(std::move(uniform_name)), x, y, z, w);
}

void Shader::set_vec4(Uniform_Name uniform_name, GLfloat float_value) const {
  glUniform4f(get_uniform_location(std::move(uniform_name)), float_value, float_value,
              float_value, float_value);
}

void Shader::set_vec4(Uniform_Name uniform_name, glm::vec4 vec4_value) const {
  glUniform4fv(get_uniform_location(std::move(uniform_name)), 1,
               glm::value_ptr(std::move(vec4_value)));
}

void Shader::set_colour(Uniform_Name uniform_name, GLfloat x, GLfloat y,
                        GLfloat z, GLfloat w) const {
  set_vec4(std::move(uniform_name), x, y, z, w);
}

void Shader::set_colour(Uniform_Name uniform_name, GLfloat float_value) const {
  set_vec4(std::move(uniform_name), float_value);
}

void Shader::set_colour(Uniform_Name uniform_name, glm::vec4 vec4_value) const {
  set_vec4(std::move(uniform_name), std::move(vec4_value));
}

GLuint
Shader::get_shader_program() const noexcept { return shader_program; }

GLuint
Shader::get_VAO() const noexcept { return VAO; }

GLuint
Shader::get_VBO() const noexcept { return VBO; }

GLuint
Shader::get_EBO() const noexcept { return EBO; }

};  // namespace opengl
};  // namespace hp
