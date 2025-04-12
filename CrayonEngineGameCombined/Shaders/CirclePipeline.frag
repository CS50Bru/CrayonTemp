// STANDARD HEADER BEGINS
#version 450
#extension GL_EXT_nonuniform_qualifier : enable
// STANDARD HEADER ENDS

//DESCRIPTOR INFORMATION BEGINS
// Define our DescriptorSet inputs
layout( set = 0, binding = 0, std140 ) uniform UniformBufferObject
{
	mat4 model;
	mat4 view;
	mat4 proj;
} ubo;

layout( set = 1, binding = 0 ) uniform sampler2D texSampler[];

layout( set = 2, binding = 0, rgba8 ) readonly uniform image2D stagingImages[];


struct Sprite {
    vec2 offset;       // Position offset in model space
    vec2 origin;       // Texture coordinate origin
    vec2 extent;       // Texture coordinate extent
    vec2 scale;        // Scaling factor for the sprite
    uint textureID;    // Index into the texture sampler array
    float rotation;    // Rotation angle in radians
};

layout( set = 3, binding =0, std140) readonly buffer SpriteBuffer {Sprite sprites[];} spriteBuffer;


//DESCRIPTOR INFORMATION ENDS


// Redeclare the push constants in the fragment shader
//push constants are available to every shader stage that declares them, and they’re the same for the entire draw call.
layout(push_constant) uniform Push {
    vec2 center;
    vec2 extent;
} push;

layout( location = 0 ) out vec4 outColor;

void main()
{
	vec2 uv = gl_FragCoord.xy - push.center;
	uv= uv/push.extent*2.0;
	float distanceSq= dot(uv, uv);
	outColor= vec4(1.0, 1.0, 0.0, 1.0)*step(distanceSq, 1.0);
	//outColor= vec4(1.0,1.0,0.0,1.0);
}


