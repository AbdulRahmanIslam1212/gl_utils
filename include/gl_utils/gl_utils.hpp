#pragma once

#include <glad/gl.h>
#include <vector>

namespace gl_utils {

struct Vertex {
  float x, y, z;
  float r, g, b;
};

struct MeshData {
  std::vector<Vertex> vertices;
};

struct Mat4 {
  float m[16] = {0.0f}; // Column-major for OpenGL
};

Mat4 makeOrthoAspect(float aspect);

struct Circle {
  float cx = 0.0f;
  float cy = 0.0f;
  float cz = 0.0f;
  float radius = 0.5f;
  int segments = 36;
  float r = 1.0f;
  float g = 1.0f;
  float b = 1.0f;

  MeshData buildMesh() const;
};

struct GPUMesh {
  unsigned int VAO = 0;
  unsigned int VBO = 0;
  GLsizei vertexCount = 0;

  GPUMesh() = default;
  GPUMesh(const GPUMesh&) = delete;
  GPUMesh& operator=(const GPUMesh&) = delete;

  void upload(const MeshData& data);
  void draw() const;
  void destroy();
};

} // namespace gl_utils
