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

  void CompileShader(ShaderLayout layout);
  void DisposeBuf();
  void DisposeProgram();
  Shader& Use();

private:
  void CompileResult(GLuint id, const char* typ);
  void CreateBuf(const GLfloat* vertices, const size_t vtx_count,
                 BufferLayout*& buf_layout, const size_t buf_layout_size);

public:
  const GLuint GetUniLoc(Uniform_Name uniform_name) const;
  void SetBool(Uniform_Name uniform_name, GLboolean bool_value) const;
  void SetInt(Uniform_Name uniform_name, GLint int_value) const;
  void SetFloat(Uniform_Name uniform_name, GLfloat float_value) const;
  void SetTexture(Uniform_Name uniform_name, GLint texture_value) const;

  void SetMat2(Uniform_Name uniform_name, glm::mat2 mat2_value) const;
  void SetMat3(Uniform_Name uniform_name, glm::mat3 mat3_value) const;
  void SetMat4(Uniform_Name uniform_name, glm::mat4 mat4_value) const;

  void SetVec2(Uniform_Name uniform_name, GLfloat x, GLfloat y) const;
  void SetVec2(Uniform_Name uniform_name, GLfloat float_value) const;
  void SetVec2(Uniform_Name uniform_name, glm::vec2 vec2_value) const;

  void SetVec3(Uniform_Name uniform_name, GLfloat x, GLfloat y,
               GLfloat z) const;
  void SetVec3(Uniform_Name uniform_name, GLfloat float_value) const;
  void SetVec3(Uniform_Name uniform_name, glm::vec3 vec3_value) const;

  void SetVec4(Uniform_Name uniform_name, GLfloat x, GLfloat y, GLfloat z,
               GLfloat w) const;
  void SetVec4(Uniform_Name uniform_name, GLfloat float_value) const;
  void SetVec4(Uniform_Name uniform_name, glm::vec4 vec4_value) const;

  void SetCol4(Uniform_Name uniform_name, GLfloat x, GLfloat y, GLfloat z,
               GLfloat w) const;
  void SetCol4(Uniform_Name uniform_name, GLfloat float_value) const;
  void SetCol4(Uniform_Name uniform_name, glm::vec4 vec4_value) const;

public:
  GLuint getProgram() const noexcept;
  GLuint getVAO() const noexcept;
  GLuint getVBO() const noexcept;
  GLuint getEBO() const noexcept;
  GLboolean hasProgramCreated() const noexcept;

protected:
  GLuint mProgram = 0u;
  GLuint mVAO = 0u;
  GLuint mVBO = 0u;
  GLuint mEBO = 0u;
  GLboolean mHasProgramCreated = GL_FALSE;
};
};  // namespace opengl
};  // namespace hp
