#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texture_coord;

out vec2 v_texture_coord;

void main(){
   gl_Position = position;
   v_texture_coord = texture_coord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

// input data
in vec2 v_texture_coord;
uniform sampler2D u_texture;
uniform float time;
uniform vec2 resolution;
uniform vec3 circles[100];

// shader
vec3 palette(float t){

    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);

    return a + b*cos(6.28318*(c*t+d));
}

void main(){
   
   //vec2 uv = gl_FragCoord.xy / resolution;
   //vec2 uv_animation = uv *2.0 -1.0;
   //uv.x *= resolution.x/resolution.y;
   //uv_animation.x *= resolution.x/resolution.y;
   //vec2 uv0 = uv_animation;
//
   //for(int i = 0; i < 100; i ++){
   //   if(sqrt(pow(uv.x - circles[i].x, 2.0) + pow(uv.y - circles[i].y, 2.0)) <= circles[i].z){ // if the pixel is in one of the circles
   //      vec3 finalColor = vec3(0.0);
//
   //    for(float i = 0.0; i < 4.0; i++){
   //       uv_animation = fract(uv_animation*1.5) -0.5;
//
   //       float d = length(uv_animation) * exp(-length(uv0));
   //       vec3 col = palette(length(uv0) + i*0.4 + time*0.4);
//
   //       d = sin(d * 8.0 + time)/8.0;
   //       d = abs(d);
   //       d = pow(0.01/d, 1.2);
//
   //         finalColor += col * d;
   //      }
   //      float d = length(uv - circles[i].xy);
   //      d = sin(d*75+ time*5);
   //      color = vec4(finalColor*d, 1.0);
   //      break;
   //   }
   //   else color = vec4(0);
   //}
   //vec2 flippedTexCoord = vec2(v_texture_coord.x, 1.0 - v_texture_coord.y);
   vec4 texture_color = texture(u_texture,v_texture_coord);
   color = texture_color;
};
