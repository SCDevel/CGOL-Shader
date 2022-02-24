#version 460

out vec4 FragColor;

precision highp float;

uniform vec2 resolution;
uniform sampler2D tex;

uniform float scrollSize;

uniform vec2 mousePos;
uniform bool mouseLeftDown;
uniform bool mouseRightDown;

bool getRelativePixelState(vec2 p) {
    p = gl_FragCoord.xy + p.xy;
    p = vec2(mod(p.x, resolution.x), mod(p.y, resolution.y));
    /*
    if (p.x > resolution.x || p.y > resolution.y || p.x < 0 || p.y < 0) {
        return false;
    }
    */
    return texelFetch(tex, ivec2(p), 0) == vec4(1);
}

void main( void ) {
    bool current = getRelativePixelState(vec2(0, 0));
    int living = 0;
    living += getRelativePixelState(vec2(0, 1)) ? 1 : 0;
    living += getRelativePixelState(vec2(1, 1)) ? 1 : 0;
    living += getRelativePixelState(vec2(-1, 1)) ? 1 : 0;
    living += getRelativePixelState(vec2(1, 0)) ? 1 : 0;
    living += getRelativePixelState(vec2(-1, 0)) ? 1 : 0;
    living += getRelativePixelState(vec2(0, -1)) ? 1 : 0;
    living += getRelativePixelState(vec2(1, -1)) ? 1 : 0;
    living += getRelativePixelState(vec2(-1, -1)) ? 1 : 0;

    if (current) {
        current = (living == 2 || living == 3);
    } else {
        current = (living == 3);
    }

    FragColor = (current) ? vec4(1, 1, 1, 1) : vec4(0, 0, 0, 1);

    if (distance(gl_FragCoord.xy, mousePos.xy) < scrollSize) {
        if (mouseLeftDown) {
            FragColor = vec4(vec3(1), 1.0);
        } else if (mouseRightDown) {
            FragColor = vec4(vec3(0), 1.0);
        }
    }
}