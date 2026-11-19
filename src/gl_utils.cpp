#include <gl_utils/gl_utils.hpp>
#include <cmath>
#include <cstddef>

namespace gl_utils {

Mat4 makeOrthoAspect(float aspect) {
  if (aspect == 0.0f) {
    aspect = 1.0f;
  }
  Mat4 proj;
  proj.m[0] = 1.0f / aspect;
  proj.m[5] = 1.0f;
  proj.m[10] = -1.0f;
  proj.m[15] = 1.0f;
  return proj;
}

MeshData Circle::buildMesh() const {
  MeshData mesh;
  if (segments < 3) {
    return mesh;
  }

  constexpr float PI = 3.14159265358979323846f;
  const float TAU = 2.0f * PI;

  for (int i = 0; i < segments; ++i) {
    float angle0 = (TAU * static_cast<float>(i)) / static_cast<float>(segments);
    float angle1 = (TAU * static_cast<float>(i + 1)) / static_cast<float>(segments);

    float x0 = cx + radius * std::cos(angle0);
    float y0 = cy + radius * std::sin(angle0);

    float x1 = cx + radius * std::cos(angle1);
    float y1 = cy + radius * std::sin(angle1);

    mesh.vertices.push_back({cx, cy, cz, r, g, b});
    mesh.vertices.push_back({x0, y0, cz, r, g, b});
    mesh.vertices.push_back({x1, y1, cz, r, g, b});
  }

  return mesh;
}

void GPUMesh::upload(const MeshData& data) {
  vertexCount = static_cast<GLsizei>(data.vertices.size());

  if (VAO == 0) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
  }

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(
      GL_ARRAY_BUFFER,
      static_cast<GLsizeiptr>(data.vertices.size() * sizeof(Vertex)),
      data.vertices.data(),
      GL_STATIC_DRAW);

  glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
      reinterpret_cast<const void*>(offsetof(Vertex, x)));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
      1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
      reinterpret_cast<const void*>(offsetof(Vertex, r)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void GPUMesh::draw() const {
  if (vertexCount == 0 || VAO == 0) {
    return;
  }
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  glBindVertexArray(0);
}

void GPUMesh::destroy() {
  if (VBO != 0) {
    glDeleteBuffers(1, &VBO);
    VBO = 0;
  }
  if (VAO != 0) {
    glDeleteVertexArrays(1, &VAO);
    VAO = 0;
  }
  vertexCount = 0;
}

} // namespace gl_utils
