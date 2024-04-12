#shader vertex

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in int aX;


out vec3 Color;

uniform vec3 hai;
uniform int zzzzzzzzzz;

void main() {
    Color = aColor * hai * aX * zzzzzzzzzz;
    gl_Position = vec4(aPosition, 1.0);
}

#shader fragment

in vec3 Color;
out vec4 FragColor;

void main() {
    FragColor = vec4(Color, 1.0);
}
