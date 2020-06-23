#pragma once

//#include "hpString.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "hpDebug.h"
#include "hpMacro.h"
#include "hpCast.h"
#include "hpString.h"

namespace hp {
namespace opengl {
struct BufferLayout final {
  GLuint index;
  GLint size;
  GLenum type;
  GLboolean normalized;
  GLsizei stride;
  const GLvoid* data;
};

struct ShaderLayout final {
  hpString identifier;
  hpString vtxPath;
  hpString frgPath;
  hpString geomPath;
};

class Shader final {
  using Shader_Path = hpString&&;
  using Uniform_Name = hpString&&;

public:
  explicit Shader() noexcept;

  void compile_shader(ShaderLayout layout);
  void dispose_buffers();
  void dispose_shader_program();
  Shader& use();

private:
  void get_compile_result(GLuint id, const char* typ);
  void create_buffer(const GLfloat* vertices, const size_t vtx_count,
                 BufferLayout*& buf_layout, const size_t buf_layout_size);

public:
  GLuint get_uniform_location(Uniform_Name uniform_name) const;
  void set_bool(Uniform_Name uniform_name, GLboolean bool_value) const;
  void set_int(Uniform_Name uniform_name, GLint int_value) const;
  void set_float(Uniform_Name uniform_name, GLfloat float_value) const;
  void set_texture(Uniform_Name uniform_name, GLint texture_value) const;

  void set_mat2(Uniform_Name uniform_name, glm::mat2 mat2_value) const;
  void set_mat3(Uniform_Name uniform_name, glm::mat3 mat3_value) const;
  void set_mat4(Uniform_Name uniform_name, glm::mat4 mat4_value) const;

  void set_vec2(Uniform_Name uniform_name, GLfloat x, GLfloat y) const;
  void set_vec2(Uniform_Name uniform_name, GLfloat float_value) const;
  void set_vec2(Uniform_Name uniform_name, glm::vec2 vec2_value) const;

  void set_vec3(Uniform_Name uniform_name, GLfloat x, GLfloat y, GLfloat z) const;
  void set_vec3(Uniform_Name uniform_name, GLfloat float_value) const;
  void set_vec3(Uniform_Name uniform_name, glm::vec3 vec3_value) const;

  void set_vec4(Uniform_Name uniform_name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
  void set_vec4(Uniform_Name uniform_name, GLfloat float_value) const;
  void set_vec4(Uniform_Name uniform_name, glm::vec4 vec4_value) const;

  void set_colour(Uniform_Name uniform_name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
  void set_colour(Uniform_Name uniform_name, GLfloat float_value) const;
  void set_colour(Uniform_Name uniform_name, glm::vec4 vec4_value) const;

public:
  GLuint get_shader_program() const noexcept;
  GLuint get_VAO() const noexcept;
  GLuint get_VBO() const noexcept;
  GLuint get_EBO() const noexcept;

protected:
  GLuint shader_program = 0u;
  GLuint VAO = 0u;
  GLuint VBO = 0u;
  GLuint EBO = 0u;
};
};  // namespace opengl
};  // namespace hp
