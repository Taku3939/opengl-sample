#version 460
//layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 color;
attribute vec3 VertexPosition;
attribute vec3 VertexColor;
uniform mat4 MVP;
varying vec3 Color;
void main() {
    Color = VertexColor;
    gl_Position = MVP * vec4(VertexPosition, 1.0);
}