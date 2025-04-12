// STANDARD HEADER BEGINS
#version 450
#extension GL_EXT_nonuniform_qualifier : enable
// STANDARD HEADER ENDS

layout( location=0) in vec2 fragTexCoord;
layout (location =1) flat in uint textureId;


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

layout( location = 0 ) out vec4 outColor;

void main()
{
//texture is a built-in function
	outColor= texture( texSampler[textureId], fragTexCoord );
	if(outColor.w<1) {discard;}
}