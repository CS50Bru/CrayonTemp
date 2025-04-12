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
//DESCRIPTOR INFORMATION ENDS


//Unlike gl_Position in the vertex shader, there is no built-in variable to output a color for the current fragment. 
//You have to specify your own output variable for each framebuffer where the layout(location = 0) modifier specifies 
//the index of the framebuffer

layout( location = 0 ) out vec4 outColor;

void main()
{
	outColor= vec4(1.0, 0.0, 0.0, 1.0);
}

