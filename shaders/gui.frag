#version 460

out vec4 FragColor;

precision highp float;

uniform vec2 resolution;
uniform sampler2D tex;

uniform float scrollSize;

uniform vec2 mousePos;

void main() {
    FragColor = texelFetch(tex, ivec2(gl_FragCoord.xy), 0);
    if (distance(gl_FragCoord.xy+vec2(0, 50), mousePos.xy+vec2(0, 50)) >= scrollSize && distance(gl_FragCoord.xy+vec2(0, 50), mousePos.xy+vec2(0, 50)) <= scrollSize+1) {
        FragColor = vec4(vec3(1, 0, 0), 1.0);
    }
}
