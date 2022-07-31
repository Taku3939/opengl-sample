#version 460
in vec3 outColor;
out vec4 outFragmentColor;
void main(void) {
    //outFragmentColor = vec4(1.0, 1.0, 0.0, 1.0);
    outFragmentColor = vec4(outColor, 1.0f);
}